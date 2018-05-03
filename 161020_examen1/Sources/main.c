/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "MK64F12.h"
#include "DataTypeDefinitions.h"

//#include "PIT.h"
//#include "NVIC.h"

#include "GPIO.h"
//
typedef enum {
	VERDE,
	AZUL,
	ROJO,
}StateDefinitionType;

typedef struct
{
	uint32 out;
	uint8 next[2];
}StateType;

void (*fpuntero[3])()= {azul,rojo,verde};

const StateType FineStateMachineMoore[3]=
{
		{VERDE,{VERDE, AZUL}},
		{AZUL,{AZUL, ROJO}},
		{ROJO,{ROJO, VERDE}},

};

StateDefinitionType currentState = VERDE;

void azul();
void rojo();
void verde();
void blanco();


int main(void)
{
	uint32 inputValueSW2 = 0; //variable para guardar el valor del PORTC
	uint32 inputValueSW3 = 0;
	uint8 led = 0x0;

	/*CLOCK GATING*/
	SIM_SCGC5=0x2E00; /*escribir constante en registro*/ //0010 1110 0 0 //PRENDER PUERTOS  A Y C
	/*PIN22 COMO GPIO*/
	PORTB_PCR21 =0x0000100;//B
	PORTB_PCR22 =0x0000100;//R
	PORTE_PCR26 =0x0000100;//G

	PORTC_PCR6 = PORT_PCR_MUX(1)|0x03;        //sw2  // =0x0000103;//PS //Pull up
	PORTA_PCR4 = PORT_PCR_MUX(1)|0x03;        //sw3  // =0x0000103;//PS //Pull up

	/*SAFE VALUE*/
	GPIOB_PDOR =0x00600000;/*se puso un uno en el bit 21 y 22*/   /*apagados*/
	GPIOE_PDOR =0x04000000;/*se puso un uno en el bit 26*/        /*apagados*/

	/*PIN22 AS OUTPUT*//*0entrada, 1salida*/
	GPIOB_PDDR =0x00600000;
	GPIOE_PDDR =0x04000000;

	/**Configures GPIOC pin6 as input*/
	GPIOC_PDDR = 0;
	/**Configures GPIOA pin4 as input*/
	GPIOA_PDDR = 0;

    /* This for loop should be replaced. By default this loop allows a single stepping. */
    for (;;) {

    	/** Se limpia la bandera para mandar a llamar al siguiente estado*/
    	currentState_flag = 0;

    	/** Se actualiza en el estado en el que está*/
    	currentState_Motor = FineStateMachineMoore_Motor[currentState].out;

    	/*Se manda a llamar a la función del estado actual*/
    	(*fptrSeq[currentState])();

    	/**Si la bandera de activación y el botón están encendidos se aumenta la bandera del siguiente estado*/
    	input=readFlag_PORTC();
    	if(TRUE == Flag_Enable){
    		if (TRUE == input) {
    			currentState_flag++;
    			clearFlag_PORTC();
    		}


		(*fpuntero[currentState])();

			inputValueSW2 = GPIOC_PDIR;
			inputValueSW2 = inputValueSW2 & 0x40;

			inputValueSW3 = GPIOA_PDIR;
			inputValueSW3 = inputValueSW3 & 0x10;

			inputValueSW2 = inputValueSW2 >> 6;
			inputValueSW3 = inputValueSW3 >> 3;

			led = inputValueSW2 | inputValueSW3;

			puntero[led]();

    }
    /* Never leave main */
    return 0;
}

void azul(){
	GPIOB_PDOR = ~(0x200000);
	GPIOE_PDOR = ~(0x0);
}

void rojo(){
	GPIOB_PDOR = ~(0x400000);
	GPIOE_PDOR = ~(0x0);
}

void verde(){
	GPIOB_PDOR = ~(0x0);
	GPIOE_PDOR = ~(0x4000000);
}

void blanco(){
	GPIOB_PDOR = 0;
	GPIOE_PDOR = 0;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
