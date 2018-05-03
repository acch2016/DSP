/*
 * FUNC.c
 *
 *  Created on: 17/9/2016
 *      Author: alejandrocanale
 */

#include "DataTypeDefinitions.h"
#include "MK64F12.h"
#include "DAC.h"
#include "FUNC.h"
#include "GPIO.h"
#include "NVIC.h"
#include "PIT.h"
#define CIEN_VALORES 100
#define SIGNAL_LED_1 24
#define SIGNAL_LED_2 25
#define SWITCH_3 4


#define SQUARE   &FineStateMachineMoore[0]
#define	SINE     &FineStateMachineMoore[1]
#define TRIANGLE &FineStateMachineMoore[2]
#define ZERO     &FineStateMachineMoore[3]



typedef const struct State
{

	void (*ftprSig)();
	const struct State* next[2];
}StateType;


//void(*fptrSig[4])(void)={square_1,sine_2,triangle_3,zero_4};



const StateType FineStateMachineMoore[4]=
{
		{square_1,  {SQUARE,  SINE}},
		{sine_2,    {SINE,    TRIANGLE}},
		{triangle_3,{TRIANGLE,ZERO}},
		{zero_4,    {ZERO,    SQUARE}}
};


StateType* currentState = ZERO;

GPIO_pinControlRegisterType pinControlRegister = GPIO_MUX1;
GPIO_pinControlRegisterType pinControlRegisterSwitch = GPIO_MUX1|GPIO_PE|GPIO_PS|INTR_FALLING_EDGE;

uint32 output=0,input=0;
uint8 currentState_flag=0;


void setModuleSignals() {
	GPIO_clockGating(GPIOE);
	GPIO_clockGating(GPIOA);//clock gating of switch2

	//set as GPIO
	GPIO_pinControlRegister(GPIOE, SIGNAL_LED_1, &pinControlRegister);
	GPIO_pinControlRegister(GPIOE, SIGNAL_LED_2, &pinControlRegister);
	GPIO_pinControlRegister(GPIOA, SWITCH_3, &pinControlRegisterSwitch);

	//SAFE value
	GPIO_clearPIN(GPIOE, SIGNAL_LED_1); // LED 1(PTE24) is OFF
	GPIO_clearPIN(GPIOE, SIGNAL_LED_2); // LED 2(PTE25) is OFF
	GPIO_clearPIN(GPIOA, SWITCH_3); // SWITCH_3(PTE26) is OFF

	//Peripherals as outputs
	GPIO_dataDirectionPIN(GPIOE, GPIO_OUTPUT, SIGNAL_LED_1);
	GPIO_dataDirectionPIN(GPIOE, GPIO_OUTPUT, SIGNAL_LED_2);
	//Peripherals as INPUTS
	GPIO_dataDirectionPIN(GPIOA, GPIO_INPUT, SWITCH_3);

}

void FSM_signals() {

	currentState_flag = 0;

	currentState->ftprSig();

	//(*fptrSig[currentState])();

	input = readFlag_PORTA();

	if (TRUE == input) {
		currentState_flag++;
		clearFlag_PORTA();
	}

	currentState = currentState->next[currentState_flag];
}

void square_1(){

	GPIO_setPIN(GPIOE, SIGNAL_LED_1);// LED 1(PTB18) is ON
	GPIO_clearPIN(GPIOE, SIGNAL_LED_2);// LED 2(PTB19) is OFF

   square();
}
void sine_2(){

	GPIO_clearPIN(GPIOE, SIGNAL_LED_1);// LED 1(PTB18) is OFF
	GPIO_setPIN(GPIOE, SIGNAL_LED_2);// LED 2(PTB19) is ON

	sine();
}

void triangle_3(){
	GPIO_clearPIN(GPIOE, SIGNAL_LED_1);// LED 1(PTB18) is OFF
	GPIO_clearPIN(GPIOE, SIGNAL_LED_2);// LED 2(PTB19) is OFF
    tri();
}

void zero_4(){

	GPIO_setPIN(GPIOE, SIGNAL_LED_1);// LED 1(PTB18) is ON
	GPIO_setPIN(GPIOE, SIGNAL_LED_2);// LED 2(PTB19) is ON
	PIT_Disable(PIT_0);

}


