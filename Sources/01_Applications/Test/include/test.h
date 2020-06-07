/*
 * test.h
 *
 * Created on: Jun 3, 2020
 * Author: Stephane Amans
 */
#ifndef TEST_H_
#define TEST_H_


/* Include files:        */
#include <stdint.h>
#include "globals.h"


/* Define test issue. */
typedef enum
{
    PASS = 0,
    FAIL = 1
}test_issue;


/* Functions prototypes:                       */

/** Test the queue in different ways.
 *
 * \param: void
 *
 * \return: Error code
 *
 */
t_error_handling test_queue(void);


#endif /* TEST_H_ */
