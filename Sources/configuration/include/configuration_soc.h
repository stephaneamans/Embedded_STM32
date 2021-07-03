#ifndef CONFIGURATION_SOC_H
#define CONFIGURATION_SOC_H

/*********************************
 * Clock definitions
 ********************************/

/* SOC parameters:   */

#define GPIO_PIN_NUMBER         36
#define MAX_GPIO_PIN            8
#define USART_IP_NUMBER         2
#define DMA_IP_NUMBER           1
#define DMA_CHANNELS_NUMBER     7
#define TIMER_IP_NUMBER         3
#define TIMER_CHANNELS_NUMBER   4
#define SPI_IP_NUMBER           2

/* Register map         */
#define PERIPH_BASE        0x40000000U
#define AHBPERIPH_BASE     (PERIPH_BASE + 0x00020000U)
#define APB1PERIPH_BASE    (PERIPH_BASE)
#define APB2PERIPH_BASE    (PERIPH_BASE + 0x00010000U)
#define RCC_BASE           (AHBPERIPH_BASE + 0x00001000U)

#endif /* CONFIGURATION_SOC_H_ */
