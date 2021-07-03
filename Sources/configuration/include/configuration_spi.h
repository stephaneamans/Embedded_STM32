#ifndef CONFIGURATION_SPI_H
#define CONFIGURATION_SPI_H

/*********************************
 * SPI definitions
 ********************************/

/* SPI1 configuration                     */
#define SPI1_BASE                  (APB2PERIPH_BASE + 0x00003000U)
#define SPI1_DMA_DRIVER_TX         &dma_driver[3]
#define SPI1_DMA_DRIVER_RX         &dma_driver[4]
#define MAX_SPI1_PERIPHERALS       2

/* SPI2 configuration                     */
#define SPI2_BASE                  (APB1PERIPH_BASE + 0x00003800U)
#define SPI2_DMA_DRIVER_TX         0
#define SPI2_DMA_DRIVER_RX         0
#define MAX_SPI2_PERIPHERALS       2

#endif /* CONFIGURATION_SPI_H_ */
