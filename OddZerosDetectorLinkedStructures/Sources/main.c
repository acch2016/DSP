/**
	\file
	\brief
		This proyect shows how to build a state machine using a linked structure.
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	13/09/2015
 */
#include "MK64F12.h"
#include "GPIO.h"
#include "GlobalFunctions.h"

//Este codigo es mas eficiente pero es dificil de ver
#define EVEN &FSMMoore[0]
#define ODD  &FSMMoore[1]

typedef const struct State
{
	uint32 out;
	uint16 wait;
	const struct State* next[2];
} StateType;

const StateType FSMMoore[2]=
		{
			{0x00200000,65000,{ODD,EVEN}},/**Even son direcciones*/
			{0         ,65000,{EVEN,ODD}} /**Odd*/
		};

int main(void)
{
	StateType* currentState = EVEN;	
	uint32 output=0;
	uint8 input=0;
	GPIO_pinControlRegisterType pinControlRegister = GPIO_MUX1;
	SIM_SCGC5 |= GPIO_CLOCK_GATING_PORTB;
    SIM_SCGC5 |= GPIO_CLOCK_GATING_PORTC;  
	PORTB_PCR(BIT21)= pinControlRegister;
	GPIOB_PSOR = 0x00200000;
	GPIOB_PDDR = 0x00200000;
	PORTC_PCR(6)= pinControlRegister;
	GPIOC_PDDR &= ~(0x40);
	delay(3000);
	
	for(;;) {	
		output = currentState->out;
		GPIO_writePORT(output);
		delay(currentState->wait);
		input = GPIOC_PDIR;
		input &=(0x40);
		input = input?1:0;
		currentState = currentState->next[input];	
	}// end for
	
}// end main
