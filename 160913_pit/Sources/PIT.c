/**
	\file
	\author Carem Angélica Bernabe Acosta
	\date	26/02/2016
 */


#include "DataTypeDefinitions.h"
#include "MK64F12.h"
#include "PIT.h"

extern uint8 PIT0_Flag;

//Interruption routine
void PIT0_IRQHandler(){
	PIT_TFLG0 |= PIT_TFLG_TIF_MASK;
	PIT_TCTRL0 = 0; //read control register for clear PIT flag, this is silicon bug
	PIT_TCTRL0 &= ~(PIT_TCTRL_TIE_MASK);//enables PIT timer interrupt
	PIT_TCTRL0 &= ~(PIT_TCTRL_TEN_MASK);//enables timer0
	PIT0_Flag = TRUE;
}

void PIT_delay(PIT_TimerType pitTimer,float systemClock ,float period){
	float cycles = ((systemClock*period)-1)/2; //calculates the number of cycles

	switch(pitTimer){
		case PIT_0:
			PIT_LDVAL0 = cycles; //Set up timer 0 for the calculated cycles
			PIT_TCTRL0 = PIT_TCTRL_TIE_MASK; //Enable timer 0  interrupts
			PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK; //Starts timer 0
		break;
	}

return;
}


