/**
	\file 
	\brief 
		This project shows how to configure FlexTimer in overflow mode. 
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	1/08/2015
	\todo
	    Add configuration structures.
 */

#include "MK64F12.h" /* include peripheral declarations */
#include "GPIO.h"
#include "FlexTimer.h"
#include "NVIC.h"
#define OUTPUT_PINS 0x02 /*Pin 1 as outputs*/

/**
 * Overflow frequency = (bus clock)/(Prescaler*(mod+1))
 * 
 */


int main(void)
{
	/** Variable to contain the FTM0 counter value*/
	volatile uint16 cntTimerValue=0;
	/**Pin control register configuration values*/
	GPIO_pinControlRegisterType	pinControlRegisterPORTC = GPIO_MUX1|GPIO_PE|GPIO_PS;
	/**Clock gating of port C*/	
	SIM_SCGC5 |= GPIO_CLOCK_GATING_PORTC;
	/** Configuring port C as output*/	
	GPIOC_PDDR = OUTPUT_PINS; 
	/** Configuring pin control register for C port bit1*/
	PORTC_PCR(BIT1)= pinControlRegisterPORTC;
	/**Configuration function for FlexTimer*/
	FlexTime_Init();
	/** Enabling interrupts for FlexTimer 0*/
	NVIC_enableInterruptAndPriotity(FTM0_IRQ,PRIORITY_9);

	
	EnableInterrupts;/** Enabling Global interrupts with PRIMASK bit*/

	for(;;) {	
		cntTimerValue = FTM0_CNT;
	}
	
	return 0;
}
