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

static int count = 0; //El estado inicial es amarillo = 0

void switch_func(){
	GPIOB_PDOR=0xFFFFFFFF;
	GPIOE_PDOR = 0xFFFFFFFF;

	switch (count) {
	case 0:
		GPIOB_PDOR = 0xFFBFFFFF; // RED on
		GPIOE_PDOR = 0xFBFFFFFF; // GREEN on //amarillo
		break;

	case 1:
		GPIOB_PDOR = 0xFFBFFFFF; // RED on
		break;

	case 2:
		GPIOB_PDOR = 0xFF9FFFFF; //R B MORADO
		break;

	case 3:
		GPIOB_PDOR = 0xFFDFFFFF; // BLUE on
		break;

	case 4:
		GPIOE_PDOR = 0xFBFFFFFF; // G
		break;

	case 5:    //Si se pasa al 5 , se regresa al 0
		count = 0;
		break;

	default:       //Si se pasa al -1 , se regresa al 4
		count = 4;
		break;

	}

}

int main(void)
{

uint32 inputValue_sw2 = 0; //variable para guardar el valor del PORTC
uint32 inputValue_sw3 = 0; //variable para guardar el valor del PORTA

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

    	inputValue_sw2 = GPIOC_PDIR;//obtengo valor del switch 2
    	inputValue_sw3 = GPIOA_PDIR;//obtengo valor del switch 3

    	inputValue_sw2 = inputValue_sw2 & 0x40; //conservo el valor que me interesa
    	inputValue_sw3 = inputValue_sw3 & 0x10;



    	if(!inputValue_sw2 && !inputValue_sw3){

    		GPIOB_PDOR=0xFF9FFFFF;//R B
    	    GPIOE_PDOR=0xFBFFFFFF;// G
		}

		else if (!inputValue_sw2) {
			count++;

			switch_func();
		}

		else if (!inputValue_sw3) {
			count--;

			switch_func();


		}else{  //caso para ningun switch encendido

			switch_func();
		}

    	while((!inputValue_sw2)^(!inputValue_sw3)) //Solamente sucede una transicion de color por boton presionado // y es xor para que pueda salir de esta condicionmintras los dos botones estan presionados y además entrar a la condición del blanco
    	{
    		        inputValue_sw2 = GPIOC_PDIR;//obtengo valor
    		    	inputValue_sw3 = GPIOA_PDIR;

    		    	inputValue_sw2 = inputValue_sw2 & 0x40;
    		    	inputValue_sw3 = inputValue_sw3 & 0x10;
    	}


    	/******************************************************************************************************************************/
    }
    /* Never leave main */
    return 0;
}


//}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
