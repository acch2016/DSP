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


//void FTM0_IRQHandler()
//{
//	/**Clearing the overflow interrupt flag*/
//	FTM0_SC &= ~FLEX_TIMER_TOF;
//	/** Toggling the output in port D*/
//	GPIOD_PDOR ^= 0xFF;
//}

void FTM_Init()
{
	/** Clock gating for the FlexTimer 0*/
	SIM_SCGC6 |= FLEX_TIMER_0_CLOCK_GATING;
	/**When write protection is enabled (WPDIS = 0), write protected bits cannot be written. 
	* When write protection is disabled (WPDIS = 1), write protected bits can be written.*/
	FTM0_MODE |= FLEX_TIMER_WPDIS;
	/**Enables the writing over all registers*/
	FTM0_MODE &= ~FLEX_TIMER_FTMEN;
	/**Assigning a default value for modulo register*/
	FTM0_MOD = 0x00FF;  
	/**Selects the Edge-Aligned PWM mode mode*/
	FTM0_C0SC = FLEX_TIMER_MSB | FLEX_TIMER_ELSB;
	/**Assign a duty cycle of 50%*/
	FTM0_C0V = FTM0_MOD/2;
	/**Configure the times*/
	FTM0_SC = FLEX_TIMER_CLKS_1|FLEX_TIMER_PS_128;
}


void FTM_updateCHValue(sint16 channelValue)
{
	/**Assigns a new value for the duty cycle*/
	FTM0_C0V = channelValue;
}

