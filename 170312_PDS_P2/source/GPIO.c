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


uint8 FlagPortC;
uint8 FlagPortA;

void PORTC_IRQHandler()
{
	FlagPortC = TRUE;
	GPIO_clearInterrupt(GPIO_C);

}


void PORTA_IRQHandler()
{
	while(1);

}


void GPIO_clearInterrupt(GPIO_portNameType portName)
{
	switch(portName)/** Selecting the GPIO for clock enabling*/
	{
		case GPIO_A: /** GPIO A is selected*/
			PORTA->ISFR=0xFFFFFFFF;
			break;
		case GPIO_B: /** GPIO B is selected*/
			PORTB->ISFR=0xFFFFFFFF;
			break;
		case GPIO_C: /** GPIO C is selected*/
			PORTC->ISFR = 0xFFFFFFFF;
			break;
		case GPIO_D: /** GPIO D is selected*/
			PORTD->ISFR=0xFFFFFFFF;
			break;
		default: /** GPIO E is selected*/
			PORTE->ISFR=0xFFFFFFFF;
			break;
	}// end switch
}
uint8 GPIO_clockGating(GPIO_portNameType portName)
{
	switch(portName)/** Selecting the GPIO for clock enabling*/
			{
				case GPIO_A: /** GPIO A is selected*/
					SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTA; /** Bit 9 of SIM_SCGC5 is  set*/
					break;
				case GPIO_B: /** GPIO B is selected*/
					SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTB; /** Bit 10 of SIM_SCGC5 is set*/
					break;
				case GPIO_C: /** GPIO C is selected*/
					SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTC; /** Bit 11 of SIM_SCGC5 is set*/
					break;
				case GPIO_D: /** GPIO D is selected*/
					SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTD; /** Bit 12 of SIM_SCGC5 is set*/
					break;
				case GPIO_E: /** GPIO E is selected*/
					SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTE; /** Bit 13 of SIM_SCGC5 is set*/
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
		case GPIO_A:/** GPIO A is selected*/
			PORTA->PCR[0]= *pinControlRegister;
			break;
		case GPIO_B:/** GPIO B is selected*/
			PORTA->PCR[1]= *pinControlRegister;
			break;
		case GPIO_C:/** GPIO C is selected*/
			PORTA->PCR[2]= *pinControlRegister;
			break;
		case GPIO_D:/** GPIO D is selected*/
			PORTA->PCR[3]= *pinControlRegister;
			break;
		case GPIO_E: /** GPIO E is selected*/
			PORTA->PCR[4]= *pinControlRegister;
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
	uint32 control = 0x01;
	switch(portName)
					{
					case GPIO_A:/** GPIO A is selected*/
						GPIOA->PDOR |= control << pin;
						break;
					case GPIO_B:/** GPIO B is selected*/
						GPIOB->PDOR |= control << pin;
						break;
					case GPIO_C:/** GPIO C is selected*/
						GPIOC->PDOR |= control << pin;
						break;
					case GPIO_D:/** GPIO D is selected*/
						GPIOD->PDOR |= control << pin;
						break;
					case GPIO_E: /** GPIO E is selected*/
						GPIOE->PDOR |= control << pin;
					default:/**If doesn't exist the option*/
					break;
					}

}
void GPIO_clearPIN(GPIO_portNameType portName, uint8 pin);
void GPIO_tooglePIN(GPIO_portNameType portName, uint8 pin){
	uint32 control = 0x01;
	switch(portName)
						{
						case GPIO_A:/** GPIO A is selected*/
							GPIOA->PTOR |= control << pin;
							break;
						case GPIO_B:/** GPIO B is selected*/
							GPIOB->PTOR |= control << pin;
							break;
						case GPIO_C:/** GPIO C is selected*/
							GPIOC->PTOR |= control << pin;
							break;
						case GPIO_D:/** GPIO D is selected*/
							GPIOD->PTOR |= control << pin;
							break;
						case GPIO_E: /** GPIO E is selected*/
							GPIOE->PTOR |= control << pin;
						default:/**If doesn't exist the option*/
						break;
						}
}
void GPIO_dataDirectionPORT(GPIO_portNameType portName ,uint32 direction){

}
void GPIO_dataDirectionPIN(GPIO_portNameType portName, uint8 State, uint8 pin){
	uint32 control = 0x01;
		if(GPIO_OUTPUT == State){
		switch(portName)
				{
				case GPIO_A:/** GPIO A is selected*/
					GPIOA->PDDR |= control << pin;
					break;
				case GPIO_B:/** GPIO B is selected*/
					GPIOB->PDDR |= control << pin;
					break;
				case GPIO_C:/** GPIO C is selected*/
					GPIOC->PDDR |= control << pin;
					break;
				case GPIO_D:/** GPIO D is selected*/
					GPIOD->PDDR |= control << pin;
					break;
				case GPIO_E: /** GPIO E is selected*/
					GPIOE->PDDR |= control << pin;
				default:/**If doesn't exist the option*/
				break;
				}
		}
}




