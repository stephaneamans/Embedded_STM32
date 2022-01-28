#include "bsp.h"

/* Include files:        */
//#include "bsp_configuration.h"
#include "lld_clock.h"
#include "lld_dma.h"
#include "gpio.h"
#include "usart.h"

//extern const struct t_clock_config clock_config;
//extern const struct t_usart_config usartx_cfg[USART_IP_NUMBER];
//extern const struct t_gpio_config gpio_cfg[GPIO_PIN_NUMBER];
//extern const struct t_dma_channel_cfg dma1_chx_cfg[DMA_CHANNELS_NUMBER];
//extern struct t_timer_cfg timx_chanelx_cfg [TIMER_IP_NUMBER];

//void soc_core_configuration(void)
//{
//	struct t_clock_driver *clock_driver = get_clock_driver();
//	clock_init(clock_driver, &clock_config);
//}

//void soc_peripherals_configuration(void)
//{
//	for(uint8_t index = 0; index < DMA_CHANNELS_NUMBER; index++)
//	{
//	    dma_init(&dma_driver[index], &dma1_chx_cfg[index]);
//	}

//	for(uint8_t index = 0; index < GPIO_PIN_NUMBER; index++)
//	{
//      gpio_init(&gpio_cfg[index]);
//	}

//	struct t_usart_driver *usart_driver = usart_get_driver(1);
//    usart_init(usart_driver, &usartx_cfg[0]);
//    usart_driver = usart_get_driver(2);
 //   usart_init(usart_driver, &usartx_cfg[1]);

//    timer_init(&timx_chanelx_cfg[0]);
//    timer_init(&timx_chanelx_cfg[1]);
//    timer_init(&timx_chanelx_cfg[2]);
//}
