/*
 *        lld_clock.c
 *
 *    Created on: Apr 20, 2019
 *    Author: Stéphane Amans
 */

/* Include files.        */
#include "lld_clock.h"
#ifdef CLOCK_RESET


/* Static driver structure. */
static t_clock_cfg clock_drv;


/** Initialize and activate the PLL.
 *
 * \param sys_clk: System clock frequency.
 * \param source: Clock source to drive oscillator.
 *
 * \return: Error code or OK.
 *
 */
static uint8_t init_activate_PLL(uint32_t sys_clk, int source);


/** Initialize AHB clock.
 *
 * \param sys_clk: System clock frequency.
 * \param AHB_clk: AHB clock frequency.
 *
 * \return: Error code or OK.
 *
 */
static uint8_t init_AHB(uint32_t sys_clk, uint32_t AHB_clk);


/** Initialize APB1 clock.
 *
 * \param AHB_clk: AHB clock frequency.
 * \param APB1_clk: APB1 clock frequency.
 *
 * \return: Error code or OK.
 *
 */
static uint8_t init_APB1(uint32_t AHB_clk, uint32_t APB1_clk);


/** Initialize APB2 clock.
 *
 * \param AHB_clk: AHB clock frequency.
 * \param APB2_clk: APB2 clock frequency.
 *
 * \return: Error code or OK.
 *
 */
static uint8_t init_APB2(uint32_t AHB_clk, uint32_t APB2_clk);


/** Set flash latency.
 *
 * \param sysClk: System clock frequency.
 *
 * \return: Error code or OK.
 *
 */
static uint8_t set_flash_latency(uint32_t sys_clk);


/** Start oscillator.
 *
 * \param source: Clock source to drive oscillator.
 *
 * \return: Error code or OK.
 *
 */
static uint8_t start_oscillator(int source);


/** Stop oscillator.
 *
 * \param source: Clock source to drive oscillator.
 *
 * \return: Error code or OK.
 *
 */
static uint8_t stop_oscillator(int source);


/** Switch the system clock source.
 *
 * \param source: Clock source to drive oscillator.
 *
 * \return: Error code or OK.
 *
 */
static uint8_t switch_system_clk(int source);


uint8_t clock_init(t_clock_cfg *cfg)
{
    uint8_t error = OK; /* Error flag, will be returned at the end of the function. */

    /* Fill the driver structure fields */
    clock_drv.sys_clk = cfg->sys_clk;
    clock_drv.AHB_clk = cfg->AHB_clk;
    clock_drv.APB1_clk = cfg->APB1_clk;
    clock_drv.APB2_clk = cfg->APB2_clk;

    if(cfg->source == HSI_OSC){cfg->source = HSI_OSC;}
    else if(cfg->source == SYSCLOCK){cfg->source = SYSCLOCK;}
    else if(cfg->source == HSE_OSC){cfg->source = HSE_OSC;}
    else if(cfg->source == HSE_BYP){cfg->source = HSE_BYP;}
    else if(cfg->source == PLL_HSI){cfg->source = PLL_HSI;}
    else if(cfg->source == PLL_HSE){cfg->source = PLL_HSE;}
    else if(cfg->source == PLL_HSE_BYP){cfg->source = PLL_HSE_BYP;}

    error |= start_oscillator(cfg->source);

    /* PLL needs to be activated if system clock is greater than osc. */
    if ((cfg->source >= PLL_HSI) && (cfg->source <= PLL_HSE_BYP))
    {
        error |= start_oscillator(HSI_OSC);
        error |= switch_system_clk(HSI_OSC);
        error |= init_activate_PLL(cfg->sys_clk, cfg->source); /* Set PLL. */
    }
    error |= set_flash_latency(cfg->sys_clk); /* Flash latency depends on system clock frequency. */
    error |= switch_system_clk(cfg->source);

    /* If High Speed Internal Oscillator (HSI) is selected,         */
    /* Stop High Speed External Oscillator (HSE) and the bypass.    */
    if((cfg->source == HSI_OSC) || (cfg->source == PLL_HSI))
    {
        error |= stop_oscillator(HSE_BYP);
    }
    else if ((cfg->source == HSE_OSC) || (cfg->source == HSE_BYP)
                                            || (cfg->source == PLL_HSE)
                                            || (cfg->source == PLL_HSE_BYP))
    {
        error |= stop_oscillator(HSI_OSC);

        /* If High Speed External Oscillator (HSE) is selected,         */
        /* And deactivate the bypass.                                   */
        if((cfg->source == HSE_OSC) || (cfg->source == PLL_HSE))
        {
            RCC->CR &= 0xFFFBFFFF;
        }
    }
    error |= init_AHB(cfg->sys_clk, cfg->AHB_clk);      /* Set AHB prescaler.     */
    error |= init_APB1(cfg->AHB_clk, cfg->APB1_clk);    /* Set APB1 prescaler.    */
    error |= init_APB2(cfg->AHB_clk, cfg->APB2_clk);    /* Set APB2 prescaler.    */
    return error;
}


uint8_t clock_select_clock_to_output(int source)
{
    uint32_t local_MCO_mask = 0x07000000;

    RCC->CFGR &= ~local_MCO_mask;
    if(source == SYSCLOCK){RCC->CFGR |= 0x04000000;}
    else if(source == HSI_OSC){RCC->CFGR |= 0x05000000;}
    else if(source == HSE_OSC){RCC->CFGR |= 0x06000000;}
    else if((source >= PLL_HSI) &&
            (source <= PLL_HSE_BYP)){RCC->CFGR |= 0x07000000;}
    else{RCC->CFGR &= ~local_MCO_mask;}
    return OK;
}


uint32_t get_ahb_clock(void)
{
    return clock_drv.AHB_clk;
}


uint32_t get_apb1_clock(void)
{
    return clock_drv.APB1_clk;
}


uint32_t get_apb2_clock(void)
{
    return clock_drv.APB2_clk;
}


uint32_t get_sys_clock(void)
{
    return clock_drv.sys_clk;
}


static uint8_t init_activate_PLL(uint32_t sys_clk, int source)
{
    uint8_t PLL_mult[15] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    uint32_t temp_Pll_mul = 0;                     /* Local variable to compute the PLL multiplier coefficient.     */
    uint32_t temp_clk_freq_MHZ = CLOCK_FREQ_MHZ;   /* Local var to modify the CLOCK_FREQ_MHZ function of divisions. */
    uint8_t temp_error = ERROR_WRONG_CLOCK_SET;    /* Local variable to return the complete value of the function.  */

    RCC->CR &= ~(0x01000000);                      /* PLLON = 0, disable PLL.                                       */
    while((RCC->CR & 0x02000000) != 0x00000000){}  /* Wait for PLLRDY = 0, PLL is disabled.                         */
    RCC->CFGR &= 0xFFC0FFFF;                       /* PLLMUL = 0, Clear the PLL multiplier field.                   */
                                                   /* PLLXTPRE = 0, Clear the PLL HSE divider field.                */
                                                   /* PLLSRC = 0, Clear the PLL source field.                       */
    if((((sys_clk % CLOCK_FREQ_MHZ) != 0)          /* Branch if sysclk is not a multiple of the ext crystal,        */
      || (sys_clk == CLOCK_FREQ_MHZ)) &&           /* Or if sysclk is equal to the ext crystal,                     */
         (source == PLL_HSE))                      /* And the clock is from HSE (bypassed or not) oscillator,       */
    {
        RCC->CFGR |= 0x00020000;                   /* PLLXTPRE = 1, divide the HSE input oscillator by 2.           */
        temp_clk_freq_MHZ /= 2;                    /* The clock frequency local variable is divided by 2.           */
    }
                                                   /* The clock freq local variable always divided by 2 in HSI.     */
    if((source == HSI_OSC) || (source == PLL_HSI)){temp_clk_freq_MHZ /= 2;}

    temp_Pll_mul = sys_clk / temp_clk_freq_MHZ;    /* Compute the coefficient to load into the PLL multiplier.      */
    for(uint8_t index = 0; index <= 14; index++)   /* Screen the PLL multiplier table.                              */
    {
        if((temp_clk_freq_MHZ * PLL_mult[index]) == sys_clk)
        {
            temp_Pll_mul = PLL_mult[index] - 2;
            temp_Pll_mul = (temp_Pll_mul & 0x000000FF) << 18;

            RCC->CFGR |= temp_Pll_mul;
            /* If HSE oscillator is selected, */
            /* Select the HSE PLL source.     */
            if((source == PLL_HSE) || (source == PLL_HSE_BYP))
            {
                RCC->CFGR |= 0x00010000;
            }
            /* PLLON  = 1, PLL is enabled.         */
            /* Wait for PLLRDY = 1, PLL is stable. */
            RCC->CR |= 0x01000000;
            while((RCC->CR & 0x02000000) != 0x02000000){}
            temp_error = OK;
            break;
        }
    }
    return temp_error;
}


static uint8_t init_AHB(uint32_t sys_clk, uint32_t AHB_clk)
{
    uint16_t AHB_prescaler[9] = {1, 2, 4, 8, 16, 64, 128, 256, 512};

    /* Compute the coefficient to load into the PLL multiplier. */
    uint32_t local_AHB_div = (sys_clk / AHB_clk);
    uint8_t error = ERROR_WRONG_CLOCK_SET;

    /* Screen the AHB prescaler table. */
    for(uint8_t index = 0; index < 9; index++)
    {
        if((sys_clk / AHB_prescaler[index]) == AHB_clk)
        {
            if(index == 0){local_AHB_div = 0;}
            else{local_AHB_div = index + 7;}
            local_AHB_div = (local_AHB_div & 0x000000FF) << 4;
            RCC->CFGR &= 0xFFFFFF0F;
            RCC->CFGR |= local_AHB_div;
            error = OK;
            break; /* Go out of the loop, the value has been found. */
        }
    }
    return error;
}


static uint8_t init_APB1(uint32_t AHB_clk, uint32_t APB1_clk)
{
    uint8_t APB_prescaler[5] = {1, 2, 4, 8, 16};

    /* Compute the coefficient to load into the PLL multiplier. */
    uint32_t local_APB1_div = (AHB_clk / APB1_clk);
    uint8_t error = ERROR_WRONG_CLOCK_SET;

    /* Screen the APB1 prescaler table. */
    for(uint8_t index = 0; index < 5; index++)
    {
        if((AHB_clk / APB_prescaler[index]) == APB1_clk)
        {
            if(index == 0){local_APB1_div = 0;}
            else{local_APB1_div = index + 3;}
            local_APB1_div = (local_APB1_div & 0x000000FF) << 8;
            RCC->CFGR &= 0xFFFFF8FF;
            RCC->CFGR |= local_APB1_div;
            error = OK;
            break; /* Go out of the loop, the value has been found. */
        }
    }
    return error;
}


static uint8_t init_APB2(uint32_t AHB_clk, uint32_t APB2_clk)
{
    uint8_t APB_prescaler[5] = {1, 2, 4, 8, 16};

    /* Compute the coefficient to load into the PLL multiplier. */
    uint32_t local_APB2_div = (AHB_clk / APB2_clk);
    uint8_t error = ERROR_WRONG_CLOCK_SET;

    /* Screen the APB2 prescaler table. */
    for(uint8_t index = 0; index < 5; index++)
    {
        if((AHB_clk / APB_prescaler[index]) == APB2_clk)
        {
            if(index == 0){local_APB2_div = 0;}
            else{local_APB2_div = index + 3;}
            local_APB2_div = (local_APB2_div & 0x000000FF) << 11;
            RCC->CFGR &= 0xFFFFC7FF;
            RCC->CFGR |= local_APB2_div;
            error = OK;
            break; /* Go out of the loop, the value has been found. */
        }
    }
    return error;
}


static uint8_t set_flash_latency(uint32_t sys_clk)
{
    uint32_t temp_flash_ACR = 0;
    start_oscillator(HSI_OSC);

    /* If the system clock is between 0 and 24 MHz, */
    /* LATENCY = 0, 0 wait states configured.       */
    if((sys_clk > 0) && (sys_clk <= 24000000))
    {
        FLASH->ACR &= 0xFFFFFFF8;
    }

    /* If the system clock is between 24 and 48 MHz, */
    /* Store the FLASH_ACR register.                 */
    /* LATENCY	= 1, 1 wait state is configured.     */
    else if((sys_clk > 24000000) && (sys_clk <= 48000000))
    {
        temp_flash_ACR = FLASH->ACR;
        FLASH->ACR = ((temp_flash_ACR & 0xFFFFFFF8)+1);
    }

    /* If the system clock is between 48 and 72 MHz, */
    /* Store the FLASH_ACR register.                 */
    /* LATENCY = 2, 2 wait states are configured.    */
    else if((sys_clk > 48000000) && (sys_clk <= 72000000))
    {
        temp_flash_ACR = FLASH->ACR;
        FLASH->ACR = ((temp_flash_ACR & 0xFFFFFFF8)+2);
    }
    FLASH->ACR |= 0x00000010;                        /* LATENCY = 0, 0 wait states configured. */
    while((FLASH->ACR & 0x00000020) != 0x00000020){} /* Wait for PLLRDY = 1, PLL is stable.    */
    return OK;
}


static uint8_t start_oscillator(int source)
{
    if((source == HSI_OSC) || (source == PLL_HSI))
    {
    	/* HSION = 1, enable High Speed Internal oscillator. */
    	/* Wait for HSIRDY = 1, HSI oscillator is stable.    */
        RCC->CR |= 0x00000001;
        while((RCC->CR & 0x00000002) != 2){}
    }
    else if((source == HSE_OSC) || (source == PLL_HSE))
    {
    	/* HSEON = 1, enable High Speed External oscillator. */
    	/* Wait for HSERDY = 1, HSE oscillator is stable.    */
        RCC->CR |= 0x00010000;
        while((RCC->CR & 0x00020000) != 0x20000){}
    }
    else if((source == HSE_BYP) || (source == PLL_HSE_BYP))
    {
    	/* HSEON = 1, enable High Speed External source.          */
    	/* HSEBYP = 1, bypass the crystal for an external source. */
    	/* Wait for HSERDY = 1, HSE oscillator is stable.         */
        RCC->CR |= 0x00050000;
        while((RCC->CR & 0x00020000) != 0x20000){}
    }
    return OK;
}


static uint8_t stop_oscillator(int source)
{
    if(source == HSI_OSC)
    {
        RCC->CR &= (~0x00000001); /* Clear HSION bit. */
    }
    else if(source == HSE_OSC)
    {
        RCC->CR &= (~0x00010000); /* Clear HSEON bit. */
    }
    else if(source == HSE_BYP)
    {
        RCC->CR &= (~0x00050000); /* Clear HSEON and HSEBYP bits. */
    }
    return OK;
}


static uint8_t switch_system_clk(int source)
{
    uint8_t local_source = (RCC->CFGR & 0x0C) >> 2;

    if((local_source != source) && (source == HSI_OSC))
    {
        RCC->CFGR &= 0xFFFFFFF0; /* SW = 0, Select the HSI oscillator. */
    }
    else if((local_source != source) && (source == HSE_OSC))
    {
        /* If local source is HSI oscillator.          */
        /* SW = 1, Disable HSI oscillator, LSB is set. */
        if(local_source == 0x00)
        {
            RCC->CFGR |= 0x01;
        }
        /* If local source is PLL.                 */
        /* SW = 1, Disable PLL, invert the 2 bits. */
        else if(local_source == 0x02)
        {
            RCC->CFGR ^= 0x03;
        }
    }
    else if((local_source != source) && ((source >= PLL_HSI) && (source <= PLL_HSE_BYP)))
    {
    	/* If local source is HSI oscillator.           */
    	/* SW = 2, Disable HSI oscillator , MSB is set. */
        if(local_source == 0x00)
        {
            RCC->CFGR |= 0x02;
        }
        /* If local source is HSE oscillator.      */
        /* SW = 2, Disable PLL, invert the 2 bits. */
        else if(local_source == 0x01)
        {
            RCC->CFGR ^= 0x03;
        }
    }
    return OK;
}

#endif /* CLOCK_RESET */
