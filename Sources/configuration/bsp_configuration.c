#include "bsp_configuration.h"

const struct t_clock_config clock_config =
{
    .sys_clk_freq = SYS_CLK,
    .AHB_clk_freq = AHB_CLK,
    .APB1_clk_freq = APB1_CLK,
    .APB2_clk_freq = APB2_CLK,
    .source = SOURCE,
};

struct t_dma_driver dma_driver[DMA_IP_NUMBER] =
{
    [0] = 
    {
        .base_address_dma                   = DMA1_BASE,
        .peripheral                         = DMA_1,
        .instance                           = 0
    },
};

struct t_dma_channel_driver dma_channel_driver[DMA_CHANNEL_NUMBER] = 
{
    [0] =
    {
        .base_address_dma_channel        = DMA1_CH1_BASE,
        .channel_number                  = 0,
        .mem2mem                         = DMA1_CH1_MEM2MEM,
        .dma_priority_level              = DMA1_CH1_PRIORITY,
        .irq.priority                    = DMA1_CH1_IRQ_PRIORITY,
        .irq.transfer_complete           = DMA1_CH1_IRQ_TRANSFER_COMPLETE,
        .irq.half_transfer_complete      = DMA1_CH1_IRQ_HALF_TRANSFER_COMPLETE,
        .irq.transfer_error              = DMA1_CH1_IRQ_TRANSFER_ERROR,
        .irq.callback                    = DMA1_CH1_IRQ_CALLBACK,
    },

    [1] =
    {
        .base_address_dma_channel        = DMA1_CH2_BASE,
        .channel_number                  = 1,
        .mem2mem                         = DMA1_CH2_MEM2MEM,
        .dma_priority_level              = DMA1_CH2_PRIORITY,
        .irq.priority                    = DMA1_CH2_IRQ_PRIORITY,
        .irq.transfer_complete           = DMA1_CH2_IRQ_TRANSFER_COMPLETE,
        .irq.half_transfer_complete      = DMA1_CH2_IRQ_HALF_TRANSFER_COMPLETE,
        .irq.transfer_error              = DMA1_CH2_IRQ_TRANSFER_ERROR,
        .irq.callback                    = DMA1_CH2_IRQ_CALLBACK,
    },

    [2] =
    {
        .base_address_dma_channel        = DMA1_CH3_BASE,
        .channel_number                  = 2,
        .mem2mem                         = DMA1_CH3_MEM2MEM,
        .dma_priority_level              = DMA1_CH3_PRIORITY,
        .irq.priority                    = DMA1_CH3_IRQ_PRIORITY,
        .irq.transfer_complete           = DMA1_CH3_IRQ_TRANSFER_COMPLETE,
        .irq.half_transfer_complete      = DMA1_CH3_IRQ_HALF_TRANSFER_COMPLETE,
        .irq.transfer_error              = DMA1_CH3_IRQ_TRANSFER_ERROR,
        .irq.callback                    = DMA1_CH3_IRQ_CALLBACK,
    },

    [3] =
    {
        .base_address_dma_channel        = DMA1_CH4_BASE,
        .channel_number                  = 3,
        .mem2mem                         = DMA1_CH4_MEM2MEM,
        .dma_priority_level              = DMA1_CH4_PRIORITY,
        .irq.priority                    = DMA1_CH4_IRQ_PRIORITY,
        .irq.transfer_complete           = DMA1_CH4_IRQ_TRANSFER_COMPLETE,
        .irq.half_transfer_complete      = DMA1_CH4_IRQ_HALF_TRANSFER_COMPLETE,
        .irq.transfer_error              = DMA1_CH4_IRQ_TRANSFER_ERROR,
        .irq.callback                    = DMA1_CH4_IRQ_CALLBACK,
    },

    [4] =
    {
        .base_address_dma_channel        = DMA1_CH5_BASE,
        .channel_number                  = 4,
        .mem2mem                         = DMA1_CH5_MEM2MEM,
        .dma_priority_level              = DMA1_CH5_PRIORITY,
        .irq.priority                    = DMA1_CH5_IRQ_PRIORITY,
        .irq.transfer_complete           = DMA1_CH5_IRQ_TRANSFER_COMPLETE,
        .irq.half_transfer_complete      = DMA1_CH5_IRQ_HALF_TRANSFER_COMPLETE,
        .irq.transfer_error              = DMA1_CH5_IRQ_TRANSFER_ERROR,
        .irq.callback                    = DMA1_CH5_IRQ_CALLBACK,
    },

    [5] =
    {
        .base_address_dma_channel        = DMA1_CH6_BASE,
        .channel_number                  = 5,
        .mem2mem                         = DMA1_CH6_MEM2MEM,
        .dma_priority_level              = DMA1_CH6_PRIORITY,
        .irq.priority                    = DMA1_CH6_IRQ_PRIORITY,
        .irq.transfer_complete           = DMA1_CH6_IRQ_TRANSFER_COMPLETE,
        .irq.half_transfer_complete      = DMA1_CH6_IRQ_HALF_TRANSFER_COMPLETE,
        .irq.transfer_error              = DMA1_CH6_IRQ_TRANSFER_ERROR,
        .irq.callback                    = DMA1_CH6_IRQ_CALLBACK,
    },

    [6] =
    {
        .base_address_dma_channel        = DMA1_CH7_BASE,
        .channel_number                  = 6,
        .mem2mem                         = DMA1_CH7_MEM2MEM,
        .dma_priority_level              = DMA1_CH7_PRIORITY,
        .irq.priority                    = DMA1_CH7_IRQ_PRIORITY,
        .irq.transfer_complete           = DMA1_CH7_IRQ_TRANSFER_COMPLETE,
        .irq.half_transfer_complete      = DMA1_CH7_IRQ_HALF_TRANSFER_COMPLETE,
        .irq.transfer_error              = DMA1_CH7_IRQ_TRANSFER_ERROR,
        .irq.callback                    = DMA1_CH7_IRQ_CALLBACK,
    },
};

const struct t_exti_config exti_config =
{
    .base_address_exti = EXTI_BASE,
};

const struct t_afio_config afio_config =
{
    .base_address_afio = AFIO_BASE,
};

struct t_gpio_driver gpio_driver[GPIO_PIN_NUMBER] =
{
	[0] =
	{
        .base_address_gpio = GPIOA_BASE,
        .exti_config = &exti_config,
        .afio_config = &afio_config,
        .pin = PA0_PIN,
        .type = PA0_TYPE,
        .peripheral = PORT_A,
        .instance = 0,
        .irq.active = PA0_IRQ_ENABLE,
        .irq.rising = PA0_IRQ_RISING,
        .irq.priority = PA0_IRQ_PRIORITY,
        .irq.callback = PA0_IRQ_CALLBACK,
	},

    [1] =
    {
        .base_address_gpio = GPIOA_BASE,
        .exti_config = &exti_config,
        .afio_config = &afio_config,
        .pin = PA1_PIN,
        .type = PA1_TYPE,
        .peripheral = PORT_A,
        .instance = 1,
        .irq.active = PA1_IRQ_ENABLE,
        .irq.rising = PA1_IRQ_RISING,
        .irq.priority = PA1_IRQ_PRIORITY,
        .irq.callback = PA1_IRQ_CALLBACK,
    },

    [2] =
    {
        .base_address_gpio = GPIOA_BASE,
        .exti_config = &exti_config,
        .afio_config = &afio_config,
        .pin = PA2_PIN,
        .type = PA2_TYPE,
        .peripheral = PORT_A,
        .instance = 2,
        .irq.active = PA2_IRQ_ENABLE,
        .irq.rising = PA2_IRQ_RISING,
        .irq.priority = PA2_IRQ_PRIORITY,
        .irq.callback = PA2_IRQ_CALLBACK,
    },

	[3] =
    {
      .base_address_gpio = GPIOA_BASE,
      .exti_config = &exti_config,
      .afio_config = &afio_config,
      .pin = PA3_PIN,
      .type = PA3_TYPE,
      .peripheral = PORT_A,
      .instance = 3,
      .irq.active = PA3_IRQ_ENABLE,
      .irq.rising = PA3_IRQ_RISING,
      .irq.priority = PA3_IRQ_PRIORITY,
      .irq.callback = PA3_IRQ_CALLBACK,
    },

	[4] =
    {
      .base_address_gpio = GPIOA_BASE,
      .exti_config = &exti_config,
      .afio_config = &afio_config,
      .pin = PA4_PIN,
      .type = PA4_TYPE,
      .peripheral = PORT_A,
      .instance = 4,
      .irq.active = PA4_IRQ_ENABLE,
      .irq.rising = PA4_IRQ_RISING,
      .irq.priority = PA4_IRQ_PRIORITY,
      .irq.callback = PA4_IRQ_CALLBACK,
    },

	[5] =
    {
      .base_address_gpio = GPIOA_BASE,
      .exti_config = &exti_config,
      .afio_config = &afio_config,
      .pin = PA5_PIN,
      .type = PA5_TYPE,
      .peripheral = PORT_A,
      .instance = 5,
      .irq.active = PA5_IRQ_ENABLE,
      .irq.rising = PA5_IRQ_RISING,
      .irq.priority = PA5_IRQ_PRIORITY,
      .irq.callback = PA5_IRQ_CALLBACK,
    },

	[6] =
    {
      .base_address_gpio = GPIOA_BASE,
      .exti_config = &exti_config,
      .afio_config = &afio_config,
      .pin = PA6_PIN,
      .type = PA6_TYPE,
      .peripheral = PORT_A,
      .instance = 6,
      .irq.active = PA6_IRQ_ENABLE,
      .irq.rising = PA6_IRQ_RISING,
      .irq.priority = PA6_IRQ_PRIORITY,
      .irq.callback = PA6_IRQ_CALLBACK,
    },

	[7] =
    {
      .base_address_gpio = GPIOA_BASE,
      .exti_config = &exti_config,
      .afio_config = &afio_config,
      .pin = PA7_PIN,
      .type = PA7_TYPE,
      .peripheral = PORT_A,
      .instance = 7,
      .irq.active = PA7_IRQ_ENABLE,
      .irq.rising = PA7_IRQ_RISING,
      .irq.priority = PA7_IRQ_PRIORITY,
      .irq.callback = PA7_IRQ_CALLBACK,
    },

	[8] =
    {
      .base_address_gpio = GPIOA_BASE,
      .exti_config = &exti_config,
      .afio_config = &afio_config,
      .pin = PA8_PIN,
      .type = PA8_TYPE,
      .peripheral = PORT_A,
      .instance = 8,
      .irq.active = PA8_IRQ_ENABLE,
      .irq.rising = PA8_IRQ_RISING,
      .irq.priority = PA8_IRQ_PRIORITY,
      .irq.callback = PA8_IRQ_CALLBACK,
    },

	[9] =
    {
      .base_address_gpio = GPIOA_BASE,
      .exti_config = &exti_config,
      .afio_config = &afio_config,
      .pin = PA9_PIN,
      .type = PA9_TYPE,
      .peripheral = PORT_A,
      .instance = 9,
      .irq.active = PA9_IRQ_ENABLE,
      .irq.rising = PA9_IRQ_RISING,
      .irq.priority = PA9_IRQ_PRIORITY,
      .irq.callback = PA9_IRQ_CALLBACK,
    },

	[10] =
    {
      .base_address_gpio = GPIOA_BASE,
      .exti_config = &exti_config,
      .afio_config = &afio_config,
      .pin = PA10_PIN,
      .type = PA10_TYPE,
      .peripheral = PORT_A,
      .instance = 10,
      .irq.active = PA10_IRQ_ENABLE,
      .irq.rising = PA10_IRQ_RISING,
      .irq.priority = PA10_IRQ_PRIORITY,
      .irq.callback = PA10_IRQ_CALLBACK,
    },

	[11] =
    {
      .base_address_gpio = GPIOA_BASE,
      .exti_config = &exti_config,
      .afio_config = &afio_config,
      .pin = PA11_PIN,
      .type = PA11_TYPE,
      .peripheral = PORT_A,
      .instance = 11,
      .irq.active = PA11_IRQ_ENABLE,
      .irq.rising = PA11_IRQ_RISING,
      .irq.priority = PA11_IRQ_PRIORITY,
      .irq.callback = PA11_IRQ_CALLBACK,
    },

	[12] =
    {
      .base_address_gpio = GPIOA_BASE,
      .exti_config = &exti_config,
      .afio_config = &afio_config,
      .pin = PA12_PIN,
      .type = PA12_TYPE,
      .peripheral = PORT_A,
      .instance = 12,
      .irq.active = PA12_IRQ_ENABLE,
      .irq.rising = PA12_IRQ_RISING,
      .irq.priority = PA12_IRQ_PRIORITY,
      .irq.callback = PA12_IRQ_CALLBACK,
    },

	[13] =
    {
      .base_address_gpio = GPIOA_BASE,
      .exti_config = &exti_config,
      .afio_config = &afio_config,
      .pin = PA13_PIN,
      .type = PA13_TYPE,
      .peripheral = PORT_A,
      .instance = 13,
      .irq.active = PA13_IRQ_ENABLE,
      .irq.rising = PA13_IRQ_RISING,
      .irq.priority = PA13_IRQ_PRIORITY,
      .irq.callback = PA13_IRQ_CALLBACK,
    },

	[14] =
    {
      .base_address_gpio = GPIOA_BASE,
      .exti_config = &exti_config,
      .afio_config = &afio_config,
      .pin = PA14_PIN,
      .type = PA14_TYPE,
      .peripheral = PORT_A,
      .instance = 14,
      .irq.active = PA14_IRQ_ENABLE,
      .irq.rising = PA14_IRQ_RISING,
      .irq.priority = PA14_IRQ_PRIORITY,
      .irq.callback = PA14_IRQ_CALLBACK,
    },

	[15] =
    {
      .base_address_gpio = GPIOA_BASE,
      .exti_config = &exti_config,
      .afio_config = &afio_config,
      .pin = PA15_PIN,
      .type = PA15_TYPE,
      .peripheral = PORT_A,
      .instance = 15,
      .irq.active = PA15_IRQ_ENABLE,
      .irq.rising = PA15_IRQ_RISING,
      .irq.priority = PA15_IRQ_PRIORITY,
      .irq.callback = PA15_IRQ_CALLBACK,
    },

	[16] =
    {
      .base_address_gpio = GPIOB_BASE,
      .exti_config = &exti_config,
      .afio_config = &afio_config,
      .pin = PB0_PIN,
      .type = PB0_TYPE,
      .peripheral = PORT_B,
      .instance = 16,
      .irq.active = PB0_IRQ_ENABLE,
      .irq.rising = PB0_IRQ_RISING,
      .irq.priority = PB0_IRQ_PRIORITY,
      .irq.callback = PB0_IRQ_CALLBACK,
    },

	[17] =
    {
      .base_address_gpio = GPIOB_BASE,
      .exti_config = &exti_config,
      .afio_config = &afio_config,
      .pin = PB1_PIN,
      .type = PB1_TYPE,
      .peripheral = PORT_B,
      .instance = 17,
      .irq.active = PB1_IRQ_ENABLE,
      .irq.rising = PB1_IRQ_RISING,
      .irq.priority = PB1_IRQ_PRIORITY,
      .irq.callback = PB1_IRQ_CALLBACK,
    },

	[18] =
    {
      .base_address_gpio = GPIOB_BASE,
      .exti_config = &exti_config,
      .afio_config = &afio_config,
      .pin = PB2_PIN,
      .type = PB2_TYPE,
      .peripheral = PORT_B,
      .instance = 18,
      .irq.active = PB2_IRQ_ENABLE,
      .irq.rising = PB2_IRQ_RISING,
      .irq.priority = PB2_IRQ_PRIORITY,
      .irq.callback = PB2_IRQ_CALLBACK,
    },

	[19] =
    {
      .base_address_gpio = GPIOB_BASE,
      .exti_config = &exti_config,
      .afio_config = &afio_config,
      .pin = PB3_PIN,
      .type = PB3_TYPE,
      .peripheral = PORT_B,
      .instance = 19,
      .irq.active = PB3_IRQ_ENABLE,
      .irq.rising = PB3_IRQ_RISING,
      .irq.priority = PB3_IRQ_PRIORITY,
      .irq.callback = PB3_IRQ_CALLBACK,
    },

	[20] =
    {
      .base_address_gpio = GPIOB_BASE,
      .exti_config = &exti_config,
      .afio_config = &afio_config,
      .pin = PB4_PIN,
      .type = PB4_TYPE,
      .peripheral = PORT_B,
      .instance = 20,
      .irq.active = PB4_IRQ_ENABLE,
      .irq.rising = PB4_IRQ_RISING,
      .irq.priority = PB4_IRQ_PRIORITY,
      .irq.callback = PB4_IRQ_CALLBACK,
    },

	[21] =
    {
      .base_address_gpio = GPIOB_BASE,
      .exti_config = &exti_config,
      .afio_config = &afio_config,
      .pin = PB5_PIN,
      .type = PB5_TYPE,
      .peripheral = PORT_B,
      .instance = 21,
      .irq.active = PB5_IRQ_ENABLE,
      .irq.rising = PB5_IRQ_RISING,
      .irq.priority = PB5_IRQ_PRIORITY,
      .irq.callback = PB5_IRQ_CALLBACK,
    },

    [22] =
    {
     .base_address_gpio = GPIOB_BASE,
     .exti_config = &exti_config,
     .afio_config = &afio_config,
     .pin = PB6_PIN,
     .type = PB6_TYPE,
     .peripheral = PORT_B,
     .instance = 22,
     .irq.active = PB6_IRQ_ENABLE,
     .irq.rising = PB6_IRQ_RISING,
     .irq.priority = PB6_IRQ_PRIORITY,
     .irq.callback = PB6_IRQ_CALLBACK,
    },

	[23] =
    {
      .base_address_gpio = GPIOB_BASE,
      .exti_config = &exti_config,
      .afio_config = &afio_config,
      .pin = PB7_PIN,
      .type = PB7_TYPE,
      .peripheral = PORT_B,
      .instance = 23,
      .irq.active = PB7_IRQ_ENABLE,
      .irq.rising = PB7_IRQ_RISING,
      .irq.priority = PB7_IRQ_PRIORITY,
      .irq.callback = PB7_IRQ_CALLBACK,
    },

	[24] =
    {
      .base_address_gpio = GPIOB_BASE,
      .exti_config = &exti_config,
      .afio_config = &afio_config,
      .pin = PB8_PIN,
      .type = PB8_TYPE,
      .peripheral = PORT_B,
      .instance = 24,
      .irq.active = PB8_IRQ_ENABLE,
      .irq.rising = PB8_IRQ_RISING,
      .irq.priority = PB8_IRQ_PRIORITY,
      .irq.callback = PB8_IRQ_CALLBACK,
    },

	[25] =
    {
      .base_address_gpio = GPIOB_BASE,
      .exti_config = &exti_config,
      .afio_config = &afio_config,
      .pin = PB9_PIN,
      .type = PB9_TYPE,
      .peripheral = PORT_B,
      .instance = 25,
      .irq.active = PB9_IRQ_ENABLE,
      .irq.rising = PB9_IRQ_RISING,
      .irq.priority = PB9_IRQ_PRIORITY,
      .irq.callback = PB9_IRQ_CALLBACK,
    },

	[26] =
    {
      .base_address_gpio = GPIOB_BASE,
      .exti_config = &exti_config,
      .afio_config = &afio_config,
      .pin = PB10_PIN,
      .type = PB10_TYPE,
      .peripheral = PORT_B,
      .instance = 26,
      .irq.active = PB10_IRQ_ENABLE,
      .irq.rising = PB10_IRQ_RISING,
      .irq.priority = PB10_IRQ_PRIORITY,
      .irq.callback = PB10_IRQ_CALLBACK,
    },

	[27] =
    {
      .base_address_gpio = GPIOB_BASE,
      .exti_config = &exti_config,
      .afio_config = &afio_config,
      .pin = PB11_PIN,
      .type = PB11_TYPE,
      .peripheral = PORT_B,
      .instance = 27,
      .irq.active = PB11_IRQ_ENABLE,
      .irq.rising = PB11_IRQ_RISING,
      .irq.priority = PB11_IRQ_PRIORITY,
      .irq.callback = PB11_IRQ_CALLBACK,
    },

	[28] =
    {
      .base_address_gpio = GPIOB_BASE,
      .exti_config = &exti_config,
      .afio_config = &afio_config,
      .pin = PB12_PIN,
      .type = PB12_TYPE,
      .peripheral = PORT_B,
      .instance = 28,
      .irq.active = PB12_IRQ_ENABLE,
      .irq.rising = PB12_IRQ_RISING,
      .irq.priority = PB12_IRQ_PRIORITY,
      .irq.callback = PB12_IRQ_CALLBACK,
    },

	[29] =
    {
      .base_address_gpio = GPIOB_BASE,
      .exti_config = &exti_config,
      .afio_config = &afio_config,
      .pin = PB13_PIN,
      .type = PB13_TYPE,
      .peripheral = PORT_B,
      .instance = 29,
      .irq.active = PB13_IRQ_ENABLE,
      .irq.rising = PB13_IRQ_RISING,
      .irq.priority = PB13_IRQ_PRIORITY,
      .irq.callback = PB13_IRQ_CALLBACK,
    },

	[30] =
    {
      .base_address_gpio = GPIOB_BASE,
      .exti_config = &exti_config,
      .afio_config = &afio_config,
      .pin = PB14_PIN,
      .type = PB14_TYPE,
      .peripheral = PORT_B,
      .instance = 30,
      .irq.active = PB14_IRQ_ENABLE,
      .irq.rising = PB14_IRQ_RISING,
      .irq.priority = PB14_IRQ_PRIORITY,
      .irq.callback = PB14_IRQ_CALLBACK,
    },

	[31] =
    {
      .base_address_gpio = GPIOB_BASE,
      .exti_config = &exti_config,
      .afio_config = &afio_config,
      .pin = PB15_PIN,
      .type = PB15_TYPE,
      .peripheral = PORT_B,
      .instance = 31,
      .irq.active = PB15_IRQ_ENABLE,
      .irq.rising = PB15_IRQ_RISING,
      .irq.priority = PB15_IRQ_PRIORITY,
      .irq.callback = PB15_IRQ_CALLBACK,
    },

	[32] =
    {
      .base_address_gpio = GPIOC_BASE,
      .exti_config = &exti_config,
      .afio_config = &afio_config,
      .pin = PC13_PIN,
      .type = PC13_TYPE,
      .peripheral = PORT_C,
      .instance = 32,
      .irq.active = PC13_IRQ_ENABLE,
      .irq.rising = PC13_IRQ_RISING,
      .irq.priority = PC13_IRQ_PRIORITY,
      .irq.callback = PC13_IRQ_CALLBACK,
    },

	[33] =
    {
      .base_address_gpio = GPIOC_BASE,
      .exti_config = &exti_config,
      .afio_config = &afio_config,
      .pin = PC14_PIN,
      .type = PC14_TYPE,
      .peripheral = PORT_C,
      .instance = 33,
      .irq.active = PC14_IRQ_ENABLE,
      .irq.rising = PC14_IRQ_RISING,
      .irq.priority = PC14_IRQ_PRIORITY,
      .irq.callback = PC14_IRQ_CALLBACK,
    },

	[34] =
    {
      .base_address_gpio = GPIOC_BASE,
      .exti_config = &exti_config,
      .afio_config = &afio_config,
      .pin = PC15_PIN,
      .type = PC15_TYPE,
      .peripheral = PORT_C,
      .instance = 34,
      .irq.active = PC15_IRQ_ENABLE,
      .irq.rising = PC15_IRQ_RISING,
      .irq.priority = PC15_IRQ_PRIORITY,
      .irq.callback = PC15_IRQ_CALLBACK,
    },

	[35] =
    {
      .base_address_gpio = GPIOD_BASE,
      .exti_config = &exti_config,
      .afio_config = &afio_config,
      .pin = PD0_PIN,
      .type = PD0_TYPE,
      .peripheral = PORT_D,
      .instance = 35,
      .irq.active = PD0_IRQ_ENABLE,
      .irq.rising = PD0_IRQ_RISING,
      .irq.priority = PD0_IRQ_PRIORITY,
      .irq.callback = PD0_IRQ_CALLBACK,
    },


  [36] =
    {
      .base_address_gpio = GPIOD_BASE,
      .exti_config = &exti_config,
      .afio_config = &afio_config,
      .pin = PD1_PIN,
      .type = PD1_TYPE,
      .peripheral = PORT_D,
      .instance = 36,
      .irq.active = PD1_IRQ_ENABLE,
      .irq.rising = PD1_IRQ_RISING,
      .irq.priority = PD1_IRQ_PRIORITY,
      .irq.callback = PD1_IRQ_CALLBACK,
    },
};

struct t_timer_cfg timx_chanelx_cfg [TIMER_IP_NUMBER] =
{
	[0] =
	{
		.timer = TIM1,
		.time_frequency = TIM1_TIME_FREQUENCY,
		.channel[0] =
		{
		    .channel_enable = TIM1_CH1_ENABLE,
		    .timer_mode = TIM1_CH1_MODE,
		    .tim_mux = TIM1_CH1_TIM_MUX,
		    .percent_pwm = TIM1_CH1_PERCENT_PWM,
		    .polarity = TIM1_CH1_POLARITY,
		    .irq_dma.active = TIM1_CH1_IRQ_DMA_ENABLE,
		    //.irq_dma.edge = TIM1_CH1_IRQ_DMA_ENABLE,
		    .irq_dma.priority = TIM1_CH1_IRQ_DMA_PRIORITY,
//		    .irq_dma.callback = TIM1_CH1_IRQ_DMA_CALLBACK,
		    .out_cmp_mode = TIM1_CH1_OC_MODE,
		},
		.channel[1] =
		{
			.channel_enable = TIM1_CH2_ENABLE,
		    .timer_mode = TIM1_CH2_MODE,
		    .tim_mux = TIM1_CH2_TIM_MUX,
		    .percent_pwm = TIM1_CH2_PERCENT_PWM,
		    .polarity = TIM1_CH2_POLARITY,
		    .irq_dma.active = TIM1_CH2_IRQ_DMA_ENABLE,
		    //.irq_dma.edge = TIM1_CH2_IRQ_DMA_ENABLE,
		    .irq_dma.priority = TIM1_CH2_IRQ_DMA_PRIORITY,
//		    .irq_dma.callback = TIM1_CH2_IRQ_DMA_CALLBACK,
		    .out_cmp_mode = TIM1_CH2_OC_MODE,
		},
		.channel[2] =
		{
			.channel_enable = TIM1_CH3_ENABLE,
		    .timer_mode = TIM1_CH3_MODE,
		    .tim_mux = TIM1_CH3_TIM_MUX,
		    .percent_pwm = TIM1_CH3_PERCENT_PWM,
		    .polarity = TIM1_CH3_POLARITY,
		    .irq_dma.active = TIM1_CH3_IRQ_DMA_ENABLE,
		    //.irq_dma.edge = TIM1_CH3_IRQ_DMA_ENABLE,
		    .irq_dma.priority = TIM1_CH3_IRQ_DMA_PRIORITY,
//		    .irq_dma.callback = TIM1_CH3_IRQ_DMA_CALLBACK,
		    .out_cmp_mode = TIM1_CH3_OC_MODE,
		},
		.channel[3] =
		{
			.channel_enable = TIM1_CH4_ENABLE,
		    .timer_mode = TIM1_CH4_MODE,
		    .tim_mux = TIM1_CH4_TIM_MUX,
		    .percent_pwm = TIM1_CH4_PERCENT_PWM,
		    .polarity = TIM1_CH4_POLARITY,
		    .irq_dma.active = TIM1_CH4_IRQ_DMA_ENABLE,
		    //.irq_dma.edge = TIM1_CH4_IRQ_DMA_ENABLE,
		    .irq_dma.priority = TIM1_CH4_IRQ_DMA_PRIORITY,
//		    .irq_dma.callback = TIM1_CH4_IRQ_DMA_CALLBACK,
		    .out_cmp_mode = TIM1_CH4_OC_MODE,
		},
	},
	[1] =
	{
		.timer = TIM2,
	    .time_frequency = TIM2_TIME_FREQUENCY,
	    .channel[0] =
	    {
    		.channel_enable = TIM2_CH1_ENABLE,
   		    .timer_mode = TIM2_CH1_MODE,
   		    .tim_mux = TIM2_CH1_TIM_MUX,
   		    .percent_pwm = TIM2_CH1_PERCENT_PWM,
  		    .polarity = TIM2_CH1_POLARITY,
   		    .irq_dma.active = TIM2_CH1_IRQ_DMA_ENABLE,
   		    //.irq_dma.edge = TIM2_CH1_IRQ_DMA_ENABLE,
   		    .irq_dma.priority = TIM2_CH1_IRQ_DMA_PRIORITY,
 //  		    .irq_dma.callback = TIM2_CH1_IRQ_DMA_CALLBACK,
   		    .out_cmp_mode = TIM2_CH1_OC_MODE,
	    },
		.channel[1] =
		{
			.channel_enable = TIM2_CH2_ENABLE,
		    .timer_mode = TIM2_CH2_MODE,
		    .tim_mux = TIM2_CH2_TIM_MUX,
		    .percent_pwm = TIM2_CH2_PERCENT_PWM,
		    .polarity = TIM2_CH2_POLARITY,
		    .irq_dma.active = TIM2_CH2_IRQ_DMA_ENABLE,
		    //.irq_dma.edge = TIM2_CH2_IRQ_DMA_ENABLE,
		    .irq_dma.priority = TIM2_CH2_IRQ_DMA_PRIORITY,
//		    .irq_dma.callback = TIM2_CH2_IRQ_DMA_CALLBACK,
		    .out_cmp_mode = TIM2_CH2_OC_MODE,
		},
		.channel[2] =
		{
			.channel_enable = TIM2_CH3_ENABLE,
		    .timer_mode = TIM2_CH3_MODE,
		    .tim_mux = TIM2_CH3_TIM_MUX,
		    .percent_pwm = TIM2_CH3_PERCENT_PWM,
		    .polarity = TIM2_CH3_POLARITY,
		    .irq_dma.active = TIM2_CH3_IRQ_DMA_ENABLE,
		    //.irq_dma.edge = TIM2_CH3_IRQ_DMA_ENABLE,
		    .irq_dma.priority = TIM2_CH3_IRQ_DMA_PRIORITY,
//		    .irq_dma.callback = TIM2_CH3_IRQ_DMA_CALLBACK,
		    .out_cmp_mode = TIM2_CH3_OC_MODE,
		},
		.channel[3] =
		{
			.channel_enable = TIM2_CH4_ENABLE,
		    .timer_mode = TIM2_CH4_MODE,
		    .tim_mux = TIM2_CH3_TIM_MUX,
		    .percent_pwm = TIM2_CH3_PERCENT_PWM,
		    .polarity = TIM2_CH3_POLARITY,
		    .irq_dma.active = TIM2_CH3_IRQ_DMA_ENABLE,
		    //.irq_dma.edge = TIM2_CH3_IRQ_DMA_ENABLE,
		    .irq_dma.priority = TIM2_CH3_IRQ_DMA_PRIORITY,
//		    .irq_dma.callback = TIM2_CH3_IRQ_DMA_CALLBACK,
		    .out_cmp_mode = TIM2_CH3_OC_MODE,
		},
	},
	[2] =
	{
		.timer = TIM3,
	    .time_frequency = TIM3_TIME_FREQUENCY,
		.channel[0] =
		{
			.channel_enable = TIM3_CH1_ENABLE,
		    .timer_mode = TIM3_CH1_MODE,
		    .tim_mux = TIM3_CH1_TIM_MUX,
		    .percent_pwm = TIM3_CH1_PERCENT_PWM,
		    .polarity = TIM3_CH1_POLARITY,
		    .irq_dma.active = TIM3_CH1_IRQ_DMA_ENABLE,
		    //.irq_dma.edge = TIM3_CH1_IRQ_DMA_ENABLE,
		    .irq_dma.priority = TIM3_CH1_IRQ_DMA_PRIORITY,
//		    .irq_dma.callback = TIM3_CH1_IRQ_DMA_CALLBACK,
		    .out_cmp_mode = TIM3_CH1_OC_MODE,
		},
		.channel[1] =
		{
			.channel_enable = TIM3_CH2_ENABLE,
		    .timer_mode = TIM3_CH2_MODE,
		    .tim_mux = TIM3_CH2_TIM_MUX,
		    .percent_pwm = TIM3_CH2_PERCENT_PWM,
		    .polarity = TIM3_CH2_POLARITY,
		    .irq_dma.active = TIM3_CH2_IRQ_DMA_ENABLE,
		    //.irq_dma.edge = TIM3_CH2_IRQ_DMA_ENABLE,
		    .irq_dma.priority = TIM3_CH2_IRQ_DMA_PRIORITY,
//		    .irq_dma.callback = TIM3_CH2_IRQ_DMA_CALLBACK,
		    .out_cmp_mode = TIM3_CH2_OC_MODE,
		},
		.channel[2] =
		{
			.channel_enable = TIM3_CH3_ENABLE,
		    .timer_mode = TIM3_CH3_MODE,
		    .tim_mux = TIM3_CH3_TIM_MUX,
		    .percent_pwm = TIM3_CH3_PERCENT_PWM,
		    .polarity = TIM3_CH3_POLARITY,
		    .irq_dma.active = TIM3_CH3_IRQ_DMA_ENABLE,
		    //.irq_dma.edge = TIM3_CH3_IRQ_DMA_ENABLE,
		    .irq_dma.priority = TIM3_CH3_IRQ_DMA_PRIORITY,
//		    .irq_dma.callback = TIM3_CH3_IRQ_DMA_CALLBACK,
		    .out_cmp_mode = TIM3_CH3_OC_MODE,
		},
		.channel[3] =
		{
			.channel_enable = TIM3_CH4_ENABLE,
		    .timer_mode = TIM3_CH4_MODE,
		    .tim_mux = TIM3_CH3_TIM_MUX,
		    .percent_pwm = TIM3_CH3_PERCENT_PWM,
		    .polarity = TIM3_CH3_POLARITY,
		    .irq_dma.active = TIM3_CH3_IRQ_DMA_ENABLE,
		    //.irq_dma.edge = TIM3_CH3_IRQ_DMA_ENABLE,
		    .irq_dma.priority = TIM3_CH3_IRQ_DMA_PRIORITY,
//		    .irq_dma.callback = TIM3_CH3_IRQ_DMA_CALLBACK,
		    .out_cmp_mode = TIM3_CH3_OC_MODE,
		},
	},
};

struct t_spi_driver spi_driver[SPI_IP_NUMBER] =
{
    [0] =
    {
        .base_address = SPI1_BASE,
        .peripheral = SPI1,
        .instance = 0,
        .irq.active = SPI1_IRQ_ENABLE,
        .irq.priority = SPI1_IRQ_PRIORITY,
        .dma.active = SPI1_DMA_ENABLE,
        .dma.tx_channel = &dma_channel_driver[2],
        .dma.rx_channel = &dma_channel_driver[1],
    },

    [1] =
    {
        .base_address = SPI2_BASE,
        .peripheral = SPI2,
        .instance = 1,
        .irq.active = SPI2_IRQ_ENABLE,
        .irq.priority = SPI2_IRQ_PRIORITY,
        .dma.active = SPI2_DMA_ENABLE,
        .dma.tx_channel = &dma_channel_driver[4],
        .dma.rx_channel = &dma_channel_driver[3],
    },
};

struct t_usart_driver usart_driver[USART_IP_NUMBER] =
{
    [0] =
    {
        .base_address   = USART1_BASE,
        .peripheral     = USART1,
        .instance       = 0,
        .baudrate       = USART1_BAUDRATE,
        .data_length    = USART1_LENGTH,
        .parity         = USART1_PARITY,
        .stop_bit       = USART1_STOP_BITS,
        .irq.active     = USART1_IRQ_ACTIVE,
        .irq.priority   = USART1_IRQ_PRIORITY,
        .dma.active     = USART1_DMA_ACTIVE,
        .dma.tx_channel = &dma_channel_driver[3],
        .dma.rx_channel = &dma_channel_driver[4],
    },

    [1] =
    {
        .base_address   = USART2_BASE,
        .peripheral     = USART2,
        .instance       = 1,
        .baudrate       = USART2_BAUDRATE,
        .data_length    = USART2_LENGTH,
        .parity         = USART2_PARITY,
        .stop_bit       = USART2_STOP_BITS,
        .irq.active     = USART2_IRQ_ACTIVE,
        .irq.priority   = USART2_IRQ_PRIORITY,
        .dma.active     = USART2_DMA_ACTIVE,
        .dma.tx_channel = 0,
        .dma.rx_channel = 0,
    },
};


/* Static driver structures. */
struct t_gpio_driver gpio_driver[GPIO_PIN_NUMBER];
struct t_spi_driver spi_driver[SPI_IP_NUMBER];

/* Labels */
struct t_gpio_driver *pa0  = &gpio_driver[0];
struct t_gpio_driver *pa1  = &gpio_driver[1];
struct t_gpio_driver *pa2  = &gpio_driver[2];
struct t_gpio_driver *pa3  = &gpio_driver[3];
struct t_gpio_driver *pa4  = &gpio_driver[4];
struct t_gpio_driver *pa5  = &gpio_driver[5];
struct t_gpio_driver *pa6  = &gpio_driver[6];
struct t_gpio_driver *pa7  = &gpio_driver[7];
struct t_gpio_driver *pa8  = &gpio_driver[8];
struct t_gpio_driver *pa9  = &gpio_driver[9];
struct t_gpio_driver *pa10 = &gpio_driver[10];
struct t_gpio_driver *pa11 = &gpio_driver[11];
struct t_gpio_driver *pa12 = &gpio_driver[12];
struct t_gpio_driver *pa13 = &gpio_driver[13];
struct t_gpio_driver *pa14 = &gpio_driver[14];
struct t_gpio_driver *pa15 = &gpio_driver[15];

struct t_gpio_driver *pbo  = &gpio_driver[16];
struct t_gpio_driver *pb1  = &gpio_driver[17];
struct t_gpio_driver *pb2  = &gpio_driver[18];
struct t_gpio_driver *pb3  = &gpio_driver[19];
struct t_gpio_driver *pb4  = &gpio_driver[20];
struct t_gpio_driver *pb5  = &gpio_driver[21];
struct t_gpio_driver *pb6  = &gpio_driver[22];
struct t_gpio_driver *pb7  = &gpio_driver[23];
struct t_gpio_driver *pb8  = &gpio_driver[24];
struct t_gpio_driver *pb9  = &gpio_driver[25];
struct t_gpio_driver *pb10 = &gpio_driver[26];
struct t_gpio_driver *pb11 = &gpio_driver[27];
struct t_gpio_driver *pb12 = &gpio_driver[28];
struct t_gpio_driver *pb13 = &gpio_driver[29];
struct t_gpio_driver *pb14 = &gpio_driver[30];
struct t_gpio_driver *pb15 = &gpio_driver[31];

struct t_gpio_driver *pc13 = &gpio_driver[32];
struct t_gpio_driver *pc14 = &gpio_driver[33];
struct t_gpio_driver *pc15 = &gpio_driver[34];

struct t_gpio_driver *pd0  = &gpio_driver[35];
struct t_gpio_driver *pd1  = &gpio_driver[36];

struct t_dma_channel_driver *dma_ch1  = &dma_channel_driver[0];
struct t_dma_channel_driver *dma_ch2  = &dma_channel_driver[1];
struct t_dma_channel_driver *dma_ch3  = &dma_channel_driver[2];
struct t_dma_channel_driver *dma_ch4  = &dma_channel_driver[3];
struct t_dma_channel_driver *dma_ch5  = &dma_channel_driver[4];
struct t_dma_channel_driver *dma_ch6  = &dma_channel_driver[5];
struct t_dma_channel_driver *dma_ch7  = &dma_channel_driver[6];

struct t_spi_driver *nrf24l01 = &spi_driver[0];
struct t_spi_driver *max_xxxx = &spi_driver[1];

struct t_usart_driver *usart1 = &usart_driver[0];
struct t_usart_driver *usart2 = &usart_driver[1];


void soc_core_configuration(void)
{
	clock_init(&clock_driver, &clock_config);
}

void soc_peripherals_configuration(void)
{
    for(uint8_t index = 0; index < GPIO_PIN_NUMBER; index++)
    {
        gpio_initialization(&gpio_driver[index]);
    }

    for(uint8_t index = 0; index < DMA_IP_NUMBER; index++)
    {
        for(uint8_t index_channel = 0; index_channel < DMA_CHANNEL_NUMBER; index_channel++)
        {
            dma_initialization(&dma_driver[index], &dma_channel_driver[index_channel]);
        }
    }

    for(uint8_t index = 0; index < SPI_IP_NUMBER; index++)
    {
        spi_initialization(&spi_driver[index]);
    }

    for(uint8_t index = 0; index < USART_IP_NUMBER; index++)
    {
        usart_initialization(&usart_driver[index]);
    }

//    timer_init(&timx_chanelx_cfg[0]);
//    timer_init(&timx_chanelx_cfg[1]);
//    timer_init(&timx_chanelx_cfg[2]);
}
