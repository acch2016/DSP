/**
	\file
	\brief
		This proyect shows how to build a state machine using a struct.
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	13/09/2015
 */
#include "MK64F12.h"
#include "GPIO.h"
#include "GlobalFunctions.h"


#define EVEN 0
#define ODD  1

typedef struct
{
	uint32 out;
	uint16 wait;
	uint8 next[2];
}StateType;

const StateType FineStateMachineMoore[2]=
		{
			{0x00200000,65000,{ODD,EVEN}}, /** Even*/
			{0         ,65000,{EVEN,ODD}}  /** Odd*/
		};

int main(void)
{
	uint8 currentState = EVEN;	
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
		output = FineStateMachineMoore[currentState].out;
		GPIO_writePORT(output);
		delay(FineStateMachineMoore[currentState].wait);
		input = GPIOC_PDIR;
		input &=(0x40);
		input = input?1:0;
		currentState = FineStateMachineMoore[currentState].next[input];	
	}// end for
	
}// end main
