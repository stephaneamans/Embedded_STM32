/* Includes ------------------------------------------------------------------*/
#include "bsp_configuration.h"
#include "lld_gpio.h"

int main(void)
{
	soc_core_configuration();
	soc_peripherals_configuration();

	//clock_select_clock_to_output(SYSCLOCK);

	/*Timer channel-configuration in input mode*/
	/* Variable to store timestamp for last detected active edge */
//	uint32_t TimeStamp;
	/* The ARR register reset value is 0x0000FFFF for TIM3 timer. So it should
	be ok for this snippet */
	/* If you want to change it uncomment the below line */
	/* TIM3->ARR = ANY_VALUE_YOU_WANT */
	/* Set the TIM3 timer channel 1 as input */
	/* CC1S bits are writable only when the channel1 is off */
	/* After reset, all the timer channels are turned off */
//	TIM3->CCMR1 |= TIM_CCMR1_CC1S_0;
	/* Enable the TIM3 channel1 and keep the default configuration (state after
	reset) for channel polarity */
//	TIM3->CCER |= TIM_CCER_CC1E;
	/* Start the timer counter */
//	TIM3->CR1 |= TIM_CR1_CEN;
	/* Clear the Capture event flag for channel 1 */
//	TIM3->SR = ~TIM_SR_CC1IF;
	/* Loop until the capture event flag is set */
//	while (!(TIM3->SR & TIM_SR_CC1IF));
	/* An active edge was detected, so store the timestamp */
//	TimeStamp = TIM3->CCR1;




	/* The ARR register reset value is 0x0000FFFF for TIM3 timer. So it should
	be ok for this snippet. If you want to change it uncomment the below line */
	/* TIM3->ARR = ANY_VALUE_YOU_WANT */
	/* The TIM3 timer channel 1 after reset is configured as output */
	/* TIM3->CC1S reset value is 0                                                  => fait à tester on OFF          */
	
	/* To select PWM2 output mode set the OC1M control bit-field to '111' */
	//TIM3->CCMR1 |= TIM_CCMR1_OC1M_0 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;        =>  fait
	/* Set the duty cycle to 50% */
	/*TIM3->CCR1 = TIM3->ARR / 2;                                                   => fait */
	/* By default, after reset, preload for channel 1 is turned off */
	/* To change it uncomment the below line */
	// TIM3->CCMR1 |= TIM_CCMR1_OC1PE;                                              => test avec et sans     !!!!!!!!!!!!!!!
	/* Enable the TIM3 channel1 and keep the default configuration (state after
	reset) for channel polarity */
	/* TIM3->CCER |= TIM_CCER_CC1E;                                                 => fait */
	






    while(1)
    {


    	//gpio_toggle(GPIOA, 8);
        tim_wait(TIM1, channel_3);
        gpio_toggle(GPIOA, 6);
        
        //if(gpio_read_GPIO(GPIOB, 9)){
        //gpio_set_GPIO(GPIOC, 13);
        //}
        //else{
            //gpio_clear_GPIO(GPIOC,13);
        //}
    }
}
