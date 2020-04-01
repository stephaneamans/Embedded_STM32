/*
 *        lld_gpio.h
 *
 *    Created on: Apr 12, 2019
 *    Author: Stéphane Amans
 */
#ifndef LLD_GPIO_H_
#define LLD_GPIO_H_


/* Include files:        */
#include <stdint.h>

#include "configuration.h"
#include "lld_clock.h"
#include "lld_nvic.h"
#include "regbase_exti.h"
#include "regbase_gpio.h"


/* GPIO initialization structure definition :        */
typedef struct
{
	GPIO_TypeDef *gpio;
    uint8_t pin;
    uint8_t mode;
    uint8_t config;
    struct
    {
        uint8_t active;
        uint8_t rising;
        uint8_t priority;
        void(*callback)(uint32_t);
    }irq;
}t_gpio_cfg;


/* Function re mapping structure definition:        */
typedef struct
{
    uint8_t swj_tag;
    uint8_t adc2;
    uint8_t adc1;
    uint8_t tim5;
    uint8_t pd01;
    uint8_t can;
    uint8_t tim4;
    uint8_t tim3;
    uint8_t tim2;
    uint8_t tim1;
    uint8_t usart3;
    uint8_t usart2;
    uint8_t usart1;
    uint8_t i2c1;
    uint8_t spi1;
}PERIPH_REMAP;


/* GPIOx_CRL and GPIOx_CRH, Port configuration register group definition: */
/* Configuration flag for GPIO input:          */
typedef enum
{
    config_input_analog   = 0x00,
    config_input_floating = 0x01,
    config_input_pullup   = 0x02,
    config_input_pulldown = 0x03
}config_gpio_output;

/* Configuration flag for GPIO output:         */
typedef enum
{
    config_output_outpushpull  = 0x00,
    config_output_outopendrain = 0x01,
    config_output_altpushpull  = 0x02,
    config_output_altopendrain = 0x03
}config_gpio_input;

/* MODE, GPIO configuration mode:              */
typedef enum
{
    mode_input        = 0x00,
    mode_output_10mhz = 0x01,
    mode_output_2mhz  = 0x02,
    mode_output_50mhz = 0x03
}mode_gpio;


/* Functions prototypes:                       */

/** Configure GPIO (port, pin, in/out, mode, interruption):
 *
 * \param gpio: Pointer to the gpio register base.
 * \param pin: Pin number.
 * \param cfg : Configuration structure.
 *
 * \return : Error code or 0 if OK.
 *
 */
uint8_t gpio_init(t_gpio_cfg *cfg);


/** Outputs the EVENTOUT Cortex's output on the selected pin and port.
*
* \param eventOutEn : Enables the functionality.
* \param port : Port selection (see .h for possibilities).
* \param pin : Pin number selection (between 0 and MAX_GPIO_PIN).
*
* \return : Error code or 0 if OK.
*
*/
uint8_t gpio_init_event_ctrl(uint8_t event_out_en, uint8_t port, uint8_t pin);


/** Set a GPIO.
*
* \param gpio : Pointer to the GPIO base adress.
* \param pin : Pin number (u8 between 0 and MAX_GPIO_PIN).
*
* \return : Error code or 0 if OK.
*
*/
uint8_t gpio_set(GPIO_TypeDef *gpio, uint16_t pin);


/**  Set all GPIOs on the port.
*
* \param gpio : Pointer to the GPIO base adress.
* \param pin : Pin number.
*
* \return : Error code or 0 if OK.
*
*/
uint8_t gpio_set_all(GPIO_TypeDef *gpio);


/** Clear a GPIO.
*
* \param gpio : Pointer to the GPIO base adress.
* \param pin : Pin number (u8 between 0 and MAX_GPIO_PIN).
*
* \return : Error code or 0 if OK.
*
*/
uint8_t gpio_clear(GPIO_TypeDef *gpio, uint8_t pin);


/** Clear all GPIOs on the port.
*
* \param gpio : Pointer to the GPIO base address.
*
* \return : Error code or 0 if OK.
*
*/
uint8_t gpio_clear_all(GPIO_TypeDef *gpio);


/** Toggle a GPIO.
*
* \param gpio : Pointer to the GPIO base address.
* \param pin : Pin number (u8 between 0 a1d MAX_GPIO_PIN).
*
* \return : Error code or 0 if OK.
*
*/
uint8_t gpio_toggle(GPIO_TypeDef *gpio, uint8_t pin);


/** Read a GPIO.
*
* \param gpio : Pointer to the GPIO base address.
* \param pin : Pin number (u8 between 0 and MAX_GPIO_PIN).
*
* \return : return the pin value.
*
*/
uint8_t gpio_read(GPIO_TypeDef *gpio, uint8_t pin);


/** Disable an GPIO port clock.
 *
 * \param gpio : address of the GPIO port to unclock.
 *
 * \return : Error code or OK.
 *
 */
uint8_t gpio_disable_clock(GPIO_TypeDef *gpio);


/** Set the remapping of the different peripherals.
*
* \param remap : Structure containing all remap parameters (defined in GPIO header).
*
* \return : Error code or 0 if OK.
*/
uint8_t gpio_pin_remap(PERIPH_REMAP remap);


/* Pointer callback function table prototype	*/
void (*gpio_callback[5])(uint32_t pin_numb);

 
#endif /* LLD_GPIO_H_ */
