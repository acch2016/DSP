/**
	\file
	\brief
		This is the source file for the GPIO device driver for Kinetis K64.
		It contains all the implementation for configuration functions and runtime functions.
		i.e., this is the application programming interface (API) for the GPIO peripheral.
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	7/09/2014
	\todo
	    Interrupts are not implemented in this API implementation.
 */
#include "MK64F12.h"
#include "GPIO.h"


void GPIO_clearInterrupt(GPIO_portNameType portName)
{
	switch(portName)/** Selecting the GPIO for clock enabling*/
	{
		case GPIOA: /** GPIO A is selected*/
			PORTA_ISFR=0xFFFFFFFF;
			break;
		case GPIOB: /** GPIO B is selected*/
			PORTB_ISFR=0xFFFFFFFF;
			break;
		case GPIOC: /** GPIO C is selected*/
			PORTC_ISFR = 0xFFFFFFFF;
			break;
		case GPIOD: /** GPIO D is selected*/
			PORTD_ISFR=0xFFFFFFFF;
			break;
		default: /** GPIO E is selected*/
			PORTE_ISFR=0xFFFFFFFF;
//			break;
//		default:
//			PORTF_ISFR=0xFFFFFFFF;
	}// end switch
}
uint8 GPIO_clockGating(GPIO_portNameType portName)
{
	switch(portName)/** Selecting the GPIO for clock enabling*/
			{
				case GPIOA: /** GPIO A is selected*/
					SIM_SCGC5 |= GPIO_CLOCK_GATING_PORTA; /** Bit 9 of SIM_SCGC5 is  set*/
					break;
				case GPIOB: /** GPIO B is selected*/
					SIM_SCGC5 |= GPIO_CLOCK_GATING_PORTB; /** Bit 10 of SIM_SCGC5 is set*/
					break;
				case GPIOC: /** GPIO C is selected*/
					SIM_SCGC5 |= GPIO_CLOCK_GATING_PORTC; /** Bit 11 of SIM_SCGC5 is set*/
					break;
				case GPIOD: /** GPIO D is selected*/
					SIM_SCGC5 |= GPIO_CLOCK_GATING_PORTD; /** Bit 12 of SIM_SCGC5 is set*/
					break;
				case GPIOE: /** GPIO E is selected*/
					SIM_SCGC5 |= GPIO_CLOCK_GATING_PORTE; /** Bit 13 of SIM_SCGC5 is set*/
					break;
				default: /**If doesn't exist the option*/
					return(FALSE);
			}// end switch
	/**Successful configuration*/
	return(TRUE);
}// end function

uint8 GPIO_pinControlRegister(GPIO_portNameType portName,uint8 pin,const GPIO_pinControlRegisterType*  pinControlRegister)
{

	switch(portName)
		{
		case GPIOA:/** GPIO A is selected*/
			PORTA_PCR(pin)= *pinControlRegister;
			break;
		case GPIOB:/** GPIO B is selected*/
			PORTB_PCR(pin)= *pinControlRegister;
			break;
		case GPIOC:/** GPIO C is selected*/
			PORTC_PCR(pin)= *pinControlRegister;
			break;
		case GPIOD:/** GPIO D is selected*/
			PORTD_PCR(pin)= *pinControlRegister;
			break;
		case GPIOE: /** GPIO E is selected*/
			PORTE_PCR(pin)= *pinControlRegister;
		default:/**If doesn't exist the option*/
			return(FALSE);
		break;
		}
	/**Successful configuration*/
	return(TRUE);
}

void GPIO_writePORT(GPIO_portNameType portName, uint32 Data );
uint32 GPIO_readPORT(GPIO_portNameType portName);
uint8 GPIO_readPIN(GPIO_portNameType portName, uint8 pin);
void GPIO_setPIN(GPIO_portNameType portName, uint8 pin){
	GPIOD_PDOR = 0x1; //Logic level for general porpouse output
}
void GPIO_clearPIN(GPIO_portNameType portName, uint8 pin);
void GPIO_tooglePIN(GPIO_portNameType portName, uint8 pin){
	GPIOD_PTOR = 0x1;//bit in PDORn is set to the inverse of its existing logic state
}
void GPIO_dataDirectionPORT(GPIO_portNameType portName ,uint32 direction);
void GPIO_dataDirectionPIN(GPIO_portNameType portName, uint8 State, uint8 pin){
	GPIOD_PDDR = 0x1; //configures pin0 as an output
}




