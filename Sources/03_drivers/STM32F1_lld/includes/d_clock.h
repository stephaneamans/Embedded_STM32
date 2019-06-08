/*
 * d_clock.h
 *
 *  Created on: Apr 20, 2019
 *      Author: Stéphane Amans
 */

#ifndef D_CLOCK_H_
#define D_CLOCK_H_


/* Include files:																								*/
#include "globals.h"
#include "stm32f103x6.h"


/* Structures definition for remapping function																	*/


/* Enumeration definition forSource selection: 																	*/
typedef enum{
	HSI_OSC			= 1,					/* High speed internal oscillator mask.								*/
	SYSCLOCK		= 2,					/* System clock ID for output										*/
	HSE_OSC			= 3,					/* High speed external oscillator mask.								*/
	HSE_BYP			= 4,					/* High speed external drive source mask.							*/
	PLL_HSI			= 5,					/* PLL clocked with HSI oscillator.									*/
	PLL_HSE			= 6,					/* PLL clocked with HSE oscillator.									*/
	PLL_HSE_BYP		= 7						/* PLL clocked with HSE Bypass oscillator.							*/
}CLOCK_SOURCES;


/* Functions prototypes:																*/
uint8_t clock_initClock(uint32_t sysclk, uint32_t AHBclk, uint32_t APB1clk, uint32_t APB2clk, CLOCK_SOURCES source);
uint8_t clock_startOscillator(CLOCK_SOURCES source);
uint8_t clock_stopOscillator(CLOCK_SOURCES source);
uint8_t clock_switchSystemClk(CLOCK_SOURCES systemSource);
uint8_t clock_initActivatePLL(uint32_t sysclk, CLOCK_SOURCES source);
uint8_t clock_initAHB(uint32_t sysclk, uint32_t AHBclk);
uint8_t clock_initAPB1(uint32_t AHBclk, uint32_t APB1clk);
uint8_t clock_initAPB2(uint32_t AHBclk, uint32_t APB2clk);
uint8_t clock_setFlashLatency(uint32_t sysClk);
uint8_t clock_selectClockToOutput(CLOCK_SOURCES source);

#endif /* D_CLOCK_H_ */
