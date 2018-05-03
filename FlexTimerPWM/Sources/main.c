/**
	\file 
	\brief 
		This project shows how to configure FlexTimer in PWM mode. 
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	7/09/2014
	\todo
	    Add configuration structures.
 */


#include "MK64F12.h" /* include peripheral declarations */
#include "GPIO.h"
#include "FlexTimer.h"
#include "NVIC.h"



int main(void)
{
	sint16 dutyCycle=0;
	uint8 inputValueA=0,inputPortC = 0;
	GPIO_pinControlRegisterType	pinControlRegisterPORTA = GPIO_MUX1|GPIO_PE|GPIO_PS;
	GPIO_pinControlRegisterType	pinControlRegisterPORTC6 = GPIO_MUX1|GPIO_PE|GPIO_PS;
	/**Clock gating for port A and C*/		
    SIM_SCGC5 |= GPIO_CLOCK_GATING_PORTA|GPIO_CLOCK_GATING_PORTC; 
   	PORTC_PCR1   = PORT_PCR_MUX(0x4); //mascara en donde solo te preocupas por poner el valor del mux.
	/**Pin control register configuration for GPIO*/
	PORTA_PCR(BIT4)= pinControlRegisterPORTA;
	PORTC_PCR(BIT6)= pinControlRegisterPORTC6;
	/**Pin 4 and pin 6 of port A and C, respectively as inputs*/
	GPIOA_PDDR &= ~(BIT4);
	GPIOC_PDDR &= ~(BIT6);
	/**Configuration function for FlexTimer*/
	FTM_Init();

	for(;;) {	
		/**Reading the input values for port A and C*/
		inputPortC = GPIOC_PDIR;
		inputPortC &=(0x40);
		inputPortC = inputPortC >> 6;
		inputValueA = GPIOA_PDIR;
		inputValueA &=(0x10);
		inputValueA = inputValueA >> 4;
		
		if(inputValueA ==0)
		{
			dutyCycle=dutyCycle+10;
			FTM_updateCHValue(dutyCycle);
			delay(20000);
		}
		if(inputPortC==0)
		{
			dutyCycle = dutyCycle-10;
			FTM_updateCHValue(dutyCycle);
			delay(20000);
		}
	   	
	}
	
	return 0;
}
