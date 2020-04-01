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
    usart1_configuration.baud_rate = USART1_BAUDRATE;
    usart1_configuration.length = USART1_LENGTH;
    usart1_configuration.wake_up = USART1_WAKEUP;
    usart1_configuration.parity = USART1_PARITY;
    usart1_configuration.stop = USART1_STOP;
    usart1_configuration.clock_modes = USART1_CLOCK_MODES;
    usart1_configuration.cts_rts = USART1_RTS;
    usart1_configuration.dma = USART1_DMA;
    usart1_configuration.irq.type = USART1_IRQ_TYPE;
    usart1_configuration.irq.callback_parity_err = USART1_IRQ_CALLBACK_PARITY;
    usart1_configuration.irq.callback_tx_err = USART1_IRQ_CALLBACK_TX_ERR;
    usart1_configuration.irq.callback_tx_complete_err = USART1_IRQ_CALLBACK_TX_COMPLETE_ERR;
    usart1_configuration.irq.callback_rx_err = USART1_IRQ_CALLBACK_RX_ERR;
    usart1_configuration.irq.callback_idle = USART1_IRQ_CALLBACK_IDLE;
    usart1_configuration.irq.callback_cts = USART1_IRQ_CALLBACK_CTS;
    usart1_configuration.irq.callback_error_irq = USART1_IRQ_CALLBACK_ERROR_IRQ;
    usart_init(USART1, &usart1_configuration);
#endif

#ifdef USART_2
    t_usart_cfg usart2_configuration;
    usart2_configuration.baud_rate = USART2_BAUDRATE;
    usart2_configuration.length = USART2_LENGTH;
    usart2_configuration.wake_up = USART2_WAKEUP;
    usart2_configuration.parity = USART2_PARITY;
    usart2_configuration.stop = USART2_STOP;
    usart2_configuration.clock_modes = USART2_CLOCK_MODES;
    usart2_configuration.cts_rts = USART2_RTS;
    usart2_configuration.dma = USART2_DMA;
    usart2_configuration.irq.type = USART2_IRQ_TYPE;
    usart2_configuration.irq.callback_parity_err = USART2_IRQ_CALLBACK_PARITY;
    usart2_configuration.irq.callback_tx_err = USART2_IRQ_CALLBACK_TX_ERR;
    usart2_configuration.irq.callback_tx_complete_err = USART2_IRQ_CALLBACK_TX_COMPLETE_ERR;
    usart2_configuration.irq.callback_rx_err = USART2_IRQ_CALLBACK_RX_ERR;
    usart2_configuration.irq.callback_idle = USART2_IRQ_CALLBACK_IDLE;
    usart2_configuration.irq.callback_cts = USART2_IRQ_CALLBACK_CTS;
    usart2_configuration.irq.callback_error_irq = USART2_IRQ_CALLBACK_ERROR_IRQ;
    usart_init(USART2, &usart2_configuration);
#endif

#ifdef TIM_1
    t_timer_cfg tim1_configuration;
    tim1_configuration.timer = TIM1;
   // tim1_configuration.mode = TIM1_MODE;
    tim1_configuration.channel = TIM1_CHANNEL;
    tim1_configuration.irq_dma.active = TIM1_IRQ_ENABLE;
    tim1_configuration.tim_mux = 0;
    tim1_configuration.polarity = 0;
    tim1_configuration.percent_pwm = 0;
   // tim1_configuration.out_cmp_mode = TIM1_OC_MODE;
    tim1_configuration.duration = TIM1_DURATION;
    tim1_configuration.prescaler = 0;
    tim1_configuration.irq_dma.active = 0;
    tim1_configuration.irq_dma.rising = 0;
    tim1_configuration.irq_dma.priority = 0;
    timer_init(&tim1_configuration);
#endif


}

