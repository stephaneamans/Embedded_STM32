#ifndef CONFIGURATION_SPI_H
#define CONFIGURATION_SPI_H

/*********************************
 * SPI definitions
 ********************************/

/* SPI1 configuration                     */
#define SPI1_BASE                  (APB2PERIPH_BASE + 0x00003000U)
#define MAX_SPI1_PERIPHERALS       2
#define SPI1_IRQ_ENABLE            false
#define SPI1_IRQ_PRIORITY          2
#define SPI1_DMA_ENABLE            true

/* SPI2 configuration                     */
#define SPI2_BASE                  (APB1PERIPH_BASE + 0x00003800U)
#define MAX_SPI2_PERIPHERALS       2
#define SPI2_IRQ_ENABLE            false
#define SPI2_IRQ_PRIORITY          2
#define SPI2_DMA_ENABLE            false

#endif /* CONFIGURATION_SPI_H_ */
