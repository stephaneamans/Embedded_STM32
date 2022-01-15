#ifndef CONFIGURATION_SOC_H
#define CONFIGURATION_SOC_H

/*********************************
 * Clock definitions
 ********************************/

/* SOC parameters:   */

#define GPIO_PIN_NUMBER         37
#define EXTI_CHANNEL_NUMBER     5
#define USART_IP_NUMBER         2
#define DMA_IP_NUMBER           1
#define DMA_CHANNEL_NUMBER      7
#define TIMER_IP_NUMBER         3
#define TIMER_CHANNELS_NUMBER   4
#define SPI_IP_NUMBER           2
#define I2C_IP_NUMBER           1

/* Register map         */
#define PERIPH_BASE        0x40000000U
#define AHBPERIPH_BASE     (PERIPH_BASE + 0x00020000U)
#define APB1PERIPH_BASE    (PERIPH_BASE)
#define APB2PERIPH_BASE    (PERIPH_BASE + 0x00010000U)
#define RCC_BASE           (AHBPERIPH_BASE + 0x00001000U)


/* SoC internal peripherals enumeration:        */
enum t_peripheral
{
    DMA_1,
    I2C_1,
    I2C_2,
    PORT_A,
    PORT_B,
    PORT_C,
    PORT_D,
    PORT_E,
    PORT_F,
    PORT_G,
    SPI_0,
    SPI_1,
    TIM_1,
    TIM_2,
    TIM_3,
    USART_1,
    USART_2
};

#endif /* CONFIGURATION_SOC_H_ */
