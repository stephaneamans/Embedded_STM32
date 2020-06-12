#include "bsp_configuration.h"


void soc_core_configuration(void)
{
#ifdef CLOCK_RESET
	t_clock_cfg clock_configuration;
	clock_configuration.sys_clk = SYS_CLK;
	clock_configuration.AHB_clk = AHB_CLK;
	clock_configuration.APB1_clk = APB1_CLK;
	clock_configuration.APB2_clk = APB2_CLK;
	clock_configuration.source = SOURCE;
	clock_init(&clock_configuration);
#endif
}

void soc_peripherals_configuration(void)
{

#ifdef DMA1_CH1
	t_dma_channel_cfg dma1_ch1_configuration;
	dma1_ch1_configuration.reg = DMA1_Ch1;
	dma1_ch1_configuration.mem2mem = DMA1_CH1_MEM2MEM;
	dma1_ch1_configuration.dma_priority = DMA1_CH1_PRIORITY;
	dma1_ch1_configuration.mem_data_type = DMA1_CH1_MEM_DATA_TYPE;
	dma1_ch1_configuration.memory_zone_size = DMA1_CH1_MEMORY_ZONE_SIZE;
	dma1_ch1_configuration.memory_zone_address = DMA1_CH1_MEMORY_ZONE_ADDRESS;
	dma1_ch1_configuration.peripheral_address = (uint32_t)DMA1_CH1_PERIPHERAL_ADDRESS;
	dma1_ch1_configuration.periph_data_type = DMA1_CH1_PERIPH_DATA_TYPE;
	dma1_ch1_configuration.memory_increment = DMA1_CH1_MEMORY_INCREMENT;
	dma1_ch1_configuration.peripheral_increment = DMA1_CH1_PERIPHERAL_INCREMENT;
	dma1_ch1_configuration.read_from_memory = DMA1_CH1_READ_FROM_MEMORY;
	dma1_ch1_configuration.irq.transfer_error_interrupt = DMA1_CH1_IRQ_TRANSFER_ERROR;
	dma1_ch1_configuration.irq.half_transfer_interrupt = DMA1_CH1_IRQ_HALF_TRANSFER;
	dma1_ch1_configuration.irq.transfer_complete_interrupt = DMA1_CH1_IRQ_TRANSFER_COMPLETE;
 	dma_init(&dma_driver[0], &dma1_ch1_configuration);
#endif

#ifdef DMA1_CH2
	t_dma_channel_cfg dma1_ch2_configuration;
	dma1_ch2_configuration.reg = DMA1_Ch2;
	dma1_ch2_configuration.mem2mem = DMA1_CH2_MEM2MEM;
	dma1_ch2_configuration.dma_priority = DMA1_CH2_PRIORITY;
	dma1_ch2_configuration.mem_data_type = DMA1_CH2_MEM_DATA_TYPE;
	dma1_ch2_configuration.memory_zone_size = DMA1_CH2_MEMORY_ZONE_SIZE;
	dma1_ch2_configuration.memory_zone_address = DMA1_CH2_MEMORY_ZONE_ADDRESS;
	dma1_ch2_configuration.peripheral_address = DMA1_CH2_PERIPHERAL_ADDRESS;
	dma1_ch2_configuration.periph_data_type = DMA1_CH2_PERIPH_DATA_TYPE;
	dma1_ch2_configuration.memory_increment = DMA1_CH2_MEMORY_INCREMENT;
	dma1_ch2_configuration.peripheral_increment = DMA1_CH2_PERIPHERAL_INCREMENT;
	dma1_ch2_configuration.read_from_memory = DMA1_CH2_READ_FROM_MEMORY;
	dma1_ch2_configuration.irq.transfer_error_interrupt = DMA1_CH2_IRQ_TRANSFER_ERROR;
	dma1_ch2_configuration.irq.half_transfer_interrupt = DMA1_CH2_IRQ_HALF_TRANSFER;
	dma1_ch2_configuration.irq.transfer_complete_interrupt = DMA1_CH2_IRQ_TRANSFER_COMPLETE;
	dma1_ch2_configuration.irq.priority = DMA1_CH2_IRQ_PRIORITY;
	dma_init(&dma_driver[1], &dma1_ch2_configuration);
#endif

#ifdef DMA1_CH3
	t_dma_channel_cfg dma1_ch3_configuration;
	dma1_ch3_configuration.reg = DMA1_Ch3;
	dma1_ch3_configuration.mem2mem = DMA1_CH3_MEM2MEM;
	dma1_ch3_configuration.dma_priority = DMA1_CH3_PRIORITY;
	dma1_ch3_configuration.mem_data_type = DMA1_CH3_MEM_DATA_TYPE;
	dma1_ch3_configuration.memory_zone_size = DMA1_CH3_MEMORY_ZONE_SIZE;
	dma1_ch3_configuration.memory_zone_address = DMA1_CH3_MEMORY_ZONE_ADDRESS;
	dma1_ch3_configuration.peripheral_address = DMA1_CH3_PERIPHERAL_ADDRESS;
	dma1_ch3_configuration.periph_data_type = DMA1_CH3_PERIPH_DATA_TYPE;
	dma1_ch3_configuration.memory_increment = DMA1_CH3_MEMORY_INCREMENT;
	dma1_ch3_configuration.peripheral_increment = DMA1_CH3_PERIPHERAL_INCREMENT;
	dma1_ch3_configuration.read_from_memory = DMA1_CH3_READ_FROM_MEMORY;
	dma1_ch3_configuration.irq.transfer_error_interrupt = DMA1_CH3_IRQ_TRANSFER_ERROR;
	dma1_ch3_configuration.irq.half_transfer_interrupt = DMA1_CH3_IRQ_HALF_TRANSFER;
	dma1_ch3_configuration.irq.transfer_complete_interrupt = DMA1_CH3_IRQ_TRANSFER_COMPLETE;
	dma1_ch3_configuration.irq.priority = DMA1_CH3_IRQ_PRIORITY;
	dma_init(&dma_driver[2], &dma1_ch3_configuration);
#endif

#ifdef DMA1_CH4
	t_dma_channel_cfg dma1_ch4_configuration;
	dma1_ch4_configuration.reg = DMA1_Ch4;
    dma1_ch4_configuration.mem2mem = DMA1_CH4_MEM2MEM;
    dma1_ch4_configuration.dma_priority = DMA1_CH4_PRIORITY;
	dma1_ch4_configuration.mem_data_type = DMA1_CH4_MEM_DATA_TYPE;
	dma1_ch4_configuration.memory_zone_size = DMA1_CH4_MEMORY_ZONE_SIZE;
	dma1_ch4_configuration.memory_zone_address = DMA1_CH4_MEMORY_ZONE_ADDRESS;
	dma1_ch4_configuration.peripheral_address = DMA1_CH4_PERIPHERAL_ADDRESS;
	dma1_ch4_configuration.periph_data_type = DMA1_CH4_PERIPH_DATA_TYPE;
	dma1_ch4_configuration.memory_increment = DMA1_CH4_MEMORY_INCREMENT;
	dma1_ch4_configuration.peripheral_increment = DMA1_CH4_PERIPHERAL_INCREMENT;
	dma1_ch4_configuration.read_from_memory = DMA1_CH4_READ_FROM_MEMORY;
	dma1_ch4_configuration.irq.transfer_error_interrupt = DMA1_CH4_IRQ_TRANSFER_ERROR;
	dma1_ch4_configuration.irq.half_transfer_interrupt = DMA1_CH4_IRQ_HALF_TRANSFER;
	dma1_ch4_configuration.irq.transfer_complete_interrupt = DMA1_CH4_IRQ_TRANSFER_COMPLETE;
	dma1_ch4_configuration.irq.priority = DMA1_CH4_IRQ_PRIORITY;
	dma_init(&dma_driver[3], &dma1_ch4_configuration);
#endif

#ifdef DMA1_CH5
	t_dma_channel_cfg dma1_ch5_configuration;
	dma1_ch5_configuration.reg = DMA1_Ch5;
	dma1_ch5_configuration.mem2mem = DMA1_CH5_MEM2MEM;
	dma1_ch5_configuration.dma_priority = DMA1_CH5_PRIORITY;
	dma1_ch5_configuration.mem_data_type = DMA1_CH5_MEM_DATA_TYPE;
	dma1_ch5_configuration.memory_zone_size = DMA1_CH5_MEMORY_ZONE_SIZE;
	dma1_ch5_configuration.memory_zone_address = DMA1_CH5_MEMORY_ZONE_ADDRESS;
	dma1_ch5_configuration.peripheral_address = DMA1_CH5_PERIPHERAL_ADDRESS;
	dma1_ch5_configuration.periph_data_type = DMA1_CH5_PERIPH_DATA_TYPE;
	dma1_ch5_configuration.memory_increment = DMA1_CH5_MEMORY_INCREMENT;
	dma1_ch5_configuration.peripheral_increment = DMA1_CH5_PERIPHERAL_INCREMENT;
	dma1_ch5_configuration.read_from_memory = DMA1_CH5_READ_FROM_MEMORY;
	dma1_ch5_configuration.irq.transfer_error_interrupt = DMA1_CH5_IRQ_TRANSFER_ERROR;
	dma1_ch5_configuration.irq.half_transfer_interrupt = DMA1_CH5_IRQ_HALF_TRANSFER;
	dma1_ch5_configuration.irq.transfer_complete_interrupt = DMA1_CH5_IRQ_TRANSFER_COMPLETE;
	dma1_ch5_configuration.irq.priority = DMA1_CH5_IRQ_PRIORITY;
	dma_init(&dma_driver[4], &dma1_ch5_configuration);
#endif

#ifdef DMA1_CH6
	t_dma_channel_cfg dma1_ch6_configuration;
	dma1_ch6_configuration.reg = DMA1_Ch6;
	dma1_ch6_configuration.mem2mem = DMA1_CH6_MEM2MEM;
	dma1_ch6_configuration.dma_priority = DMA1_CH6_PRIORITY;
	dma1_ch6_configuration.mem_data_type = DMA1_CH6_MEM_DATA_TYPE;
	dma1_ch6_configuration.memory_zone_size = DMA1_CH6_MEMORY_ZONE_SIZE;
	dma1_ch6_configuration.memory_zone_address = DMA1_CH6_MEMORY_ZONE_ADDRESS;
	dma1_ch6_configuration.peripheral_address = DMA1_CH6_PERIPHERAL_ADDRESS;
	dma1_ch6_configuration.periph_data_type = DMA1_CH6_PERIPH_DATA_TYPE;
	dma1_ch6_configuration.memory_increment = DMA1_CH6_MEMORY_INCREMENT;
	dma1_ch6_configuration.peripheral_increment = DMA1_CH6_PERIPHERAL_INCREMENT;
	dma1_ch6_configuration.read_from_memory = DMA1_CH6_READ_FROM_MEMORY;
	dma1_ch6_configuration.irq.transfer_error_interrupt = DMA1_CH6_IRQ_TRANSFER_ERROR;
	dma1_ch6_configuration.irq.half_transfer_interrupt = DMA1_CH6_IRQ_HALF_TRANSFER;
	dma1_ch6_configuration.irq.transfer_complete_interrupt = DMA1_CH6_IRQ_TRANSFER_COMPLETE;
	dma1_ch6_configuration.irq.priority = DMA1_CH6_IRQ_PRIORITY;
	dma_init(&dma_driver[5], &dma1_ch6_configuration);
#endif

#ifdef DMA1_CH7
	t_dma_channel_cfg dma1_ch7_configuration;
	dma1_ch7_configuration.reg = DMA1_Ch7;
	dma1_ch7_configuration.mem2mem = DMA1_CH7_MEM2MEM;
	dma1_ch7_configuration.dma_priority = DMA1_CH7_PRIORITY;
	dma1_ch7_configuration.mem_data_type = DMA1_CH7_MEM_DATA_TYPE;
	dma1_ch7_configuration.memory_zone_size = DMA1_CH7_MEMORY_ZONE_SIZE;
	dma1_ch7_configuration.memory_zone_address = DMA1_CH7_MEMORY_ZONE_ADDRESS;
	dma1_ch7_configuration.peripheral_address = DMA1_CH7_PERIPHERAL_ADDRESS;
	dma1_ch7_configuration.periph_data_type = DMA1_CH7_PERIPH_DATA_TYPE;
	dma1_ch7_configuration.memory_increment = DMA1_CH7_MEMORY_INCREMENT;
	dma1_ch7_configuration.peripheral_increment = DMA1_CH7_PERIPHERAL_INCREMENT;
	dma1_ch7_configuration.read_from_memory = DMA1_CH7_READ_FROM_MEMORY;
	dma1_ch7_configuration.irq.transfer_error_interrupt = DMA1_CH7_IRQ_TRANSFER_ERROR;
	dma1_ch7_configuration.irq.half_transfer_interrupt = DMA1_CH7_IRQ_HALF_TRANSFER;
	dma1_ch7_configuration.irq.transfer_complete_interrupt = DMA1_CH7_IRQ_TRANSFER_COMPLETE;
	dma1_ch7_configuration.irq.priority = DMA1_CH7_IRQ_PRIORITY;
	dma_init(&dma_driver[6], &dma1_ch7_configuration);
#endif

#ifdef GPIO_PA0
    t_gpio_cfg gpio_pa0_configuration;
    gpio_pa0_configuration.gpio = PA0_GPIO_PORT;
    gpio_pa0_configuration.pin = PA0_PIN;
    gpio_pa0_configuration.mode = PA0_MODE;
    gpio_pa0_configuration.config = PA0_CONFIG;
    gpio_pa0_configuration.irq.active = PA0_IRQ_ENABLE;
    gpio_pa0_configuration.irq.rising = PA0_IRQ_RISING;
    gpio_pa0_configuration.irq.priority = PA0_IRQ_PRIORITY;
    gpio_pa0_configuration.irq.callback = PA0_IRQ_CALLBACK;
    gpio_init(&gpio_pa0_configuration);
#endif

#ifdef GPIO_PA1
    t_gpio_cfg gpio_pa1_configuration;
    gpio_pa1_configuration.gpio = PA1_GPIO_PORT;
    gpio_pa1_configuration.pin = PA1_PIN;
    gpio_pa1_configuration.mode = PA1_MODE;
    gpio_pa1_configuration.config = PA1_CONFIG;
    gpio_pa1_configuration.irq.active = PA1_IRQ_ENABLE;
    gpio_pa1_configuration.irq.rising = PA1_IRQ_RISING;
    gpio_pa1_configuration.irq.priority = PA1_IRQ_PRIORITY;
    gpio_pa1_configuration.irq.callback = PA1_IRQ_CALLBACK;
    gpio_init(&gpio_pa1_configuration);
#endif

#ifdef GPIO_PA2
    t_gpio_cfg gpio_pa2_configuration;
    gpio_pa2_configuration.gpio = PA2_GPIO_PORT;
    gpio_pa2_configuration.pin = PA2_PIN;
    gpio_pa2_configuration.mode = PA2_MODE;
    gpio_pa2_configuration.config = PA2_CONFIG;
    gpio_pa2_configuration.irq.active = PA2_IRQ_ENABLE;
    gpio_pa2_configuration.irq.rising = PA2_IRQ_RISING;
    gpio_pa2_configuration.irq.priority = PA2_IRQ_PRIORITY;
    gpio_pa2_configuration.irq.callback = PA2_IRQ_CALLBACK;
    gpio_init(&gpio_pa2_configuration);
#endif

#ifdef GPIO_PA6
    t_gpio_cfg gpio_pa6_configuration;
    gpio_pa6_configuration.gpio = PA6_GPIO_PORT;
    gpio_pa6_configuration.pin = PA6_PIN;
    gpio_pa6_configuration.mode = PA6_MODE;
    gpio_pa6_configuration.config = PA6_CONFIG;
    gpio_pa6_configuration.irq.active = PA6_IRQ_ENABLE;
    gpio_pa6_configuration.irq.rising = PA6_IRQ_RISING;
    gpio_pa6_configuration.irq.priority = PA6_IRQ_PRIORITY;
    gpio_pa6_configuration.irq.callback = PA6_IRQ_CALLBACK;
    gpio_init(&gpio_pa6_configuration);
#endif

#ifdef GPIO_PA8
    t_gpio_cfg gpio_pa8_configuration;
    gpio_pa8_configuration.gpio = PA8_GPIO_PORT;
    gpio_pa8_configuration.pin = PA8_PIN;
    gpio_pa8_configuration.mode = PA8_MODE;
    gpio_pa8_configuration.config = PA8_CONFIG;
    gpio_pa8_configuration.irq.active = PA8_IRQ_ENABLE;
    gpio_pa8_configuration.irq.rising = PA8_IRQ_RISING;
    gpio_pa8_configuration.irq.priority = PA8_IRQ_PRIORITY;
    gpio_pa8_configuration.irq.callback = PA8_IRQ_CALLBACK;
    gpio_init(&gpio_pa8_configuration);
#endif

#ifdef GPIO_PA9
    t_gpio_cfg gpio_pa9_configuration;
    gpio_pa9_configuration.gpio = PA9_GPIO_PORT;
    gpio_pa9_configuration.pin = PA9_PIN;
    gpio_pa9_configuration.mode = PA9_MODE;
    gpio_pa9_configuration.config = PA9_CONFIG;
    gpio_pa9_configuration.irq.active = PA9_IRQ_ENABLE;
    gpio_pa9_configuration.irq.rising = PA9_IRQ_RISING;
    gpio_pa9_configuration.irq.priority = PA9_IRQ_PRIORITY;
    gpio_pa9_configuration.irq.callback = PA9_IRQ_CALLBACK;
    gpio_init(&gpio_pa9_configuration);
#endif

#ifdef GPIO_PA10
    t_gpio_cfg gpio_pa10_configuration;
    gpio_pa10_configuration.gpio = PA10_GPIO_PORT;
    gpio_pa10_configuration.pin = PA10_PIN;
    gpio_pa10_configuration.mode = PA10_MODE;
    gpio_pa10_configuration.config = PA10_CONFIG;
    gpio_pa10_configuration.irq.active = PA10_IRQ_ENABLE;
    gpio_pa10_configuration.irq.rising = PA10_IRQ_RISING;
    gpio_pa10_configuration.irq.priority = PA10_IRQ_PRIORITY;
    gpio_pa10_configuration.irq.callback = PA10_IRQ_CALLBACK;
    gpio_init(&gpio_pa10_configuration);
#endif

#ifdef GPIO_PB7
    t_gpio_cfg gpio_pb7_configuration;
    gpio_pb7_configuration.gpio = PB7_GPIO_PORT;
    gpio_pb7_configuration.pin = PB7_PIN;
    gpio_pb7_configuration.mode = PB7_MODE;
    gpio_pb7_configuration.config = PB7_CONFIG;
    gpio_pb7_configuration.irq.active = PB7_IRQ_ENABLE;
    gpio_pb7_configuration.irq.rising = PB7_IRQ_RISING;
    gpio_pb7_configuration.irq.priority = PB7_IRQ_PRIORITY;
    gpio_pb7_configuration.irq.callback = PB7_IRQ_CALLBACK;
    gpio_init(&gpio_pb7_configuration);
#endif

#ifdef GPIO_PB9
    t_gpio_cfg gpio_pb9_configuration;
    gpio_pb9_configuration.gpio = PB9_GPIO_PORT;
    gpio_pb9_configuration.pin = PB9_PIN;
    gpio_pb9_configuration.mode = PB9_MODE;
    gpio_pb9_configuration.config = PB9_CONFIG;
    gpio_pb9_configuration.irq.active = PB9_IRQ_ENABLE;
    gpio_pb9_configuration.irq.rising = PB9_IRQ_RISING;
    gpio_pb9_configuration.irq.priority = PB9_IRQ_PRIORITY;
    gpio_pb9_configuration.irq.callback = PB9_IRQ_CALLBACK;
    gpio_init(&gpio_pb9_configuration);
#endif

#ifdef GPIO_PC13
    t_gpio_cfg gpio_pc13_configuration;
    gpio_pc13_configuration.gpio = PC13_GPIO_PORT;
    gpio_pc13_configuration.pin = PC13_PIN;
    gpio_pc13_configuration.mode = PC13_MODE;
    gpio_pc13_configuration.config = PC13_CONFIG;
    gpio_pc13_configuration.irq.active = PC13_IRQ_ENABLE;
    gpio_pc13_configuration.irq.rising = PC13_IRQ_RISING;
    gpio_pc13_configuration.irq.priority = PC13_IRQ_PRIORITY;
    gpio_pc13_configuration.irq.callback = PC13_IRQ_CALLBACK;
    gpio_init(&gpio_pc13_configuration);
#endif

#ifdef USART_1
    struct t_usart_config usart1_configuration;
    struct t_usart_driver *usart_driver1 = usart_get_driver(1);
    usart1_configuration.reg = USART1_REGS;
    usart1_configuration.baudrate = USART1_BAUDRATE;
    usart1_configuration.length = USART1_LENGTH;
    usart1_configuration.parity = USART1_PARITY;
    usart1_configuration.stop = USART1_STOP_BITS;
    usart1_configuration.mode = USART1_MODE;
    usart1_configuration.irq_dma.priority = USART1_IRQ_DMA_PRIORITY;
    usart1_configuration.irq_dma.tx_dma_channel = USART1_DMA_DRIVER_TX;
    usart1_configuration.irq_dma.rx_dma_channel = USART1_DMA_DRIVER_RX;
    usart_init(usart_driver1, &usart1_configuration);
#endif

#ifdef USART_2
    t_usart_config usart2_configuration;
    struct t_usart_driver *usart_driver2 = usart_get_driver(2);
    usart2_configuration.reg = USART2REGS;
    usart2_configuration.baudrate = USART2_BAUDRATE;
    usart2_configuration.length = USART2_LENGTH;
    usart2_configuration.parity = USART2_PARITY;
    usart2_configuration.stop = USART2_STOP_BITS;
    usart2_configuration.mode = USART2_MODE;
    usart2_configuration.irq_dma.priority = USART2_IRQ_DMA_PRIORITY;
    usart2_configuration.irq_dma.tx_dma_channel = USART2_DMA_DRIVER_TX;
    usart2_configuration.irq_dma.rx_dma_channel = USART2_DMA_DRIVER_RX;
    usart_init(usart_driver2, &usart1_configuration);
#endif

#ifdef TIM_1
    t_timer_cfg tim1_configuration;

    tim1_configuration.timer = TIM1;
    tim1_configuration.time_frequency = TIM1_TIME_FREQUENCY;
    tim1_configuration.channel[0].channel_enable = TIM1_CH1_ENABLE;
    tim1_configuration.channel[0].timer_mode = TIM1_CH1_MODE;
    tim1_configuration.channel[0].tim_mux = TIM1_CH1_TIM_MUX;
    tim1_configuration.channel[0].percent_pwm = TIM1_CH1_PERCENT_PWM;
    
    tim1_configuration.channel[0].polarity = TIM1_CH1_POLARITY;
    tim1_configuration.channel[0].irq_dma.active = TIM1_CH1_IRQ_DMA_ENABLE;
    //tim1_configuration.channel[0].irq_dma.edge = TIM1_CH1_IRQ_DMA_ENABLE;
    tim1_configuration.channel[0].irq_dma.priority = TIM1_CH1_IRQ_DMA_PRIORITY;
    tim1_configuration.channel[0].irq_dma.callback = TIM1_CH1_IRQ_DMA_CALLBACK;
    
    tim1_configuration.channel[0].out_cmp_mode = TIM1_CH1_OC_MODE;


    tim1_configuration.channel[1].channel_enable = TIM1_CH2_ENABLE;
    tim1_configuration.channel[1].timer_mode = TIM1_CH2_MODE;
    tim1_configuration.channel[1].tim_mux = TIM1_CH2_TIM_MUX;
    tim1_configuration.channel[1].percent_pwm = TIM1_CH2_PERCENT_PWM;
    
    tim1_configuration.channel[1].polarity = TIM1_CH2_POLARITY;
    tim1_configuration.channel[1].irq_dma.active = TIM1_CH2_IRQ_DMA_ENABLE;
    //tim1_configuration.channel[1].irq_dma.edge = TIM1_CH2_IRQ_DMA_ENABLE;
    tim1_configuration.channel[1].irq_dma.priority = TIM1_CH2_IRQ_DMA_PRIORITY;
    tim1_configuration.channel[1].irq_dma.callback = TIM1_CH2_IRQ_DMA_CALLBACK;
    
    tim1_configuration.channel[1].out_cmp_mode = TIM1_CH2_OC_MODE;


    tim1_configuration.channel[2].channel_enable = TIM1_CH3_ENABLE;
    tim1_configuration.channel[2].timer_mode = TIM1_CH3_MODE;
    tim1_configuration.channel[2].tim_mux = TIM1_CH3_TIM_MUX;
    tim1_configuration.channel[2].percent_pwm = TIM1_CH3_PERCENT_PWM;
    
    tim1_configuration.channel[2].polarity = TIM1_CH3_POLARITY;
    tim1_configuration.channel[2].irq_dma.active = TIM1_CH3_IRQ_DMA_ENABLE;
    //tim1_configuration.channel[2].irq_dma.edge = TIM1_CH3_IRQ_DMA_ENABLE;
    tim1_configuration.channel[2].irq_dma.priority = TIM1_CH3_IRQ_DMA_PRIORITY;
    tim1_configuration.channel[2].irq_dma.callback = TIM1_CH3_IRQ_DMA_CALLBACK;
    
    tim1_configuration.channel[2].out_cmp_mode = TIM1_CH3_OC_MODE;


    tim1_configuration.channel[3].channel_enable = TIM1_CH4_ENABLE;
    tim1_configuration.channel[3].timer_mode = TIM1_CH4_MODE;
    tim1_configuration.channel[3].tim_mux = TIM1_CH4_TIM_MUX;
    tim1_configuration.channel[3].percent_pwm = TIM1_CH4_PERCENT_PWM;
    
    tim1_configuration.channel[3].polarity = TIM1_CH4_POLARITY;
    tim1_configuration.channel[3].irq_dma.active = TIM1_CH4_IRQ_DMA_ENABLE;
    //tim1_configuration.channel[3].irq_dma.edge = TIM1_CH4_IRQ_DMA_ENABLE;
    tim1_configuration.channel[3].irq_dma.priority = TIM1_CH4_IRQ_DMA_PRIORITY;
    tim1_configuration.channel[3].irq_dma.callback = TIM1_CH4_IRQ_DMA_CALLBACK;
    
    tim1_configuration.channel[3].out_cmp_mode = TIM1_CH4_OC_MODE;
    
    //tim1_configuration.mode = TIM1_MODE;
    
    timer_init(&tim1_configuration);
#endif

#ifdef TIM_2
    t_timer_cfg tim2_configuration;

    tim2_configuration.timer = TIM2;
    tim2_configuration.time_frequency = TIM2_TIME_FREQUENCY;
    tim2_configuration.channel[0].channel_enable = TIM2_CH1_ENABLE;
    tim2_configuration.channel[0].timer_mode = TIM2_CH1_MODE;
    tim2_configuration.channel[0].tim_mux = TIM2_CH1_TIM_MUX;
    tim2_configuration.channel[0].percent_pwm = TIM2_CH1_PERCENT_PWM;
    
    tim2_configuration.channel[0].polarity = TIM2_CH1_POLARITY;
    tim2_configuration.channel[0].irq_dma.active = TIM2_CH1_IRQ_DMA_ENABLE;
    //tim2_configuration.channel[0].irq_dma.edge = TIM2_CH1_IRQ_DMA_ENABLE;
    tim2_configuration.channel[0].irq_dma.priority = TIM2_CH1_IRQ_DMA_PRIORITY;
    tim2_configuration.channel[0].irq_dma.callback = TIM2_CH1_IRQ_DMA_CALLBACK;
    
    tim2_configuration.channel[0].out_cmp_mode = TIM2_CH1_OC_MODE;


    tim2_configuration.channel[1].channel_enable = TIM2_CH2_ENABLE;
    tim2_configuration.channel[1].timer_mode = TIM2_CH2_MODE;
    tim2_configuration.channel[1].tim_mux = TIM2_CH2_TIM_MUX;
    tim2_configuration.channel[1].percent_pwm = TIM2_CH2_PERCENT_PWM;
    
    tim2_configuration.channel[1].polarity = TIM2_CH2_POLARITY;
    tim2_configuration.channel[1].irq_dma.active = TIM2_CH2_IRQ_DMA_ENABLE;
    //tim2_configuration.channel[1].irq_dma.edge = TIM2_CH2_IRQ_DMA_ENABLE;
    tim2_configuration.channel[1].irq_dma.priority = TIM2_CH2_IRQ_DMA_PRIORITY;
    tim2_configuration.channel[1].irq_dma.callback = TIM2_CH2_IRQ_DMA_CALLBACK;
    
    tim2_configuration.channel[1].out_cmp_mode = TIM2_CH2_OC_MODE;


    tim2_configuration.channel[2].channel_enable = TIM2_CH3_ENABLE;
    tim2_configuration.channel[2].timer_mode = TIM2_CH3_MODE;
    tim2_configuration.channel[2].tim_mux = TIM2_CH3_TIM_MUX;
    tim2_configuration.channel[2].percent_pwm = TIM2_CH3_PERCENT_PWM;
    
    tim2_configuration.channel[2].polarity = TIM2_CH3_POLARITY;
    tim2_configuration.channel[2].irq_dma.active = TIM2_CH3_IRQ_DMA_ENABLE;
    //tim2_configuration.channel[2].irq_dma.edge = TIM2_CH3_IRQ_DMA_ENABLE;
    tim2_configuration.channel[2].irq_dma.priority = TIM2_CH3_IRQ_DMA_PRIORITY;
    tim2_configuration.channel[2].irq_dma.callback = TIM2_CH3_IRQ_DMA_CALLBACK;
    
    tim2_configuration.channel[2].out_cmp_mode = TIM2_CH3_OC_MODE;


    tim2_configuration.channel[3].channel_enable = TIM2_CH4_ENABLE;
    tim2_configuration.channel[3].timer_mode = TIM2_CH4_MODE;
    tim2_configuration.channel[3].tim_mux = TIM2_CH3_TIM_MUX;
    tim2_configuration.channel[3].percent_pwm = TIM2_CH3_PERCENT_PWM;
    
    tim2_configuration.channel[3].polarity = TIM2_CH3_POLARITY;
    tim2_configuration.channel[3].irq_dma.active = TIM2_CH3_IRQ_DMA_ENABLE;
    //tim2_configuration.channel[3].irq_dma.edge = TIM2_CH3_IRQ_DMA_ENABLE;
    tim2_configuration.channel[3].irq_dma.priority = TIM2_CH3_IRQ_DMA_PRIORITY;
    tim2_configuration.channel[3].irq_dma.callback = TIM2_CH3_IRQ_DMA_CALLBACK;
    
    tim2_configuration.channel[3].out_cmp_mode = TIM2_CH3_OC_MODE;
    
    //tim2_configuration.mode = TIM2_MODE;
    
    timer_init(&tim2_configuration);
#endif

#ifdef TIM_3
    t_timer_cfg tim3_configuration;

    tim3_configuration.timer = TIM3;
    tim3_configuration.time_frequency = TIM3_TIME_FREQUENCY;
    tim3_configuration.channel[0].channel_enable = TIM3_CH1_ENABLE;
    tim3_configuration.channel[0].timer_mode = TIM3_CH1_MODE;
    tim3_configuration.channel[0].tim_mux = TIM3_CH1_TIM_MUX;
    tim3_configuration.channel[0].percent_pwm = TIM3_CH1_PERCENT_PWM;
    
    tim3_configuration.channel[0].polarity = TIM3_CH1_POLARITY;
    tim3_configuration.channel[0].irq_dma.active = TIM3_CH1_IRQ_DMA_ENABLE;
    //tim3_configuration.channel[0].irq_dma.edge = TIM3_CH1_IRQ_DMA_ENABLE;
    tim3_configuration.channel[0].irq_dma.priority = TIM3_CH1_IRQ_DMA_PRIORITY;
    tim3_configuration.channel[0].irq_dma.callback = TIM3_CH1_IRQ_DMA_CALLBACK;
    
    tim3_configuration.channel[0].out_cmp_mode = TIM3_CH1_OC_MODE;


    tim3_configuration.channel[1].channel_enable = TIM3_CH2_ENABLE;
    tim3_configuration.channel[1].timer_mode = TIM3_CH2_MODE;
    tim3_configuration.channel[1].tim_mux = TIM3_CH2_TIM_MUX;
    tim3_configuration.channel[1].percent_pwm = TIM3_CH2_PERCENT_PWM;
    
    tim3_configuration.channel[1].polarity = TIM3_CH2_POLARITY;
    tim3_configuration.channel[1].irq_dma.active = TIM3_CH2_IRQ_DMA_ENABLE;
    //tim3_configuration.channel[1].irq_dma.edge = TIM3_CH2_IRQ_DMA_ENABLE;
    tim3_configuration.channel[1].irq_dma.priority = TIM3_CH2_IRQ_DMA_PRIORITY;
    tim3_configuration.channel[1].irq_dma.callback = TIM3_CH2_IRQ_DMA_CALLBACK;
    
    tim3_configuration.channel[1].out_cmp_mode = TIM3_CH2_OC_MODE;


    tim3_configuration.channel[2].channel_enable = TIM3_CH3_ENABLE;
    tim3_configuration.channel[2].timer_mode = TIM3_CH3_MODE;
    tim3_configuration.channel[2].tim_mux = TIM3_CH3_TIM_MUX;
    tim3_configuration.channel[2].percent_pwm = TIM3_CH3_PERCENT_PWM;
    
    tim3_configuration.channel[2].polarity = TIM3_CH3_POLARITY;
    tim3_configuration.channel[2].irq_dma.active = TIM3_CH3_IRQ_DMA_ENABLE;
    //tim3_configuration.channel[2].irq_dma.edge = TIM3_CH3_IRQ_DMA_ENABLE;
    tim3_configuration.channel[2].irq_dma.priority = TIM3_CH3_IRQ_DMA_PRIORITY;
    tim3_configuration.channel[2].irq_dma.callback = TIM3_CH3_IRQ_DMA_CALLBACK;
    
    tim3_configuration.channel[2].out_cmp_mode = TIM3_CH3_OC_MODE;


    tim3_configuration.channel[3].channel_enable = TIM3_CH4_ENABLE;
    tim3_configuration.channel[3].timer_mode = TIM3_CH4_MODE;
    tim3_configuration.channel[3].tim_mux = TIM3_CH3_TIM_MUX;
    tim3_configuration.channel[3].percent_pwm = TIM3_CH3_PERCENT_PWM;
    
    tim3_configuration.channel[3].polarity = TIM3_CH3_POLARITY;
    tim3_configuration.channel[3].irq_dma.active = TIM3_CH3_IRQ_DMA_ENABLE;
    //tim3_configuration.channel[3].irq_dma.edge = TIM3_CH3_IRQ_DMA_ENABLE;
    tim3_configuration.channel[3].irq_dma.priority = TIM3_CH3_IRQ_DMA_PRIORITY;
    tim3_configuration.channel[3].irq_dma.callback = TIM3_CH3_IRQ_DMA_CALLBACK;
    
    tim3_configuration.channel[3].out_cmp_mode = TIM3_CH3_OC_MODE;
    
    //tim3_configuration.mode = TIM3_MODE;
    
    timer_init(&tim3_configuration);
#endif
}
