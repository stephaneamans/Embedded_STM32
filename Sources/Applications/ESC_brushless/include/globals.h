/*
 * globals.h
 *
 *  Created on: Apr 12, 2019
 *      Author: nxa21324
 */
#ifndef GLOBALS_H_
#define GLOBALS_H_

#define MAX_GPIO_PIN            16
#define CLOCK_FREQ_MHZ          8000000

enum ERROR_HANDLING{
    OK                          = 0,
    ERROR_WRONG_VALUE_PASSED    = 1,
    ERROR_WRONG_CLOCK_SET       = 2
};

#endif /* GLOBALS_H_ */
