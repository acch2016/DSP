/*
 * PIT.c
 *
 *  Created on: 09/09/2016
 *      Author: Alexis
 */

#include "MK64F12.h"
#include "PIT.h"

 uint8 PIT0_Flag;

void PIT0_IRQHandler(){
	PIT_TFLG0 |= PIT_TFLG_TIF_MASK;
	PIT_TCTRL0; //read control register for clear PIT flag, this is silicon bug
	PIT_TCTRL0 &= ~(PIT_TCTRL_TIE_MASK);//enables PIT timer interrupt
	PIT_TCTRL0 &= ~(PIT_TCTRL_TEN_MASK);//enables timer0
	PIT0_Flag = TRUE;		//Bandera de control dentro del programa

}

void PIT_delay(PIT_TimerType pitTimer,float systemClock ,float perior){
	float periodo = 0.0f;
	periodo =  (perior*systemClock)/2 - 1; //formula para calcular el periodo de la onda cuadrada
	PIT_LDVAL0 = (int)periodo;			   //Carga el valor de autorecarga
	PIT_TCTRL0 = 0x00;					   //Desabiita la interrupción
	PIT_TCTRL0 = 0x02; // activa la interrupción del timer 0
	PIT_TCTRL0 |= 0x01; // habilita el timer 0

}
