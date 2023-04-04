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

/* Status register masks */
#define NRF24L01_STATUS_TX_FULL_BIT_MASK      0x1
#define NRF24L01_STATUS_MAX_RT_BIT_MASK       0x10
#define NRF24L01_STATUS_TX_DS_BIT_MASK        0x20
#define NRF24L01_STATUS_RX_DR_BIT_MASK        0x40

enum e_nrf24l01_state
{
    power_on_reset,
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
    uint32_t timestamp_1;
    uint32_t timestamp_2;
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


//t_error_handling nrf24l01_transmit(struct t_nrf24l01_driver *driver, uint8_t address, uint8_t *data, uint8_t length)
void nrf24l01_transmit(struct t_nrf24l01_driver *driver)
{
    uint8_t status;
    uint8_t config_write;
    uint8_t config_read;
    uint32_t time;

    gpio_write(&pc13, true);

    /* RF channel */
    config_write = 2;
    nrf24l01_write_register_request(driver, RF_CH, &config_write, 1);
    while(nrf24l01_read_write_status(driver, NULL, &status) != ERROR_OK){}
    config_read = 0;
    nrf24l01_read_register_request(driver, RF_CH, 1);
    while(nrf24l01_read_write_status(driver, &config_read, &status) != ERROR_OK){}
    while (config_write != config_read){}

    /* Configure pipe 0 */
    config_write = 0;
    nrf24l01_write_register_request(driver, RX_PW_P0, &config_write, 1);
    while(nrf24l01_read_write_status(driver, NULL, &status) != ERROR_OK){}
    config_read = 0;
    nrf24l01_read_register_request(driver, RX_PW_P0, 1);
    while(nrf24l01_read_write_status(driver, &config_read, &status) != ERROR_OK){}
    while (config_write != config_read){}

    /* Configure pipe 1 */
    config_write = 4;
    nrf24l01_write_register_request(driver, RX_PW_P1, &config_write, 1);
    while(nrf24l01_read_write_status(driver, NULL, &status) != ERROR_OK){}
    config_read = 0;
    nrf24l01_read_register_request(driver, RX_PW_P1, 1);
    while(nrf24l01_read_write_status(driver, &config_read, &status) != ERROR_OK){}
    while (config_write != config_read){}

    /* Configure pipe 2 */
    config_write = 0;
    nrf24l01_write_register_request(driver, RX_PW_P2, &config_write, 1);
    while(nrf24l01_read_write_status(driver, NULL, &status) != ERROR_OK){}
    config_read = 0;
    nrf24l01_read_register_request(driver, RX_PW_P2, 1);
    while(nrf24l01_read_write_status(driver, &config_read, &status) != ERROR_OK){}
    while (config_write != config_read){}

    /* Configure pipe 3 */
    config_write = 0;
    nrf24l01_write_register_request(driver, RX_PW_P3, &config_write, 1);
    while(nrf24l01_read_write_status(driver, NULL, &status) != ERROR_OK){}
    config_read = 0;
    nrf24l01_read_register_request(driver, RX_PW_P3, 1);
    while(nrf24l01_read_write_status(driver, &config_read, &status) != ERROR_OK){}
    while (config_write != config_read){}

    /* Configure pipe 4 */
    config_write = 0;
    nrf24l01_write_register_request(driver, RX_PW_P4, &config_write, 1);
    while(nrf24l01_read_write_status(driver, NULL, &status) != ERROR_OK){}
    config_read = 0;
    nrf24l01_read_register_request(driver, RX_PW_P4, 1);
    while(nrf24l01_read_write_status(driver, &config_read, &status) != ERROR_OK){}
    while (config_write != config_read){}

    /* Configure pipe 5 */
    config_write = 0;
    nrf24l01_write_register_request(driver, RX_PW_P5, &config_write, 1);
    while(nrf24l01_read_write_status(driver, NULL, &status) != ERROR_OK){}
    config_read = 0;
    nrf24l01_read_register_request(driver, RX_PW_P5, 1);
    while(nrf24l01_read_write_status(driver, &config_read, &status) != ERROR_OK){}
    while (config_write != config_read){}

    /* RF low power */
    config_write = 0b00001110;
    nrf24l01_write_register_request(driver, RF_SETUP, &config_write, 1);
    while(nrf24l01_read_write_status(driver, NULL, &status) != ERROR_OK){}
    config_read = 0;
    nrf24l01_read_register_request(driver, RF_SETUP, 1);
    while(nrf24l01_read_write_status(driver, &config_read, &status) != ERROR_OK){}
    while (config_write != config_read){}

    /* Auto acknowledgement */
    config_write = 0b00000011;
    nrf24l01_write_register_request(driver, EN_AA, &config_write, 1);
    while(nrf24l01_read_write_status(driver, NULL, &status) != ERROR_OK){}
    config_read = 0;
    nrf24l01_read_register_request(driver, EN_AA, 1);
    while(nrf24l01_read_write_status(driver, &config_read, &status) != ERROR_OK){}
    while (config_write != config_read){}

    /* Enable pipe 0 */
    config_write = 0b00000011;
    nrf24l01_write_register_request(driver, EN_RXADDR, &config_write, 1);
    while(nrf24l01_read_write_status(driver, NULL, &status) != ERROR_OK){}
    config_read = 0;
    nrf24l01_read_register_request(driver, EN_RXADDR, 1);
    while(nrf24l01_read_write_status(driver, &config_read, &status) != ERROR_OK){}
    while (config_write != config_read){}

    /* Set retransmission */
    config_write = 0b01001111;
    nrf24l01_write_register_request(driver, SETUP_RETR, &config_write, 1);
    while(nrf24l01_read_write_status(driver, NULL, &status) != ERROR_OK){}
    config_read = 0;
    nrf24l01_read_register_request(driver, SETUP_RETR, 1);
    while(nrf24l01_read_write_status(driver, &config_read, &status) != ERROR_OK){}
    while (config_write != config_read){}

    /* Address = 4 bytes */
    config_write = 0b00000010;
    nrf24l01_write_register_request(driver, SETUP_AW, &config_write, 1);
    while(nrf24l01_read_write_status(driver, NULL, &status) != ERROR_OK){}
    config_read = 0;
    nrf24l01_read_register_request(driver, SETUP_AW, 1);
    while(nrf24l01_read_write_status(driver, &config_read, &status) != ERROR_OK){}
    while (config_write != config_read){}

    /* Flush buffer */
    driver->priv->data.buffer_write[1] = 0;
    driver->priv->data.length = 2;
    driver->priv->data.buffer_write[0] = FLUSH_RX;
    spi_transfer(driver->spi, &driver->spi_parameters, &driver->priv->data);
    while(nrf24l01_read_write_status(driver, NULL, &status) != ERROR_OK);

    /* Clear status flags */
    config_write = 0b01110000;
    nrf24l01_write_register_request(driver, STATUS, &config_write, 1);
    while(nrf24l01_read_write_status(driver, NULL, &status) != ERROR_OK){}

    /* Start listening */
//    config_write = 0b00001011;
//    nrf24l01_write_register_request(driver, CONFIG, &config_write, 1);
//    while(nrf24l01_read_write_status(driver, NULL, &status) != ERROR_OK){}
//    config_read = 0;
//    nrf24l01_read_register_request(driver, CONFIG, 1);
//    while(nrf24l01_read_write_status(driver, &config_read, &status) != ERROR_OK){}
//    while (config_write != config_read){}

    /* Set RX address, RX_$ADDR_P0 must be set to the sending addr for auto ack to work. */
    uint8_t data[4] = {0xE7,0xE7,0xE7,0xE7};
    nrf24l01_write_register_request(driver, RX_ADDR_P0, &data[0], 4);
    while(nrf24l01_read_write_status(driver, NULL, &status) != ERROR_OK){}
    for (uint8_t i = 0; i < 4; i++)
    {
        data[i] = 0;
    }
    nrf24l01_read_register_request(driver, RX_ADDR_P0, 4);
    while(nrf24l01_read_write_status(driver, &data[0], &status) != ERROR_OK){}

    for (uint8_t i = 0; i < 4; i++)
    {
        data[i] = 0;
    }

    /* Set TX address */
    data[0] = 0xE7;
    data[1] = 0xE7;
    data[2] = 0xE7;
    data[3] = 0xE7;
    nrf24l01_write_register_request(driver, TX_ADDR, &data[0], 4);
    while(nrf24l01_read_write_status(driver, NULL, &status) != ERROR_OK){}
    for (uint8_t i = 0; i < 4; i++)
    {
        data[i] = 0;
    }
    nrf24l01_read_register_request(driver, TX_ADDR, 4);
    while(nrf24l01_read_write_status(driver, &data[0], &status) != ERROR_OK){}

    /* Set RX address, RX_ADDR_P1. */
    data[0] = 0xD7;
    data[1] = 0xD7;
    data[2] = 0xD7;
    data[3] = 0xD7;
 
    nrf24l01_write_register_request(driver, RX_ADDR_P1, &data[0], 4);
    while(nrf24l01_read_write_status(driver, NULL, &status) != ERROR_OK){}
    for (uint8_t i = 0; i < 4; i++)
    {
        data[i] = 0;
    }
    nrf24l01_read_register_request(driver, RX_ADDR_P1, 4);
    while(nrf24l01_read_write_status(driver, &data[0], &status) != ERROR_OK){}

    for (uint8_t i = 0; i < 4; i++)
    {
        data[i] = 0;
    }

    /*********************  TX ***************************************/
    CE_HIGH

    /* Set TX and power up */
    config_write = 0b01111010;
    nrf24l01_write_register_request(driver, CONFIG, &config_write, 1);
    while(nrf24l01_read_write_status(driver, NULL, &status) != ERROR_OK){}
    config_read = 0;
    nrf24l01_read_register_request(driver, CONFIG, 1);
    while(nrf24l01_read_write_status(driver, &config_read, &status) != ERROR_OK){}

    systick_start();
    systick_get_parameters(&driver->priv->timestamp_1);
    time = driver->priv->timestamp_1;
    
    while((driver->priv->timestamp_1 - time) <= DELAY_1_5_MS)
    {
        systick_get_parameters(&time);
    }

    systick_stop();

    while(1)
    {
        /* Clear status */
        status = NRF24L01_STATUS_MAX_RT_BIT_MASK | NRF24L01_STATUS_TX_DS_BIT_MASK;
        nrf24l01_write_register_request(driver, STATUS, &status, 1);
        while(nrf24l01_read_write_status(driver, NULL, &status) != ERROR_OK){}

        /* Flush buffer */
        driver->priv->data.buffer_write[1] = 0;
        driver->priv->data.length = 2;
        driver->priv->data.buffer_write[0] = FLUSH_TX;
        spi_transfer(driver->spi, &driver->spi_parameters, &driver->priv->data);
        while(nrf24l01_read_write_status(driver, NULL, &status) != ERROR_OK);
        
        driver->priv->data.buffer_write[0] = W_TX_PAYLOAD;
        driver->priv->data.buffer_write[1] = 0xCA;
        driver->priv->data.buffer_write[2] = 0xFE;
        driver->priv->data.buffer_write[3] = 0xCA;
        driver->priv->data.buffer_write[4] = 0xFE;
        driver->priv->data.length = 5;
        spi_transfer(driver->spi, &driver->spi_parameters, &driver->priv->data);
        while(nrf24l01_read_write_status(driver, NULL, &status) != ERROR_OK);

    //    CE_HIGH
        gpio_write(&pc13, false);

        while(((status & NRF24L01_STATUS_TX_DS_BIT_MASK) == 0) &&
              ((status & NRF24L01_STATUS_MAX_RT_BIT_MASK) == 0))
        {
            nrf24l01_read_register_request(driver, CONFIG, 1);
            while(nrf24l01_read_write_status(driver, NULL, &status) != ERROR_OK);
        }

        gpio_write(&pc13, true);

        /* Observe TX */
        config_read = 0;
        nrf24l01_read_register_request(driver, OBSERVE_TX, 1);
        while(nrf24l01_read_write_status(driver, &config_read, &status) != ERROR_OK){}


        systick_start();
        systick_get_parameters(&driver->priv->timestamp_1);
        time = driver->priv->timestamp_1;

        while((driver->priv->timestamp_1 - time) <= DELAY_10_MS)
        {
            systick_get_parameters(&time);
        }

        gpio_write(&pb9, false);
        systick_stop();
    }
}



//t_error_handling nrf24l01_receive(struct t_nrf24l01_driver *driver, uint8_t address, uint8_t *data, uint8_t length)
void nrf24l01_receive(struct t_nrf24l01_driver *driver)
{
    uint8_t config_write;
    uint8_t config_read;
    uint8_t status;
    uint8_t payload[4];
    uint32_t time = 0;

    gpio_write(&pc13, true);

    driver->priv->data.buffer_read[0] = 0;
    driver->priv->data.buffer_read[1] = 0;
    driver->priv->data.buffer_read[2] = 0;
    driver->priv->data.buffer_read[3] = 0;
    driver->priv->data.buffer_read[4] = 0;
    driver->priv->data.buffer_read[5] = 0;
    driver->priv->data.buffer_read[6] = 0;

    /* RF channel */
    config_write = 2;
    nrf24l01_write_register_request(driver, RF_CH, &config_write, 1);
    while(nrf24l01_read_write_status(driver, NULL, &status) != ERROR_OK){}
    config_read = 0;
    nrf24l01_read_register_request(driver, RF_CH, 1);
    while(nrf24l01_read_write_status(driver, &config_read, &status) != ERROR_OK){}
    while (config_write != config_read){}

    /* Configure pipe 0 */
    config_write = 0;
    nrf24l01_write_register_request(driver, RX_PW_P0, &config_write, 1);
    while(nrf24l01_read_write_status(driver, NULL, &status) != ERROR_OK){}
    config_read = 0;
    nrf24l01_read_register_request(driver, RX_PW_P0, 1);
    while(nrf24l01_read_write_status(driver, &config_read, &status) != ERROR_OK){}
    while (config_write != config_read){}

    /* Configure pipe 1 */
    config_write = 4;
    nrf24l01_write_register_request(driver, RX_PW_P1, &config_write, 1);
    while(nrf24l01_read_write_status(driver, NULL, &status) != ERROR_OK){}
    config_read = 0;
    nrf24l01_read_register_request(driver, RX_PW_P1, 1);
    while(nrf24l01_read_write_status(driver, &config_read, &status) != ERROR_OK){}
    while (config_write != config_read){}

    /* Configure pipe 2 */
    config_write = 0;
    nrf24l01_write_register_request(driver, RX_PW_P2, &config_write, 1);
    while(nrf24l01_read_write_status(driver, NULL, &status) != ERROR_OK){}
    config_read = 0;
    nrf24l01_read_register_request(driver, RX_PW_P2, 1);
    while(nrf24l01_read_write_status(driver, &config_read, &status) != ERROR_OK){}
    while (config_write != config_read){}

    /* Configure pipe 3 */
    config_write = 0;
    nrf24l01_write_register_request(driver, RX_PW_P3, &config_write, 1);
    while(nrf24l01_read_write_status(driver, NULL, &status) != ERROR_OK){}
    config_read = 0;
    nrf24l01_read_register_request(driver, RX_PW_P3, 1);
    while(nrf24l01_read_write_status(driver, &config_read, &status) != ERROR_OK){}
    while (config_write != config_read){}

    /* Configure pipe 4 */
    config_write = 0;
    nrf24l01_write_register_request(driver, RX_PW_P4, &config_write, 1);
    while(nrf24l01_read_write_status(driver, NULL, &status) != ERROR_OK){}
    config_read = 0;
    nrf24l01_read_register_request(driver, RX_PW_P4, 1);
    while(nrf24l01_read_write_status(driver, &config_read, &status) != ERROR_OK){}
    while (config_write != config_read){}

    /* Configure pipe 5 */
    config_write = 0;
    nrf24l01_write_register_request(driver, RX_PW_P5, &config_write, 1);
    while(nrf24l01_read_write_status(driver, NULL, &status) != ERROR_OK){}
    config_read = 0;
    nrf24l01_read_register_request(driver, RX_PW_P5, 1);
    while(nrf24l01_read_write_status(driver, &config_read, &status) != ERROR_OK){}
    while (config_write != config_read){}

    /* RF low power */
    config_write = 0b00001110;
    nrf24l01_write_register_request(driver, RF_SETUP, &config_write, 1);
    while(nrf24l01_read_write_status(driver, NULL, &status) != ERROR_OK){}
    config_read = 0;
    nrf24l01_read_register_request(driver, RF_SETUP, 1);
    while(nrf24l01_read_write_status(driver, &config_read, &status) != ERROR_OK){}
    while (config_write != config_read){}

    /* Auto acknowledgement */
    config_write = 0b00000011;
    nrf24l01_write_register_request(driver, EN_AA, &config_write, 1);
    while(nrf24l01_read_write_status(driver, NULL, &status) != ERROR_OK){}
    config_read = 0;
    nrf24l01_read_register_request(driver, EN_AA, 1);
    while(nrf24l01_read_write_status(driver, &config_read, &status) != ERROR_OK){}
    while (config_write != config_read){}

    /* Enable pipe 0 */
    config_write = 0b00000011;
    nrf24l01_write_register_request(driver, EN_RXADDR, &config_write, 1);
    while(nrf24l01_read_write_status(driver, NULL, &status) != ERROR_OK){}
    config_read = 0;
    nrf24l01_read_register_request(driver, EN_RXADDR, 1);
    while(nrf24l01_read_write_status(driver, &config_read, &status) != ERROR_OK){}
    while (config_write != config_read){}

    /* Set retransmission */
    config_write = 0b01001111;
    nrf24l01_write_register_request(driver, SETUP_RETR, &config_write, 1);
    while(nrf24l01_read_write_status(driver, NULL, &status) != ERROR_OK){}
    config_read = 0;
    nrf24l01_read_register_request(driver, SETUP_RETR, 1);
    while(nrf24l01_read_write_status(driver, &config_read, &status) != ERROR_OK){}
    while (config_write != config_read){}

    /* Address = 4 bytes */
    config_write = 0b00000010;
    nrf24l01_write_register_request(driver, SETUP_AW, &config_write, 1);
    while(nrf24l01_read_write_status(driver, NULL, &status) != ERROR_OK){}
    config_read = 0;
    nrf24l01_read_register_request(driver, SETUP_AW, 1);
    while(nrf24l01_read_write_status(driver, &config_read, &status) != ERROR_OK){}
    while (config_write != config_read){}

    /* Flush buffer */
    driver->priv->data.buffer_write[1] = 0;
    driver->priv->data.length = 2;
    driver->priv->data.buffer_write[0] = FLUSH_RX;
    spi_transfer(driver->spi, &driver->spi_parameters, &driver->priv->data);
    while(nrf24l01_read_write_status(driver, NULL, &status) != ERROR_OK);

    /* Clear status flags */
    config_write = 0b01110000;
    nrf24l01_write_register_request(driver, STATUS, &config_write, 1);
    while(nrf24l01_read_write_status(driver, NULL, &status) != ERROR_OK){}

//    /* Start listening */
//    config_write = 0b00001011;
//    nrf24l01_write_register_request(driver, CONFIG, &config_write, 1);
//    while(nrf24l01_read_write_status(driver, NULL, &status) != ERROR_OK){}
//    config_read = 0;
//    nrf24l01_read_register_request(driver, CONFIG, 1);
//    while(nrf24l01_read_write_status(driver, &config_read, &status) != ERROR_OK){}
//    while (config_write != config_read){}
//
//    CE_HIGH

    /* Set RX address, RX_ADDR_P0 must be set to the sending addr for auto ack to work. */
    uint8_t data[4] = {0xD7,0xD7,0xD7,0xD7};
    nrf24l01_write_register_request(driver, RX_ADDR_P0, &data[0], 4);
    while(nrf24l01_read_write_status(driver, NULL, &status) != ERROR_OK){}
    for (uint8_t i = 0; i < 4; i++)
    {
        data[i] = 0;
    }
    nrf24l01_read_register_request(driver, RX_ADDR_P0, 4);
    while(nrf24l01_read_write_status(driver, &data[0], &status) != ERROR_OK){}

    for (uint8_t i = 0; i < 4; i++)
    {
        data[i] = 0;
    }

    /* Set TX address */
    data[0] = 0xD7;
    data[1] = 0xD7;
    data[2] = 0xD7;
    data[3] = 0xD7;
    nrf24l01_write_register_request(driver, TX_ADDR, &data[0], 4);
    while(nrf24l01_read_write_status(driver, NULL, &status) != ERROR_OK){}
    for (uint8_t i = 0; i < 4; i++)
    {
        data[i] = 0;
    }
    nrf24l01_read_register_request(driver, TX_ADDR, 4);
    while(nrf24l01_read_write_status(driver, &data[0], &status) != ERROR_OK){}

    /* Set RX address, RX_ADDR_P1. */
    data[0] = 0xE7;
    data[1] = 0xE7;
    data[2] = 0xE7;
    data[3] = 0xE7;
 
    nrf24l01_write_register_request(driver, RX_ADDR_P1, &data[0], 4);
    while(nrf24l01_read_write_status(driver, NULL, &status) != ERROR_OK){}
    for (uint8_t i = 0; i < 4; i++)
    {
        data[i] = 0;
    }
    nrf24l01_read_register_request(driver, RX_ADDR_P1, 4);
    while(nrf24l01_read_write_status(driver, &data[0], &status) != ERROR_OK){}

    for (uint8_t i = 0; i < 4; i++)
    {
        data[i] = 0;
    }

    /*********************  RX ***************************************/

    CE_HIGH

    /* Start listening */
    config_write = 0b00001011;
    nrf24l01_write_register_request(driver, CONFIG, &config_write, 1);
    while(nrf24l01_read_write_status(driver, NULL, &status) != ERROR_OK){}
    config_read = 0;
    nrf24l01_read_register_request(driver, CONFIG, 1);
    while(nrf24l01_read_write_status(driver, &config_read, &status) != ERROR_OK){}
    while (config_write != config_read){}

    systick_start();
    systick_get_parameters(&driver->priv->timestamp_1);
    time = driver->priv->timestamp_1;
    
    while((driver->priv->timestamp_1 - time) <= DELAY_1_5_MS)
    {
        systick_get_parameters(&time);
    }

    systick_stop();

    status = 0;

    while(1)
    {
        payload[0] = 0;
        payload[1] = 0;
        payload[2] = 0;
        payload[3] = 0;
    
        /* to test pipe bits */
        nrf24l01_read_register_request(driver, STATUS, 1);
        while(nrf24l01_read_write_status(driver, NULL, &status) != ERROR_OK){}

        if ((status & NRF24L01_STATUS_RX_DR_BIT_MASK) == NRF24L01_STATUS_RX_DR_BIT_MASK)
        {
            gpio_write(&pc13, false);
            driver->priv->data.buffer_write[0] = R_RX_PAYLOAD;
            driver->priv->data.buffer_write[1] = NOP;
            driver->priv->data.buffer_write[2] = NOP;
            driver->priv->data.buffer_write[3] = NOP;
            driver->priv->data.buffer_write[4] = NOP;
            driver->priv->data.length = 5;
            spi_transfer(driver->spi, &driver->spi_parameters, &driver->priv->data);

            while(nrf24l01_read_write_status(driver, &payload[0], &status) != ERROR_OK){}

            if ((status & NRF24L01_STATUS_RX_DR_BIT_MASK) == NRF24L01_STATUS_RX_DR_BIT_MASK)
            {
                while(nrf24l01_read_write_status(driver, &payload[0], &status) != ERROR_OK){}
            }

            /* Clear status */
            status = NRF24L01_STATUS_RX_DR_BIT_MASK;
            nrf24l01_write_register_request(driver, STATUS, &status, 1);
            while(nrf24l01_read_write_status(driver, NULL, &status) != ERROR_OK){}

            /* FIFO status */
            nrf24l01_write_register_request(driver, FIFO_STATUS, &status, 1);
            while(nrf24l01_read_write_status(driver, &config_read, &status) != ERROR_OK){}

            if ((payload[0] != 0xCA) || (payload[1] != 0xFE) || (payload[2] != 0xCA) || (payload[3] != 0xFE))
            {
                while(1)
                {
                    /* Wrong data received */
                }
            }
            gpio_write(&pc13, true);
        }
    }
}















void nrf24l01_initialization(struct t_nrf24l01_driver *config)
{
    /* Associate private instance to the driver */
    config->priv = &priv;

    /* Update the nrf24l01 state machine */
    config->priv->state = power_on_reset;

    /* Clear the private structure instance */
    memset(config->priv, 0, sizeof(struct t_nrf24l01_private));

    /* Locate registers to the base address */
    //config->priv->reg = (struct t_spi_regs*)config->base_address;

    /* Register SPI slave into the SPI driver*/
    spi_slave_register(&config->spi_parameters);

    /* Initialize local buffers */
    memset(&nrf24l01_buffer_tx[0], 0, sizeof(NRF24L01_BUFFER_TX_LENGTH));
    memset(&nrf24l01_buffer_rx[0], 0, sizeof(NRF24L01_BUFFER_RX_LENGTH));
    config->priv->data.buffer_write = &nrf24l01_buffer_tx[0];
    config->priv->data.buffer_read = &nrf24l01_buffer_rx[0];

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

    nrf24l01_write_register_request(config, CONFIG, &local_config, 1);
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

    nrf24l01_write_register_request(config, SETUP_AW, &local_config, 1);
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

    nrf24l01_write_register_request(config, RF_SETUP, &local_config, 1);
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

/*static void memcpy16(uint16_t *dest, uint16_t *src, size_t len)
{
    size_t cpy = len
    while (cpy)
    for (uint8_t index = 0; index < len; index++)
    {
        dest[index] = src[index];
    }
}*/

t_error_handling nrf24l01_write_register_request(struct t_nrf24l01_driver *driver,
                                                 uint8_t periph_reg,
                                                 uint8_t *write_value,
                                                 uint8_t byte_number)
{
    driver->priv->data.buffer_write[0] = W_REGISTER | periph_reg;
//    memcpy(&driver->priv->data.buffer_write[1], (uint16_t*)write_value, byte_number);
//    memcpy16(&driver->priv->data.buffer_write[1], (uint16_t*)write_value, byte_number);


    for (uint16_t index = 0; index < byte_number; index++)
    {
        driver->priv->data.buffer_write[1 + index] = write_value[index];
    }

//    driver->priv->data.buffer_write[1] = *write_value;
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
//            memcpy(&read_value[0], &driver->priv->data.buffer_read[1], driver->priv->data.length - 1);
            for (uint16_t index = 0; index < (driver->priv->data.length - 1); index++)
            {
                read_value[index] = driver->priv->data.buffer_read[index + 1];
            }




        }
    }
    return error;
}


/*

RX

memcpy(pipe0_reading_address, &address, addr_width);
_is_p0_rx = true; -------------------------------------------------------------+
                                                                               |
if (!(config_reg & _BV(PWR_UP))) {                                             |
        config_reg |= _BV(PWR_UP);                                             |
        write_register(NRF_CONFIG, config_reg);                                |
                                                                               |
delayMicroseconds(RF24_POWERUP_DELAY);                                         |
                                                                               |
config_reg |= _BV(PRIM_RX);                                                    |
write_register(NRF_CONFIG, config_reg);                                        |
write_register(NRF_STATUS, _BV(RX_DR) | _BV(TX_DS) | _BV(MAX_RT));             |
ce(HIGH);                                                                      |
                                                                               |
if (_is_p0_rx) {       <-------------------------------------------------------+
    write_register(RX_ADDR_P0, pipe0_reading_address, addr_width);
}

LOOP

if radio available":
// get implied RX FIFO empty flag from status byte
uint8_t pipe = (get_status() >> RX_P_NO) & 0x07;
if (pipe > 5)
return 0;

// If the caller wants the pipe number, include that
if (pipe_num)
*pipe_num = pipe;

status = _spi->transfer(R_RX_PAYLOAD);
while (data_len--) {
    *current++ = _spi->transfer(0xFF);
}

END LOOP

****************************************************************************************************
TX

write_register(RX_ADDR_P0, reinterpret_cast<uint8_t*>(&value), addr_width);
write_register(TX_ADDR, reinterpret_cast<uint8_t*>(&value), addr_width);


"Stop listening if needeed":
ce(LOW);
delayMicroseconds(static_cast<int>(txDelay));
if (ack_payloads_enabled) {
    flush_tx();
}
config_reg = static_cast<uint8_t>(config_reg & ~_BV(PRIM_RX));
write_register(NRF_CONFIG, config_reg);
if (ce_pin == csn_pin) {
    powerDown();
    powerUp();
}
 write_register(EN_RXADDR, static_cast<uint8_t>(read_register(EN_RXADDR) | _BV(pgm_read_byte(&child_pipe_enable[0])))); // Enable RX on pipe0

LOOP

write_payload(buf, len, multicast ? W_TX_PAYLOAD_NO_ACK : W_TX_PAYLOAD);
if (startTx) {
    ce(HIGH);
}
while (!(get_status() & (_BV(TX_DS) | _BV(MAX_RT)))) {
ce(LOW);
write_register(NRF_STATUS, _BV(RX_DR) | _BV(TX_DS) | _BV(MAX_RT));
END LOOP

*/


