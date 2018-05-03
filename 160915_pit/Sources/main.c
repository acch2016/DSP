/**
	\file 
	\brief 
		This is a starter file to implement a function able to produce an accurate delay
		using the PIT module. 

	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	7/09/2014
 */

#include "MK64F12.h"
//#include "derivative.h" /* include peripheral declarations */

#include "DataTypeDefinitions.h"
#include "PIT.h"
#include "NVIC.h"
#include "GPIO.h"
#define SYSTEM_CLOCK 21000000					//Relog del sistema
#define DELAY 0.25							//Periodo de la señal

extern uint8 PIT0_Flag = FALSE;					//Bandera para la interrupción del PIT0

int main(void)
{
	GPIO_pinControlRegisterType pinControlRegisterPORTD = GPIO_MUX1;
	GPIO_clockGating(GPIOD);	 										//Se activa el reloj del puerto D
	SIM_SCGC6 |= 0x00800000;										    //Se activa el reloj del timer PIT
	PIT_MCR = 0x00;														//Registro para habilitar los timers
	GPIO_pinControlRegister(GPIOD,BIT0,&pinControlRegisterPORTD);		//Se configura como periferico de entrada y salida
	GPIO_dataDirectionPIN(GPIOD,GPIO_OUTPUT,BIT0);						//Se activa como salida el pin 0 de
																		//del puerto D
	GPIO_setPIN(GPIOD,BIT0);											//Se activa el valor por defecto del pin0 //Valor seguro
	NVIC_setBASEPRI_threshold(PRIORITY_9);								//Se activa la prioridad máxima
	NVIC_enableInterruptAndPriotity(PIT_CH0_IRQ, PRIORITY_8				//Se activa la prioridad de la interrupción
																		//del timer 0 del PIT
			);
	EnableInterrupts;



	
	for(;;) {	   
		PIT0_Flag = FALSE;			//Se limpia la bandera de la interrupción
		GPIO_tooglePIN(GPIOD, BIT0);			//Se cambia el estdo del PIN 0

		PIT_delay(PIT_0, SYSTEM_CLOCK, DELAY);//Se activa el timer y el valor de autorecarga
		while (FALSE == PIT0_Flag)
			;									//Se mantiene hasta que la interrupción del PIT
	   	 																//activa

//	   	 PIT0_Flag = FALSE;												//Se limpia la bandera de la interrupción
//	   	 	GPIO_tooglePIN(GPIOD,BIT0);									//Se cambia el estdo del PIN 0
//	   		PIT_delay(PIT_0,SYSTEM_CLOCK,DELAY);						//Se activa el timer y el valor de autorecarga
//	   		while(FALSE == PIT0_Flag);									//Se mantiene hasta que la interrupción del PIT
//	   																	//activa
	}
	
	return 0;
}
