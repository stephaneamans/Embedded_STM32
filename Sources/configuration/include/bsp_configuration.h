#ifndef BSP_CONFIGURATION_H
#define BSP_CONFIGURATION_H

#include <stdint.h>

#include "configuration_module_activation.h"
#include "configuration_clock.h"
#include "configuration_dma.h"
#include "configuration_gpio.h"
#include "configuration_soc.h"
#include "configuration_timer.h"
#include "configuration_usart.h"

#include "lld_afio.h"
#include "lld_clock.h"
#include "lld_dma.h"
#include "lld_exti.h"

#include "gpio.h"
#include "lld_spi.h"
#include "usart.h"
#include "timer.h"


extern struct t_spi_driver spi_driver[SPI_IP_NUMBER];
extern struct t_gpio_driver gpio_driver[GPIO_PIN_NUMBER];


/** Configure core elements of the SoC.
 *
 * \param: void
 *
 * \return: void
 *
 */
void soc_core_configuration(void);

/** Configure SoC peripherals.
 *
 * \param: void
 *
 * \return: void
 *
 */
void soc_peripherals_configuration(void);


#endif //BSP_CONFIGURATION_H
