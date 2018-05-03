/**
	\file 
	\brief 
		This is the starter file of FlexTimer. 
		In this file the FlexTimer is configured in overflow mode. 
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	7/09/2014
	\todo
	    Add configuration structures.
 */

#include "FlexTimer.h"


void FTM0_IRQHandler()
{
	/**Clearing the overflow interrupt flag*/
	FTM0_SC &= ~FLEX_TIMER_TOF;
	/** Toggling the output in port C*/
	GPIOC_PDOR ^= 0x02;
}

void FlexTime_Init()
{	/** Clock gating for the FlexTimer 0*/
	SIM_SCGC6 |= FLEX_TIMER_0_CLOCK_GATING;
	/**When write protection is enabled (WPDIS = 0), write protected bits cannot be written. 
	 * When write protection is disabled (WPDIS = 1), write protected bits can be written.*/
	FTM0_MODE = FLEX_TIMER_WPDIS;
	/**Assigning a default value for modulo register*/
	FTM0_MOD = 0xA;
	/**Enabling the interrupt,selecting the clock source and a pre-scaler of 128*/
	FTM0_SC = FLEX_TIMER_TOIE| FLEX_TIMER_CLKS_1|FLEX_TIMER_PS_128;
	
}
