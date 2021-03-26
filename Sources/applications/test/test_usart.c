/*
 * test_usart.c
 *
 * Created on: Jun 12, 2020
 * Author: Stephane Amans
 */

/* Include files.        */
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "lld_clock.h"
#include "lld_dma.h"

#include "test.h"
#include "usart.h"

/* Defines */
#define BUFFER_LENGTH_256   256

t_error_handling print_test_header(void)
{
    /* Declarations. */
    char buffer_tx_8bits[BUFFER_LENGTH_256];
    char buffer_rx_8bits[BUFFER_LENGTH_256];
    uint32_t string_length;
    t_error_handling error = ERROR_OK;
    uint8_t *ptr_read = (uint8_t*)&buffer_rx_8bits;

    for(uint16_t index_loop = 0; index_loop < BUFFER_LENGTH_256; index_loop++)
    {
    	buffer_tx_8bits[index_loop] = 0;
    	buffer_rx_8bits[index_loop] = 0;
    }

   	struct t_usart_driver *usart1 = usart_get_driver(1);

    string_length = sprintf(buffer_tx_8bits, "\r\nSTM32F test application\r\n-----------------------\n\n\rDo you want to start(yes/no): ");

    error += usart1->methods.transmit(usart1, (uint8_t*)&buffer_tx_8bits, string_length);


    while(*ptr_read != 0x0d)
    {
    	error = usart1->methods.receive(usart1, (uint8_t*)&buffer_rx_8bits, 1);
    }

    if(strcmp(&buffer_rx_8bits[0], "yes\r") == 0)
    {
        string_length = sprintf(&buffer_tx_8bits[0], "\n\n\ryes, cool !");
        while(usart1->methods.transmit(usart1, (uint8_t*)&buffer_tx_8bits[0], string_length) == ERROR_USART_NOT_READY_TO_SEND);
    }
    else if(strcmp(&buffer_rx_8bits[0], "no\r") == 0)
    {
    	string_length = sprintf(&buffer_tx_8bits[0], "\n\n\roh non, pas cool !");
    	while(usart1->methods.transmit(usart1, (uint8_t*)&buffer_tx_8bits[0], string_length) == ERROR_USART_NOT_READY_TO_SEND);
    }
    else
    {
     	string_length = sprintf(&buffer_tx_8bits[0], "\n\n\rbon, ben je ne sais pas ...");
     	while(usart1->methods.transmit(usart1, (uint8_t*)&buffer_tx_8bits[0], string_length) == ERROR_USART_NOT_READY_TO_SEND);
    }
    return error;
}

