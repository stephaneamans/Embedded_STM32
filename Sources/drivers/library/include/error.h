/*
 * error.h
 *
 * Created on: Mar 25, 2021
 * Author: Stephane Amans
 */
#ifndef ERROR_H_
#define ERROR_H_

typedef enum{
    ERROR_OK                      = 0,
    ERROR_WRONG_VALUE             = 1,
    ERROR_WRONG_CLOCK_SET         = 2,
    ERROR_WRONG_DATA_TYPE         = 3,
    ERROR_DRIVER_NOT_INITIALIZED  = 4,
    ERROR_UNDEFINED               = 5,
	ERROR_WRITTEN_VALUE_CORRUPTED = 6,

    ERROR_USART_NOT_READY_TO_SEND = 10,
    ERROR_USART_NO_DATA_RECEIVED  = 11,
    ERROR_USART_PARITY            = 12,
    ERROR_USART_FRAMING           = 13,
    ERROR_USART_NOISE             = 14,
    ERROR_USART_OVERRUN           = 15,

    ERROR_QUEUE_FULL              = 20,
    ERROR_QUEUE_EMPTY             = 21,

}t_error_handling;

#endif /* ERROR_H_ */
