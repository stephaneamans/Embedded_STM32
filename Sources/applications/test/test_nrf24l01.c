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

    uint8_t status_reg = 0;
    uint8_t read_config[3];
    uint8_t read_setup_aw[3];
    uint8_t read_setup_rf[3];

    for(uint8_t i = 0; i < 3; i++)
    {
        read_config[i] = 0;
        read_setup_aw[i] = 0;
        read_setup_rf[i] = 0;
    }

    nrf24l01_configure(&nrf24l01);

    /* Check CONFIG */
    error = nrf24l01_read_register_request(&nrf24l01, 0, 1);
    while(nrf24l01_read_write_status(&nrf24l01, &read_config[0], &status_reg) != ERROR_OK);

    /* Check SETUP_AW */
    error = nrf24l01_read_register_request(&nrf24l01, 3, 1);
    while(nrf24l01_read_write_status(&nrf24l01, &read_setup_aw[0], &status_reg) != ERROR_OK);

    /* Check SETUP_RF */
    error = nrf24l01_read_register_request(&nrf24l01, 6, 1);
    while(nrf24l01_read_write_status(&nrf24l01, &read_setup_rf[0], &status_reg) != ERROR_OK);

    while(1)
    {

    }

    return error;
}
