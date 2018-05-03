/**
	\file
	\brief
		This proyect shows how to build a state machine using a structure and a pointer to fucntions.
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
	void(*fptrPort)(uint32);
	uint16 wait;
	void (*fptrDelay)(uint16);
	uint8 next[2];
}StateType;

const StateType FSMMoore[2]=
		{
				{0x00200000,GPIO_writePORT,65000,delay,{ODD,EVEN}}, /**Even*/
				{0         ,GPIO_writePORT,65000,delay,{EVEN,ODD}}  /**Odd*/
		};

int main(void)
{
	uint8 currentState = EVEN;	
	uint32 output=0,input=0;
	uint16 delayValue = 0;
	void(*fptr[2])(GPIO_portNameType , uint8 );
	GPIO_pinControlRegisterType pinControlRegister = GPIO_MUX1|GPIO_PE|GPIO_PS;
	
	
	SIM_SCGC5 |= GPIO_CLOCK_GATING_PORTB;
    SIM_SCGC5 |= GPIO_CLOCK_GATING_PORTC;  
	PORTB_PCR(BIT21)= pinControlRegister;
	GPIOB_PSOR = 0x00200000;
	GPIOB_PDDR = 0x00200000;
	PORTC_PCR(6)= pinControlRegister;
	GPIOC_PDDR &= ~(0x40);
	delay(3000);
	
	for(;;) {	
		output = FSMMoore[currentState].out;
		FSMMoore[currentState].fptrPort(output);
		delayValue = FSMMoore[currentState].wait;
		FSMMoore[currentState].fptrDelay(delayValue);
		input = GPIOC_PDIR;
		input &=(0x40);
		input = input?1:0;
		currentState = FSMMoore[currentState].next[input];	
	}// end for
	
}// end main
