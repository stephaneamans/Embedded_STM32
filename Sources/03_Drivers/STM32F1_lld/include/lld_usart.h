/*
 *        lld_usart.h
 *
 *    Created on: Apr 12, 2019
 *    Author: St�phane Amans
 */
#ifndef LLD_USART_H_
#define LLD_USART_H_


/* Include files:        */
#include <stdint.h>

#include "configuration_module_activation.h"
#include "configuration_usart.h"
#include "lld_clock.h"
#include "regbase_usart.h"
#include "lld_nvic.h"


/*
1. 1 stop bit: This is the default value.
2. 2 stop bits: This is supported by normal USART, single-wire and modem modes.
3. 0.5 stop bit: To be used when receiving data in Smartcard mode.
4. 1.5 stop bits: To be used when transmitting and receiving data in Smartcard mode.
*/


typedef enum
{
    bits_data_8    = 0,
    bits_data_9    = 1
}bits_data;


typedef enum
{
    idle_line     = 0,
    address_mark  = 1
}wakeup_method;


typedef enum
{
    parity_none = 0x00,
    parity_even = 0x02,
    parity_odd  = 0x03
}parity_sel;


typedef enum
{
    one      = 0x00,
    half     = 0x01,
    two      = 0x02,
    one_half = 0x04
}stop_bits;


typedef enum
{
    low_and_first_edge   = 0x04,
	low_and_second_edge  = 0x05,
	high_and_first_edge  = 0x06,
	high_and_second_edge = 0x07
}clock;


typedef enum
{
    rts     = 0x01,
    cts     = 0x02,
    rts_cts = 0x03
}cts_rts;


//typedef enum
//{
//	no_usart_irq_dma = 0x00,
//    parity_err_irq   = 0x01,
//    tx_err_irq       = 0x02,
//    tx_complete_irq  = 0x04,
//    rx_err_irq       = 0x08,
//    idle_irq         = 0x10,
 //   cts_irq	         = 0x20,
//    error_irq        = 0x40,
//	dma_rx_tx        = 0x83
//}irq_dma_type;


typedef enum
{
	no_usart_irq_dma = 0x00,
	idle_irq         = 0x01,
	rx_not_empty_irq = 0x02,
	tx_complete_irq  = 0x04,
	tx_empty_irq     = 0x08,
    parity_err_irq   = 0x10,
	cts_irq	         = 0x20,
    error_irq        = 0x40,
	dma_rx_tx        = 0xC0
}irq_dma_type;


/* USART initialization structure definition :        */
typedef struct
{
	USART_TypeDef *usart;
    uint32_t baud_rate;
    bits_data length;
    wakeup_method wake_up;
    parity_sel parity;
    stop_bits stop;
    clock clock_modes;
    cts_rts cts_rts;
    struct
    {
    	irq_dma_type type;
    	irq_priority priority;
        void(*callback)(void);
    }irq_dma;
}t_usart_cfg;


typedef struct
{
	USART_TypeDef *usart;
    uint32_t baud_rate;
    struct
    {
    	irq_dma_type type;
    }irq;
}t_usart_drv;


/* USARTx_CRx, Peripheral configuration register group definition:        */

/* DMA bits configuration :             */
#define DMA_RX_ENABLE           0x01
#define DMA_TX_ENABLE           0x02
#define DMA_RX_TX_ENABLE        0x03


/* Functions prototypes:                */

/** Configure USART (baudrate, interruptions, mode, ...):
 *
 * \param cfg: Configuration structure.
 *
 * \return: Error code or 0 if OK.
 *
 */
t_error_handling usart_init(t_usart_cfg *cfg);


/** Send data via USART.
 *
 * \param usart: address of the USART to use for transfert.
 * \param data: data to send.
 *
 * \return: Error code or OK.
 *
 */
t_error_handling usart_send(USART_TypeDef *usart, uint8_t data);


/** Disable USART port clock.
 *
 * \param usart: address of the USART to clock.
 *
 * \return: Error code or OK.
 *
 */
t_error_handling usart_disable_clock(USART_TypeDef *usart);

void usart_test(void);


/* Pointer callback function table prototype	*/
void (*usart_callback[3])(void);

#endif /* LLD_USART_H_ */
