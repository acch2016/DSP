/**
	\file
	\author Alejandro Canale Chombo
	\date	2016/09/25
 */


#include "DataTypeDefinitions.h"
#include "MK64F12.h"
#include "PIT.h"
//#include "DAC.h"

uint8 PIT0_Flag;
uint8 PIT1_Flag=TRUE;
//uint8 wave_form = TRI;
float cycles;
//Interruption routine
void PIT0_IRQHandler(){
	PIT_TFLG0 |= PIT_TFLG_TIF_MASK;
	PIT_TCTRL0 = 0; //read control register for clear PIT flag, this is silicon bug
	PIT_TCTRL0 &= ~(PIT_TCTRL_TIE_MASK);//enables PIT timer interrupt
	PIT_TCTRL0 &= ~(PIT_TCTRL_TEN_MASK);//enables timer0

	//funcGen(wave_form);
	PIT0_Flag = TRUE;

//	PIT_LDVAL0 = cycles; //Set up timer 0 for the calculated cycles
//	PIT_TCTRL0 = PIT_TCTRL_TIE_MASK; //Enable timer 0  interrupts
//	PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK; //Starts timer 0
}

void PIT1_IRQHandler(){
	PIT_TFLG1 |= PIT_TFLG_TIF_MASK;
	PIT_TCTRL1 = 0; //read control register for clear PIT flag, this is silicon bug
	PIT_TCTRL1 &= ~(PIT_TCTRL_TIE_MASK);//enables PIT timer interrupt
	PIT_TCTRL1 &= ~(PIT_TCTRL_TEN_MASK);//enables timer0

	PIT1_Flag = TRUE;
}



uint8 PIT0_Flag_state(){

return PIT0_Flag;
}

void PIT0_Flag_edit(){

	PIT0_Flag=FALSE;
}

uint8 PIT1_Flag_state(){

return PIT1_Flag;
}

void PIT1_Flag_edit(){

	PIT1_Flag=FALSE;
}

void PIT_delay(PIT_TimerType pitTimer, float systemClock, float period) {
	cycles = ((systemClock * period) - 1); //calculates the number of cycles

	switch (pitTimer) {
	case PIT_0:
		PIT_LDVAL0 = cycles; //Set up timer 0 for the calculated cycles
		PIT_TCTRL0 = PIT_TCTRL_TIE_MASK; //Enable timer 0  interrupts
		PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK; //Starts timer 0
		break;
	case PIT_1:
		PIT_LDVAL1 = cycles; //Set up timer 0 for the calculated cycles
		PIT_TCTRL1 = PIT_TCTRL_TIE_MASK; //Enable timer 0  interrupts
		PIT_TCTRL1 |= PIT_TCTRL_TEN_MASK; //Starts timer 0
		break;
	}


	return;
}


