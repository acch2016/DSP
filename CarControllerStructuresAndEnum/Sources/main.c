/**
	\file
	\brief
		This proyect shows how to build a state machine using a struct and an enum type.
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	13/09/2015
 */
#include "MK64F12.h"
#include "GPIO.h"
#include "GlobalFunctions.h"

typedef enum {
	STOP,
	RUN,
	WAIT,
	FAST,
}StateDefinitionType;



typedef struct
{
	uint32 out;
	uint16 wait;
	uint8 next[4];
}StateType;

const StateType FineStateMachineMoore[4]=
		{
			{0x0,40000,{STOP, RUN,STOP,STOP}},
			{0x1,40000,{FAST,  RUN,WAIT,RUN}},
			{0x3,40000,{FAST, RUN,STOP,WAIT}},
			{0x07,40000,{FAST, RUN,STOP,FAST}}
		};

int main(void)
{
	StateDefinitionType currentState = STOP;	
	uint32 output=0,inputPortA=0, inputPortC=0, totalInput = 0;
	GPIO_pinControlRegisterType pinControlRegister = GPIO_MUX1|GPIO_PE|GPIO_PS;
	SIM_SCGC5 |= GPIO_CLOCK_GATING_PORTD;
    SIM_SCGC5 |= GPIO_CLOCK_GATING_PORTA; 
    SIM_SCGC5 |= GPIO_CLOCK_GATING_PORTC;
    
	PORTD_PCR(BIT0)= pinControlRegister;
	PORTD_PCR(BIT1)= pinControlRegister;
	PORTD_PCR(BIT2)= pinControlRegister;
	PORTA_PCR(BIT4)= pinControlRegister;
	PORTC_PCR(BIT6)= pinControlRegister;
	
	GPIOB_PCOR = 0x07;
	
	GPIOD_PDDR = 0x07;
	GPIOA_PDDR &= ~(BIT4);
	GPIOC_PDDR &= ~(BIT6);
	delay(3000);
	
	for(;;) {	
		output = FineStateMachineMoore[currentState].out;
		GPIOD_PDOR = output;
		delay(FineStateMachineMoore[currentState].wait);
		inputPortA = GPIOA_PDIR;
		inputPortA &=(0x10);
		inputPortC = GPIOC_PDIR;
		inputPortC &=(0x40);
		inputPortC = inputPortC >> 6;
		inputPortA = inputPortA >> 3;
		totalInput = inputPortA|inputPortC;
		currentState = FineStateMachineMoore[currentState].next[totalInput];	
	}// end for
	
}// end main
