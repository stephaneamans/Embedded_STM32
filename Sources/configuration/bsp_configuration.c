#include "bsp_configuration.h"

const struct t_clock_config clock_config =
{
	.sys_clk_freq = SYS_CLK,
	.AHB_clk_freq = AHB_CLK,
	.APB1_clk_freq = APB1_CLK,
	.APB2_clk_freq = APB2_CLK,
	.source = SOURCE,
};

const struct t_usart_config usartx_cfg[USART_IP_NUMBER] =
{
	[0] =
	{
	    .reg = USART1_REGS,
	    .baudrate = USART1_BAUDRATE,
	    .length = USART1_LENGTH,
	    .parity = USART1_PARITY,
	    .stop = USART1_STOP_BITS,
	    .mode = USART1_MODE,
	    .irq_dma.priority = USART1_IRQ_DMA_PRIORITY,
	    .irq_dma.tx_dma_channel = USART1_DMA_DRIVER_TX,
	    .irq_dma.rx_dma_channel = USART1_DMA_DRIVER_RX,
	},

	[1] =
	{
		.reg = USART2_REGS,
	    .baudrate = USART2_BAUDRATE,
	    .length = USART2_LENGTH,
	    .parity = USART2_PARITY,
	    .stop = USART2_STOP_BITS,
	    .mode = USART2_MODE,
	    .irq_dma.priority = USART2_IRQ_DMA_PRIORITY,
	    .irq_dma.tx_dma_channel = USART2_DMA_DRIVER_TX,
	    .irq_dma.rx_dma_channel = USART2_DMA_DRIVER_RX,
	},
};

const struct t_dma_channel_cfg dma1_chx_cfg[DMA_CHANNELS_NUMBER] =
{
	[0] =
	{
	    .reg                             = DMA1_Ch1,
    	.mem2mem                         = DMA1_CH1_MEM2MEM,
	    .dma_priority                    = DMA1_CH1_PRIORITY,
    	.mem_data_type                   = DMA1_CH1_MEM_DATA_TYPE,
	    .memory_zone_size                = DMA1_CH1_MEMORY_ZONE_SIZE,
    	.memory_zone_address             = DMA1_CH1_MEMORY_ZONE_ADDRESS,
//	    .peripheral_address              = (uint32_t)usartx_cfg[0].reg,
    	.periph_data_type                = DMA1_CH1_PERIPH_DATA_TYPE,
	    .memory_increment                = DMA1_CH1_MEMORY_INCREMENT,
    	.peripheral_increment            = DMA1_CH1_PERIPHERAL_INCREMENT,
	    .read_from_memory                = DMA1_CH1_READ_FROM_MEMORY,
    	.irq.transfer_error_interrupt    = DMA1_CH1_IRQ_TRANSFER_ERROR,
	    .irq.half_transfer_interrupt     = DMA1_CH1_IRQ_HALF_TRANSFER,
    	.irq.transfer_complete_interrupt = DMA1_CH1_IRQ_TRANSFER_COMPLETE,
		.irq.callback                    = 0,
	},

	[1] =
	{
        .reg                             = DMA1_Ch2,
    	.mem2mem                         = DMA1_CH2_MEM2MEM,
	    .dma_priority                    = DMA1_CH2_PRIORITY,
    	.mem_data_type                   = DMA1_CH2_MEM_DATA_TYPE,
	    .memory_zone_size                = DMA1_CH2_MEMORY_ZONE_SIZE,
    	.memory_zone_address             = DMA1_CH2_MEMORY_ZONE_ADDRESS,
        .peripheral_address              = DMA1_CH2_PERIPHERAL_ADDRESS,
    	.periph_data_type                = DMA1_CH2_PERIPH_DATA_TYPE,
	    .memory_increment                = DMA1_CH2_MEMORY_INCREMENT,
    	.peripheral_increment            = DMA1_CH2_PERIPHERAL_INCREMENT,
	    .read_from_memory                = DMA1_CH2_READ_FROM_MEMORY,
    	.irq.transfer_error_interrupt    = DMA1_CH2_IRQ_TRANSFER_ERROR,
	    .irq.half_transfer_interrupt     = DMA1_CH2_IRQ_HALF_TRANSFER,
    	.irq.transfer_complete_interrupt = DMA1_CH2_IRQ_TRANSFER_COMPLETE,
	    .irq.priority                    = DMA1_CH2_IRQ_PRIORITY,
		.irq.callback                    = 0,
	},

	[2] =
	{
	    .reg                             = DMA1_Ch3,
    	.mem2mem                         = DMA1_CH3_MEM2MEM,
	    .dma_priority                    = DMA1_CH3_PRIORITY,
    	.mem_data_type                   = DMA1_CH3_MEM_DATA_TYPE,
	    .memory_zone_size                = DMA1_CH3_MEMORY_ZONE_SIZE,
    	.memory_zone_address             = DMA1_CH3_MEMORY_ZONE_ADDRESS,
	    .peripheral_address              = DMA1_CH3_PERIPHERAL_ADDRESS,
    	.periph_data_type                = DMA1_CH3_PERIPH_DATA_TYPE,
	    .memory_increment                = DMA1_CH3_MEMORY_INCREMENT,
    	.peripheral_increment            = DMA1_CH3_PERIPHERAL_INCREMENT,
	    .read_from_memory                = DMA1_CH3_READ_FROM_MEMORY,
    	.irq.transfer_error_interrupt    = DMA1_CH3_IRQ_TRANSFER_ERROR,
	    .irq.half_transfer_interrupt     = DMA1_CH3_IRQ_HALF_TRANSFER,
    	.irq.transfer_complete_interrupt = DMA1_CH3_IRQ_TRANSFER_COMPLETE,
	    .irq.priority                    = DMA1_CH3_IRQ_PRIORITY,
		.irq.callback                    = 0,
	},

	[3] =
	{
	    .reg                             = DMA1_Ch4,
        .mem2mem                         = DMA1_CH4_MEM2MEM,
        .dma_priority                    = DMA1_CH4_PRIORITY,
    	.mem_data_type                   = DMA1_CH4_MEM_DATA_TYPE,
	    .memory_zone_size                = DMA1_CH4_MEMORY_ZONE_SIZE,
    	.memory_zone_address             = DMA1_CH4_MEMORY_ZONE_ADDRESS,
	    .peripheral_address              = DMA1_CH4_PERIPHERAL_ADDRESS,
    	.periph_data_type                = DMA1_CH4_PERIPH_DATA_TYPE,
	    .memory_increment                = DMA1_CH4_MEMORY_INCREMENT,
    	.peripheral_increment            = DMA1_CH4_PERIPHERAL_INCREMENT,
	    .read_from_memory                = DMA1_CH4_READ_FROM_MEMORY,
    	.irq.transfer_error_interrupt    = DMA1_CH4_IRQ_TRANSFER_ERROR,
	    .irq.half_transfer_interrupt     = DMA1_CH4_IRQ_HALF_TRANSFER,
    	.irq.transfer_complete_interrupt = DMA1_CH4_IRQ_TRANSFER_COMPLETE,
	    .irq.priority                    = DMA1_CH4_IRQ_PRIORITY,
		.irq.callback                    = 0,
	},

	[4] =
	{
	    .reg                             = DMA1_Ch5,
	    .mem2mem                         = DMA1_CH5_MEM2MEM,
	    .dma_priority                    = DMA1_CH5_PRIORITY,
	 	.mem_data_type                   = DMA1_CH5_MEM_DATA_TYPE,
	    .memory_zone_size                = DMA1_CH5_MEMORY_ZONE_SIZE,
	   	.memory_zone_address             = DMA1_CH5_MEMORY_ZONE_ADDRESS,
	    .peripheral_address              = DMA1_CH5_PERIPHERAL_ADDRESS,
	   	.periph_data_type                = DMA1_CH5_PERIPH_DATA_TYPE,
	    .memory_increment                = DMA1_CH5_MEMORY_INCREMENT,
	   	.peripheral_increment            = DMA1_CH5_PERIPHERAL_INCREMENT,
	    .read_from_memory                = DMA1_CH5_READ_FROM_MEMORY,
	   	.irq.transfer_error_interrupt    = DMA1_CH5_IRQ_TRANSFER_ERROR,
	    .irq.half_transfer_interrupt     = DMA1_CH5_IRQ_HALF_TRANSFER,
	   	.irq.transfer_complete_interrupt = DMA1_CH5_IRQ_TRANSFER_COMPLETE,
	    .irq.priority                    = DMA1_CH5_IRQ_PRIORITY,
		.irq.callback                    = 0,
	},

	[5] =
	{
	    .reg                             = DMA1_Ch6,
    	.mem2mem                         = DMA1_CH6_MEM2MEM,
	    .dma_priority                    = DMA1_CH6_PRIORITY,
    	.mem_data_type                   = DMA1_CH6_MEM_DATA_TYPE,
	    .memory_zone_size                = DMA1_CH6_MEMORY_ZONE_SIZE,
    	.memory_zone_address             = DMA1_CH6_MEMORY_ZONE_ADDRESS,
	    .peripheral_address              = DMA1_CH6_PERIPHERAL_ADDRESS,
    	.periph_data_type                = DMA1_CH6_PERIPH_DATA_TYPE,
	    .memory_increment                = DMA1_CH6_MEMORY_INCREMENT,
    	.peripheral_increment            = DMA1_CH6_PERIPHERAL_INCREMENT,
	    .read_from_memory                = DMA1_CH6_READ_FROM_MEMORY,
    	.irq.transfer_error_interrupt    = DMA1_CH6_IRQ_TRANSFER_ERROR,
	    .irq.half_transfer_interrupt     = DMA1_CH6_IRQ_HALF_TRANSFER,
    	.irq.transfer_complete_interrupt = DMA1_CH6_IRQ_TRANSFER_COMPLETE,
	    .irq.priority                    = DMA1_CH6_IRQ_PRIORITY,
		.irq.callback                    = 0,
	},

	[6] =
	{
	    .reg                             = DMA1_Ch7,
    	.mem2mem                         = DMA1_CH7_MEM2MEM,
	    .dma_priority                    = DMA1_CH7_PRIORITY,
    	.mem_data_type                   = DMA1_CH7_MEM_DATA_TYPE,
	    .memory_zone_size                = DMA1_CH7_MEMORY_ZONE_SIZE,
    	.memory_zone_address             = DMA1_CH7_MEMORY_ZONE_ADDRESS,
	    .peripheral_address              = DMA1_CH7_PERIPHERAL_ADDRESS,
    	.periph_data_type                = DMA1_CH7_PERIPH_DATA_TYPE,
	    .memory_increment                = DMA1_CH7_MEMORY_INCREMENT,
    	.peripheral_increment            = DMA1_CH7_PERIPHERAL_INCREMENT,
	    .read_from_memory                = DMA1_CH7_READ_FROM_MEMORY,
    	.irq.transfer_error_interrupt    = DMA1_CH7_IRQ_TRANSFER_ERROR,
	    .irq.half_transfer_interrupt     = DMA1_CH7_IRQ_HALF_TRANSFER,
    	.irq.transfer_complete_interrupt = DMA1_CH7_IRQ_TRANSFER_COMPLETE,
	    .irq.priority                    = DMA1_CH7_IRQ_PRIORITY,
		.irq.callback                    = 0,
	},
};

const struct t_gpio_config gpio_cfg[GPIO_PIN_NUMBER] =
{
	[0] =
	{
        .gpio = PA0_GPIO_PORT,
        .pin = PA0_PIN,
        .input_type = PA0_MODE,
        .config = PA0_CONFIG,
        .irq.active = PA0_IRQ_ENABLE,
        .irq.rising = PA0_IRQ_RISING,
        .irq.priority = PA0_IRQ_PRIORITY,
        .irq.callback = PA0_IRQ_CALLBACK,
	},

    [1] =
    {
        .gpio = PA1_GPIO_PORT,
        .pin = PA1_PIN,
        .input_type = PA1_MODE,
        .config = PA1_CONFIG,
        .irq.active = PA1_IRQ_ENABLE,
        .irq.rising = PA1_IRQ_RISING,
        .irq.priority = PA1_IRQ_PRIORITY,
        .irq.callback = PA1_IRQ_CALLBACK,
    },

    [2] =
    {
        .gpio = PA2_GPIO_PORT,
        .pin = PA2_PIN,
        .input_type = PA2_MODE,
        .config = PA2_CONFIG,
        .irq.active = PA2_IRQ_ENABLE,
        .irq.rising = PA2_IRQ_RISING,
        .irq.priority = PA2_IRQ_PRIORITY,
        .irq.callback = PA2_IRQ_CALLBACK,
    },

	[3] =
    {
      .gpio = PA3_GPIO_PORT,
      .pin = PA3_PIN,
      .input_type = PA3_MODE,
      .config = PA3_CONFIG,
      .irq.active = PA3_IRQ_ENABLE,
      .irq.rising = PA3_IRQ_RISING,
      .irq.priority = PA3_IRQ_PRIORITY,
      .irq.callback = PA3_IRQ_CALLBACK,
    },

	[4] =
    {
      .gpio = PA4_GPIO_PORT,
      .pin = PA4_PIN,
      .input_type = PA4_MODE,
      .config = PA4_CONFIG,
      .irq.active = PA4_IRQ_ENABLE,
      .irq.rising = PA4_IRQ_RISING,
      .irq.priority = PA4_IRQ_PRIORITY,
      .irq.callback = PA4_IRQ_CALLBACK,
    },

	[5] =
    {
      .gpio = PA5_GPIO_PORT,
      .pin = PA5_PIN,
      .input_type = PA5_MODE,
      .config = PA5_CONFIG,
      .irq.active = PA5_IRQ_ENABLE,
      .irq.rising = PA5_IRQ_RISING,
      .irq.priority = PA5_IRQ_PRIORITY,
      .irq.callback = PA5_IRQ_CALLBACK,
    },

	[6] =
    {
      .gpio = PA6_GPIO_PORT,
      .pin = PA6_PIN,
      .input_type = PA6_MODE,
      .config = PA6_CONFIG,
      .irq.active = PA6_IRQ_ENABLE,
      .irq.rising = PA6_IRQ_RISING,
      .irq.priority = PA6_IRQ_PRIORITY,
      .irq.callback = PA6_IRQ_CALLBACK,
    },

	[7] =
    {
      .gpio = PA7_GPIO_PORT,
      .pin = PA7_PIN,
      .input_type = PA7_MODE,
      .config = PA7_CONFIG,
      .irq.active = PA7_IRQ_ENABLE,
      .irq.rising = PA7_IRQ_RISING,
      .irq.priority = PA7_IRQ_PRIORITY,
      .irq.callback = PA7_IRQ_CALLBACK,
    },

	[8] =
    {
      .gpio = PA8_GPIO_PORT,
      .pin = PA8_PIN,
      .input_type = PA8_MODE,
      .config = PA8_CONFIG,
      .irq.active = PA8_IRQ_ENABLE,
      .irq.rising = PA8_IRQ_RISING,
      .irq.priority = PA8_IRQ_PRIORITY,
      .irq.callback = PA8_IRQ_CALLBACK,
    },

	[9] =
    {
      .gpio = PA9_GPIO_PORT,
      .pin = PA9_PIN,
      .input_type = PA9_MODE,
      .config = PA9_CONFIG,
      .irq.active = PA9_IRQ_ENABLE,
      .irq.rising = PA9_IRQ_RISING,
      .irq.priority = PA9_IRQ_PRIORITY,
      .irq.callback = PA9_IRQ_CALLBACK,
    },

	[10] =
    {
      .gpio = PA10_GPIO_PORT,
      .pin = PA10_PIN,
      .input_type = PA10_MODE,
      .config = PA10_CONFIG,
      .irq.active = PA10_IRQ_ENABLE,
      .irq.rising = PA10_IRQ_RISING,
      .irq.priority = PA10_IRQ_PRIORITY,
      .irq.callback = PA10_IRQ_CALLBACK,
    },

	[11] =
    {
      .gpio = PA11_GPIO_PORT,
      .pin = PA11_PIN,
      .input_type = PA11_MODE,
      .config = PA11_CONFIG,
      .irq.active = PA11_IRQ_ENABLE,
      .irq.rising = PA11_IRQ_RISING,
      .irq.priority = PA11_IRQ_PRIORITY,
      .irq.callback = PA11_IRQ_CALLBACK,
    },

	[12] =
    {
      .gpio = PA12_GPIO_PORT,
      .pin = PA12_PIN,
      .input_type = PA12_MODE,
      .config = PA12_CONFIG,
      .irq.active = PA12_IRQ_ENABLE,
      .irq.rising = PA12_IRQ_RISING,
      .irq.priority = PA12_IRQ_PRIORITY,
      .irq.callback = PA12_IRQ_CALLBACK,
    },

	[13] =
    {
      .gpio = PA13_GPIO_PORT,
      .pin = PA13_PIN,
      .input_type = PA13_MODE,
      .config = PA13_CONFIG,
      .irq.active = PA13_IRQ_ENABLE,
      .irq.rising = PA13_IRQ_RISING,
      .irq.priority = PA13_IRQ_PRIORITY,
      .irq.callback = PA13_IRQ_CALLBACK,
    },

	[14] =
    {
      .gpio = PA14_GPIO_PORT,
      .pin = PA14_PIN,
      .input_type = PA14_MODE,
      .config = PA14_CONFIG,
      .irq.active = PA14_IRQ_ENABLE,
      .irq.rising = PA14_IRQ_RISING,
      .irq.priority = PA14_IRQ_PRIORITY,
      .irq.callback = PA14_IRQ_CALLBACK,
    },

	[15] =
    {
      .gpio = PA15_GPIO_PORT,
      .pin = PA15_PIN,
      .input_type = PA15_MODE,
      .config = PA15_CONFIG,
      .irq.active = PA15_IRQ_ENABLE,
      .irq.rising = PA15_IRQ_RISING,
      .irq.priority = PA15_IRQ_PRIORITY,
      .irq.callback = PA15_IRQ_CALLBACK,
    },

	[16] =
    {
      .gpio = PB1_GPIO_PORT,
      .pin = PB1_PIN,
      .input_type = PB1_MODE,
      .config = PB1_CONFIG,
      .irq.active = PB1_IRQ_ENABLE,
      .irq.rising = PB1_IRQ_RISING,
      .irq.priority = PB1_IRQ_PRIORITY,
      .irq.callback = PB1_IRQ_CALLBACK,
    },

	[17] =
    {
      .gpio = PB2_GPIO_PORT,
      .pin = PB2_PIN,
      .input_type = PB2_MODE,
      .config = PB2_CONFIG,
      .irq.active = PB2_IRQ_ENABLE,
      .irq.rising = PB2_IRQ_RISING,
      .irq.priority = PB2_IRQ_PRIORITY,
      .irq.callback = PB2_IRQ_CALLBACK,
    },

	[18] =
    {
      .gpio = PB3_GPIO_PORT,
      .pin = PB3_PIN,
      .input_type = PB3_MODE,
      .config = PB3_CONFIG,
      .irq.active = PB3_IRQ_ENABLE,
      .irq.rising = PB3_IRQ_RISING,
      .irq.priority = PB3_IRQ_PRIORITY,
      .irq.callback = PB3_IRQ_CALLBACK,
    },

	[19] =
    {
      .gpio = PB4_GPIO_PORT,
      .pin = PB4_PIN,
      .input_type = PB4_MODE,
      .config = PB4_CONFIG,
      .irq.active = PB4_IRQ_ENABLE,
      .irq.rising = PB4_IRQ_RISING,
      .irq.priority = PB4_IRQ_PRIORITY,
      .irq.callback = PB4_IRQ_CALLBACK,
    },

	[20] =
    {
      .gpio = PB5_GPIO_PORT,
      .pin = PB5_PIN,
      .input_type = PB5_MODE,
      .config = PB5_CONFIG,
      .irq.active = PB5_IRQ_ENABLE,
      .irq.rising = PB5_IRQ_RISING,
      .irq.priority = PB5_IRQ_PRIORITY,
      .irq.callback = PB5_IRQ_CALLBACK,
    },

	[21] =
    {
      .gpio = PB6_GPIO_PORT,
      .pin = PB6_PIN,
      .input_type = PB6_MODE,
      .config = PB6_CONFIG,
      .irq.active = PB6_IRQ_ENABLE,
      .irq.rising = PB6_IRQ_RISING,
      .irq.priority = PB6_IRQ_PRIORITY,
      .irq.callback = PB6_IRQ_CALLBACK,
    },

    [22] =
    {
     .gpio = PB7_GPIO_PORT,
     .pin = PB7_PIN,
     .input_type = PB7_MODE,
     .config = PB7_CONFIG,
     .irq.active = PB7_IRQ_ENABLE,
     .irq.rising = PB7_IRQ_RISING,
     .irq.priority = PB7_IRQ_PRIORITY,
     .irq.callback = PB7_IRQ_CALLBACK,
    },

	[23] =
    {
      .gpio = PB8_GPIO_PORT,
      .pin = PB8_PIN,
      .input_type = PB8_MODE,
      .config = PB8_CONFIG,
      .irq.active = PB8_IRQ_ENABLE,
      .irq.rising = PB8_IRQ_RISING,
      .irq.priority = PB8_IRQ_PRIORITY,
      .irq.callback = PB8_IRQ_CALLBACK,
    },

	[24] =
    {
      .gpio = PB9_GPIO_PORT,
      .pin = PB9_PIN,
      .input_type = PB9_MODE,
      .config = PB9_CONFIG,
      .irq.active = PB9_IRQ_ENABLE,
      .irq.rising = PB9_IRQ_RISING,
      .irq.priority = PB9_IRQ_PRIORITY,
      .irq.callback = PB9_IRQ_CALLBACK,
    },

	[25] =
    {
      .gpio = PB10_GPIO_PORT,
      .pin = PB10_PIN,
      .input_type = PB10_MODE,
      .config = PB10_CONFIG,
      .irq.active = PB10_IRQ_ENABLE,
      .irq.rising = PB10_IRQ_RISING,
      .irq.priority = PB10_IRQ_PRIORITY,
      .irq.callback = PB10_IRQ_CALLBACK,
    },

	[26] =
    {
      .gpio = PB11_GPIO_PORT,
      .pin = PB11_PIN,
      .input_type = PB11_MODE,
      .config = PB11_CONFIG,
      .irq.active = PB11_IRQ_ENABLE,
      .irq.rising = PB11_IRQ_RISING,
      .irq.priority = PB11_IRQ_PRIORITY,
      .irq.callback = PB11_IRQ_CALLBACK,
    },

	[27] =
    {
      .gpio = PB12_GPIO_PORT,
      .pin = PB12_PIN,
      .input_type = PB12_MODE,
      .config = PB12_CONFIG,
      .irq.active = PB12_IRQ_ENABLE,
      .irq.rising = PB12_IRQ_RISING,
      .irq.priority = PB12_IRQ_PRIORITY,
      .irq.callback = PB12_IRQ_CALLBACK,
    },

	[28] =
    {
      .gpio = PB13_GPIO_PORT,
      .pin = PB13_PIN,
      .input_type = PB13_MODE,
      .config = PB13_CONFIG,
      .irq.active = PB13_IRQ_ENABLE,
      .irq.rising = PB13_IRQ_RISING,
      .irq.priority = PB13_IRQ_PRIORITY,
      .irq.callback = PB13_IRQ_CALLBACK,
    },

	[29] =
    {
      .gpio = PB14_GPIO_PORT,
      .pin = PB14_PIN,
      .input_type = PB14_MODE,
      .config = PB14_CONFIG,
      .irq.active = PB14_IRQ_ENABLE,
      .irq.rising = PB14_IRQ_RISING,
      .irq.priority = PB14_IRQ_PRIORITY,
      .irq.callback = PB14_IRQ_CALLBACK,
    },

	[30] =
    {
      .gpio = PB15_GPIO_PORT,
      .pin = PB15_PIN,
      .input_type = PB15_MODE,
      .config = PB15_CONFIG,
      .irq.active = PB15_IRQ_ENABLE,
      .irq.rising = PB15_IRQ_RISING,
      .irq.priority = PB15_IRQ_PRIORITY,
      .irq.callback = PB15_IRQ_CALLBACK,
    },

	[31] =
    {
      .gpio = PC13_GPIO_PORT,
      .pin = PC13_PIN,
      .input_type = PC13_MODE,
      .config = PC13_CONFIG,
      .irq.active = PC13_IRQ_ENABLE,
      .irq.rising = PC13_IRQ_RISING,
      .irq.priority = PC13_IRQ_PRIORITY,
      .irq.callback = PC13_IRQ_CALLBACK,
    },

	[32] =
    {
      .gpio = PC14_GPIO_PORT,
      .pin = PC14_PIN,
      .input_type = PC14_MODE,
      .config = PC14_CONFIG,
      .irq.active = PC14_IRQ_ENABLE,
      .irq.rising = PC14_IRQ_RISING,
      .irq.priority = PC14_IRQ_PRIORITY,
      .irq.callback = PC14_IRQ_CALLBACK,
    },

	[33] =
    {
      .gpio = PC15_GPIO_PORT,
      .pin = PC15_PIN,
      .input_type = PC15_MODE,
      .config = PC15_CONFIG,
      .irq.active = PC15_IRQ_ENABLE,
      .irq.rising = PC15_IRQ_RISING,
      .irq.priority = PC15_IRQ_PRIORITY,
      .irq.callback = PC15_IRQ_CALLBACK,
    },

	[34] =
    {
      .gpio = PD0_GPIO_PORT,
      .pin = PD0_PIN,
      .input_type = PD0_MODE,
      .config = PD0_CONFIG,
      .irq.active = PD0_IRQ_ENABLE,
      .irq.rising = PD0_IRQ_RISING,
      .irq.priority = PD0_IRQ_PRIORITY,
      .irq.callback = PD0_IRQ_CALLBACK,
    },

	[35] =
    {
      .gpio = PD1_GPIO_PORT,
      .pin = PD1_PIN,
      .input_type = PD1_MODE,
      .config = PD1_CONFIG,
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

static struct t_spi_config spi_config[SPI_IP_NUMBER] =
{
    [0] =
    {
        .instance = 0,
        .base_address = SPI1_BASE,
    },

    [1] =
    {
        .instance = 1,
        .base_address = SPI2_BASE,
    },
};

/* Static driver structure. */
struct t_spi_driver spi_driver[SPI_IP_NUMBER];



void soc_core_configuration(void)
{
	clock_init(&clock_driver, &clock_config);
}

void soc_peripherals_configuration(void)
{
	for(uint8_t index = 0; index < DMA_CHANNELS_NUMBER; index++)
	{
	    dma_init(&dma_driver[index], &dma1_chx_cfg[index]);
	}

	for(uint8_t index = 0; index < GPIO_PIN_NUMBER; index++)
	{
      gpio_init(&gpio_driver[index], &gpio_cfg[index]);
	}

	struct t_usart_driver *usart_driver = usart_get_driver(1);
    usart_init(usart_driver, &usartx_cfg[0]);
    usart_driver = usart_get_driver(2);
    usart_init(usart_driver, &usartx_cfg[1]);

    for(uint8_t index = 0; index < SPI_IP_NUMBER; index++)
    {
    	spi_init(&spi_driver[index], &spi_config[index]);
    }

//    timer_init(&timx_chanelx_cfg[0]);
//    timer_init(&timx_chanelx_cfg[1]);
//    timer_init(&timx_chanelx_cfg[2]);
}

