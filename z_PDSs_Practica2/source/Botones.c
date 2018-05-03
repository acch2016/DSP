/*
 * Botones.c
 *
 *  Created on: 15/03/2017
 *      Author: Andrea
 */

#include "Botones.h"


static float signalAmplitudScaler = 1.0;
static float h1AmplitudScaler = 1.0;
static float h2AmplitudScaler = 1.0;

static uint16_t x[7] = {0, 0, 0, 0, 0, 0, 0};
static float h1[7] = {0.07840464525404556, 0.17707825519483075,	0.22014353249171387, 0.2759015644497544, 0.22014353249171387, 0.17707825519483075, 0.07840464525404556};
static float h2[7] = {-0.08857280384687653,	-0.20001387909943527, -0.13289448474069163,	0.7755518089951376, -0.13289448474069163, -0.20001387909943527, -0.08857280384687653};

void Buttons_Config(){
	CLOCK_EnableClock(kCLOCK_PortC);
	PORT_SetPinMux(PORTC, PIN0, kPORT_MuxAsGpio);          // PORTC0 como GPIO
	PORT_SetPinMux(PORTC, PIN1, kPORT_MuxAsGpio);          // PORTC1 como GPIO
	PORT_SetPinMux(PORTC, PIN2, kPORT_MuxAsGpio);          // PORTC2 como GPIO
	PORT_SetPinMux(PORTC, PIN3, kPORT_MuxAsGpio);          // PORTC3 como GPIO
	PORT_SetPinMux(PORTC, PIN4, kPORT_MuxAsGpio);          // PORTC4 como GPIO
	PORT_SetPinMux(PORTC, PIN5, kPORT_MuxAsGpio);          // PORTC5 como GPIO
	PORT_SetPinMux(PORTC, PIN7, kPORT_MuxAsGpio);          // PORTC6 como GPIO
	PORT_SetPinMux(PORTC, PIN8, kPORT_MuxAsGpio);          // PORTC7 como GPIO

	gpio_pin_config_t bt_config = {								//Declarando como entradas
	   kGPIO_DigitalInput, 0,
	};

	PORT_SetPinInterruptConfig(PORTC, PIN0, kPORT_InterruptFallingEdge);	//Interrupción en flanco de bajada
	PORT_SetPinInterruptConfig(PORTC, PIN1, kPORT_InterruptFallingEdge);
	PORT_SetPinInterruptConfig(PORTC, PIN2, kPORT_InterruptFallingEdge);
	PORT_SetPinInterruptConfig(PORTC, PIN3, kPORT_InterruptFallingEdge);
	PORT_SetPinInterruptConfig(PORTC, PIN4, kPORT_InterruptFallingEdge);
	PORT_SetPinInterruptConfig(PORTC, PIN5, kPORT_InterruptFallingEdge);
	PORT_SetPinInterruptConfig(PORTC, PIN7, kPORT_InterruptFallingEdge);
	PORT_SetPinInterruptConfig(PORTC, PIN8, kPORT_InterruptFallingEdge);

	GPIO_PinInit(GPIOC, PIN0, &bt_config);

	NVIC_SetPriority(PORTC_IRQn, 5);
	NVIC_EnableIRQ(PORTC_IRQn);
}

void setFlag_ButtonPressed(){
	Flag_ButtonPressed = true;
}

void clearFlag_ButtonPressed(){
	Flag_ButtonPressed = false;
}

bool getFlag_ButtonPressed(){
	return Flag_ButtonPressed;
}

void menu_ButtonPressed(uint8_t buttonPressed){
	switch (buttonPressed){
		case 0:
			changeSamplingFrequency(0);				//Disminuir frecuencia de muestreo
			break;
		case 1:
			changeSamplingFrequency(1);				//Aumentar frequencia de muestreo
			break;
		case 2:
			changeSignalAmplitud(0);						//Disminuir amplitud de la señal
			break;
		case 3:
			changeSignalAmplitud(1);						//Aumentar amplitud de la señal
			break;
		case 4:
			change_h1Scaler(0);
			break;
		case 5:
			change_h1Scaler(1);
			break;
		case 6:
			break;
		case 7:
			change_h2Scaler(0);
			break;
		case 8:
			change_h2Scaler(1);
			break;
		default:
			break;
	}
}

void changeSamplingFrequency(bool changeSamplingFrequency){
	if(0 == changeSamplingFrequency){				//Disminuir frequencia de muestreo
		if(10000 < get_SamplingFrequency()){
			set_SamplingFrequency(get_SamplingFrequency() - 5000);
		}
	}else{											//Aumentar frequencia de muestreo
		if(60000 > get_SamplingFrequency()){
			set_SamplingFrequency(get_SamplingFrequency() + 5000);
		}
	}
	PRINTF("La frecuencia de muestreo es de %d Hz\n\r", get_SamplingFrequency());
}


void changeSignalAmplitud(bool changeAmplitud){
	if(0 == changeAmplitud){						//Disminuir amplitud de la señal
		if(0 < signalAmplitudScaler){
			set_SignalAmplitudScaler(signalAmplitudScaler - 0.2);
		}
	}else{											//Disminuir amplitud de la señal
		if(2 > signalAmplitudScaler){
			set_SignalAmplitudScaler(signalAmplitudScaler + 0.2);
		}
	}
	PRINTF("La amplitud de la señal se escalo a %d . %d \n\r", (uint8_t)get_SignalAmplitudScaler(), (uint8_t)((get_SignalAmplitudScaler()-(uint8_t)get_SignalAmplitudScaler())*100));
}

void change_h1Scaler(bool change_h1Scaler){
	if(0 == change_h1Scaler){						//Disminuir amplitud de la señal
		if(0 < h1AmplitudScaler){
			set_h1Scaler(h1AmplitudScaler - 0.2);
		}
	}else{											//Disminuir amplitud de la señal
		if(1 > h1AmplitudScaler){
			set_h1Scaler(h1AmplitudScaler + 0.2);
		}
	}
	PRINTF("El filtro h1 se escalo a %d . %d \n\r", (uint8_t)get_h1Scaler(), (uint8_t)((get_h1Scaler()-(uint8_t)get_h1Scaler())*100));
}

void change_h2Scaler(bool change_h2Scaler){
	if(0 == change_h2Scaler){						//Disminuir amplitud de la señal
		if(0 < h2AmplitudScaler){
			set_h2Scaler(h2AmplitudScaler - 0.2);
		}
	}else{											//Disminuir amplitud de la señal
		if(1 > h2AmplitudScaler){
			set_h2Scaler(h2AmplitudScaler + 0.2);
		}
	}
	PRINTF("El filtro h2 se escalo a %d . %d \n\r", (uint8_t)get_h2Scaler(), (uint8_t)((get_h2Scaler()-(uint8_t)get_h2Scaler())*100));
}

float get_SignalOutput(uint16_t signalInput){
	set_NewSignalInput(signalInput - 2000);				//-2047 para quitar el offset
	return (((get_SignalAmplitudScaler())*(get_h1Scaler() * convolution_h1() + get_h2Scaler() * convolution_h2())) + 2000);		//+2047 para añadir el offset
	//return signalInput;

}

void set_NewSignalInput(uint16_t signalInput){

	x[0] = x[1];
	x[1] = x[2];
	x[2] = x[3];
	x[3] = x[4];
	x[4] = x[5];
	x[5] = x[6];
	x[6] = signalInput;

}

float convolution_h1(){
	static uint8_t i;
	static float sum;

	sum = 0;
	for(i = 0; i < 7; i++){
		sum = sum + h1[i] * x[6 - i];
	}
	return sum;
}

float convolution_h2(){
	static uint8_t i;
	static float sum;

	sum = 0;
	for(i = 0; i < 7; i++){
		sum = sum + h2[i] * x[6 - i];
	}
	return sum;
}

//------------------------------------------------Setters & Getters------------------------------------------------
float get_SignalAmplitudScaler(){
	return signalAmplitudScaler;
}

void set_SignalAmplitudScaler(float newAmplitudScaler){
	signalAmplitudScaler = newAmplitudScaler;
}

float get_h1Scaler(){
	return h1AmplitudScaler;
}

void set_h1Scaler(float new_h1Scaler){
	h1AmplitudScaler = new_h1Scaler;
}

float get_h2Scaler(){
	return h2AmplitudScaler;
}

void set_h2Scaler(float new_h2Scaler){
	h2AmplitudScaler = new_h2Scaler;
}

