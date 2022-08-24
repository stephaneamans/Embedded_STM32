#ifndef PLATFORM_CONFIGURATION_H_
#define PLATFORM_CONFIGURATION_H_

#include "nrf24l01.h"

/* Platform parameters:   */

#define MAX_SPI1_PERIPHERALS       2
#define MAX_SPI2_PERIPHERALS       2

#define NRF24L01_BUFFER_TX_LENGTH  32
#define NRF24L01_BUFFER_RX_LENGTH  32

extern struct t_nrf24l01_driver nrf24l01;

#define INIT_NRF24L01()              \
                                     \
nrf24l01_initialization(&nrf24l01);  \
                                     \

#endif /* PLATFORM_CONFIGURATION_H_ */




