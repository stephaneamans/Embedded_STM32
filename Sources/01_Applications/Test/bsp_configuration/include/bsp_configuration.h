#ifndef BSP_CONFIGURATION_H
#define BSP_CONFIGURATION_H

#include <stdint.h>
#include "configuration_module_activation.h"
#include "configuration_dma.h"
#include "configuration_gpio.h"
#include "configuration_soc.h"
#include "configuration_timer.h"
#include "configuration_usart.h"

#ifdef CLOCK_RESET
#include "lld_clock.h"
#endif

#if defined(DMA1_CH1) || defined(DMA1_CH2)|| defined(DMA1_CH3) || defined(DMA1_CH4) || defined(DMA1_CH5) || defined(DMA1_CH6) || defined(DMA1_CH7)
#include "lld_dma.h"
#endif

#if defined(GPIO_PA0) || defined(GPIO_PA1)|| defined(GPIO_PA2) || defined(GPIO_PA6) || defined(GPIO_PA8) || defined(GPIO_PA9) || defined(GPIO_PA10) || defined(GPIO_PB7) || defined(GPIO_PB9) || defined(GPIO_PC13)
#include "lld_gpio.h"
#endif

#if defined(USART_1) || defined(USART_2)
#include "lld_usart.h"
#endif

#if defined(TIM_1) || defined(TIM_2) || defined(TIM_3)
#include "lld_timer.h"
#endif


void soc_core_configuration(void);
void soc_peripherals_configuration(void);

#endif //BSP_CONFIGURATION_H
