/**
	\file 
	\brief 
		This is a starter file to implement a function able to produce an accurate delay
		using the PIT module. 

	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	7/09/2014
 */


//#include "derivative.h" /* include peripheral declarations */
#include "MK64F12.h"
#include "PIT.h"
#include "NVIC.h"
#include "GPIO.h"
#define SYSTEM_CLOCK 21000000
#define DELAY 0.25

extern uint8 PIT0_Flag;

int main(void)
{
	GPIO_pinControlRegisterType pinControlRegisterPORTD = GPIO_MUX1;
	GPIO_clockGating(PORTD);
	GPIO_pinControlRegister(PORTD,BIT0,&pinControlRegisterPORTD);
	GPIO_dataDirectionPIN(PORTD,GPIO_OUTPUT,BIT0);
	GPIO_setPIN(PORTD,BIT0);
	NVIC_EnableInterruptAndPriotity(PIT_CH0_INTR, PRIORITY_10);
	EnableInterrupts;
	
	for(;;) {	   

	   		GPIO_tooglePIN(PORTD,BIT0);
	   	 	PIT0_Flag = FALSE;
	   	 	PIT_delay(PIT_0,SYSTEM_CLOCK,DELAY);
	   	 	while(FALSE == PIT0_Flag);

	   		GPIO_tooglePIN(PORTD,BIT0);
	   		PIT0_Flag = FALSE;
	   		PIT_delay(PIT_0,SYSTEM_CLOCK,DELAY);
	   		while(FALSE == PIT0_Flag);
	}
	
	return 0;
}
