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

uint8 FlagPortC=FALSE;
uint8 FlagPortA;

void PORTC_IRQHandler() {
	FlagPortC = TRUE;
	GPIO_clearInterrupt(GPIOC);

}

void PORTA_IRQHandler() {
	while (1)
		;

}

uint8 readFlag_PORTC(){
return 	FlagPortC;
}

void clearFlag_PORTC(){
FlagPortC=0;
}

void GPIO_clearInterrupt(GPIO_portNameType portName) {
	switch (portName)/** Selecting the GPIO for clock enabling*/
	{
	case GPIOA: /** GPIO A is selected*/
		PORTA_ISFR = 0xFFFFFFFF;
		break;
	case GPIOB: /** GPIO B is selected*/
		PORTB_ISFR = 0xFFFFFFFF;
		break;
	case GPIOC: /** GPIO C is selected*/
		PORTC_ISFR = 0xFFFFFFFF;
		break;
	case GPIOD: /** GPIO D is selected*/
		PORTD_ISFR = 0xFFFFFFFF;
		break;
	default: /** GPIO E is selected*/
		PORTE_ISFR = 0xFFFFFFFF;
		break;
	} // end switch
}
uint8 GPIO_clockGating(GPIO_portNameType portName) {
	switch (portName)/** Selecting the GPIO for clock enabling*/
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
		return (FALSE);
	} // end switch
	/**Successful configuration*/
	return (TRUE);
} // end function

uint8 GPIO_pinControlRegister(GPIO_portNameType portName, uint8 pin,
		const GPIO_pinControlRegisterType* pinControlRegister) {

	switch (portName) {
	case GPIOA:/** GPIO A is selected*/
		PORTA_PCR(pin) = *pinControlRegister;
		break;
	case GPIOB:/** GPIO B is selected*/
		PORTB_PCR(pin) = *pinControlRegister;
		break;
	case GPIOC:/** GPIO C is selected*/
		PORTC_PCR(pin) = *pinControlRegister;
		break;
	case GPIOD:/** GPIO D is selected*/
		PORTD_PCR(pin) = *pinControlRegister;
		break;
	case GPIOE: /** GPIO E is selected*/
		PORTE_PCR(pin) = *pinControlRegister;
	default:/**If doesn't exist the option*/
		return (FALSE);
		break;
	}
	/**Successful configuration*/
	return (TRUE);
}

void GPIO_writePORT(GPIO_portNameType portName, uint32 Data) {
	switch (portName) {
	case GPIOA:/** GPIO A is selected*/
		GPIOA_PDOR = Data;
		break;
	case GPIOB:/** GPIO B is selected*/
		GPIOB_PDOR = Data;
		break;
	case GPIOC:/** GPIO C is selected*/
		GPIOC_PDOR = Data;
		break;
	case GPIOD:/** GPIO D is selected*/
		GPIOD_PDOR = Data;
		break;
	case GPIOE: /** GPIO E is selected*/
		GPIOE_PDOR = Data;
	default:/**If doesn't exist the option*/
		break;
	}
}
uint32 GPIO_readPORT(GPIO_portNameType portName) {
	switch (portName) {
	case GPIOA:/** GPIO A is selected*/
		return(GPIOA_PDIR);
		break;
	case GPIOB:/** GPIO B is selected*/
		return(GPIOB_PDIR);
		break;
	case GPIOC:/** GPIO C is selected*/
		return(GPIOC_PDIR);
		break;
	case GPIOD:/** GPIO D is selected*/
		return(GPIOD_PDIR);
		break;
	case GPIOE: /** GPIO E is selected*/
		return(GPIOE_PDIR);
	default:/**If doesn't exist the option*/
		break;
	}
}

uint8 GPIO_readPIN(GPIO_portNameType portName, uint8 pin){
	uint32 control = 0x01;
	switch(portName){
	case GPIOA:/** GPIO A is selected*/
		return ((GPIOA_PDIR >> pin) & control);
		break;
	case GPIOB:/** GPIO B is selected*/
		return ((GPIOB_PDIR >> pin) & control);
		break;
	case GPIOC:/** GPIO C is selected*/
		return ((GPIOC_PDIR >> pin) & control);
		break;
	case GPIOD:/** GPIO D is selected*/
		return ((GPIOD_PDIR >> pin) & control);
		break;
	case GPIOE: /** GPIO E is selected*/
		return ((GPIOE_PDIR >> pin) & control);
		default:/**If doesn't exist the option*/
			break;
	}
}
void GPIO_setPIN(GPIO_portNameType portName, uint8 pin) {
	uint32 control = 0x01;
	switch (portName) {
	case GPIOA:/** GPIO A is selected*/
		GPIOA_PDOR |= control << pin;
		break;
	case GPIOB:/** GPIO B is selected*/
		GPIOB_PDOR |= control << pin;
		break;
	case GPIOC:/** GPIO C is selected*/
		GPIOC_PDOR |= control << pin;
		break;
	case GPIOD:/** GPIO D is selected*/
		GPIOD_PDOR |= control << pin;
		break;
	case GPIOE: /** GPIO E is selected*/
		GPIOE_PDOR |= control << pin;
	default:/**If doesn't exist the option*/
		break;
	}

}
void GPIO_clearPIN(GPIO_portNameType portName, uint8 pin) {
	uint32 control = 0x01;
	switch (portName) {
	case GPIOA:/** GPIO A is selected*/
		GPIOA_PCOR |= control << pin;
		break;
	case GPIOB:/** GPIO B is selected*/
		GPIOB_PCOR |= control << pin;
		break;
	case GPIOC:/** GPIO C is selected*/
		GPIOC_PCOR |= control << pin;
		break;
	case GPIOD:/** GPIO D is selected*/
		GPIOD_PCOR |= control << pin;
		break;
	case GPIOE: /** GPIO E is selected*/
		GPIOE_PCOR |= control << pin;
	default:/**If doesn't exist the option*/
		break;
	}
}
void GPIO_tooglePIN(GPIO_portNameType portName, uint8 pin) {
	uint32 control = 0x01;
	switch (portName) {
	case GPIOA:/** GPIO A is selected*/
		GPIOA_PTOR |= control << pin;
		break;
	case GPIOB:/** GPIO B is selected*/
		GPIOB_PTOR |= control << pin;
		break;
	case GPIOC:/** GPIO C is selected*/
		GPIOC_PTOR |= control << pin;
		break;
	case GPIOD:/** GPIO D is selected*/
		GPIOD_PTOR |= control << pin;
		break;
	case GPIOE: /** GPIO E is selected*/
		GPIOE_PTOR |= control << pin;
	default:/**If doesn't exist the option*/
		break;
	}
}
void GPIO_dataDirectionPORT(GPIO_portNameType portName, uint32 direction) {
	switch (portName) {
	case GPIOA:/** GPIO A is selected*/
		GPIOA_PDDR = direction;
		break;
	case GPIOB:/** GPIO B is selected*/
		GPIOB_PDDR = direction;
		break;
	case GPIOC:/** GPIO C is selected*/
		GPIOC_PDDR = direction;
		break;
	case GPIOD:/** GPIO D is selected*/
		GPIOD_PDDR = direction;
		break;
	case GPIOE: /** GPIO E is selected*/
		GPIOE_PDDR = direction;
	default:/**If doesn't exist the option*/
		break;
	}
}
void GPIO_dataDirectionPIN(GPIO_portNameType portName, uint8 State, uint8 pin) {
	uint32 control = 0x01;
	if (GPIO_OUTPUT == State) {
		switch (portName) {
		case GPIOA:/** GPIO A is selected*/
			GPIOA_PDDR |= control << pin;
			break;
		case GPIOB:/** GPIO B is selected*/
			GPIOB_PDDR |= control << pin;
			break;
		case GPIOC:/** GPIO C is selected*/
			GPIOC_PDDR |= control << pin;
			break;
		case GPIOD:/** GPIO D is selected*/
			GPIOD_PDDR |= control << pin;
			break;
		case GPIOE: /** GPIO E is selected*/
			GPIOE_PDDR |= control << pin;
		default:/**If doesn't exist the option*/
			break;
		}
	}
}

