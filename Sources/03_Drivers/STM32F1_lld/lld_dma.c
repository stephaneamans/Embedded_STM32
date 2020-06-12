/*
 * lld_dma.c
 *
 * Created on: Jun 8, 2020
 * Author: Stephane Amans
 */

/* Include files.        */
#include "lld_dma.h"

//#if defined(GPIO_PA0) || defined(GPIO_PA1) || defined(GPIO_PA2) || defined(GPIO_PA6) || defined(GPIO_PA8) || defined(GPIO_PA9) || defined(GPIO_PA10) || defined(GPIO_PB7) || defined(GPIO_PB9) || defined(GPIO_PC13)

/* Defines */
#define PSIZE_MASK  0x0300
#define MSIZE_MASK  0x0C00


/** Enable an DMA port clock.
 *
 * \param dma: address of the DMA port to clock.
 *
 * \return: Error code or OK.
 *
 */
static t_error_handling dma_enable_clock(DMA_TypeDef *dma);


t_error_handling dma_init(t_dma_channel_cfg *cfg)
{
    uint16_t local_conf = 0;
    uint8_t channel_id = 0;

    if(cfg->reg == DMA1_Ch1)
    {
        channel_id = 0;
        dma_enable_clock(DMA1);
    }
    else if(cfg->reg == DMA1_Ch2)
    {
        channel_id = 1;
        dma_enable_clock(DMA1);
    }
    else if(cfg->reg == DMA1_Ch3)
    {
        channel_id = 2;
        dma_enable_clock(DMA1);
    }
    else if(cfg->reg == DMA1_Ch4)
    {
        channel_id = 3;
        dma_enable_clock(DMA1);
    }
    else if(cfg->reg == DMA1_Ch5)
    {
        channel_id = 4;
        dma_enable_clock(DMA1);
    }
    else if(cfg->reg == DMA1_Ch6)
    {
        channel_id = 5;
        dma_enable_clock(DMA1);
    }
    else if(cfg->reg == DMA1_Ch7)
    {
        channel_id = 6;
        dma_enable_clock(DMA1);
    }

    local_conf = 0;                                                         /* Clear configuration variable. */
    cfg->reg->CCR = 0;                                        /* Clear DMA channel configurarion register.   */

    local_conf |= cfg->mem2mem;                                               /* memory to memory enable.    */
    local_conf = ((local_conf << 2) | cfg->dma_priority);                     /* DMA channel priority.       */
    local_conf = ((local_conf << 2) | cfg->mem_data_type);                    /* Memory data format.         */
    local_conf = ((local_conf << 2) | cfg->periph_data_type);                 /* Peripheral data format.     */
    local_conf = ((local_conf << 1) | cfg->memory_increment);                 /* Memory increment value.     */
    local_conf = ((local_conf << 1) | cfg->peripheral_increment);             /* Periph increment value.     */
    local_conf = ((local_conf << 1));                                         /* Disable circular buffer.    */
    local_conf = ((local_conf << 1) | cfg->read_from_memory);                 /* Datat transfert direction.  */
    local_conf = ((local_conf << 1) | cfg->irq.transfer_error_interrupt);     /* Enable or not irq.          */
    local_conf = ((local_conf << 1) | cfg->irq.half_transfer_interrupt);      /* Enable or not irq.          */
    local_conf = ((local_conf << 1) | cfg->irq.transfert_complete_interrupt); /* Enable or not irq.          */
    local_conf = (local_conf << 1);                                           /* Skip the enable field .     */
    cfg->reg->CCR = local_conf;                  /* Load the register with module configuration options.  */
    cfg->reg->CNDTR = cfg->memory_zone_size;     /* Memory zone size.    */
    cfg->reg->CMAR = cfg->memory_zone_address;   /* Memory zone address. */
    cfg->reg->CPAR = cfg->peripheral_address;    /* Peripheral address.  */

    /* If any interrupt enabled, enable nvic interrupt, set priority and assign callbacks: */
    if((cfg->irq.transfer_error_interrupt == 1) || (cfg->irq.half_transfer_interrupt == 1) ||
       (cfg->irq.transfert_complete_interrupt == 1))
    {
        dma_callback[channel_id] = cfg->irq.callback;
        set_nvic_priority(IRQ_DMA1_Channel1 + channel_id, cfg->irq.priority);
        enable_nvic_irq(IRQ_DMA1_Channel1 + channel_id);
    }
    return OK;
}


t_error_handling dma_memcpy(t_dma_channel_cfg *driver, void *address_destination, void *address_source,
                            dma_data_type data_type, uint16_t memory_zone_size)
{
    uint32_t local_conf = 0;
    dma_stop_transfer(driver);
    driver->reg->CMAR = (uint32_t)address_source;
    driver->reg->CPAR = (uint32_t)address_destination;
    driver->reg->CNDTR = memory_zone_size;

    if(data_type != driver->mem_data_type)
    {
        local_conf = data_type;
        local_conf |= ((local_conf << 2) | data_type);
        local_conf <<= 8;
        driver->reg->CCR &= ~PSIZE_MASK;
        driver->reg->CCR &= ~MSIZE_MASK;
        driver->reg->CCR |= local_conf;
    }
    return OK;
}


t_error_handling dma_start_transfer(t_dma_channel_cfg *dma_channel)
{
    t_error_handling error = ERROR_DRIVER_NOT_INITIALIZED;
    if(dma_channel != 0)
    {
        dma_channel->reg->CCR |= 1;      /* Enable the DMA channel .    */
        error = OK;
    }
    return error;
}


t_error_handling dma_stop_transfer(t_dma_channel_cfg *dma_channel)
{
    t_error_handling error = ERROR_DRIVER_NOT_INITIALIZED;
    if(dma_channel != 0)
    {
        dma_channel->reg->CCR &= ~1;            /* Disable the DMA channel .    */
        error = OK;
    }
    return error;
}


static t_error_handling dma_enable_clock(DMA_TypeDef *dma)
{
    t_error_handling error = ERROR_WRONG_VALUE_PASSED;
    if(dma == DMA1)
    {
        RCC->AHBENR |= 0x01;
        error = OK;
    }
    return error;
}


t_error_handling dma_disable_clock(DMA_TypeDef *dma)
{
    t_error_handling error = ERROR_WRONG_VALUE_PASSED;
    if(dma == DMA1)
    {
        RCC->AHBENR &= ~0x01;
        error = OK;
    }
    return error;
}


extern void DMA1_Channel1_IRQHandler(void)
{
    /**	DMA1_Channel 1 IRQ handler.
    *
    * \param void : No parameter.
    *
    * \return : No return value.
    */
    uint32_t irq_source = (DMA1->ISR & 0x0F);      /* Mask on channel 1.                        */
    dma_callback[0]((uint8_t*)&irq_source);        /* Call the DMA1 Channel 1 subroutine.       */
    DMA1->IFCR = 0x0F;                             /* Clear DMA ISR interrupts flags.           */
    clear_pending_nvic_irq(IRQ_DMA1_Channel1);     /* Clear any DMA ch1 NVIC pending interrupt. */
}


extern void DMA1_Channel2_IRQHandler(void)
{
    /**	DMA1_Channel 2 IRQ handler.
    *
    * \param void : No parameter.
    *
    * \return : No return value.
    */
    uint32_t irq_source = (DMA1->ISR & 0xF0);      /* Mask on channel 2.                        */
    irq_source >>= 4;                              /* Shift the 4 bits to the lsb position.     */
    dma_callback[1]((uint8_t*)&irq_source);        /* Call the DMA1 Channel 2 subroutine.       */
    clear_pending_nvic_irq(IRQ_DMA1_Channel2);     /* Clear any DMA ch2 NVIC pending interrupt. */
    DMA1->IFCR = 0xF0;                             /* Clear DMA ISR interrupts flags.           */
}


extern void DMA1_Channel3_IRQHandler(void)
{
    /**	DMA1_Channel 3 IRQ handler.
    *
    * \param void : No parameter.
    *
    * \return : No return value.
    */
    uint32_t irq_source = (DMA1->ISR & 0xF00);     /* Mask on channel 3.                        */
    irq_source >>= 8;                              /* Shift the 4 bits to the lsb position.     */
    dma_callback[2]((uint8_t*)&irq_source);        /* Call the DMA1 Channel 3 subroutine.       */
    clear_pending_nvic_irq(IRQ_DMA1_Channel3);     /* Clear any DMA ch3 NVIC pending interrupt. */
    DMA1->IFCR = 0xF00;                            /* Clear DMA ISR interrupts flags.           */
}


extern void DMA1_Channel4_IRQHandler(void)
{
    /**	DMA1_Channel 4 IRQ handler.
     *
     * \param void : No parameter.
     *
     * \return : No return value.
     */
    uint32_t irq_source = (DMA1->ISR & 0xF000);    /* Mask on channel 4.                        */
    irq_source >>= 12;                             /* Shift the 4 bits to the lsb position.     */
    dma_callback[3]((uint8_t*)&irq_source);        /* Call the DMA1 Channel 4 subroutine.       */
    clear_pending_nvic_irq(IRQ_DMA1_Channel4);     /* Clear any DMA ch4 NVIC pending interrupt. */
    DMA1->IFCR = 0xF000;                           /* Clear DMA ISR interrupts flags.           */
}


extern void DMA1_Channel5_IRQHandler(void)
{
    /**	DMA1_Channel 5 IRQ handler.
    *
    * \param void : No parameter.
    *
    * \return : No return value.
    */
    uint32_t irq_source = (DMA1->ISR & 0xF0000);   /* Mask on channel 5.                        */
    irq_source >>= 16;                             /* Shift the 4 bits to the lsb position.     */
    dma_callback[4]((uint8_t*)&irq_source);        /* Call the DMA1 Channel 5 subroutine.       */
    clear_pending_nvic_irq(IRQ_DMA1_Channel5);     /* Clear any DMA ch5 NVIC pending interrupt. */
    DMA1->IFCR = 0xF0000;                          /* Clear DMA ISR interrupts flags.           */
}


extern void DMA1_Channel6_IRQHandler(void)
{
    /**	DMA1_Channel 6 IRQ handler.
    *
    * \param void : No parameter.
    *
    * \return : No return value.
    */
    uint32_t irq_source = (DMA1->ISR & 0xF00000);  /* Mask on channel 6.                        */
    irq_source >>= 20;                             /* Shift the 4 bits to the lsb position.     */
    dma_callback[5]((uint8_t*)&irq_source);        /* Call the DMA1 Channel 6 subroutine.       */
    clear_pending_nvic_irq(IRQ_DMA1_Channel6);     /* Clear any DMA ch6 NVIC pending interrupt. */
    DMA1->IFCR = 0xF00000;                         /* Clear DMA ISR interrupts flags.           */
}


extern void DMA1_Channel7_IRQHandler(void)
{
    /**	DMA1_Channel 7 IRQ handler.
    *
    * \param void : No parameter.
    *
    * \return : No return value.
    */
    uint32_t irq_source = (DMA1->ISR & 0xF000000); /* Mask on channel 7.                        */
    irq_source >>= 24;                             /* Shift the 4 bits to the lsb position.     */
    dma_callback[6]((uint8_t*)&irq_source);        /* Call the DMA1 Channel 7 subroutine.       */
    clear_pending_nvic_irq(IRQ_DMA1_Channel7);     /* Clear any DMA ch7 NVIC pending interrupt. */
    DMA1->IFCR = 0xF000000;                        /* Clear DMA ISR interrupts flags.           */
}


//#endif /* DMA */
