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
    t_usart_cfg usart1_configuration;
    usart1_configuration.usart = USART1;
    usart1_configuration.baud_rate = USART1_BAUDRATE;
    usart1_configuration.length = USART1_LENGTH;
    usart1_configuration.wake_up = USART1_WAKEUP;
    usart1_configuration.parity = USART1_PARITY;
    usart1_configuration.stop = USART1_STOP_BITS;
    usart1_configuration.clock_modes = USART1_CLOCK_MODES;
    usart1_configuration.cts_rts = USART1_RTS;
    usart1_configuration.irq_dma.type = USART1_IRQ_DMA_TYPE;
    usart1_configuration.irq_dma.priority = USART1_IRQ_DMA_PRIORITY;
    usart1_configuration.irq_dma.callback = USART1_IRQ_CALLBACK;
    usart_init(&usart1_configuration);
#endif

#ifdef USART_2
    t_usart_cfg usart2_configuration;
    usart2_configuration.usart = USART2;
    usart2_configuration.baud_rate = USART2_BAUDRATE;
    usart2_configuration.length = USART2_LENGTH;
    usart2_configuration.wake_up = USART2_WAKEUP;
    usart2_configuration.parity = USART2_PARITY;
    usart2_configuration.stop = USART2_STOP_BITS;
    usart2_configuration.clock_modes = USART2_CLOCK_MODES;
    usart2_configuration.cts_rts = USART2_RTS;
    usart2_configuration.irq_dma.type = USART2_IRQ_DMA_TYPE;
    usart2_configuration.irq_dma.priority = USART2_IRQ_DMA_PRIORITY;
    usart2_configuration.irq_dma.callback = USART2_IRQ_CALLBACK;
    usart_init(&usart2_configuration);
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

