/*
 * lld_i2c.c
 *
 * Created on: Aug 23, 2021
 * Author: Stephane Amans
 *
 */

/* Include files        */
#include "lld_clock.h"
#include "lld_i2c.h"

#include "regbase_i2c.h"

/* I2C private structure definition :        */
struct t_i2c_private
{
    struct t_i2c_regs *reg;
};

/* Static DMA private structure instances. */
static struct t_i2c_private priv[I2C_IP_NUMBER];

void i2c_write(struct t_i2c_driver *driver, uint8_t *data)
{
    driver->priv->reg->CR1 |= 0x100; /* start */
    while((driver->priv->reg->SR1 & 0x01) != 0x01){}

    driver->priv->reg->DR = (0xA << 1); /* Send address and write bit */
    while((driver->priv->reg->SR1 & 0x02) != 0x02){}
    while((driver->priv->reg->SR2 & 0x02) != 0x02){}

    driver->priv->reg->DR = *data; /* Send data */

    while((driver->priv->reg->SR1 & 0x04) != 0x04){}
    while((driver->priv->reg->SR2 & 0x02) != 0x02){}

    driver->priv->reg->CR1 |= 0x200; /* stop */
}

void i2c_read(struct t_i2c_driver *driver, uint8_t *data)
{
	uint8_t counter = 0;
	driver->priv->reg->CR1 |= 0x400; /* send ack */
    driver->priv->reg->CR1 |= 0x100; /* start */
    while((driver->priv->reg->SR1 & 0x01) != 0x01){}

    driver->priv->reg->DR = (0xA << 1) | 1; /* Send address and write bit */


 //   driver->priv->reg->CR1 &= ~0x400; /* don't send ack */
    while((driver->priv->reg->SR1 & 0x02) != 0x02){}
//    while((driver->priv->reg->SR2 & 0x02) != 0x02){}
	driver->priv->reg->CR1 &= ~0x400; /* No ack */
	while(!(driver->priv->reg->SR1 & 0x40))
	{
		counter++;
	}

    driver->priv->reg->CR1 |= 0x200; /* stop */
}

void i2c_init(struct t_i2c_driver *config)
{
    config->priv = &priv[config->instance];
    config->priv->reg = (struct t_i2c_regs*)config->base_address_i2c;

    enable_clock(I2C_1);

    //struct t_clock_driver *clock_driver = get_clock_driver();

    config->priv->reg->CCR = 190;
    config->priv->reg->CR1 |= 1;
    config->priv->reg->CR1 |= 0x400; /* enable ack */

    config->priv->reg->CR2 |= 2;
}
