#ifndef CONFIGURATION_GPIO_H
#define CONFIGURATION_GPIO_H


/*********************************
 * GPIO definitions
 ********************************/


/* PAO configuration                      */
#define PA0_GPIO_PORT      GPIOA
#define PA0_PIN            0
#define PA0_MODE           mode_input
#define PA0_CONFIG         config_input_pullup
#define PA0_IRQ_ENABLE     1
#define PA0_IRQ_RISING     0
#define PA0_IRQ_PRIORITY   prio2
#define PA0_IRQ_CALLBACK   0


/* PA1 configuration                      */
#define PA1_GPIO_PORT      GPIOA
#define PA1_PIN            1
#define PA1_MODE           mode_input
#define PA1_CONFIG         config_input_floating
#define PA1_IRQ_ENABLE     0
#define PA1_IRQ_RISING     0
#define PA1_IRQ_PRIORITY   prio2
#define PA1_IRQ_CALLBACK   0


/* PA2 configuration                      */
#define PA2_GPIO_PORT      GPIOA
#define PA2_PIN            2
#define PA2_MODE           mode_output_50mhz
#define PA2_CONFIG         config_output_altpushpull
#define PA2_IRQ_ENABLE     0
#define PA2_IRQ_RISING     0
#define PA2_IRQ_PRIORITY   prio2
#define PA2_IRQ_CALLBACK   0


/* PA6 configuration                      */
#define PA6_GPIO_PORT      GPIOA
#define PA6_PIN            6
#define PA6_MODE           mode_output_50mhz
#define PA6_CONFIG         config_output_altpushpull
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


/* PA9 configuration                      */
#define PA9_GPIO_PORT      GPIOA
#define PA9_PIN            9
#define PA9_MODE           mode_output_50mhz
#define PA9_CONFIG         config_output_altpushpull
#define PA9_IRQ_ENABLE     0
#define PA9_IRQ_RISING     0
#define PA9_IRQ_PRIORITY   prio2
#define PA9_IRQ_CALLBACK   0


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

#endif /* CONFIGURATION_GPIO_H_ */
