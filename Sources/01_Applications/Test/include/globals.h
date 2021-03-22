/*
 * globals.h
 *
 * Created on: Apr 12, 2019
 * Author: Stephane Amans
 */
#ifndef GLOBALS_H_
#define GLOBALS_H_

/* IC parameters:   */
#define MAX_GPIO_PIN            16
#define CLOCK_FREQ_MHZ          8000000

#define TOTAL_USART_IP          2




typedef enum{
    OK                            = 0,
    ERROR_WRONG_VALUE_PASSED      = 1,
    ERROR_WRONG_CLOCK_SET         = 2,
	ERROR_WRONG_DATA_TYPE         = 3,
	ERROR_DRIVER_NOT_INITIALIZED  = 4,
	ERROR_UNDEFINED               = 5,

	ERROR_USART_NOT_READY_TO_SEND = 10,
	ERROR_USART_NO_DATA_RECEIVED  = 11,
	ERROR_USART_PARITY            = 12,
	ERROR_USART_FRAMING           = 13,
	ERROR_USART_NOISE             = 14,
	ERROR_USART_OVERRUN           = 15,

    ERROR_QUEUE_FULL              = 20,
    ERROR_QUEUE_EMPTY             = 21,

	ERROR_TEST_FAIL               = 30

}t_error_handling;

#endif /* GLOBALS_H_ */
