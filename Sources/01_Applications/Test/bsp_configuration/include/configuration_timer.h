#ifndef CONFIGURATION_TIMER_H
#define CONFIGURATION_TIMER_H


/*********************************
 * TIM definitions
 ********************************/


/* TIM_1 configuration                     */
#define TIM1_TIME_FREQUENCY        1 MSEC
#define TIM1_CH1_ENABLE            enable
#define TIM1_CH1_PERCENT_PWM       0
#define TIM1_CH1_POLARITY          0
#define TIM1_CH1_TIM_MUX           ccx_channel_input_ICx_straight
#define TIM1_CH1_MODE              input_capture
#define TIM1_CH1_OC_MODE           pwm2
#define TIM1_CH1_IRQ_DMA_ENABLE    irq_dma_inactive
#define TIM1_CH1_IRQ_DMA_PRIORITY  0
#define TIM1_CH1_IRQ_DMA_CALLBACK  0
#define TIM1_CH2_ENABLE            disable
#define TIM1_CH2_PERCENT_PWM       0
#define TIM1_CH2_POLARITY          0
#define TIM1_CH2_TIM_MUX           0
#define TIM1_CH2_MODE              0
#define TIM1_CH2_OC_MODE           0
#define TIM1_CH2_IRQ_DMA_ENABLE    0
#define TIM1_CH2_IRQ_DMA_PRIORITY  0
#define TIM1_CH2_IRQ_DMA_CALLBACK  0
#define TIM1_CH3_ENABLE            disable
#define TIM1_CH3_PERCENT_PWM       0
#define TIM1_CH3_POLARITY          0
#define TIM1_CH3_TIM_MUX           0
#define TIM1_CH3_MODE              0
#define TIM1_CH3_OC_MODE           0
#define TIM1_CH3_IRQ_DMA_ENABLE    0
#define TIM1_CH3_IRQ_DMA_PRIORITY  0
#define TIM1_CH3_IRQ_DMA_CALLBACK  0
#define TIM1_CH4_ENABLE            disable
#define TIM1_CH4_PERCENT_PWM       0
#define TIM1_CH4_POLARITY          0
#define TIM1_CH4_TIM_MUX           0
#define TIM1_CH4_MODE              0
#define TIM1_CH4_OC_MODE           0
#define TIM1_CH4_IRQ_DMA_ENABLE    0
#define TIM1_CH4_IRQ_DMA_PRIORITY  0
#define TIM1_CH4_IRQ_DMA_CALLBACK  0


/* TIM_2 configuration                     */
#define TIM2_TIME_FREQUENCY        1 MSEC
#define TIM2_CH1_ENABLE            disable
#define TIM2_CH1_PERCENT_PWM       0
#define TIM2_CH1_POLARITY          0
#define TIM2_CH1_TIM_MUX           0
#define TIM2_CH1_MODE              0
#define TIM2_CH1_OC_MODE           0
#define TIM2_CH1_IRQ_DMA_ENABLE    0
#define TIM2_CH1_IRQ_DMA_PRIORITY  0
#define TIM2_CH1_IRQ_DMA_CALLBACK  0
#define TIM2_CH2_ENABLE            enable
#define TIM2_CH2_PERCENT_PWM       0
#define TIM2_CH2_POLARITY          0
#define TIM2_CH2_TIM_MUX           ccx_channel_input_ICx_straight
#define TIM2_CH2_MODE              input_capture
#define TIM2_CH2_OC_MODE           pwm2
#define TIM2_CH2_IRQ_DMA_ENABLE    irq_dma_inactive
#define TIM2_CH2_IRQ_DMA_PRIORITY  0
#define TIM2_CH2_IRQ_DMA_CALLBACK  0
#define TIM2_CH3_ENABLE            disable
#define TIM2_CH3_PERCENT_PWM       0
#define TIM2_CH3_POLARITY          0
#define TIM2_CH3_TIM_MUX           0
#define TIM2_CH3_MODE              0
#define TIM2_CH3_OC_MODE           0
#define TIM2_CH3_IRQ_DMA_ENABLE    0
#define TIM2_CH3_IRQ_DMA_PRIORITY  0
#define TIM2_CH3_IRQ_DMA_CALLBACK  0
#define TIM2_CH4_ENABLE            disable
#define TIM2_CH4_PERCENT_PWM       0
#define TIM2_CH4_POLARITY          0
#define TIM2_CH4_TIM_MUX           0
#define TIM2_CH4_MODE              0
#define TIM2_CH4_OC_MODE           0
#define TIM2_CH4_IRQ_DMA_ENABLE    0
#define TIM2_CH4_IRQ_DMA_PRIORITY  0
#define TIM2_CH4_IRQ_DMA_CALLBACK  0


/* TIM_3 configuration                     */
#define TIM3_TIME_FREQUENCY        1 MSEC
#define TIM3_CH1_ENABLE            enable
#define TIM3_CH1_PERCENT_PWM       25
#define TIM3_CH1_POLARITY          0
#define TIM3_CH1_TIM_MUX           ccx_channel_output
#define TIM3_CH1_MODE              output_compare
#define TIM3_CH1_OC_MODE           pwm2
#define TIM3_CH1_IRQ_DMA_ENABLE    irq_dma_inactive
#define TIM3_CH1_IRQ_DMA_PRIORITY  0
#define TIM3_CH1_IRQ_DMA_CALLBACK  0
#define TIM3_CH2_ENABLE            disable
#define TIM3_CH2_PERCENT_PWM       0
#define TIM3_CH2_POLARITY          0
#define TIM3_CH2_TIM_MUX           0
#define TIM3_CH2_MODE              0
#define TIM3_CH2_OC_MODE           0
#define TIM3_CH2_IRQ_DMA_ENABLE    0
#define TIM3_CH2_IRQ_DMA_PRIORITY  0
#define TIM3_CH2_IRQ_DMA_CALLBACK  0
#define TIM3_CH3_ENABLE            disable
#define TIM3_CH3_PERCENT_PWM       0
#define TIM3_CH3_POLARITY          0
#define TIM3_CH3_TIM_MUX           0
#define TIM3_CH3_MODE              0
#define TIM3_CH3_OC_MODE           0
#define TIM3_CH3_IRQ_DMA_ENABLE    0
#define TIM3_CH3_IRQ_DMA_PRIORITY  0
#define TIM3_CH3_IRQ_DMA_CALLBACK  0
#define TIM3_CH4_ENABLE            disable
#define TIM3_CH4_PERCENT_PWM       0
#define TIM3_CH4_POLARITY          0
#define TIM3_CH4_TIM_MUX           0
#define TIM3_CH4_MODE              0
#define TIM3_CH4_OC_MODE           0
#define TIM3_CH4_IRQ_DMA_ENABLE    0
#define TIM3_CH4_IRQ_DMA_PRIORITY  0
#define TIM3_CH4_IRQ_DMA_CALLBACK  0


#endif /* CONFIGURATION_TIMER_H_ */
