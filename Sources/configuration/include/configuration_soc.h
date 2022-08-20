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

/* Register map         */
#define PERIPH_BASE        0x40000000U
#define AHBPERIPH_BASE     (PERIPH_BASE + 0x00020000U)
#define APB1PERIPH_BASE    (PERIPH_BASE)
#define APB2PERIPH_BASE    (PERIPH_BASE + 0x00010000U)
#define RCC_BASE           (AHBPERIPH_BASE + 0x00001000U)

/* NVIC interrupt offset */
#define NVIC_WWDG_OFFSET      0
#define NVIC_PVD_OFFSET       1
#define NVIC_TAMPER_OFFSET    2
#define NVIC_RTC_OFFSET       3
#define NVIC_FLASH_OFFSET     4
#define NVIC_RCC_OFFSET       5
#define NVIC_GPIO_OFFSET      6
#define NVIC_DMA1_OFFSET      11
#define NVIC_ADC1_OFFSET      18
#define NVIC_CAN1_OFFSET      19
#define NVIC_EXTI9_5_OFFSET   23
#define NVIC_TIM1_OFFSET      24
#define NVIC_TIM2_OFFSET      28
#define NVIC_TIM3_OFFSET      29
#define NVIC_TIM4_OFFSET      30
#define NVIC_I2C_OFFSET       31
#define NVIC_SPI_OFFSET       35
#define NVIC_USART_OFFSET     37 


/* SoC internal peripherals enumeration:        */
enum t_peripheral
{
    DMA_1,
    PORT_A,
    PORT_B,
    PORT_C,
    PORT_D,
    PORT_E,
    PORT_F,
    PORT_G,
    SPI1,
    SPI2,
    TIM_1,
    TIM_2,
    TIM_3,
    USART1,
    USART2
};

#endif /* CONFIGURATION_SOC_H_ */
