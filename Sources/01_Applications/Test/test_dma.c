/*
 * test_dma.c
 *
 * Created on: Jun 9, 2020
 * Author: Stephane Amans
 */

/* Include files.        */
#include "test.h"
#include "lld_dma.h"

/* Defines */
#define TOTAL_TEST_NUMBER   5
#define BUFFER_LENGTH_128    128
#define BUFFER_LENGTH_256   256


static void initialize_driver(struct t_dma_driver *driver)
{
	/* Implement driver structure. */
	t_dma_channel_cfg dma_ch1, dma_ch2;
	dma_ch1.reg = DMA1_Ch1;
	dma_ch2.reg = DMA1_Ch2;

    dma_ch1.mem2mem = dma_enable;
    dma_ch1.dma_priority = low;
    dma_ch1.mem_data_type = bits_8;
    dma_ch1.memory_zone_size = (BUFFER_LENGTH_256 / 2);
    dma_ch1.periph_data_type = bits_8;
    dma_ch1.memory_increment = dma_enable;
    dma_ch1.peripheral_increment = dma_enable;
    dma_ch1.read_from_memory = dma_enable;
    dma_ch1.irq.transfer_error_interrupt = dma_disable;
    dma_ch1.irq.half_transfer_interrupt = dma_disable;
    dma_ch1.irq.transfer_complete_interrupt = dma_disable;
    dma_ch1.irq.priority = 0;
    dma_ch1.irq.callback = 0;
    dma_init(driver, &dma_ch1);

    dma_ch2.mem2mem = dma_enable;
    dma_ch2.dma_priority = low;
    dma_ch2.mem_data_type = bits_32;
    dma_ch2.memory_zone_size = (BUFFER_LENGTH_256 / 2);
    dma_ch2.periph_data_type = bits_32;
    dma_ch2.memory_increment = dma_enable;
    dma_ch2.peripheral_increment = dma_enable;
    dma_ch2.read_from_memory = dma_enable;
    dma_ch2.irq.transfer_error_interrupt = dma_disable;
    dma_ch2.irq.half_transfer_interrupt = dma_disable;
    dma_ch2.irq.transfer_complete_interrupt = dma_disable;
    dma_ch2.irq.priority = 0;
    dma_ch2.irq.callback = 0;
    dma_init(driver, &dma_ch2);

}

t_error_handling test_dma(void)
{
    /* Declarations. */
    uint8_t write_8bits[BUFFER_LENGTH_256];    /* Transfer source 8 bits date table.           */
    uint8_t read_8bits[BUFFER_LENGTH_256];     /* Transfer destination location 8 bits table.  */
    uint32_t write_32bits[BUFFER_LENGTH_256];  /* Transfer source 32 bits date table.          */
    uint32_t read_32bits[BUFFER_LENGTH_256];   /* Transfer destination location 32 bits table. */
    uint32_t error = 0;

    struct t_dma_driver dma_driver[2];

    for(uint16_t index = 0; index < BUFFER_LENGTH_256; index++)
    {
    	read_8bits[BUFFER_LENGTH_256] = 0;
    	read_32bits[BUFFER_LENGTH_256] = 0;
    }

    for(uint16_t index = 0; index < BUFFER_LENGTH_256; index++)
    {
      	write_8bits[BUFFER_LENGTH_256] = index;
       	write_32bits[BUFFER_LENGTH_256] = index * 16777215;
    }

    /* Initializations. */
    initialize_driver(&dma_driver[0]);
    initialize_driver(&dma_driver[1]);

    dma_memcpy(&dma_driver[0], &read_8bits, &write_8bits, BUFFER_LENGTH_256);
    dma_start_transfer(&dma_driver[0]);

    for(uint16_t index = 0; index < BUFFER_LENGTH_256; index++)
    {
        if(write_8bits[index] != read_8bits[index])
        {
            error++;
        }
    }

    for(uint16_t index = 0; index < BUFFER_LENGTH_256; index++)
    {
       	if(write_8bits[index] != read_8bits[index])
        {
    	    error++;
    	}
    }

    dma_memcpy(&dma_driver[1], &read_32bits, &write_32bits, BUFFER_LENGTH_256);
    dma_start_transfer(&dma_driver[1]);

    for(uint16_t index = 0; index < BUFFER_LENGTH_256; index++)
    {
        if(write_32bits[index] != read_32bits[index])
        {
            error++;
        }
    }
    for(uint16_t index = 0; index < BUFFER_LENGTH_256; index++)
    {
        if(write_32bits[index] != read_32bits[index])
        {
            error++;
      	}
    }

    return error;
}
