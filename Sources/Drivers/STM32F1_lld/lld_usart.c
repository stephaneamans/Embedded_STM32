/*
 *        lld_usart.c
 *
 *    Created on: Apr 12, 2019
 *    Author: Stéphane Amans
 */

/* Include files        */
#include "lld_usart.h"
#if defined(USART_1) || defined(USART_2)


/** Enable USART port clock.
 *
 * \param usart : address of the USART to clock.
 *
 * \return : Error code or OK.
 *
 */
static uint8_t usart_enable_clock(USART_TypeDef *usart);


/*
Tx procedure

1. Enable the USART by writing the UE bit in USART_CR1 register to 1.
2. Program the M bit in USART_CR1 to define the word length.
3. Program the number of stop bits in USART_CR2.
4. Select DMA enable (DMAT) in USART_CR3 if Multi buffer Communication is to take
place. Configure the DMA register as explained in multibuffer communication.
5. Select the desired baud rate using the USART_BRR register.
6. Set the TE bit in USART_CR1 to send an idle frame as first transmission.
7. Write the data to send in the USART_DR register (this clears the TXE bit). Repeat this
for each data to be transmitted in case of single buffer.
8. After writing the last data into the USART_DR register, wait until TC=1. This indicates
that the transmission of the last frame is complete. This is required for instance when
the USART is disabled or enters the Halt mode to avoid corrupting the last
transmission.




Rx Procedure:
1. Enable the USART by writing the UE bit in USART_CR1 register to 1.
2. Program the M bit in USART_CR1 to define the word length.
3. Program the number of stop bits in USART_CR2.
4. Select DMA enable (DMAR) in USART_CR3 if multibuffer communication is to take
place. Configure the DMA register as explained in multibuffer communication. STEP 3
5. Select the desired baud rate using the baud rate register USART_BRR
6. Set the RE bit USART_CR1. This enables the receiver which begins searching for a
start bit.
When a character is received
• The RXNE bit is set. It indicates that the content of the shift register is transferred to the
RDR. In other words, data has been received and can be read (as well as its
associated error flags).
• An interrupt is generated if the RXNEIE bit is set.
• The error flags can be set if a frame error, noise or an overrun error has been detected
during reception.
• In multibuffer, RXNE is set after every byte received and is cleared by the DMA read to
the Data Register.
• In single buffer mode, clearing the RXNE bit is performed by a software read to the
USART_DR register. The RXNE flag can also be cleared by writing a zero to it. The
RXNE bit must be cleared before the end of the reception of the next character to avoid
an overrun error.

*/

/*
Transmission using DMA
DMA mode can be enabled for transmission by setting DMAT bit in the USART_CR3
register. Data is loaded from a SRAM area configured using the DMA peripheral (refer to the
DMA specification) to the USART_DR register whenever the TXE bit is set. To map a DMA
channel for USART transmission, use the following procedure (x denotes the channel
number):

1. Write the USART_DR register address in the DMA control register to configure it as the
destination of the transfer. The data will be moved to this address from memory after
each TXE event.
2. Write the memory address in the DMA control register to configure it as the source of
the transfer. The data will be loaded into the USART_DR register from this memory
area after each TXE event.
3. Configure the total number of bytes to be transferred to the DMA control register.
4. Configure the channel priority in the DMA register
5. Configure DMA interrupt generation after half/ full transfer as required by the
application.
6. Clear the TC bit in the SR register by writing 0 to it.
7. Activate the channel in the DMA register.
When the number of data transfers programmed in the DMA Controller is reached, the DMA
controller generates an interrupt on the DMA channel interrupt vector
*/

/*
Reception using DMA
DMA mode can be enabled for reception by setting the DMAR bit in USART_CR3 register.
Data is loaded from the USART_DR register to a SRAM area configured using the DMA
peripheral (refer to the DMA specification) whenever a data byte is received. To map a DMA
channel for USART reception, use the following procedure:
1. Write the USART_DR register address in the DMA control register to configure it as the
source of the transfer. The data will be moved from this address to the memory after
each RXNE event.
2. Write the memory address in the DMA control register to configure it as the destination
of the transfer. The data will be loaded from USART_DR to this memory area after each
RXNE event.
3. Configure the total number of bytes to be transferred in the DMA control register.
4. Configure the channel priority in the DMA control register
5. Configure interrupt generation after half/ full transfer as required by the application.
6. Activate the channel in the DMA control register.
When the number of data transfers programmed in the DMA Controller is reached, the DMA
controller generates an interrupt on the DMA channel interrupt vector.
*/


/** Compute divider from the bus frequency.
 *
 * \param bus_frequency: USART bus frequency value.
 *
 *
 * \return : Error code or OK.
 *
 */
static uint16_t compute_baudrate_divider(uint32_t bus_frequency, uint32_t baudrate);


uint8_t usart_init(USART_TypeDef *usart, t_usart_cfg *cfg)
{
    uint16_t local_conf = 0;
    usart_enable_clock(usart);

    uint32_t clock_frequency = get_apb1_clock();
    if(usart == USART1)
    {
	    clock_frequency = get_apb2_clock();
    }

    usart->BRR = compute_baudrate_divider(clock_frequency, cfg->baud_rate);

    local_conf = (0x02 | cfg->length) << 1;                   /* Enables module and fix frame length.    */
    local_conf = cfg->wake_up;                                /* Wake up mode.                           */
    local_conf = (local_conf << 2) | cfg->parity;             /* Select parity.                          */
    local_conf = (local_conf << 5) | (cfg->irq.type >> 5);    /* Enables wanted interrupts.              */
    local_conf = (local_conf << 2) | 0x03;                    /* Enables RX and TX modes.                */
    usart->CR1 = local_conf;

    local_conf = cfg->stop;                                   /* Configure stop bit length.              */
    local_conf = (local_conf << 3) | cfg->clock_modes;        /* Configure clock modes.                  */
    local_conf = (local_conf << 9);                           /* Shift to the good position.             */
    usart->CR2 = local_conf;

    local_conf = (cfg->irq.type >> 1) & 0x02;                 /* Enables wanted interrupt.               */
    local_conf = (local_conf << 2) | cfg->cts_rts;            /* Configure CTS and RTS.                  */
    local_conf = (local_conf << 2) | cfg->dma;                /* Configure DMA.                          */
    local_conf = (local_conf << 6) | (cfg->irq.type & 0x01);  /* Enables wanted interrupt.               */
    usart->CR3 = local_conf;

    return 0;
}


uint8_t usart_disable_clock(USART_TypeDef *usart)
{
    if(usart == USART1)
    {
        RCC->APB2ENR &= (!0x4000);
    }
    else if(usart == USART2)
	{
        RCC->APB1ENR &= (!0x20000);
    }
    return OK;
}


static uint16_t compute_baudrate_divider(uint32_t bus_frequency, uint32_t baudrate)
{
    uint32_t local_divider = baudrate * 16;
    uint16_t mantissa = bus_frequency / local_divider;
    uint8_t fraction = (uint8_t)((bus_frequency % local_divider) / local_divider) * 16;
    return ((mantissa << 4) | (fraction & 0x0F));
}


static uint8_t usart_enable_clock(USART_TypeDef *usart)
{
    if (usart == USART1)
    {
        RCC->APB2ENR |= 0x4000;
    }
    else if(usart == USART2)
    {
        RCC->APB1ENR |= 0x20000;
    }
    return OK;
}

#endif /* USART */

