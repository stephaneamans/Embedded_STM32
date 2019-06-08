/*
 * d_clock.c
 *
 *  Created on: Apr 20, 2019
 *      Author: Stéphane Amans
 */


/* Include files																				*/
#include "d_clock.h"


uint8_t clock_initClock(uint32_t sysClk, uint32_t AHBclk, uint32_t APB1clk, uint32_t APB2clk, CLOCK_SOURCES source){
	uint8_t	error = OK;										/* Error flag, will be returned at the end of the function.			*/
	error		= clock_startOscillator(source);			/* Start the appropriate oscillator									*/
	if ((source >= PLL_HSI) && (source <= PLL_HSE_BYP)){	/* PLL needs to be activated if system clock is greater than osc,	*/
		error 	|= clock_startOscillator(HSI_OSC);
		error 	|= clock_switchSystemClk(HSI_OSC);
		error 	|= clock_initActivatePLL(sysClk, source);	/* Set PLL with the parameters.										*/
	}
	error		|= clock_setFlashLatency(sysClk);			/* Set the flash latency function of the system clock.				*/
	error		|= clock_switchSystemClk(source);			/* Switch system clock.												*/
	if		((source == HSI_OSC) || (source == PLL_HSI)){	/* If High Speed Internal Oscillator (HSI) is selected,				*/
		error	|=	clock_stopOscillator(HSE_BYP);			/* Stop High Speed External Oscillator (HSE) and the bypass.		*/
	}
	else if	((source == HSE_OSC) || (source == HSE_BYP)		/* If any HSE source is selected,									*/
			|| (source == PLL_HSE)
			|| (source == PLL_HSE_BYP)) {
		error	|=	clock_stopOscillator(HSI_OSC);			/* Stop High Speed Internal Oscillator (HSI),						*/
		if	((source == HSE_OSC) || (source == PLL_HSE)) {	/* If High Speed External Oscillator (HSE) is selected,				*/
			RCC->CR		&= 0xFFFBFFFF;						/* And deactivate the bypass.										*/
		}
	}

	//error =  	clock_initAHB(sysClk, AHBclk);				/* Set AHB prescaler with the parameters.							*/
	//error =  	clock_initAPB1(AHBclk, APB1clk);			/* Set APB1 prescaler with the parameters.							*/
	//error =	 	clock_initAPB2(AHBclk, APB2clk);		/* Set APB2 prescaler with the parameters.							*/
	return error;
}


uint8_t clock_startOscillator(CLOCK_SOURCES source){
	if		((source == HSI_OSC) || (source == PLL_HSI)){
		RCC->CR 	|= 0x00000001;							/* HSION 	= 1, enable High Speed Internal oscillator.				*/
		while((RCC->CR & 0x00000002) != 2){}				/* Wait for HSIRDY = 1, HSI oscillator is stable.					*/
	}
	else if	((source == HSE_OSC) || (source == PLL_HSE)){
		RCC->CR 	|= 0x00010000;							/* HSEON 	= 1, enable High Speed External oscillator.				*/
		while((RCC->CR & 0x00020000) != 0x20000){}			/* Wait for HSERDY = 1, HSE oscillator is stable.					*/
	}
	else if ((source == HSE_BYP) || (source == PLL_HSE_BYP)){
		RCC->CR |= 0x00050000;								/* HSEON 	= 1, enable High Speed External source.					*/
															/* HSEBYP 	= 1, Bypass the crystal for an external source.			*/
		while((RCC->CR & 0x00020000) != 0x20000){}			/* Wait for HSERDY = 1, HSE oscillator is stable.					*/													/* HSEBYP	= 1, select external source.					*/
	}
	return OK;
}


uint8_t clock_stopOscillator(CLOCK_SOURCES source){
	if		(source == HSI_OSC){
		RCC->CR 	&= (~0x00000001);						/* Clear HSION bit.													*/
	}
	else if	(source == HSE_OSC){
		RCC->CR 	&= (~0x00010000);						/* Clear HSEON bit. 												*/
	}
	else if	(source == HSE_BYP){
		RCC->CR 	&= (~0x00050000);						/* Clear HSEON and HSEBYP bits.										*/
	}
	return OK;
}


uint8_t clock_switchSystemClk(CLOCK_SOURCES source){
	uint8_t localSource = (RCC->CFGR & 0x0C) >> 2;			/* Read SWS bits to know the source currently selected.				*/

	if		((localSource != source) && (source == HSI_OSC)){
		RCC->CFGR 	&= 0xFFFFFFF0;							/* SW		= 0, Select the HSI oscillator.							*/
	}
	else if	((localSource != source) && (source == HSE_OSC)){
		if(localSource == 0x00){							/* If local source is HSI oscillator.								*/
			RCC->CFGR 	|= 0x01;							/* SW		= 1, Disable HSI oscillator, LSB is set.				*/
		}
		else if(localSource == 0x02){						/* If local source is PLL.											*/
			RCC->CFGR 	^= 0x03;							/* SW		= 1, Disable PLL, invert the 2 bits.					*/
		}
	}
	else if	((localSource != source) && ((source >= PLL_HSI) && (source <= PLL_HSE_BYP))){
		if(localSource == 0x00){							/* If local source is HSI oscillator.								*/
			RCC->CFGR 	|= 0x02;							/* SW		= 2, Disable HSI oscillator , MSB is set.				*/
		}
		else if(localSource == 0x01){						/* If local source is HSE oscillator.								*/
			RCC->CFGR 	^= 0x03;							/* SW		= 2, Disable PLL, invert the 2 bits.					*/
		}
	}
	return OK;
}


uint8_t clock_initActivatePLL(uint32_t sysclk, CLOCK_SOURCES source){
	uint8_t		PLLmult[15]		= {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
	uint32_t 	tempPllMul 	= 0;								/* Local variable to compute the PLL multiplier coefficient.	*/
	uint32_t	tempClkFreqMHZ	= CLOCK_FREQ_MHZ;				/* Local var to modify the CLOCK_FREQ_MHZ function of divisions.*/
	uint8_t		tempError = ERROR_WRONG_CLOCK_SET;				/* Local variable to return the complete value of the function.	*/

	RCC->CR 	&= ~(0x01000000);								/* PLLON 	= 0, disable PLL.									*/
	while((RCC->CR & 0x02000000) != 0x00000000){}				/* Wait for PLLRDY = 0, PLL is disabled.						*/
	RCC->CFGR &= 0xFFC0FFFF;									/* PLLMUL	= 0, Clear the PLL multiplier field.				*/
																/* PLLXTPRE	= 0, Clear the PLL HSE divider field.				*/
																/* PLLSRC 	= 0, Clear the PLL source field.					*/
	if((((sysclk % CLOCK_FREQ_MHZ) != 0) 						/* Branch if sysclk is not a multiple of the ext crystal,		*/
	  || (sysclk == CLOCK_FREQ_MHZ)) &&							/* Or if sysclk is equal to the ext crystal,					*/
	    (source == PLL_HSE)){									/* And the clock is from HSE (bypassed or not) oscillator,		*/
		RCC->CFGR |= 0x00020000;								/* PLLXTPRE	= 1, divide the HSE input oscillator by 2.			*/
		tempClkFreqMHZ /= 2;									/* The clock frequency local variable is divided by 2.			*/
	}
	/* The clock freq local variable always divided by 2 in HSI.																*/
	if((source == HSI_OSC) || (source == PLL_HSI)){tempClkFreqMHZ /= 2;}

	tempPllMul 	= sysclk / tempClkFreqMHZ;						/* Compute the coefficient to load into the PLL multiplier.		*/
	for(uint8_t index = 0; index <= 14; index++){				/* Screen the PLL multiplier table.								*/
		if((tempClkFreqMHZ * PLLmult[index]) == sysclk){		/* If the result correspond to a valid system clock value,		*/
			tempPllMul = PLLmult[index]-2;						/* -2 offset to translate the multiplier coeff into a register.	*/
			tempPllMul = (tempPllMul & 0x000000FF) << 18;		/* Mask and shift to the PLL MULT position in the register. 	*/

			RCC->CFGR 	|= tempPllMul;							/* PLLMUL	= x, Set the PLL multiplier.						*/
			if ((source == PLL_HSE) || (source == PLL_HSE_BYP)){/* If HSE oscillator is selected,								*/
				RCC->CFGR	|= 0x00010000;						/* Select the HSE PLL source.									*/
			}
			RCC->CR 	|= 0x01000000;							/* PLLON 	= 1, PLL is enabled.								*/
			while((RCC->CR & 0x02000000) != 0x02000000){}		/* Wait for PLLRDY = 1, PLL is stable.							*/
			tempError = OK;
			break;
		}
	}
	return tempError;
}


uint8_t clock_initAHB(uint32_t sysclk, uint32_t AHBclk){
	uint16_t 	AHBprescaler[9] 	= {1, 2, 4, 8, 16, 64, 128, 256, 512};
	uint32_t 	localAHBdiv 		= (sysclk / AHBclk);		/* Compute the coefficient to load into the PLL multiplier.	*/
	uint8_t		error = ERROR_WRONG_CLOCK_SET;

	for(uint8_t index = 0; index < 9; index++){					/* Screen the AHB prescaler table.							*/
		if((sysclk / AHBprescaler[index]) == AHBclk){
			if(index == 0){localAHBdiv = 0;}
			else{
				localAHBdiv = index + 7;
			}
			localAHBdiv = (localAHBdiv & 0x000000FF) << 4;
			RCC->CFGR 	&= 0xFFFFFF0F;							/* HPRE		= 0, Clear the AHB prescaler field.				*/
			RCC->CFGR 	|= localAHBdiv;							/* HPRE 	= x, Set the HPRE prescaler.					*/
			error = OK;											/* No error reported.										*/
			break;												/* Go out of the loop, the value has been found.			*/
		}
	}
	return error;
}


uint8_t clock_initAPB1(uint32_t AHBclk, uint32_t APB1clk){
	uint8_t 	APBprescaler[5] 	= {1, 2, 4, 8, 16};
	uint32_t 	localAPB1div 		= (AHBclk / APB1clk);		/* Compute the coefficient to load into the PLL multiplier.	*/
	uint8_t		error = ERROR_WRONG_CLOCK_SET;

	for(uint8_t index = 0; index < 5; index++){					/* Screen the APB1 prescaler table.			 				*/
		if((AHBclk / APBprescaler[index]) == APB1clk){
			if(index == 0){localAPB1div = 0;}
			else{
				localAPB1div = index + 3;
			}
			localAPB1div = (localAPB1div & 0x000000FF) << 8;
			RCC->CFGR 	&= 0xFFFFF8FF;							/* PPRE1	= 0, Clear the APB1 prescaler field.			*/
			RCC->CFGR 	|= localAPB1div;						/* PPRE1 	= x, Set the APB1 prescaler.					*/
			error = OK;
			break;												/* Go out of the loop, the value has been found.			*/
		}
	}
	return error;
}


uint8_t clock_initAPB2(uint32_t AHBclk, uint32_t APB2clk){
	uint8_t 	APBprescaler[5] 	= {1, 2, 4, 8, 16};
	uint32_t 	localAPB2div 		= (AHBclk / APB2clk);		/* Compute the coefficient to load into the PLL multiplier.	*/
	uint8_t		error = ERROR_WRONG_CLOCK_SET;

	for(uint8_t index = 0; index < 5; index++){					/* Screen the APB2 prescaler table.							*/
		if((AHBclk / APBprescaler[index]) == APB2clk){
			if(index == 0){localAPB2div = 0;}
			else{
				localAPB2div = index + 3;
			}
			localAPB2div = (localAPB2div & 0x000000FF) << 11;
			RCC->CFGR 	&= 0xFFFFF8FF;							/* PPRE2	= 0, Clear the APB2 prescaler field.			*/
			RCC->CFGR 	|= localAPB2div;						/* PPRE2 	= x, Set the APB2 prescaler.					*/
			error = OK;
			break;												/* Go out of the loop, the value has been found.			*/
		}
	}
	return error;
}


uint8_t clock_setFlashLatency(uint32_t sysClk){
	uint32_t tempFlashACR = 0;
	clock_startOscillator(HSI_OSC);

	//FLASH->ACR &= 0xFFFFFFEF;									/* LATENCY	= 0, 0 wait states configured.					*/
	//while((FLASH->ACR & 0x00000020) != 0x0){}					/* Wait for PLLRDY = 1, PLL is stable.							*/

	if((sysClk > 0) && (sysClk <= 24000000)){					/* If the system clock is between 0 and 24 MHz,				*/
		FLASH->ACR &= 0xFFFFFFF8;								/* LATENCY	= 0, 0 wait states configured.					*/
	}
	else if((sysClk > 24000000) && (sysClk <= 48000000)){		/* If the system clock is between 24 and 48 MHz,			*/
		tempFlashACR = FLASH->ACR;								/* Store the FLASH_ACR register.							*/
		FLASH->ACR = ((tempFlashACR & 0xFFFFFFF8)+1);			/* LATENCY	= 1, 1 wait state is configured.				*/
	}
	else if((sysClk > 48000000) && (sysClk <= 72000000)){		/* If the system clock is between 48 and 72 MHz,			*/
		tempFlashACR = FLASH->ACR;								/* Store the FLASH_ACR register.							*/
		//FLASH->ACR &= 0xFFFFFFFE;
		//FLASH->ACR |= 0x00000002;
		FLASH->ACR = ((tempFlashACR & 0xFFFFFFF8)+2);			/* LATENCY	= 2, 2 wait states are configured.				*/
	}
	FLASH->ACR |= 0x00000010;								/* LATENCY	= 0, 0 wait states configured.					*/
	while((FLASH->ACR & 0x00000020) != 0x00000020){}		/* Wait for PLLRDY = 1, PLL is stable.							*/
	return OK;
}


uint8_t clock_selectClockToOutput(CLOCK_SOURCES source){
	/*
	 Outputs the clock selected, system, HSI, HSE or PLL on the alternate for MCO pin.			;
	 The GPIO must be configured as alternate push pull 50 MHz output, example below:			;
	 gpio_initGPIO(GPIOA, 8 , MODE_OUTPUT_50MHZ, CNF_OUTPUT_ALTPUSHPULL, 0);					;

	:parameter	`source`: Clock to output: HSI_OSC, SYSCLOCK, HSE_OSC or PLL (defined in header);

	:return 	'u8'	: return 0 if OK.														;
	*/

	uint32_t localMCOMask = 0x07000000;

	RCC->CFGR	&= ~localMCOMask;								/* MCO 		= 0, Clear the MCO field, no clock selected.	*/
	if		(source == SYSCLOCK)	{RCC->CFGR |= 0x04000000;}	/* MCO 		= 4, Set the MCO field, SYSCLK selected for out.*/
	else if	(source == HSI_OSC)		{RCC->CFGR |= 0x05000000;}	/* MCO 		= 5, Set the MCO field, HSI selected for out.	*/
	else if	(source == HSE_OSC)		{RCC->CFGR |= 0x06000000;}	/* MCO 		= 6, Set the MCO field, HSE selected for out.	*/
	else if	((source >= PLL_HSI) &&
			(source <= PLL_HSE_BYP)){RCC->CFGR |= 0x07000000;}	/* MCO 		= 0, Set the MCO field, PLL/2 selected for out.	*/
	else						{RCC->CFGR	&= ~localMCOMask;}	/* MCO 		= 0, Clear the MCO field, no clock selected.	*/
	return OK;
}



