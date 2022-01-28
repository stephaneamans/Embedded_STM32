/*
 * test_spi.c
 *
 * Created on: Jul 4, 2021
 * Author: Stephane Amans
 */

/* Include files.        */
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "lld_clock.h"
#include "lld_dma.h"

#include "test.h"
#include "lld_spi.h"

#include "bsp_configuration.h"

/* Defines */
#define BUFFER_LENGTH_256   256

struct t_spi_slave component[3] =
{
    [0] =
    {
        .freq_khz = 4000,
		.cs = GPIOA,
        .frame_length = spi_frame_8_bits,
        .frame_direction = spi_frame_msb_first,
        .clock_phase = spi_clk_first,
        .clock_polarity = spi_clk_rising,
    },

    [1] =
    {
        .freq_khz = 1125,
		.cs = GPIOA,
        .frame_length = spi_frame_16_bits,
        .frame_direction = spi_frame_lsb_first,
        .clock_phase = spi_clk_second,
        .clock_polarity = spi_clk_rising,
    },

    [2] =
    {
        .freq_khz = 18000,
		.cs = GPIOA,
        .frame_length = spi_frame_8_bits,
        .frame_direction = spi_frame_msb_first,
        .clock_phase = spi_clk_first,
        .clock_polarity = spi_clk_rising,
    },
};


t_error_handling spi_test(void)
{
    /* Declarations. */
    uint16_t buffer_write[BUFFER_LENGTH_256];
    uint16_t buffer_read[BUFFER_LENGTH_256];
    t_error_handling error = ERROR_OK;
    struct t_spi_data data;

    buffer_write[0] = 0x2A;
    data.write_buffer = &buffer_write[0];
    data.read_buffer = &buffer_read[0];
    data.length = 1;

   	//struct t_spi_driver *spi1 = spi_get_driver(1);
    struct t_spi_driver *spi1 = &spi_driver[0];

   	spi_record_slave(&component[0]);
   	spi_record_slave(&component[1]);
   	spi_record_slave(&component[2]);


   	gpio_set(component[0].cs, 4);
    error = spi_transfer(spi1, &component[0], &data);
    error = spi_transfer(spi1, &component[1], &data);
    error = spi_transfer(spi1, &component[2], &data);
    error = spi_transfer(spi1, &component[0], &data);

    while(error != ERROR_OK){}

    return error;
}

