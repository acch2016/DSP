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
#include "DataTypeDefinitions.h"
#include "GPIO.h"


void GPIO_clockGating(GPIO_portNameType portName);

void GPIO_pinControlRegister(GPIO_portNameType portName,uint8 pin,const GPIO_pinControlRegisterType*  pinControlRegister);

void GPIO_writePORT(uint32 data )
{
	GPIOB_PDOR = data;
}
uint32 GPIO_readPORT(GPIO_portNameType portName);
uint8 GPIO_readPIN(GPIO_portNameType portName, uint8 pin);
void GPIO_setPIN(GPIO_portNameType portName, uint8 pin);
void GPIO_clearPIN(GPIO_portNameType portName, uint8 pin);
void GPIO_tooglePIN(GPIO_portNameType portName, uint8 pin);
void GPIO_dataDirectionPORT(GPIO_portNameType portName ,uint32 direction);
void GPIO_dataDirectionPIN(GPIO_portNameType portName, uint8 State, uint8 pin);




