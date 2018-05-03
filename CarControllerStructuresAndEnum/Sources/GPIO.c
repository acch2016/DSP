/**
	\file 
	\brief 
		This is the source file for the GPIO device driver for Kinetis K64. 
		It contains all the implementation for configuration functions and runtime functions. 
		i.e., this is the application programming interface (API) for the GPIO peripheral. 
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	7/09/2014
	\todo
	    Interrupts are not implemented in this API.
 */
#include "MK64F12.h"
#include "GPIO.h"


void GPIO_clockGating(GPIO_portNameType portName)
{
	switch(portName)/** Selecting the GPIO for clock enabling*/
			{
				case GPIOA: /** GPIO A is selected*/
					SIM_SCGC5 |= GPIO_CLOCK_GATING_PORTA; /** Bit 9 of is SIM_SCGC5 set*/
					break;
				case GPIOB: /** GPIO B is selected*/
					SIM_SCGC5 |= GPIO_CLOCK_GATING_PORTB; /** Bit 10 of is SIM_SCGC5 set*/
					break;
				case GPIOC: /** GPIO C is selected*/
					SIM_SCGC5 |= GPIO_CLOCK_GATING_PORTC; /** Bit 11 of is SIM_SCGC5 set*/
					break;
				case GPIOD: /** GPIO D is selected*/
					SIM_SCGC5 |= GPIO_CLOCK_GATING_PORTD; /** Bit 12 of is SIM_SCGC5 set*/
					break; 
				default: /** GPIO E is selected*/
					SIM_SCGC5 |= GPIO_CLOCK_GATING_PORTE; /** Bit 13 of is SIM_SCGC5 set*/
			}// end switch
}// end function

void GPIO_pinControlRegister(GPIO_portNameType portName,uint8 pin,const GPIO_pinControlRegisterType*  pinControlRegister)
{

}

void GPIO_writePORT(GPIO_portNameType portName, uint32 Data );
uint32 GPIO_readPORT(GPIO_portNameType portName);
uint8 GPIO_readPIN(GPIO_portNameType portName, uint8 pin);
void GPIO_setPIN(GPIO_portNameType portName, uint8 pin);
void GPIO_clearPIN(GPIO_portNameType portName, uint8 pin);
void GPIO_tooglePIN(GPIO_portNameType portName, uint8 pin);
void GPIO_dataDirectionPORT(GPIO_portNameType portName ,uint32 direction);
void GPIO_dataDirectionPIN(GPIO_portNameType portName, uint8 State, uint8 pin);




