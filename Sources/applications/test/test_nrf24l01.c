/*
 * test_nrf24l01.c
 *
 * Created on: Aug 24, 2022
 * Author: Stephane Amans
 */

/* Include files.        */
#include <stdint.h>
#include <stdio.h>

#include "test.h"
#include "nrf24l01.h"

#include "platform_configuration.h"

t_error_handling nrf24l01_test(void)
{
    /* Declarations. */
    t_error_handling error = ERROR_OK;

//    nrf24l01_transmit(&nrf24l01);
    nrf24l01_receive(&nrf24l01);

    while(1)
    {

    }

    return error;
}
