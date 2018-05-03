/**
	\file 
	\brief 
		This is a starter file to implement a function able to produce an accurate delay
		using the PIT module. 

	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	7/09/2014
 */

//Librerías
#include "MK64f12.h"
#include "PIT.h"
#include "NVIC.h"
#include "GPIO.h"
#define SYSTEM_CLOCK 21000000 //Clock Frequeency
#define DELAY 0.0005 //Period


uint8 PIT0_Flag = FALSE; //Declaración de variable para puerto 0

int main(void)
{
	SIM_SCGC6 |= SIM_SCGC6_PIT_MASK; //Activa el clock Gating del PIT, bit 23 0x800000
	PIT_MCR = 0x00;//Clock for PIT timers and timerand timers continue to run in debug mode
	GPIO_pinControlRegisterType pinControlRegisterGPIOD = GPIO_MUX1;
	GPIO_clockGating(GPIOD); //Enable clock gating for port D
	GPIO_pinControlRegister(GPIOD,BIT0,&pinControlRegisterGPIOD);
	GPIO_dataDirectionPIN(GPIOD,GPIO_OUTPUT,BIT0);
	GPIO_setPIN(GPIOD,BIT0);
	NVIC_setBASEPRI_threshold(PRIORITY_9);
	NVIC_enableInterruptAndPriotity(PIT_CH0_IRQ, PRIORITY_8);
	EnableInterrupts;
	
	for(;;) {	   

				GPIO_tooglePIN(GPIOD,BIT0);
		   	 	PIT0_Flag = FALSE;
		   	 	PIT_delay(PIT_0,SYSTEM_CLOCK,DELAY);
		   	 	while(FALSE == PIT0_Flag);
		   		GPIO_tooglePIN(GPIOD,BIT0);
		   		PIT0_Flag = FALSE;
		   		PIT_delay(PIT_0,SYSTEM_CLOCK,DELAY);
		   		while(FALSE == PIT0_Flag);
	}
	
	return 0;
}
