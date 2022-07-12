/*
 * spi.h
 *
 * Created on: Jun 25, 2021
 * Author: Stephane Amans
 */

#ifndef SPI_H_
#define SPI_H_

/* Include files:        */
#include <stdint.h>
#include <stdbool.h>

#include "configuration_module_activation.h"
#include "configuration_spi.h"

#include "gpio.h"

#include "lld_clock.h"

enum t_frame_length
{
    spi_frame_8_bits,
    spi_frame_16_bits
};

enum t_frame_direction
{
    spi_frame_msb_first,
    spi_frame_lsb_first
};

enum t_clock_phase
{
    spi_clk_first,
    spi_clk_second
};

enum t_clock_polarity
{
    spi_clk_rising,
    spi_clk_falling
};


struct t_spi_data
{
    uint16_t *write_buffer;
    uint16_t *read_buffer;
    uint32_t length;
};

struct t_spi_slave
{
    struct t_gpio_driver *cs;
    uint16_t freq_khz;
    enum t_frame_length frame_length;
    enum t_frame_direction frame_direction;
    enum t_clock_phase clock_phase;
    enum t_clock_polarity clock_polarity;
    uint8_t id;
};


/* SPI configuration structure definition */
struct t_spi_config
{
    uintptr_t base_address;
    enum t_peripheral peripheral;
    uint8_t instance;
};


/* SPI driver structure definition :        */
struct t_spi_driver
{
    const struct t_spi_config *config;
    struct t_spi_private *priv;
};


/* Functions prototypes:                */


/** Record a SPI slave into the internal database.
 *.
 * \param slave: Pointer to the slave configuration.
 *
 * \return : void.
 *
 */
void spi_record_slave(struct t_spi_slave *slave);


/** Polling function to perform a SPI transfer.
 *
 * \param driver: Pointer to the SPI driver.
 * \param slave: Pointer to the slave configuration..
 * \param data: Pointer to the data buffer.
 *
 * \return : Error code or ERROR_OK.
 *
 */
t_error_handling spi_transfer(struct t_spi_driver *driver, struct t_spi_slave *slave, struct t_spi_data *data);


/** SPI initialization.
 *
 * \param driver: Pointer to the SPI driver structure.
 * \param config: Pointer to the configuration structure.
 *
 * \return void.
 *
 */
void spi_init(struct t_spi_driver *driver, const struct t_spi_config *config);

#endif /* SPI_H_ */
