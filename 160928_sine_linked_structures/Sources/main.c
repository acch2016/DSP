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
//falta corregir el que no usare pit0 sino pit1
#include "MK64F12.h"

#include "GlobalFunctions.h"
#include "DataTypeDefinitions.h"
#include "PIT.h"
#include "NVIC.h"
#include "DAC.h"
#include "FUNC.h"
#include "GPIO.h"
#define SYSTEM_CLOCK 21000000 //Clock Frequeency
#define DELAY 0.002 //Period

//uint8 PIT0_Flag = FALSE;



int main(void)
{
/**********************************************************************************************/
////////////////////////////////////////////DAC
SIM_SCGC2  |= SIM_SCGC2_DAC0_MASK;//clock gating del DAC0
//SIM_SCGC4  |= SIM_SCGC4_VREF_MASK;//clock gating del VREF

DAC0_C0 |= DAC_C0_DACEN_MASK;//pin DAC enable
DAC0_C0 |= DAC_C0_DACRFS_MASK;//pin DAC reference Select

//VREF_SC |= VREF_SC_VREFEN_MASK |1;// Enable VREF y en modo High Power Buffer


/**********************************************************************************************/
////////////////////////////////////////////PIT
SIM_SCGC6 |= SIM_SCGC6_PIT_MASK; //Activa el clock Gating del PIT, bit 23 0x800000
PIT_MCR = 0x00;//Clock for PIT timers and timerand timers continue to run in debug mode



/**********************************************************************************************/
////////////////////////////////////////////NVIC
NVIC_setBASEPRI_threshold(PRIORITY_9);
NVIC_enableInterruptAndPriotity(PIT_CH0_IRQ, PRIORITY_8);
NVIC_enableInterruptAndPriotity(PORTA_IRQ, PRIORITY_7);
EnableInterrupts;


/**********************************************************************************************/

//PIT_delay(PIT_0,SYSTEM_CLOCK,DELAY);
 setModuleSignals();
    for (;;) {


    	 FSM_signals();
    	//PIT0_Flag = FALSE;

    	//while(FALSE == PIT0_Flag);



    }

    return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
