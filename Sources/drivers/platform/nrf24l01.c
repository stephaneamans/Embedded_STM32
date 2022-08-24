/*
 * nrf24l01.c
 *
 * Created on: Aug 21, 2022
 * Author: Stephane Amans
 *
 */

/* Include files        */
#include <string.h>

#include "nrf24l01.h"
#include "fault.h"

#include "platform_configuration.h"

/* Defines */

/* NRF24L01 commands */
#define R_REGISTER          0x00
#define W_REGISTER          0x20
#define R_RX_PAYLOAD        0x61
#define W_TX_PAYLOAD        0xA0
#define FLUSH_TX            0xE1
#define FLUSH_RX            0xE2
#define REUSE_TX_PL         0xE3
#define ACTIVATE            0x50
#define R_RX_PL_WID         0x60
#define W_ACK_PAYLOAD       0xA8
#define W_TX_PAYLOAD_NOACK  0xB0
#define NOP                 0xFF

/* NRF24L01 internal registers */
#define CONFIG          0x00
#define EN_AA           0x01
#define EN_RXADDR       0x02
#define SETUP_AW        0x03
#define SETUP_RETR      0x04
#define RF_CH           0x05
#define RF_SETUP        0x06
#define STATUS          0x07
#define OBSERVE_TX      0x08
#define CD              0x09
#define RX_ADDR_P0      0x0A
#define RX_ADDR_P1      0x0B
#define RX_ADDR_P2      0x0C
#define RX_ADDR_P3      0x0D
#define RX_ADDR_P4      0x0E
#define RX_ADDR_P5      0x0F
#define TX_ADDR         0x10
#define RX_PW_P0        0x11
#define RX_PW_P1        0x12
#define RX_PW_P2        0x13
#define RX_PW_P3        0x14
#define RX_PW_P4        0x15
#define RX_PW_P5        0x16
#define FIFO_STATUS     0x17
#define DYNPD           0x1c
#define FEATURE         0x1d

/* Config register masks */
#define NRF24L01_CONFIG_PRIM_RX_BIT_MASK      0x1
#define NRF24L01_CONFIG_PWR_UP_BIT_MASK       0x2
#define NRF24L01_CONFIG_CRCO_BIT_MASK         0x4
#define NRF24L01_CONFIG_EN_CRC_BIT_MASK       0x8
#define NRF24L01_CONFIG_MASK_MAX_RT_BIT_MASK  0x10
#define NRF24L01_CONFIG_MASK_TX_DS_BIT_MASK   0x20
#define NRF24L01_CONFIG_MASK_RX_DR_BIT_MASK   0x40

/* Setup_AW register masks */
#define NRF24L01_SETUP_AW_3_BYTES_MASK      0x1
#define NRF24L01_SETUP_AW_4_BYTES_MASK      0x2
#define NRF24L01_SETUP_AW_5_BYTES_MASK      0x3

/* RF_Setup register masks */
#define NRF24L01_RF_SETUP_LNA_HCURR_BIT_MASK      0x1
#define NRF24L01_RF_SETUP_RF_PWR_M12DBM_BIT_MASK  0x2
#define NRF24L01_RF_SETUP_RF_PWR_M6DBM_BIT_MASK   0x4
#define NRF24L01_RF_SETUP_RF_PWR_0DBM_BIT_MASK    0x6
#define NRF24L01_RF_SETUP_RF_DR_2MBPS_BIT_MASK    0x8


enum e_nrf24l01_state
{
    power_down,
    standby_1,
    standby_2,
    tx_mode,
    rx_mode,
};

/* NRF24L01 private structure definition :        */
struct t_nrf24l01_private
{
    struct t_spi_data data;
    enum e_nrf24l01_state state;
//    struct t_spi_regs *reg;
//    struct t_spi_slave *slave;
//    uint32_t clock_frequency;
//    uint16_t freq_khz;
//    uint8_t last_config;
//    uint16_t *write_buffer;
//    uint16_t *read_buffer;
//    uint32_t buffer_length;
//    uint16_t buffer_index;
//    struct t_dma_client spi_dma_tx;
//    struct t_dma_client spi_dma_rx;
//    struct
//    {
//        void (*transfer)(struct t_spi_driver *driver, struct t_spi_slave *slave);
//    }methods;
};

/* Static NRF24L01 private structure instance. */
static struct t_nrf24l01_private priv;
static uint8_t nrf24l01_buffer_tx[NRF24L01_BUFFER_TX_LENGTH];
static uint8_t nrf24l01_buffer_rx[NRF24L01_BUFFER_RX_LENGTH];

/* Set chip enable pin in a low state. */
#define CE_LOW gpio_write(driver->ce, false);

/* Set chip enable pin in a high state. */
#define CE_HIGH gpio_write(driver->ce, true);

void nrf24l01_initialization(struct t_nrf24l01_driver *config)
{
    /* Associate private instance to the driver */
    config->priv = &priv;

    /* Clear the private structure instance */
    memset(config->priv, 0, sizeof(struct t_nrf24l01_private));

    /* Locate registers to the base address */
    //config->priv->reg = (struct t_spi_regs*)config->base_address;

    /* Register SPI slave into the SPI driver*/
    spi_slave_register(&config->spi_parameters);

    /* Initialize local buffers */
    memset(&nrf24l01_buffer_tx[0], 0, sizeof(NRF24L01_BUFFER_TX_LENGTH));
    memset(&nrf24l01_buffer_rx[0], 0, sizeof(NRF24L01_BUFFER_RX_LENGTH));
    config->priv->data.buffer_write = (uint16_t *)&nrf24l01_buffer_tx[0];
    config->priv->data.buffer_read = (uint16_t *)&nrf24l01_buffer_rx[0];

    /* CS is set high */
    gpio_write(config->spi_parameters.cs, true);

    /* CE set low */
    gpio_write(config->ce, false);
}

void nrf24l01_configure(struct t_nrf24l01_driver *config)
{
    uint8_t local_config = 0;

    if(config->ic_setup.startup_receiver)
    {
         local_config |= NRF24L01_CONFIG_PRIM_RX_BIT_MASK;
    }

    if(config->ic_setup.crc == nrf24l01_1byte)
    {
        local_config |= NRF24L01_CONFIG_EN_CRC_BIT_MASK;
    }

    else if(config->ic_setup.crc == nrf24l01_2bytes)
    {
        local_config |= NRF24L01_CONFIG_EN_CRC_BIT_MASK | NRF24L01_CONFIG_CRCO_BIT_MASK;
    }

    if(config->ic_setup.mask_max_rt_irq)
    {
         local_config |= NRF24L01_CONFIG_MASK_MAX_RT_BIT_MASK;
    }

    if(config->ic_setup.mask_tx_ds_irq)
    {
        local_config |= NRF24L01_CONFIG_MASK_TX_DS_BIT_MASK;
    }

    if(config->ic_setup.mask_rx_dr_irq)
    {
        local_config |= NRF24L01_CONFIG_MASK_RX_DR_BIT_MASK;
    }

    nrf24l01_write_register_request(config, CONFIG, local_config, 1);
    while(nrf24l01_read_write_status(config, NULL, NULL) != ERROR_OK){}

    if(config->ic_setup.address_width == nrf24l01_3bytes)
    {
        local_config = NRF24L01_SETUP_AW_3_BYTES_MASK;
    }

    else if(config->ic_setup.address_width == nrf24l01_4bytes)
    {
        local_config = NRF24L01_SETUP_AW_4_BYTES_MASK;
    }

    else if(config->ic_setup.address_width == nrf24l01_5bytes)
    {
        local_config = NRF24L01_SETUP_AW_5_BYTES_MASK;
    }

    nrf24l01_write_register_request(config, SETUP_AW, local_config, 1);
    while(nrf24l01_read_write_status(config, NULL, NULL) != ERROR_OK){}

    local_config = 0;

    if(config->rf_setup.high_current)
    {
        local_config |= NRF24L01_RF_SETUP_LNA_HCURR_BIT_MASK;
    }

    if(config->rf_setup.tx_output_power == nrf24l01_m12dBm)
    {
        local_config |= NRF24L01_RF_SETUP_RF_PWR_M12DBM_BIT_MASK;
    }

    else if(config->rf_setup.tx_output_power == nrf24l01_m6dBm)
    {
        local_config |= NRF24L01_RF_SETUP_RF_PWR_M6DBM_BIT_MASK;
    }

    else if(config->rf_setup.tx_output_power == nrf24l01_0dBm)
    {
        local_config |= NRF24L01_RF_SETUP_RF_PWR_0DBM_BIT_MASK;
    }

    if(config->rf_setup.air_data_rate == nrf24l01_air_datarate_2mbps)
    {
        local_config |= NRF24L01_RF_SETUP_RF_DR_2MBPS_BIT_MASK;
    }

    nrf24l01_write_register_request(config, RF_SETUP, local_config, 1);
    while(nrf24l01_read_write_status(config, NULL, NULL) != ERROR_OK){}
};

t_error_handling nrf24l01_read_register_request(struct t_nrf24l01_driver *driver,
                                                uint8_t periph_reg,
                                                uint8_t byte_number)
{
    driver->priv->data.buffer_write[0] = R_REGISTER | periph_reg;
    driver->priv->data.length = byte_number + 1;

    return spi_transfer(driver->spi, &driver->spi_parameters, &driver->priv->data);
}

t_error_handling nrf24l01_write_register_request(struct t_nrf24l01_driver *driver,
                                                 uint8_t periph_reg,
                                                 uint8_t value,
                                                 uint8_t byte_number)
{
    driver->priv->data.buffer_write[0] = W_REGISTER | periph_reg;
    driver->priv->data.buffer_write[1] = value;
    driver->priv->data.length = byte_number + 1;

    return spi_transfer(driver->spi, &driver->spi_parameters, &driver->priv->data);
}

t_error_handling nrf24l01_read_write_status(struct t_nrf24l01_driver *driver,
                                            uint8_t *read_value,
                                            uint8_t *status)
{
    t_error_handling error;
    error = spi_transfer_status(driver->spi, &driver->spi_parameters);

    if(error == ERROR_OK)
    {
        if(status != NULL)
        {
            *status = driver->priv->data.buffer_read[0];
        }
        if(read_value != NULL)
        {
            memcpy(&read_value[0], &driver->priv->data.buffer_read[1], driver->priv->data.length);
        }
    }
    return error;
}
