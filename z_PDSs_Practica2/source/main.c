/*
 * Copyright (c) 2013 - 2016, Freescale Semiconductor, Inc.
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

/**
 * This is template for main module created by New Kinetis SDK 2.x Project Wizard. Enjoy!
 **/

#include "Botones.h"


float valorADC = 0;
uint16_t pinFlag;
uint8_t buttonPressed;
uint16_t i;

 //uint8 PIT0_Flag=FALSE;
extern volatile bool pitIsrFlag;

void delay(uint16_t repetitions);

/**CONFIGURACIÓN DEL ADC*/
const ADC_ConfigType ADC_Config={
		ADC_0,
		BITMODE_12_13,
		DADP1,
		SAMPLES_32,
		AVERAGE_ENABLE,
		INTERRUPT_ENABLE
};

void PORTC_IRQHandler(void)
{
	buttonPressed = 0;
	setFlag_ButtonPressed();

	pinFlag = GPIO_GetPinsInterruptFlags(GPIOC);
	while(pinFlag != 1){
		pinFlag = pinFlag >> 1;
		buttonPressed++;
	}
	delay(25000);

	GPIO_ClearPinsInterruptFlags(GPIOC, 1U << buttonPressed);

}

int main(void) {
	/* Init board hardware. */
	BOARD_InitPins();
	BOARD_BootClockRUN();
	BOARD_InitDebugConsole();
	Buttons_Config();

	/* Add your code here */
	ADC_init(&ADC_Config);
	DAC_Init();
	PIT_init();

	for (;;) { /* Infinite loop to avoid leaving the main function */

		if (true == pitIsrFlag) {
			valorADC = ADC_read(ADC_Config.ADC_Channel);
			//DAC_DataRegister(0);
			DAC_DataRegister(get_SignalOutput(valorADC));
			pitIsrFlag = false;
		}
		if(getFlag_ButtonPressed()){
				  menu_ButtonPressed(buttonPressed);
				  clearFlag_ButtonPressed();
		}
	}
}

void delay(uint16_t repetitions){
	for(i = 0; i < repetitions; i++){

	}
}



