/*
 *        lld_gpio.c
 *
 *    Created on: Apr 12, 2019
 *    Author: Stephane Amans
 */

/* Include files.        */
#include "lld_gpio.h"

#if defined(GPIO_PA0) || defined(GPIO_PA1) || defined(GPIO_PA2) || defined(GPIO_PA6) || defined(GPIO_PA8) || defined(GPIO_PA9) || defined(GPIO_PA10) || defined(GPIO_PB7) || defined(GPIO_PB9) || defined(GPIO_PC13)


/** Enable an GPIO port clock.
 *
 * \param gpio: address of the GPIO port to clock.
 *
 * \return: Error code or OK.
 *
 */
static t_error_handling gpio_enable_clock(GPIO_TypeDef *gpio);


t_error_handling gpio_init(t_gpio_cfg *cfg)
{
    uint8_t local_cnf_mode = 0;
    uint32_t local_mask = 0; /* Local variable for masks operations. */
    uint8_t local_port = 0;  /* Local variable port operations.      */

    gpio_enable_clock(cfg->gpio);

    /* Concatenate 2 bits config with 2 bits mode. */
    if(cfg->config < 3){local_cnf_mode = ((cfg->config & 0x3) <<2) + (cfg->mode & 0x3);}
    else{local_cnf_mode = (((cfg->config - 1) & 0x3) << 2) + (cfg->mode & 0x3);}

    /* Set the localPort variable function of the port number. */
    if(cfg->gpio == GPIOA)
    {
        local_port = 1;
    }
    else if(cfg->gpio == GPIOB)
    {
        local_port = 2;
    }
    else if(cfg->gpio == GPIOC)
    {
        local_port = 3;
    }
    else if(cfg->gpio == GPIOD)
    {
        local_port = 4;
    }

    /* Write in the low register for GPIO 0 to 7.    */
    if(cfg->pin>=0 && cfg->pin<=7)
    {
        local_mask = 0xF << (cfg->pin * 4);
        cfg->gpio->CRL &= ~local_mask;
        cfg->gpio->CRL |= local_cnf_mode << (cfg->pin * 4);
    }
    /* Write in the high register for GPIO 8 to 15. */
    else if(cfg->pin >= 8 && cfg->pin <= 15)
    {
        local_mask = 0xF << ((cfg->pin - 8) * 4);
        cfg->gpio->CRH &= ~local_mask;
        cfg->gpio->CRH |= local_cnf_mode<<((cfg->pin -8 ) * 4);
    }

    /* Set all parameters for a GPIO set in input. */
    if(cfg->mode == mode_input)
    {
        local_mask = 0xF << ((cfg->pin % 4) * 4);
        AFIO->EXTICR[cfg->pin / 4] &= ~local_mask; /* Clear the 4 bits corresponding to the port selection. */

        /* Set all patameters for an input GPIO interrupt driven. */
        if(cfg->irq.active == 1)
        {
            AFIO->EXTICR[cfg->pin / 4] |= local_port << ((cfg->pin % 4) * 4);
            EXTI->IMR |= 0x01 << cfg->pin; /* Unmask interrupt line. */
            EXTI->EMR |= 0x01 << cfg->pin; /* Unmask event line.     */

            /* Associate the callbacks references. */
            if((cfg->pin >= 0) && (cfg->pin <= 4))
            {
                enable_nvic_irq(cfg->pin + 6);
                set_nvic_priority(cfg->pin + 6, cfg->irq.priority);
                gpio_callback[cfg->pin] = cfg->irq.callback;
            }

            /* Set all parameters to configure interrupts on rising edge.*/
            if(cfg->irq.rising == 1)
            {
                EXTI->RTSR |= 0x01 << cfg->pin;    /* Interrupt / event on rising edge.          */
                EXTI->FTSR &= (~0x01) << cfg->pin; /* Disable interrupt / event on falling edge. */
            }

            /* Set all parameters to configure interrupts on falling edge. */
            else
            {
                EXTI->RTSR &= (~0x01) << cfg->pin; /* Disable interrupt / event on rising edge. */
                EXTI->FTSR |= 0x01 << cfg->pin;    /* Interrupt / event on falling edge.        */
                disable_nvic_irq(cfg->pin + 6);
                gpio_callback[cfg->pin] = 0;
            }

            /* Set input pullup. */
            if(cfg->mode == mode_input && cfg->config == config_input_pullup)
            {
            	cfg->gpio->ODR |= 0x01 << cfg->pin;
            }

            /* Set input pulldown. */
            else if(cfg->mode == mode_input && cfg->config == config_input_pulldown)
            {
            	cfg->gpio->ODR &= (~0x01) << cfg->pin;
            }
        }

        /* Set all patameters for an input GPIO. */
        else if(cfg->irq.active == 0)
        {
            EXTI->IMR &= (~0x01) << cfg->pin;  /* Mask interrupt line.                       */
            EXTI->EMR &= (~0x01) << cfg->pin;  /* Mask event line.                           */
            EXTI->FTSR &= (~0x01) << cfg->pin; /* Disable interrupt / event on falling edge. */
            EXTI->RTSR &= (~0x01) << cfg->pin; /* Disable interrupt / event on rising edge.  */

            /* Set input pullup. */
            if(cfg->mode == mode_input && cfg->config == config_input_pullup)
            {
            	cfg->gpio->ODR |= 0x01 << cfg->pin;
            }
            
            /* Set input pulldown. */
            else if(cfg->mode == mode_input && cfg->config == config_input_pulldown)
            {
            	cfg->gpio->ODR &= (~0x01) << cfg->pin;
            }
        }
    }
    return OK;
}


t_error_handling gpio_init_event_ctrl(uint8_t event_out_en, uint8_t port, uint8_t pin)
{
	t_error_handling error = ERROR_WRONG_VALUE_PASSED;
    if(pin < MAX_GPIO_PIN)
    {
        uint32_t local_setup = (((event_out_en << 3) + port) << 4) + pin; /* Concatenate all fields. */
        AFIO->EVCR = local_setup;
        error = OK;
    }
    return error;
}


t_error_handling gpio_set(GPIO_TypeDef *gpio, uint16_t pin)
{
	t_error_handling error = ERROR_WRONG_VALUE_PASSED;
    if(pin < MAX_GPIO_PIN)
    {
        gpio->BSRR = 1 << pin;
        error = OK;
    }
    return error;
}


t_error_handling gpio_set_all(GPIO_TypeDef *gpio)
{
    gpio->ODR = 0xFFFF;
    return OK;
}


t_error_handling gpio_clear(GPIO_TypeDef *gpio, uint8_t pin)
{
	t_error_handling error = ERROR_WRONG_VALUE_PASSED;
    if(pin < MAX_GPIO_PIN)        /* Check if pin number don't exceeds max value.               */
    {
        gpio->BRR = 1 << pin;     /* Write 1 in the corresponding bit of set reset register.    */
        error = OK;
    }
    return error;
}


t_error_handling gpio_clear_all(GPIO_TypeDef *gpio)
{
    gpio->ODR = 0x0000;    /* Write 0 in all bits of the data register.    */
    return OK;
}


t_error_handling gpio_toggle(GPIO_TypeDef *gpio, uint8_t pin)
{
	t_error_handling error = ERROR_WRONG_VALUE_PASSED;
    if(pin < MAX_GPIO_PIN)                    /* Check if pin number don't exceeds max value.    */
    {
        uint32_t local_mask = 1 << pin;
        if((gpio->ODR & local_mask) == local_mask) /* If the pin is high level                        */
        {
            gpio->ODR &= ~local_mask;         /* then clear the pin.                             */
            error = OK;
        }
        else if((gpio->ODR & local_mask) != local_mask) /* If the pin is low level                         */
        {
            gpio->ODR |= local_mask;          /* then set the pin.                               */        
            error = OK;
        }
    }
    return error;
}


uint8_t gpio_read(GPIO_TypeDef *gpio, uint8_t pin)
{
    uint32_t local_read = 0;
    local_read = gpio->IDR;               /* Read all the data input register.                     */
    return ((local_read >> pin) & 0x1);   /* Return the IDR value shifted right (pin in LSBit).    */
}


t_error_handling gpio_pin_remap(PERIPH_REMAP remap)
{
    /* Concatenate all fields in a same variable.    */
    uint32_t local_remap = (remap.swj_tag & 0x7);
    local_remap = (local_remap << 5) + (remap.adc2 & 0x3);
    local_remap = (local_remap  << 2) + (remap.adc1 & 0x3);
    local_remap = (local_remap  << 1) + (remap.tim5 & 0x1);
    local_remap = (local_remap  << 1) + (remap.pd01 & 0x1);
    local_remap = (local_remap  << 2) + (remap.can & 0x3);
    local_remap = (local_remap  << 1) + (remap.tim4 & 0x1);
    local_remap = (local_remap  << 2) + (remap.tim3 & 0x3);
    local_remap = (local_remap  << 2) + (remap.tim2 & 0x3);
    local_remap = (local_remap  << 2) + (remap.tim1 & 0x3);
    local_remap = (local_remap  << 2) + (remap.usart3 & 0x3);
    local_remap = (local_remap  << 1) + (remap.usart2 & 0x1);
    local_remap = (local_remap  << 1) + (remap.usart1 & 0x1);
    local_remap = (local_remap  << 1) + (remap.i2c1 & 0x1);
    local_remap = (local_remap  << 1) + (remap.spi1 & 0x1);
    AFIO->MAPR = local_remap;    /* Write all parameters in the register.    */
    return OK;
}


static t_error_handling gpio_enable_clock(GPIO_TypeDef *gpio)
{
    if(gpio == GPIOA)
    {
    	RCC->APB2ENR |= 0x04;
    }
    else if(gpio == GPIOB)
    {
        RCC->APB2ENR |= 0x08;
    }
    else if(gpio == GPIOC)
    {
        RCC->APB2ENR |= 0x10;
    }
    else if(gpio == GPIOD)
    {
        RCC->APB2ENR |= 0x20;
    }
    return OK;
}


t_error_handling gpio_disable_clock(GPIO_TypeDef *gpio)
{
	if(gpio == GPIOA)
    {
        RCC->APB2ENR &= ~0x04;
    }
	else if(gpio == GPIOB)
	{
        RCC->APB2ENR &= ~0x08;
	}
	else if(gpio == GPIOC)
	{
        RCC->APB2ENR &= ~0x10;
	}
	else if(gpio == GPIOD)
	{
        RCC->APB2ENR &= ~0x20;
    }
    return OK;
}


extern void EXTI0_IRQHandler(void)
{
    /** GPIO0 IRQ handler.
    *
    * \param void: No parameter.
    *
    * \return: No return value.
    */

    gpio_callback[0](EXTI->PR);	       /* Call the GPIO0 subroutine.                  */
    clear_pending_nvic_irq(IRQ_EXTI0); /* Clear any GPIO0 NVIC pending interrupt.     */
    EXTI->PR = 0xFFFFFFFF;             /* Clear all GPIO0 pending interrupt flags.    */
}


extern void EXTI1_IRQHandler(void)
{
    /** GPIO1 IRQ handler.
    *
    * \param void: No parameter.
    *
    * \return: No return value.
    */

    gpio_callback[1](EXTI->PR);	        /* Call the GPIO1 subroutine.                  */
    clear_pending_nvic_irq(IRQ_EXTI1);  /* Clear any GPIO1 NVIC pending interrupt.     */
    EXTI->PR = 0xFFFFFFFF;              /* Clear all GPIO1 pending interrupt flags.    */
}


extern void EXTI2_IRQHandler(void)
{
    /** GPIO2 IRQ handler.
    *
    * \param void: No parameter.
    *
    * \return : No return value.
    */

    gpio_callback[2](EXTI->PR);         /* Call the GPIO2 subroutine.                  */
    clear_pending_nvic_irq(IRQ_EXTI2);  /* Clear any GPIO2 NVIC pending interrupt.     */
    EXTI->PR = 0xFFFFFFFF;              /* Clear all GPIO2 pending interrupt flags.    */
}


extern void EXTI3_IRQHandler(void)
{
    /**	GPIO3 IRQ handler.
    *
    * \param void : No parameter.
    *
    * \return : No return value.
    */

    gpio_callback[3](EXTI->PR);	        /* Call the GPIO3 subroutine.                  */
    clear_pending_nvic_irq(IRQ_EXTI3);  /* Clear any GPIO3 NVIC pending interrupt.     */
    EXTI->PR = 0xFFFFFFFF;              /* Clear all GPIO3 pending interrupt flags.    */
}


extern void EXTI4_IRQHandler(void)
{
    /**	GPIO4 IRQ handler.
    *
    * \param void : No parameter.
    *
    * \return : No return value.
    */

    gpio_callback[4](EXTI->PR);         /* Call the GPIO4 subroutine.                  */
    clear_pending_nvic_irq(IRQ_EXTI4);  /* Clear any GPIO4 NVIC pending interrupt.     */
    EXTI->PR = 0xFFFFFFFF;              /* Clear all GPIO4 pending interrupt flags.    */
}

#endif /* GPIO */
