/*
 * lld_i2c.h
 *
 * Created on: Aug 23, 2021
 * Author: Stephane Amans
 */

#ifndef I2C_H_
#define I2C_H_

/* Include files:        */
#include <stdint.h>
#include <stdbool.h>

//#include "configuration_module_activation.h"
//#include "configuration_usart.h"
#include "bsp.h"
#include "lld_clock.h"
//#include "lld_dma.h"
//#include "lld_nvic.h"*/
#include "regbase_i2c.h"


/* Functions prototypes:                */

/** Configure USART (baudrate, interruptions, mode, ...):
 *
 * \param driver: Driver structure
 * \param config: Configuration structure.
 *
 * \return: t_error_handling code or ERROR_OK.
 *
 */
t_error_handling i2c_init(void);
void i2c_write(void);
void i2c_write_loop(void);
void i2c_read(uint8_t *data);

#endif /* I2C_H_ */
