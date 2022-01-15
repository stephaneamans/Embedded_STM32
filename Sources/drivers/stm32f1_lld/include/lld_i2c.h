/*
 * lld_i2c.h
 *
 * Created on: Jul 28, 2022
 * Author: Stephane Amans
 */
#ifndef LLD_I2C_H_
#define LLD_I2C_H_

/* Include files:        */
#include <stdbool.h>
#include <stdint.h>

#include "configuration_soc.h"

/* Memory or peripheral data length. */
//enum t_dma_data_type
//{
//    dma_8_bits,
//    dma_16_bits,
//    dma_32_bits
//};

/* I2C driver structure definition :        */
struct t_i2c_driver
{
    uintptr_t base_address_i2c;
    enum t_peripheral peripheral;
    uint16_t instance;
    struct t_i2c_private *priv;
};

/** Send an I2C read command:
 *
 * \param driver: Pointer to the I2C driver structure.
 * \param client: Pointer to the data.
 * 
 * \return: void.
 *
 */
void i2c_read(struct t_i2c_driver *driver, uint8_t *data);

/** Send an I2C write command:
 *
 * \param driver: Pointer to the I2C driver structure.
 * \param client: Pointer to the data.
 * 
 * \return: void.
 *
 */
void i2c_write(struct t_i2c_driver *driver, uint8_t *data);

/** Configure I2C:
 *
 * \param config         : Pointer to the DMA driver structure;
 *
 * \return: void.
 *
 */
void i2c_init(struct t_i2c_driver *config);

#endif /* LLD_I2C_H_ */
