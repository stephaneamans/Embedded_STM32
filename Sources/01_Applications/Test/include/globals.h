/*
 * globals.h
 *
 * Created on: Apr 12, 2019
 * Author: Stephane Amans
 */
#ifndef GLOBALS_H_
#define GLOBALS_H_

#define MAX_GPIO_PIN            16
#define CLOCK_FREQ_MHZ          8000000

typedef enum{
    OK                            = 0,
    ERROR_WRONG_VALUE_PASSED      = 1,
    ERROR_WRONG_CLOCK_SET         = 2,
	ERROR_USART_NOT_READY_TO_SEND = 10,

    ERROR_QUEUE_FULL              = 20,
    ERROR_QUEUE_EMPTY             = 21,

	ERROR_TEST_FAIL               = 30

}t_error_handling;

#endif /* GLOBALS_H_ */
