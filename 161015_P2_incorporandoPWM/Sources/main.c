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
#include "GPIO.h"
#include "SPI.h"
#include "NVIC.h"
#include "Menu.h"
#include "FlexTimer.h"
#include "Motor.h"
#include "GlobalFunctions.h"


static int i = 0;

int main(void)
{
	Configuration_Menu();
	const SPI_ConfigType SPI_Config={SPI_DISABLE_FIFO,
								SPI_LOW_POLARITY,
								SPI_LOW_PHASE,
								SPI_MSB,
								SPI_0,
								SPI_MASTER,
								GPIO_MUX2,
								SPI_BAUD_RATE_2,
								SPI_FSIZE_8,
								{GPIOD,BIT1,BIT2}};
	const FTM_ConfigType FTM0_Config={	FTM_0,
									    FLEX_TIMER_0_CLOCK_GATING,
										FLEX_TIMER_CLKS_1 | FLEX_TIMER_PS_2,
										FLEX_TIMER_WPDIS,
										FALSE,
										FTM_CnSC_ELSA_MASK | FTM_CnSC_CHIE_MASK,
										FTM_CONF_BDMMODE(3),
										~(FTM_COMBINE_DECAPEN0_MASK | FTM_COMBINE_COMBINE0_MASK)};



	const FTM_ConfigType FTM1_Config={	FTM_1,
									    FLEX_TIMER_1_CLOCK_GATING,
										FLEX_TIMER_CLKS_1|FLEX_TIMER_PS_128,
										FLEX_TIMER_WPDIS,
										0x00FF,
										FLEX_TIMER_MSB | FLEX_TIMER_ELSB,
										FALSE,
										~(FTM_COMBINE_DECAPEN0_MASK | FTM_COMBINE_COMBINE0_MASK)};

	const FTM_ConfigType FTM2_Config={	FTM_2,
										    FLEX_TIMER_2_CLOCK_GATING,
											FLEX_TIMER_TOIE | FLEX_TIMER_CLKS_1|FLEX_TIMER_PS_128,
											FLEX_TIMER_WPDIS,
											0x0052,
											FALSE,
											FALSE,
											FALSE};
	/*! This array hold the initial picture that is shown in the LCD*/
	GPIO_pinControlRegisterType pinControlRegister = PORT_PCR_MUX(0x4);
	GPIO_clockGating(GPIOA);
	GPIO_clockGating(GPIOC);
	GPIO_pinControlRegister(GPIOC,BIT1,&pinControlRegister);
	SPI_init(&SPI_Config);
	LCDNokia_init();
	clearAllFlag();
	ADC_Configuration();
	FTM_Init(&FTM0_Config);
	FTM_Init(&FTM1_Config);
	FTM_Init(&FTM2_Config);
	FTM_updateCHValue(FTM_1, FTM0_MOD/2);
	NVIC_enableInterruptAndPriotity(FTM0_IRQ, PRIORITY_8);
	NVIC_enableInterruptAndPriotity(FTM1_IRQ, PRIORITY_8);
	NVIC_enableInterruptAndPriotity(FTM2_IRQ, PRIORITY_8);
	EnableInterrupts;
    /* Write your code here */

    /* This for loop should be replaced. By default this loop allows a single stepping. */
    for (;;) {
    	LCDNokia_clear();
    	Screen_Machine();
    	clearAllFlag();
    	MotorControler();
    	delay(65000);
    }

    return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
