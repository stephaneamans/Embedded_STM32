/*
 *        lld_usart.h
 *
 *    Created on: Apr 12, 2019
 *    Author: Stéphane Amans
 */
#ifndef LLD_USART_H_
#define LLD_USART_H_


/* Include files:        */
#include <stdint.h>

#include "lld_clock.h"
#include "regbase_usart.h"
#include "lld_nvic.h"


/*
1. 1 stop bit: This is the default value.
2. 2 stop bits: This is supported by normal USART, single-wire and modem modes.
3. 0.5 stop bit: To be used when receiving data in Smartcard mode.
4. 1.5 stop bits: To be used when transmitting and receiving data in Smartcard mode.
*/


/* USART initialization structure definition :        */
typedef struct
{
    uint32_t baud_rate;
    uint8_t length;
    uint8_t wake_up;
    uint8_t parity;
    uint8_t stop;
    uint8_t clock_modes;
    uint8_t cts_rts;
    uint8_t dma;
    struct
    {
        uint8_t type;
        void(*callback_parity_err)();
        void(*callback_tx_err)();
        void(*callback_tx_complete_err)();
        void(*callback_rx_err)();
        void(*callback_idle)();
        void(*callback_cts)();
        void(*callback_error_irq)();
    }irq;
}t_usart_cfg;


/* USARTx_CRx, Peripheral configuration register group definition:        */
/* Parity configuration :               */
#define	PARITY_EVEN             0x02
#define	PARITY_ODD              0x03

/* Interruptions configuration :        */
#define	PARITY_ERR_IRQ          0x01
#define	TX_ERR_IRQ              0x02
#define TX_COMPLETE_IRQ         0x04
#define RX_ERR_IRQ              0x08
#define IDLE_IRQ                0x10
#define CTS_IRQ	                0x20
#define ERROR_IRQ               0x40

/* Stop bits configuration :            */
#define	ONE_STOP_BIT            0x00
#define HALF_STOP_BIT           0x01
#define TWO_STOP_BITS           0x02
#define ONE_HALF_STOP_BIT       0x04

/* Clock pin bits configuration :       */
#define	LOW_AND_FIRST_EDGE      0x04
#define LOW_AND_SECOND_EDGE     0x05
#define HIGH_AND_FIRST_EDGE     0x06
#define HIGH_AND_SECOND_EDGE    0x07

/* CTS and RTS bits configuration :     */
#define RTS_ENABLE              0x01
#define CTS_ENABLE              0x02
#define RTS_CTS_ENABLE          0x03

/* DMA bits configuration :             */
#define DMA_RX_ENABLE           0x01
#define DMA_TX_ENABLE           0x02
#define DMA_RX_TX_ENABLE        0x03


/* Functions prototypes:                */

/** Disnable USART port clock.
 *
 * \param usart : address of the USART to clock.
 *
 * \return : Error code or OK.
 *
 */
uint8_t usart_disable_clock(USART_TypeDef *usart);


/** Configure USART (baudrate, interruptions, mode, ...):
 *
 * \param usart: Pointer to the usart register base.
 * \param cfg: Configuration structure.
 *
 * \return : Error code or 0 if OK.
 *
 */
uint8_t usart_init(USART_TypeDef *usart, t_usart_cfg *cfg);


/* Pointer callback function table prototype	*/
void (*USART_callback[2])(uint32_t pinNumb);

#endif /* LLD_USART_H_ */
