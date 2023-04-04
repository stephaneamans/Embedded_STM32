/*
 * nrf24l01.h
 *
 * Created on: Aug 21, 2022
 * Author: Stephane Amans
 *
 */

#ifndef NRF24L01_H_
#define NRF24L01_H_

/* Include files:        */
#include <stdint.h>
#include <stdbool.h>

#include "lld_spi.h"

#include "gpio.h"
extern struct t_gpio_driver pb9;

void test(void);

/* Enum used to configure the CRC size. */
enum e_crc_size
{
    nrf24l01_none,
    nrf24l01_1byte,
    nrf24l01_2bytes,
};

/* Enum used to configure the address width. */
enum e_address_width
{
    nrf24l01_3bytes,
    nrf24l01_4bytes,
    nrf24l01_5bytes,
};

/* Enum used to configure air data rate. */
enum e_nrf24l01_air_data_rate
{
    nrf24l01_air_datarate_1mbps,
    nrf24l01_air_datarate_2mbps
};

/* Enum used to configure the output power in transmit mode. */
enum e_nrf24l01_tx_rf_output_power
{
    nrf24l01_m18dBm,
    nrf24l01_m12dBm,
    nrf24l01_m6dBm,
    nrf24l01_0dBm,
};

/* NRF24L01 IC configuration structure definition. */
struct t_nrf24l01_ic_configuration
{
    bool mask_rx_dr_irq;
    bool mask_tx_ds_irq;
    bool mask_max_rt_irq;
    enum e_crc_size crc;
    bool startup_receiver;
    enum e_address_width address_width;
};

/* NRF24L01 RF configuration structure definition. */
struct t_nrf24l01_rf_configuration
{
    enum e_nrf24l01_air_data_rate air_data_rate;
    enum e_nrf24l01_tx_rf_output_power tx_output_power;
    bool high_current;
};

/* NRF24L01 driver structure definition, it contains the global configuration setting fields of the module. */
struct t_nrf24l01_driver
{
    uint8_t instance;
    struct t_spi_driver *spi;
    struct t_gpio_driver *cs;
    struct t_gpio_driver *ce;
    struct t_gpio_driver *irq;
    struct t_spi_slave spi_parameters;
    struct t_nrf24l01_ic_configuration ic_setup;
    struct t_nrf24l01_rf_configuration rf_setup;
    struct t_nrf24l01_private *priv;
};

/* Functions prototypes:                */



t_error_handling nrf24l01_read_register_request(struct t_nrf24l01_driver *driver,
                                                uint8_t periph_reg,
                                                uint8_t byte_number);


t_error_handling nrf24l01_write_register_request(struct t_nrf24l01_driver *driver,
                                                 uint8_t periph_reg,
                                                 uint8_t *value,
                                                 uint8_t byte_number);


t_error_handling nrf24l01_read_write_status(struct t_nrf24l01_driver *driver,
                                            uint8_t *read_value,
                                            uint8_t *status);



//t_error_handling nrf24l01_transmit(struct t_nrf24l01_driver *driver, uint8_t address, uint8_t *data, uint8_t length);
void nrf24l01_transmit(struct t_nrf24l01_driver *driver);
void nrf24l01_receive(struct t_nrf24l01_driver *driver);


/** Configure NRF24L01 with the generated parameters.
 *
 * \param config: Pointer to the NRF24L01 driver structure.
 *
 * \return void.
 *
 */
void nrf24l01_configure(struct t_nrf24l01_driver *config);

/** NRF24L01 initialization.
 *
 * \param config: Pointer to the NRF24L01 driver structure.
 *
 * \return void.
 *
 */
void nrf24l01_initialization(struct t_nrf24l01_driver *config);

#endif /* NRF24L01_H_ */
