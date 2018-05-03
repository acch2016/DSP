/**
	\file PIT.c
	\brief Controla las interrupciones del timer PIT y configuraciones de este
	\author Jose Luis Pizano & Alexis Andalón
	\date	26/02/2016
 */

/*Estos archivos contienen los tipos de datos y nombre de registros para la k64*/
#include "DataTypeDefinitions.h"
#include "MK64F12.h"
/**Llamada del header de este modulo*/
#include "PIT.h"
#include "NVIC.h"

/**Banderas utilizada para saber si una interrupción se ha activado*/
uint8 PIT0_Flag = FALSE;
uint8 PIT1_Flag = TRUE;
uint8 PIT2_Flag = TRUE;
float cycles;

//Interruption routine
void PIT0_IRQHandler()/**Rutina de interrupción del PIT 0*/
{
	PIT_TFLG0 |= PIT_TFLG_TIF_MASK;
	PIT_TCTRL0 = 0; //read control register for clear PIT flag, this is silicon bug
	PIT_TCTRL0 &= ~(PIT_TCTRL_TIE_MASK);//enables PIT timer interrupt
	PIT_TCTRL0 &= ~(PIT_TCTRL_TEN_MASK);//enables timer0
	PIT0_Flag = TRUE;
}

void PIT1_IRQHandler()/**Rutina de interrupción del PIT 0*/
{
	PIT_TFLG1 |= PIT_TFLG_TIF_MASK;
	PIT_TCTRL1 = 0; //read control register for clear PIT flag, this is silicon bug
	PIT_TCTRL1 &= ~(PIT_TCTRL_TIE_MASK);//enables PIT timer interrupt
	PIT_TCTRL1 &= ~(PIT_TCTRL_TEN_MASK);//enables timer0

	PIT1_Flag = TRUE;
}

void PIT2_IRQHandler()/**Rutina de interrupción del PIT 0*/
{
	PIT_TFLG2 |= PIT_TFLG_TIF_MASK;
	PIT_TCTRL2 = 0; //read control register for clear PIT flag, this is silicon bug
	PIT_TCTRL2 &= ~(PIT_TCTRL_TIE_MASK);//enables PIT timer interrupt
	PIT_TCTRL2 &= ~(PIT_TCTRL_TEN_MASK);//enables timer0
	PIT2_Flag = TRUE;
}

void PIT_delay(PIT_TimerType pitTimer,float systemClock ,float period)
/**Activación del PIT y su valor de recarga*/
{
	cycles = (((systemClock*period)/2)-1); //calculates the number of cycles

	switch(pitTimer){
	case PIT_0:
		PIT_LDVAL0 = cycles; //Set up timer 0 for the calculated cycles
		PIT_TCTRL0 = PIT_TCTRL_TIE_MASK; //Enable timer 0  interrupts
		PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK; //Starts timer 0
		break;
	case PIT_1:
		PIT_LDVAL1 = cycles; //Set up timer 1 for the calculated cycles
		PIT_TCTRL1 = PIT_TCTRL_TIE_MASK; //Enable timer 1  interrupts
		PIT_TCTRL1 |= PIT_TCTRL_TEN_MASK; //Starts timer 1
		break;
	case PIT_2:
		PIT_LDVAL2 = cycles; //Set up timer 1 for the calculated cycles
		PIT_TCTRL2 = PIT_TCTRL_TIE_MASK; //Enable timer 2  interrupts
		PIT_TCTRL2 |= PIT_TCTRL_TEN_MASK; //Starts timer 2
		break;
	}
	return;

}

void PIT_Disable(PIT_TimerType pitTimer)
/**Funcion para apagar el PIT*/
{
	switch (pitTimer) {
	case PIT_0:
		PIT_LDVAL0 = 0; //Set up timer 0 for the calculated cycles
		PIT_TCTRL0 = 0; //Disable timer 0  interrupts
		break;
	case PIT_1:
		PIT_LDVAL1 = 0; //Set up timer 1 for the calculated cycles
		PIT_TCTRL1 = 0; //Disable timer 1  interrupts
		break;
	case PIT_2:
		PIT_LDVAL2 = 0; //Set up timer 2 for the calculated cycles
		PIT_TCTRL2 = 0; //Disable timer 2  interrupts
		break;
	}
	return;
}


uint8 PIT2_Flag_read(){
	return PIT2_Flag;
}

void PIT2_Flag_clear(){
	PIT2_Flag = FALSE;
}

uint8 PIT0_Flag_state(){
	return PIT0_Flag;
}

void PIT0_Flag_edit(){
	PIT0_Flag = FALSE;
}

uint8 PIT1_Flag_state(){

	return PIT1_Flag;
}

void PIT1_Flag_edit(){

	PIT1_Flag=FALSE;
}


void PIT_init(){
	SIM_SCGC6 |= 0x00800000;										    //Se activa el reloj del timer PIT
	PIT_MCR = 0x00;														//Registro para habilitar los timers
	NVIC_setBASEPRI_threshold(PRIORITY_9);								//Se activa la prioridad máxima
	NVIC_enableInterruptAndPriotity(PIT_CH0_IRQ, PRIORITY_8	);			//Se activa la prioridad de la interrupción
																		//del timer 0 del PIT
}

