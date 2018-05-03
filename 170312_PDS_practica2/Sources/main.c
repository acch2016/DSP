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
#include "MCG.h"
#include "ADC.h"
#include "DAC.h"
#include "stdio.h"
#include "PIT.h"

#define CLK_FREQ_HZ 50000000  /* CLKIN0 frequency */
#define SLOW_IRC_FREQ 32768	/*This is the approximate value for the slow irc*/
#define FAST_IRC_FREQ 4000000 /*This is the approximate value for the fast irc*/
#define EXTERNAL_CLOCK 0 /*It defines an external clock*/
#define PLL_ENABLE 1 /**PLL is enabled*/
#define PLL_DISABLE 0 /**PLL is disabled*/
#define CRYSTAL_OSC 1  /*It defines an crystal oscillator*/
#define LOW_POWER 0     /* Set the oscillator for low power mode */
#define SLOW_IRC 0 		/* Set the slow IRC */
#define CLK0_TYPE 0     /* Crystal or canned oscillator clock input */
#define PLL0_PRDIV 25    /* PLL predivider value */
#define PLL0_VDIV 30    /* PLL multiplier value*/

/** Macros for debugging*/
#define DEBUG
float valorADC = 0;

extern uint8 PIT0_Flag;

	/**CONFIGURACIÓN DEL ADC*/
	const ADC_ConfigType ADC_Config={
		ADC_0,
		BITMODE_12_13,
		DADP1,
		SAMPLES_32,
		AVERAGE_ENABLE,
		INTERRUPT_ENABLE
	};

int main(void)
{

    /* Write your code here */
	int mcg_clk_hz;
	unsigned char modeMCG = 0;

	mcg_clk_hz = fei_fbi(SLOW_IRC_FREQ, SLOW_IRC); //64 Hz ----> 32768
	mcg_clk_hz = fbi_fbe(CLK_FREQ_HZ, LOW_POWER, EXTERNAL_CLOCK); //97.656KHz ----> 50MHz
	mcg_clk_hz = fbe_pbe(CLK_FREQ_HZ, PLL0_PRDIV, PLL0_VDIV); //97.656KHz --------> 50MHz
	mcg_clk_hz = pbe_pee(CLK_FREQ_HZ);

	modeMCG = what_mcg_mode();
#ifdef DEBUG
	printf("\nMCG mode =  %d\n",modeMCG);
	printf("Clock Rate =  %d MHz\n",mcg_clk_hz);
#endif

	/** Configuration for the output compare mode of the FlexTimer 0*/
	    SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
	  	SIM_SCGC6 |= SIM_SCGC6_FTM0_MASK;
		PORTC_PCR1   = PORT_PCR_MUX(0x4);

		FTM0_MODE |= FTM_MODE_WPDIS_MASK;
		FTM0_MODE &= ~FTM_MODE_FTMEN_MASK;
		FTM0_CONF |= FTM_CONF_BDMMODE(3);

		FTM0_CNT = 0x0;
		FTM0_COMBINE = 0;
		FTM0_MOD = 0x1;
		FTM0_CNTIN = 0;
		FTM0_COMBINE = 0;
		FTM0_SC = 0;
		FTM0_C0SC = FTM_CnSC_MSA_MASK| FTM_CnSC_ELSA_MASK;
		FTM0_C0V = 0x1;
		FTM0_SC |= FTM_SC_PS(7)|FTM_SC_CLKS(1);




	ADC_init(&ADC_Config);
	DAC_Init();
	PIT_init();



	PIT_delay(PIT_0,SYSTEM_CLOCK,DELAY);


    /* This for loop should be replaced. By default this loop allows a single stepping. */
	for (;;) {


		if (TRUE == PIT0_Flag) {

			valorADC = ADC_read(ADC_Config.ADC_Channel);
			DAC_DataRegister(valorADC);
			PIT_delay(PIT_0,SYSTEM_CLOCK,DELAY);
			PIT0_Flag=FALSE;



		}
	}
    /* Never leave main */
    return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
