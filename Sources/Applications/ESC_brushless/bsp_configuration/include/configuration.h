#ifndef CONFIGURATION_H
#define CONFIGURATION_H


/*********************************
 * Peripheral activations
 ********************************/
#define CLOCK_RESET
//#define GPIO_PA0
#define GPIO_PA6
#define GPIO_PA8
//#define GPIO_PB7
//#define GPIO_PB9
#define GPIO_PC13
#define TIM_1
//#define TIM_2
//#define TIM_3
//#define USART_1
//#define USART_2


/*********************************
 * Clock definitions
 ********************************/
/* Define units          */
//#define KHZ  *1000
//#define MHZ  *1000000

#define SYS_CLK     72 MHZ
#define AHB_CLK     36 MHZ
#define	APB1_CLK    36 MHZ
#define	APB2_CLK     9 MHZ
#define SOURCE      PLL_HSE


/*********************************
 * GPIO definitions
 ********************************/
#include "lld_gpio.h"

/* PAO configuration                      */
#define PA0_GPIO_PORT      GPIOA
#define PA0_PIN            0
#define PA0_MODE           mode_input
#define PA0_CONFIG         config_input_pullup
#define PA0_IRQ_ENABLE     1
#define PA0_IRQ_RISING     0
#define PA0_IRQ_PRIORITY   prio2
#define PA0_IRQ_CALLBACK   0

/* PA6 configuration                      */
#define PA6_GPIO_PORT      GPIOA
#define PA6_PIN            6
#define PA6_MODE           mode_output_50mhz
#define PA6_CONFIG         config_output_outpushpull
#define PA6_IRQ_ENABLE     0
#define PA6_IRQ_RISING     0
#define PA6_IRQ_PRIORITY   prio2
#define PA6_IRQ_CALLBACK   0

/* PA8 configuration                      */
#define PA8_GPIO_PORT      GPIOA
#define PA8_PIN            8
#define PA8_MODE           mode_output_50mhz
#define PA8_CONFIG         config_output_altpushpull
#define PA8_IRQ_ENABLE     0
#define PA8_IRQ_RISING     0
#define PA8_IRQ_PRIORITY   prio2
#define PA8_IRQ_CALLBACK   0

/* PB7 configuration                      */
#define PB7_GPIO_PORT      GPIOB
#define PB7_PIN            7
#define PB7_MODE           mode_output_50mhz
#define PB7_CONFIG         config_output_outpushpull
#define PB7_IRQ_ENABLE     0
#define PB7_IRQ_RISING     0
#define PB7_IRQ_PRIORITY   prio2
#define PB7_IRQ_CALLBACK   0

/* PB9 configuration                      */
#define PB9_GPIO_PORT      GPIOB
#define PB9_PIN            9
#define PB9_MODE           mode_input
#define PB9_CONFIG         config_input_pullup
#define PB9_IRQ_ENABLE     0
#define PB9_IRQ_RISING     0
#define PB9_IRQ_PRIORITY   prio2
#define PB9_IRQ_CALLBACK   0

/* PC13 configuration                     */
#define PC13_GPIO_PORT     GPIOC
#define PC13_PIN           13
#define PC13_MODE          mode_output_50mhz
#define PC13_CONFIG        config_output_outopendrain
#define PC13_IRQ_ENABLE    0
#define PC13_IRQ_RISING    0
#define PC13_IRQ_PRIORITY  prio2
#define PC13_IRQ_CALLBACK  0


/*********************************
 * USART definitions
 ********************************/
#include "lld_usart.h"

/* USART1 configuration                     */
#define USART1_BAUDRATE                      115200
#define USART1_LENGTH                        8
#define USART1_WAKEUP                        0
#define USART1_PARITY                        PARITY_EVEN
#define USART1_STOP                          ONE_STOP_BIT
#define USART1_CLOCK_MODES                   LOW_AND_FIRST_EDGE
#define USART1_RTS                           0
#define USART1_DMA                           0
#define USART1_IRQ_TYPE                      0
#define USART1_IRQ_CALLBACK_PARITY           0
#define USART1_IRQ_CALLBACK_TX_ERR           0
#define USART1_IRQ_CALLBACK_TX_COMPLETE_ERR  0
#define USART1_IRQ_CALLBACK_RX_ERR           0
#define USART1_IRQ_CALLBACK_IDLE             0
#define USART1_IRQ_CALLBACK_CTS              0
#define USART1_IRQ_CALLBACK_ERROR_IRQ        0

/* USART2 configuration                     */
#define USART2_BAUDRATE                      115200
#define USART2_LENGTH                        8
#define USART2_WAKEUP                        0
#define USART2_PARITY                        PARITY_EVEN
#define USART2_STOP                          ONE_STOP_BIT
#define USART2_CLOCK_MODES                   LOW_AND_FIRST_EDGE
#define USART2_RTS                           0
#define USART2_DMA                           0
#define USART2_IRQ_TYPE                      0
#define USART2_IRQ_CALLBACK_PARITY           0
#define USART2_IRQ_CALLBACK_TX_ERR           0
#define USART2_IRQ_CALLBACK_TX_COMPLETE_ERR  0
#define USART2_IRQ_CALLBACK_RX_ERR           0
#define USART2_IRQ_CALLBACK_IDLE             0
#define USART2_IRQ_CALLBACK_CTS              0
#define USART2_IRQ_CALLBACK_ERROR_IRQ        0


/*********************************
 * TIM definitions
 ********************************/
#include "lld_timer.h"

/* TIM_1 configuration                     */
#define TIM1_CHANNEL        channel_1
#define TIM1_DURATION       1 MSEC
#define TIM1_IRQ_ENABLE     irq
//#define TIM1_OC_MODE        pwm2
//#define TIM1_MODE           pwm_output


#endif
