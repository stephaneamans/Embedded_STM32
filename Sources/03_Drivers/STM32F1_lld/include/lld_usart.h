/*
 * lld_usart.h
 *
 * Created on: Apr 12, 2019
 * Author: Stephane Amans
 */

#ifndef LLD_USART_H_
#define LLD_USART_H_

/* Include files:        */
#include <stdint.h>
#include <stdbool.h>

#include "configuration_module_activation.h"
#include "configuration_usart.h"
#include "lld_clock.h"
#include "lld_dma.h"
#include "lld_nvic.h"
#include "regbase_usart.h"

#define USART_IP_NUMBER          2

#define USART_BUFFER_TX_LENGTH 256
#define USART_BUFFER_RX_LENGTH 256

#define USART_BUFFER_LENGTH 256

enum bits_data
{
    bits_data_8    = 0x0000,
    bits_data_9    = 0x1000
};

enum parity_sel
{
    parity_none = 0x0000,
    parity_even = 0x0400,
    parity_odd  = 0x0600
};

enum stop_bits
{
    one      = 0x0000,
    half     = 0x0100,
    two      = 0x0200,
    one_half = 0x0300
};

enum mode
{
	usart_poll = 0,
	usart_dma  = 1,
	usart_irq = 2,
};

/* USART configuration structure definition :        */
struct t_usart_config
{
	USART_TypeDef *reg;
    uint32_t baudrate;
    enum bits_data length;
    enum parity_sel parity;
    enum stop_bits stop;
    enum mode mode;
    struct
    {
    	enum irq_priority priority;
    	struct t_dma_driver *tx_dma_channel;
    	struct t_dma_driver *rx_dma_channel;
    }irq_dma;
};

/* USART driver structure definition :        */
struct t_usart_driver
{
	USART_TypeDef *reg;
	uint8_t uart_number;
	struct t_usart_private *priv;
//};

struct t_dma_methods
{
/** Pointer to send data via USART.
 * This will call static functions send_usart_poll, send_usart_irq
 * or send_usart_dma function of the configuration. This pointer is affected
 * at the init of the driver.
 *
 * \param usart: address of the USART driver.
 * \param data_buffer: Pointer to the data buffer to send.
 * \param data_length: Data length.
 *
* \return: t_error_handling code or OK.
 *
 */
    t_error_handling (*transmit)(struct t_usart_driver *driver, uint8_t *data_buffer, uint32_t data_length);

/** Pointer to receive data via USART.
 * This will call static functions receive_usart_poll, receive_usart_irq
 * or receive_usart_dma function of the configuration. This pointer is affected
 * at the init of the driver.
 *
 * \param usart: address of the USART driver.
 * \param data_buffer: Pointer to the data receive buffer.
 *
 * \return: t_error_handling code or OK.
 *
 */
    t_error_handling (*receive)(struct t_usart_driver *driver, uint8_t *data_buffer, uint32_t data_length);

/** Get transmission complete flag in DMA mode.
*
* \param usart: Pointer to the USART driver.
*
*
* \return: bool .
*
*/
    bool (*tx_complete)(struct t_usart_driver *driver);

/** Get reception complete flag in DMA mode.
*
* \param usart: Pointer to the USART driver.
*
*
* \return: bool.
*
*/
    bool (*rx_complete)(struct t_usart_driver *driver);

}methods;
};

/* USARTx_CRx, Peripheral configuration register group definition:        */

/* DMA bits configuration :             */
#define DMA_RX_ENABLE           0x01
#define DMA_TX_ENABLE           0x02
#define DMA_RX_TX_ENABLE        0x03


/* Functions prototypes:                */

/** Configure USART (baudrate, interruptions, mode, ...):
 *
 * \param driver: Driver structure
 * \param config: Configuration structure.
 *
 * \return: t_error_handling code or OK.
 *
 */
t_error_handling usart_init(struct t_usart_driver *driver, struct t_usart_config *config);


/** Get USART RX transfer status:
 *
 * \param driver: Driver structure.
 *
 * \return: bool : RX transfer status.
 *
 */
bool usart_get_rx_transfer_status(struct t_usart_driver *driver);

/** Get USART TX transfer status:
 *
 * \param driver: Driver structure.
 *
  * \return: bool : TX transfer status.
 *
 */
bool usart_get_tx_transfer_status(struct t_usart_driver *driver);

/** Get USART error status:
 *
 * \param driver: Driver structure.
 *
 * \return: t_error_handling code or OK.
 *
 */
t_error_handling usart_get_error_status(struct t_usart_driver *driver);


/** Return USART driver:
 *
 * \param usart_number: number of the usart driver, must be between 1 and the maximum number of usart IPs available in the IC.
 *
 * \return: Pointer to the driver or 0 if error.
 *
 */
struct t_usart_driver *usart_get_driver(uint8_t usart_number);

/** Disable USART port clock.
 *
 * \param usart: address of the USART to clock.
 *
 * \return: t_error_handling code or OK.
 *
 */
t_error_handling usart_disable_clock(struct t_usart_driver *driver);

#endif /* LLD_USART_H_ */
