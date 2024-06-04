/*
 * spi_irq.c
 *
 * Created on: May 31, 2024
 * Author: Stephane Amans
 *
 */

/* Include files        */
#include <stdio.h>
#include <string.h>

#include "fault.h"
#include "clock.h"
#include "spi.h"

#include "regbase_spi.h"

#include "soc_configuration.h"

/* Defines */
#define SPI_CR2_RXNEIE_BIT_MASK     0x40
#define SPI_CR2_TXEIE_BIT_MASK      0x80

#define SPI_SR_TXE_BIT_MASK         0x2
#define SPI_SR_RXNE_BIT_MASK        0x1

/* SPI private structure definition :        */
struct t_spi_private
{
    struct t_spi_regs *reg;
    struct t_spi_slave *slave;
    uint8_t last_config;
    uint16_t *write_buffer;
    uint16_t *read_buffer;
    uint32_t buffer_length;
    uint16_t buffer_index;
};

/* Static SPI private and slaves record structure instances. */
static struct t_spi_private priv[SPI_IP_NUMBER];
static struct t_spi_slave *slaves_record[MAX_SPI1_PERIPHERALS + MAX_SPI2_PERIPHERALS];

/** Start a SPI transfer by interrupt.
 *
 * \param driver: Pointer to the SPI driver.
 * \param slave: Pointer to the slave instance.
 *
 * \return : void.
 *
 */
void spi_transfer(struct t_spi_driver *driver, struct t_spi_slave *slave)
{
    driver->priv->buffer_index = 0;
    driver->priv->slave = slave;

    /* Load buffer with data */
    driver->priv->reg->DR = driver->priv->write_buffer[0];

    /* Enable TX buffer empty and RX buffer not empty interrupts */
    driver->priv->reg->CR2 |= SPI_CR2_TXEIE_BIT_MASK | SPI_CR2_RXNEIE_BIT_MASK;
}

void spi_init_specific(struct t_spi_driver *config)
{
    enable_nvic_irq(config->instance + NVIC_SPI_OFFSET);
    set_nvic_priority(config->instance + NVIC_SPI_OFFSET, config->irq.priority);
}

/** SPI1 IRQ handler.
*
* \param void : No parameter.
*
* \return : No return value.
*/
void SPI1_IRQHandler(void)
{
    /* If a transmission is on going, process the next transmit and receive bytes */
    if(((priv[0].reg->SR & SPI_SR_TXE_BIT_MASK) == SPI_SR_TXE_BIT_MASK) &&
       ((priv[0].reg->SR & SPI_SR_RXNE_BIT_MASK) == SPI_SR_RXNE_BIT_MASK))
    {
        if(priv[0].buffer_length > 0)
        {
            priv[0].read_buffer[priv[0].buffer_index] = priv[0].reg->DR;
            priv[0].buffer_length--;
            priv[0].buffer_index++;
            priv[0].reg->DR = priv[0].write_buffer[priv[0].buffer_index];
        }
        else
        {
            /* Disable TX buffer empty and RX buffer not empty interrupts */
            priv[0].reg->CR2 &= ~(SPI_CR2_TXEIE_BIT_MASK | SPI_CR2_RXNEIE_BIT_MASK);
            cs_high(priv[0].slave);
        }
    }
}

/** SPI2 IRQ handler.
*
* \param void : No parameter.
*
* \return : No return value.
*/
void SPI2_IRQHandler(void)
{
    /* If a transmission is on going, process the next transmit and receive bytes */
    if(((priv[1].reg->SR & SPI_SR_TXE_BIT_MASK) == SPI_SR_TXE_BIT_MASK) &&
       ((priv[1].reg->SR & SPI_SR_RXNE_BIT_MASK) == SPI_SR_RXNE_BIT_MASK))
    {
        if(priv[1].buffer_length > 0)
        {
            priv[1].read_buffer[priv[0].buffer_index] = priv[1].reg->DR;
            priv[1].buffer_length--;
            priv[1].buffer_index++;
            priv[1].reg->DR = priv[0].write_buffer[priv[1].buffer_index];
        }
        else
        {
            /* Disable TX buffer empty and RX buffer not empty interrupts */
            priv[1].reg->CR2 &= ~(SPI_CR2_TXEIE_BIT_MASK | SPI_CR2_RXNEIE_BIT_MASK);
            cs_high(priv[1].slave);
        }
    }
}
