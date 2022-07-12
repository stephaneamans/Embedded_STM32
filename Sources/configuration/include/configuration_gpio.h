#ifndef CONFIGURATION_GPIO_H
#define CONFIGURATION_GPIO_H

/*********************************
 * GPIO definitions
 ********************************/

#define AFIO_BASE          (APB2PERIPH_BASE + 0x00000000U)
#define EXTI_BASE          (APB2PERIPH_BASE + 0x00000400U)
#define GPIOA_BASE         (APB2PERIPH_BASE + 0x00000800U)

#define PA0_PIN            0
#define PA0_TYPE           input_pullup
#define PA0_IRQ_ENABLE     false
#define PA0_IRQ_RISING     false
#define PA0_IRQ_PRIORITY   prio2
#define PA0_IRQ_CALLBACK   0

#define PA1_PIN            1
#define PA1_TYPE           input_floating
#define PA1_IRQ_ENABLE     false
#define PA1_IRQ_RISING     false
#define PA1_IRQ_PRIORITY   prio2
#define PA1_IRQ_CALLBACK   0

#define PA2_PIN            2
#define PA2_TYPE           output_pushpull_50MHz
#define PA2_IRQ_ENABLE     false
#define PA2_IRQ_RISING     false
#define PA2_IRQ_PRIORITY   prio2
#define PA2_IRQ_CALLBACK   0

#define PA3_PIN            3
#define PA3_TYPE           input_pullup
#define PA3_IRQ_ENABLE     true
#define PA3_IRQ_RISING     false
#define PA3_IRQ_PRIORITY   prio2
#define PA3_IRQ_CALLBACK   0

#define PA4_PIN            4
#define PA4_TYPE           input_pullup
#define PA4_IRQ_ENABLE     false
#define PA4_IRQ_RISING     false
#define PA4_IRQ_PRIORITY   prio2
#define PA4_IRQ_CALLBACK   0

#define PA5_PIN            5
#define PA5_TYPE           output_pushpull_50MHz
#define PA5_IRQ_ENABLE     false
#define PA5_IRQ_RISING     false
#define PA5_IRQ_PRIORITY   prio2
#define PA5_IRQ_CALLBACK   0

#define PA6_PIN            6
#define PA6_TYPE           output_pushpull_50MHz
#define PA6_IRQ_ENABLE     false
#define PA6_IRQ_RISING     false
#define PA6_IRQ_PRIORITY   prio2
#define PA6_IRQ_CALLBACK   0

#define PA7_PIN            7
#define PA7_TYPE           output_pushpull_2MHz
#define PA7_IRQ_ENABLE     false
#define PA7_IRQ_RISING     false
#define PA7_IRQ_PRIORITY   prio2
#define PA7_IRQ_CALLBACK   0

#define PA8_PIN            8
#define PA8_TYPE           output_opendrain_10MHz
#define PA8_IRQ_ENABLE     false
#define PA8_IRQ_RISING     false
#define PA8_IRQ_PRIORITY   prio2
#define PA8_IRQ_CALLBACK   0

#define PA9_PIN            9
#define PA9_TYPE           input_pullup
#define PA9_IRQ_ENABLE     false
#define PA9_IRQ_RISING     false
#define PA9_IRQ_PRIORITY   prio2
#define PA9_IRQ_CALLBACK   0

#define PA10_PIN            10
#define PA10_TYPE           output_altpushpull_2MHz
#define PA10_IRQ_ENABLE     false
#define PA10_IRQ_RISING     false
#define PA10_IRQ_PRIORITY   prio2
#define PA10_IRQ_CALLBACK   0

#define PA11_PIN            11
#define PA11_TYPE           output_altpushpull_10MHz
#define PA11_IRQ_ENABLE     false
#define PA11_IRQ_RISING     false
#define PA11_IRQ_PRIORITY   prio2
#define PA11_IRQ_CALLBACK   0

#define PA12_PIN            12
#define PA12_TYPE           output_pushpull_50MHz
#define PA12_IRQ_ENABLE     false
#define PA12_IRQ_RISING     false
#define PA12_IRQ_PRIORITY   prio2
#define PA12_IRQ_CALLBACK   0

#define PA13_PIN            13
#define PA13_TYPE           output_altopendrain_2MHz
#define PA13_IRQ_ENABLE     false
#define PA13_IRQ_RISING     false
#define PA13_IRQ_PRIORITY   prio2
#define PA13_IRQ_CALLBACK   0

#define PA14_PIN            14
#define PA14_TYPE           input_pullup
#define PA14_IRQ_ENABLE     false
#define PA14_IRQ_RISING     false
#define PA14_IRQ_PRIORITY   prio2
#define PA14_IRQ_CALLBACK   0

#define PA15_PIN            15
#define PA15_TYPE           input_pullup
#define PA15_IRQ_ENABLE     false
#define PA15_IRQ_RISING     false
#define PA15_IRQ_PRIORITY   prio2
#define PA15_IRQ_CALLBACK   0


#define GPIOB_BASE          (APB2PERIPH_BASE + 0x00000C00U)

#define PB0_PIN             0
#define PB0_TYPE            input_pullup
#define PB0_IRQ_ENABLE      true
#define PB0_IRQ_RISING      false
#define PB0_IRQ_PRIORITY    prio2
#define PB0_IRQ_CALLBACK    0

#define PB1_PIN             1
#define PB1_TYPE            input_pullup
#define PB1_IRQ_ENABLE      true
#define PB1_IRQ_RISING      false
#define PB1_IRQ_PRIORITY    prio2
#define PB1_IRQ_CALLBACK    0

#define PB2_PIN             2
#define PB2_TYPE            output_pushpull_50MHz
#define PB2_IRQ_ENABLE      false
#define PB2_IRQ_RISING      false
#define PB2_IRQ_PRIORITY    prio2
#define PB2_IRQ_CALLBACK    0

#define PB3_PIN             3
#define PB3_TYPE            input_pullup
#define PB3_IRQ_ENABLE      false
#define PB3_IRQ_RISING      false
#define PB3_IRQ_PRIORITY    prio2
#define PB3_IRQ_CALLBACK    0

#define PB4_PIN             4
#define PB4_TYPE            input_pullup
#define PB4_IRQ_ENABLE      true
#define PB4_IRQ_RISING      false
#define PB4_IRQ_PRIORITY    prio2
#define PB4_IRQ_CALLBACK    0

#define PB5_PIN             5
#define PB5_TYPE           input_pullup
#define PB5_IRQ_ENABLE     false
#define PB5_IRQ_RISING      false
#define PB5_IRQ_PRIORITY    prio2
#define PB5_IRQ_CALLBACK    0

#define PB6_PIN             6
#define PB6_TYPE            output_pushpull_50MHz
#define PB6_IRQ_ENABLE      false
#define PB6_IRQ_RISING      false
#define PB6_IRQ_PRIORITY    prio2
#define PB6_IRQ_CALLBACK    0

#define PB7_PIN             7
#define PB7_TYPE            output_pushpull_50MHz
#define PB7_IRQ_ENABLE      false
#define PB7_IRQ_RISING      false
#define PB7_IRQ_PRIORITY    prio2
#define PB7_IRQ_CALLBACK    0

#define PB8_PIN             8
#define PB8_TYPE            output_pushpull_50MHz
#define PB8_IRQ_ENABLE      false
#define PB8_IRQ_RISING      false
#define PB8_IRQ_PRIORITY    prio2
#define PB8_IRQ_CALLBACK    0

#define PB9_PIN             9
#define PB9_TYPE            input_pullup
#define PB9_IRQ_ENABLE      false
#define PB9_IRQ_RISING      false
#define PB9_IRQ_PRIORITY    prio2
#define PB9_IRQ_CALLBACK    0

#define PB10_PIN            10
#define PB10_TYPE           output_pushpull_50MHz
#define PB10_IRQ_ENABLE     false
#define PB10_IRQ_RISING     false
#define PB10_IRQ_PRIORITY   prio2
#define PB10_IRQ_CALLBACK   0

#define PB11_PIN            11
#define PB11_TYPE           input_pullup
#define PB11_IRQ_ENABLE     false
#define PB11_IRQ_RISING     false
#define PB11_IRQ_PRIORITY   prio2
#define PB11_IRQ_CALLBACK   0

#define PB12_PIN            12
#define PB12_TYPE           output_pushpull_50MHz
#define PB12_IRQ_ENABLE     false
#define PB12_IRQ_RISING     false
#define PB12_IRQ_PRIORITY   prio2
#define PB12_IRQ_CALLBACK   0

#define PB13_PIN            13
#define PB13_TYPE           output_pushpull_50MHz
#define PB13_IRQ_ENABLE     false
#define PB13_IRQ_RISING     false
#define PB13_IRQ_PRIORITY   prio2
#define PB13_IRQ_CALLBACK   0

#define PB14_PIN            14
#define PB14_TYPE           output_pushpull_50MHz
#define PB14_IRQ_ENABLE     false
#define PB14_IRQ_RISING     false
#define PB14_IRQ_PRIORITY   prio2
#define PB14_IRQ_CALLBACK   0

#define PB15_PIN            15
#define PB15_TYPE           output_pushpull_50MHz
#define PB15_IRQ_ENABLE     false
#define PB15_IRQ_RISING     false
#define PB15_IRQ_PRIORITY   prio2
#define PB15_IRQ_CALLBACK   0


#define GPIOC_BASE          (APB2PERIPH_BASE + 0x00001000U)

#define PC13_PIN            13
#define PC13_TYPE           input_pullup
#define PC13_IRQ_ENABLE     true
#define PC13_IRQ_RISING     false
#define PC13_IRQ_PRIORITY   prio2
#define PC13_IRQ_CALLBACK   0

#define PC14_PIN            14
#define PC14_TYPE           output_pushpull_50MHz
#define PC14_IRQ_ENABLE     false
#define PC14_IRQ_RISING     false
#define PC14_IRQ_PRIORITY   prio2
#define PC14_IRQ_CALLBACK   0

#define PC15_PIN            15
#define PC15_TYPE           output_opendrain_50MHz
#define PC15_IRQ_ENABLE     false
#define PC15_IRQ_RISING     false
#define PC15_IRQ_PRIORITY   prio2
#define PC15_IRQ_CALLBACK   0


#define GPIOD_BASE          (APB2PERIPH_BASE + 0x00001400U)

#define PD0_PIN             0
#define PD0_TYPE            input_pullup
#define PD0_IRQ_ENABLE      false
#define PD0_IRQ_RISING      false
#define PD0_IRQ_PRIORITY    prio2
#define PD0_IRQ_CALLBACK    0

#define PD1_PIN             1
#define PD1_TYPE            output_pushpull_50MHz
#define PD1_IRQ_ENABLE      false
#define PD1_IRQ_RISING      false
#define PD1_IRQ_PRIORITY    prio2
#define PD1_IRQ_CALLBACK    0


#endif /* CONFIGURATION_GPIO_H_ */
