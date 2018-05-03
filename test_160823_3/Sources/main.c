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

static int i = 0;


//void delay (uint16 delay);
int main(void)
{


	/*CLOCK GATING*/
SIM_SCGC5=0x2400; /*escribir constante en registro*/

/*PIN22 COMO GPIO*/
PORTB_PCR21 =0x0000100;
PORTB_PCR22 =0x0000100;
PORTE_PCR26 =0x0000100;
/*SAFE VALUE*/
GPIOB_PDOR =0x00600000;/*se puso un uno en el bit 21 y 22*/   /*apagados*/
GPIOE_PDOR =0x04000000;/*se puso un uno en el bit 26*/        /*apagados*/
/*PIN22 AS OUTPUT*//*0entrada, 1salida*/
GPIOB_PDDR =0x00600000;
GPIOE_PDDR =0x04000000;
    /* This for loop should be replaced. By default this loop allows a single stepping. */
    for (;;) {
    	/*CLEARS*/
        /*GPIOB_PDOR=0;
        /* CLEAR*/

    	GPIOB_PDOR=0xFFBFFFFF;// RED on
    	//delay(6500);
    	GPIOB_PDOR=0xFFFFFFFF;//off
    //	delay(6500);
    	GPIOB_PDOR=0xFFDFFFFF;// BLUE on
    //	delay(6500);
    	//GPIOB_PDOR=0xFFFFFFFF;//off
    	//delay(6500);
    	GPIOE_PDOR=0xFBFFFFFF;// GREEN on
    	//delay(6500);
    	GPIOE_PDOR=0xFFFFFFFF;//off
    //	delay(6500);

    	GPIOB_PDOR=0xFF9FFFFF;//R B
        GPIOE_PDOR=0xFBFFFFFF;// G
      //  delay(6500);

        GPIOB_PDOR=0xFFFFFFFF;// off
    	GPIOE_PDOR=0xFFFFFFFF;// off
    	//delay(6500);

    }
    /* Never leave main */
    return 0;
}

//void delay(uint16 delay)
//{
//	volatile uint16 counter;
//
//	for (counter=delay;counter>0;counter--)
//	{
//	}

//}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
