/**
	\file
	\brief Este es el archivo fuente para el driver del GPIO para la Kinetis K64
				 Este contiene todas las implementaciones para las configuraciones de funciones
				 y de  funciones de tiempo real.
				 Est� es la API para el periferico GPIO.
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	7/09/2014
	\todo
	   Las interrupciones no est�n implementadas en este m�dulo
 */

/**Archivo que contiene el nombre de los registros y los tipos de datos de la k64*/
#include "MK64F12.h"
/**Header de este archivo*/
#include "GPIO.h"

/**Union que contiene todas las banderas de las interrupciones de los puertos*/
typedef union  Flags{
	uint8 AllFlags;
	struct{
		uint8 FlagPortC :1;
		uint8 FlagPortB :1;
		uint8 FlagPortA :1;
	}Flagfield;
}Flags;

/** Creaci�n de la variable de tipo de dato para las banderas*/
Flags funwithFlags;


void PORTC_IRQHandler() /**Vector de interrupci�n para el puerto C*/
{
	funwithFlags.Flagfield.FlagPortC = TRUE;	/**Se activa la bandera del puerto C*/
	GPIO_clearInterrupt(GPIOC);					/**Se limpia la interrupci�n del puerto C*/

}

void PORTA_IRQHandler() /**Vector de interrupci�n para el puerto A*/
{
	funwithFlags.Flagfield.FlagPortA = TRUE;
	GPIO_clearInterrupt(GPIOA);

}

void PORTB_IRQHandler()	/** Vector para la interrupci�n del puerto B*/
{
	funwithFlags.Flagfield.FlagPortB = TRUE;
	GPIO_clearInterrupt(GPIOB);
}

//API para banderas del generador de se�ales

uint8 readFlag_PORTA() /**Funci�n que regresa el estado del puerto A*/
{
	return 	funwithFlags.Flagfield.FlagPortA;
}

void clearFlag_PORTA() /**Funci�n que limpia la bandera del puerto A*/
{
	funwithFlags.Flagfield.FlagPortA=0;
}


//API para banderas de teclado matricial
uint8 FlagPortB_Read() /**Funci�n que regresa el estado del puerto B*/
{
	return funwithFlags.Flagfield.FlagPortB;
}

void FlagPortB_Clear()	/**Funci�n que limpia la bandera del puerto B*/
{
	funwithFlags.Flagfield.FlagPortB = FALSE;
}

//API para banderas de motor
uint8 readFlag_PORTC() /**Funci�n que regresa el estado del puerto C*/
{
	return 	funwithFlags.Flagfield.FlagPortC;
}

void clearFlag_PORTC()	/**Funci�n que limpia la bandera del puerto C*/
{
	funwithFlags.Flagfield.FlagPortC=0;
}

void GPIO_clearInterrupt(GPIO_portNameType portName) /** Funci�n para limpiar la interrupci�n de los puertos*/
{
	switch (portName)/**Selecciona el puerto del GPIO*/
	{
	case GPIOA: /** Se selecciono el puerto A, se limpia el registro de la interrupci�n*/
		PORTA_ISFR = 0xFFFFFFFF;
		break;
	case GPIOB: /** Se selecciono el puerto B, se limpia el registro de la interrupci�n*/
		PORTB_ISFR = 0xFFFFFFFF;
		break;
	case GPIOC: /** Se selecciono el puerto C, se limpia el registro de la interrupci�n*/
		PORTC_ISFR = 0xFFFFFFFF;
		break;
	case GPIOD: /** Se selecciono el puerto D, se limpia el registro de la interrupci�n*/
		PORTD_ISFR = 0xFFFFFFFF;
		break;
	default: /** Se selecciono el puerto E, se limpia el registro de la interrupci�n*/
		PORTE_ISFR = 0xFFFFFFFF;
		break;
	} // end switch
}
uint8 GPIO_clockGating(GPIO_portNameType portName) /**Funci�n para activar el reloj del puerto*/
{
	switch (portName)/** Selecciona el GPIO para activar el puerto*/
	{
	case GPIOA: /** Se selecciono el GPIOA*/
		SIM_SCGC5 |= GPIO_CLOCK_GATING_PORTA; /** Se activa el Bit 9 de SIM_SCGC5*/
		break;
	case GPIOB: /** Se selecciono el GPIOB*/
		SIM_SCGC5 |= GPIO_CLOCK_GATING_PORTB; /** Se activa el Bit 10 de SIM_SCGC5*/
		break;
	case GPIOC: /** Se selecciono el GPIOC*/
		SIM_SCGC5 |= GPIO_CLOCK_GATING_PORTC; /** Se activa el Bit 11 de SIM_SCGC5*/
		break;
	case GPIOD: /** Se selecciono el GPIOD*/
		SIM_SCGC5 |= GPIO_CLOCK_GATING_PORTD; /** Se activa el Bit 12 de SIM_SCGC5*/
		break;
	case GPIOE: /** Se selecciono el GPIOE*/
		SIM_SCGC5 |= GPIO_CLOCK_GATING_PORTE; /** Se activa el Bit 13 de SIM_SCGC5*/
		break;
	default: /**Si no existe la opci�n*/
		return (FALSE);
	} // end switch
	/**Configuraci�n exitosa*/
	return (TRUE);
} // fin de la funci�n

uint8 GPIO_pinControlRegister(GPIO_portNameType portName, uint8 pin, GPIO_pinControlRegisterType* pinControlRegister)
/**Funci�n para configurar cualquier pin del GPIO*/
{
	switch (portName) {
	case GPIOA:/** Se selecciono el GPIOA*/
		PORTA_PCR(pin) = *pinControlRegister;
		break;
	case GPIOB:/** Se selecciono el GPIOB*/
		PORTB_PCR(pin) = *pinControlRegister;
		break;
	case GPIOC:/** Se selecciono el GPIOC*/
		PORTC_PCR(pin) = *pinControlRegister;
		break;
	case GPIOD:/** Se selecciono el GPIOD*/
		PORTD_PCR(pin) = *pinControlRegister;
		break;
	case GPIOE: /** Se selecciono el GPIOE*/
		PORTE_PCR(pin) = *pinControlRegister;
	default:/**Si no existe la opci�n*/
		return (FALSE);
		break;
	}
	/**Configuraci�n exitosa*/
	return (TRUE);
}

void GPIO_writePORT(GPIO_portNameType portName, uint32 Data)
/** Funci�n para escribir en todos los registros del puerto*/
{
	switch (portName) {
	case GPIOA:/** Se selecciono el GPIOA*/
		GPIOA_PDOR = Data;
		break;
	case GPIOB:/** Se selecciono el GPIOB*/
		GPIOB_PDOR = Data;
		break;
	case GPIOC:/** Se selecciono el GPIOC*/
		GPIOC_PDOR = Data;
		break;
	case GPIOD:/** Se selecciono el GPIOD*/
		GPIOD_PDOR = Data;
		break;
	case GPIOE: /** Se selecciono el GPIOE*/
		GPIOE_PDOR = Data;
	default:/**Si no existe la opci�n*/
		break;
	}
}
uint32 GPIO_readPORT(GPIO_portNameType portName)
/**Funci�n para leer el registro de un puerto*/
{
	switch (portName) {
	case GPIOA:/** Se selecciono el GPIOA*/
		return(GPIOA_PDIR);
		break;
	case GPIOB:/** Se selecciono el GPIOB*/
		return(GPIOB_PDIR);
		break;
	case GPIOC:/** Se selecciono el GPIOC*/
		return(GPIOC_PDIR);
		break;
	case GPIOD:/** Se selecciono el GPIOD*/
		return(GPIOD_PDIR);
		break;
	case GPIOE:/** Se selecciono el GPIOE*/
		return(GPIOE_PDIR);
	default:/**Si no existe la opci�n*/
		break;
	}
}

uint8 GPIO_readPIN(GPIO_portNameType portName, uint8 pin)
/** Funci�n para solo leer el valor del pin de un puerto*/
{
	uint32 control = 0x01;
	switch(portName){
	case GPIOA:/** Se selecciono el GPIOA*/
		return((GPIOA_PDIR >> pin)&control);
		break;
	case GPIOB:/** Se selecciono el GPIOB*/
		return((GPIOB_PDIR >> pin)&control);
		break;
	case GPIOC:/** Se selecciono el GPIOC*/
		return((GPIOC_PDIR >> pin)&control);
		break;
	case GPIOD:/** Se selecciono el GPIOD*/
		return((GPIOD_PDIR >> pin)&control);
		break;
	case GPIOE: /** Se selecciono el GPIOE*/
		return((GPIOE_PDIR >> pin)&control);
	default:/**Si no existe la opci�n*/
		break;
	}
}
void GPIO_setPIN(GPIO_portNameType portName, uint8 pin)
/**Funci�n para encender el pin de un puerto*/
{
	uint32 control = 0x01;
	switch (portName) {
	case GPIOA:/** Se selecciono el GPIOA*/
		GPIOA_PDOR |= control << pin;
		break;
	case GPIOB:/** Se selecciono el GPIOB*/
		GPIOB_PDOR |= control << pin;
		break;
	case GPIOC:/** Se selecciono el GPIOC*/
		GPIOC_PDOR |= control << pin;
		break;
	case GPIOD:/** Se selecciono el GPIOD*/
		GPIOD_PDOR |= control << pin;
		break;
	case GPIOE: /** Se selecciono el GPIOE*/
		GPIOE_PDOR |= control << pin;
	default:/**Si no existe la opci�n*/
		break;
	}

}
void GPIO_clearPIN(GPIO_portNameType portName, uint8 pin)
/**Funci�n para limpiar el valor de un pin*/
	{
		uint32 control = 0x01;
		switch (portName) {
		case GPIOA:/** Se selecciono el GPIOA*/
			GPIOA_PCOR |= control << pin;
			break;
		case GPIOB:/** Se selecciono el GPIOB*/
			GPIOB_PCOR |= control << pin;
			break;
		case GPIOC:/** Se selecciono el GPIOC*/
			GPIOC_PCOR |= control << pin;
			break;
		case GPIOD:/** Se selecciono el GPIOD*/
			GPIOD_PCOR |= control << pin;
			break;
		case GPIOE: /** Se selecciono el GPIOE*/
			GPIOE_PCOR |= control << pin;
		default:/**Si no existe la opci�n*/
			break;
		}
	}
	void GPIO_tooglePIN(GPIO_portNameType portName, uint8 pin)
	/**Funci�n para cambiar el estado de un pin, si est� en 1 cambia a 0 y viceversa*/
	{
		uint32 control = 0x01;
		switch (portName) {
		case GPIOA:/** Se selecciono el GPIOA*/
			GPIOA_PTOR |= control << pin;
			break;
		case GPIOB:/** Se selecciono el GPIOB*/
			GPIOB_PTOR |= control << pin;
			break;
		case GPIOC:/** Se selecciono el GPIOC*/
			GPIOC_PTOR |= control << pin;
			break;
		case GPIOD:/** Se selecciono el GPIOD*/
			GPIOD_PTOR |= control << pin;
			break;
		case GPIOE: /** Se selecciono el GPIOE*/
			GPIOE_PTOR |= control << pin;
		default:/**Si no existe la opci�n*/
			break;
		}
	}
	void GPIO_dataDirectionPORT(GPIO_portNameType portName, uint32 direction) {
		switch (portName) {
		case GPIOA:/** Se selecciono el GPIOA*/
			GPIOA_PDDR = direction;
			break;
		case GPIOB:/** Se selecciono el GPIOB*/
			GPIOB_PDDR = direction;
			break;
		case GPIOC:/** Se selecciono el GPIOC*/
			GPIOC_PDDR = direction;
			break;
		case GPIOD:/** Se selecciono el GPIOD*/
			GPIOD_PDDR = direction;
			break;
		case GPIOE:/** Se selecciono el GPIOE*/
			GPIOE_PDDR = direction;
		default:/**Si no existe la opci�n*/
			break;
		}
	}
	void GPIO_dataDirectionPIN(GPIO_portNameType portName, uint8 State, uint8 pin) {
		uint32 control = 0x01;
		if (GPIO_OUTPUT == State) {
			switch (portName) {
			case GPIOA:/** Se selecciono el GPIOA*/
				GPIOA_PDDR |= control << pin;
				break;
			case GPIOB:/** Se selecciono el GPIOB*/
				GPIOB_PDDR |= control << pin;
				break;
			case GPIOC:/** Se selecciono el GPIOC*/
				GPIOC_PDDR |= control << pin;
				break;
			case GPIOD:/** Se selecciono el GPIOD*/
				GPIOD_PDDR |= control << pin;
				break;
			case GPIOE:/** Se selecciono el GPIOE*/
				GPIOE_PDDR |= control << pin;
			default:/**Si no existe la opci�n*/
				break;
			}
		}
	}


