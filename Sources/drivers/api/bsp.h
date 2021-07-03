/*
 * bsp.h
 *
 * Created on: Jun 3, 2021
 * Author: Stephane Amans
 */
#ifndef BSP_H_
#define BSP_H_

/* SoC internal peripherals enumeration:        */
enum t_peripheral
{
    DMA_1,
	PORTA,
	PORTB,
	PORTC,
	PORTD,
	SPI1,
	SPI2,
	TIM_1,
	TIM_2,
	TIM_3,
	USART_01,
	USART_02
};

/** Configure core elements of the SoC.
 *
 * \param: void
 *
 * \return: void
 *
 */
//void soc_core_configuration(void);

/** Configure SoC peripherals.
 *
 * \param: void
 *
 * \return: void
 *
 */
//void soc_peripherals_configuration(void);

#endif /* BSP_H_ */
