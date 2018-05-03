/**
	\file
	\brief
		This proyect shows how to build a state machine using a case and an enum type.
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	13/09/2015
 */
#include "MK64F12.h"
#include "GPIO.h"
#include "GlobalFunctions.h"

#define ZERO  0
#define ONE   1
#define TWO   2
#define THREE 3

#define OUTPUT_IN_STOP 0
#define OUTPUT_IN_RUN  1
#define OUTPUT_IN_WAIT 2
#define OUTPUT_IN_FAST 3

typedef enum {
	STOP,
	RUN,
	WAIT,
	FAST,
}StateDefinitionType;

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
		inputPortA = GPIOA_PDIR;
		inputPortA &=(0x10);
		inputPortC = GPIOC_PDIR;
		inputPortC &=(0x40);
		inputPortC = inputPortC >> 6;
		inputPortA = inputPortA >> 3;
		totalInput = inputPortA|inputPortC;


		switch (currentState) {
			case STOP:
				if(THREE == totalInput)
				{
					currentState = STOP;
					GPIO_writePORT(OUTPUT_IN_STOP);
				}
				else if(ONE == totalInput)
				{
					currentState = RUN;				
				}
				
				break;
			case RUN:
				if(THREE == totalInput)
				{
					currentState = RUN;
					GPIO_writePORT(OUTPUT_IN_RUN);					
				}
				if(TWO == totalInput)
				{
					currentState = WAIT;	
				}	
				if(ZERO == totalInput)
				{
					currentState = FAST;	
				}
				break;
			case WAIT:
				if(THREE == totalInput)
				{
					currentState = WAIT;
					GPIO_writePORT(OUTPUT_IN_WAIT);						
				}
				else if(ONE == totalInput)
				{
					currentState = RUN;
				}
				else if(ZERO == totalInput)
				{
					currentState = FAST;
				}
				else if(TWO == totalInput)
				{
					currentState = STOP;
				}
				break;
			case FAST:
				switch(totalInput)
				{
				case ZERO:
					currentState = FAST;
					break;
				case ONE:
					currentState = RUN;
					break;
				case TWO:
					currentState = STOP;
					break;
				case THREE:
					currentState = FAST;
					GPIO_writePORT(OUTPUT_IN_FAST);	
					break;
				default:
					currentState = FAST;
					GPIO_writePORT(OUTPUT_IN_FAST);	
					break;
					
				}
				break;
			default:
				currentState = STOP;
				GPIO_writePORT(OUTPUT_IN_STOP);
				break;
		}
	
	}// end for
	
}// end main
