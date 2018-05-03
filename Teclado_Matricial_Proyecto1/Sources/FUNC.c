/*
 * \file FUNC.c
 * \brief Archivo fuente para el generador de señales, en este archivo utilziamos una máquina de
 * 				estados de listas enlazadas para elegir que seal deseamos reproducir
 *
 * \date 17/9/2016
 * \author Alejandro Canale
 */
/** Archivos que contienen los tipos de datos y nombres de registros*/
#include "DataTypeDefinitions.h"
#include "MK64F12.h"

#include "FUNC.h"

/**Archivos que contienen funciones necesarias para el generador de señales*/
#include "DAC.h"
/**Archivo que contiene funciones para el manejo de registros*/
#include "GPIO.h"
/**Archivo que contiene funciones para el manejo de interrupciones*/
#include "PIT.h"

/** Definiciones para el control de los LEDs*/
#define SIGNAL_LED_1 24
#define SIGNAL_LED_2 25

/** Definiciones para cada uno de los estados de la máquina, estas definiciones corresponden a espacios
 *  de memoria
 */
#define SQUARE &FineStateMachineMoore_Wave[0]
#define SINE &FineStateMachineMoore_Wave[1]
#define TRIANGLE &FineStateMachineMoore_Wave[2]
#define ZERO &FineStateMachineMoore_Wave[3]

/** Estructura para construir cada uno de los estados, está contiene un apuntador  función y
 * apuntadores para las transciciones a los siguiente estados*/
typedef const struct State
{
	void (*ftprSig)();
	const struct State* next[2];
}StateType;

/** Declaración de la máquina de estados*/
const StateType FineStateMachineMoore_Wave[4]=
{
		{square_1,  {SQUARE,  SINE}},
		{sine_2,    {SINE,    TRIANGLE}},
		{triangle_3,{TRIANGLE,ZERO}},
		{zero_4,    {ZERO,    SQUARE}}
};

/**Declaración del estado inicial*/
StateType * currentState_Wave = ZERO;

/**Declaración para el control de transcición dentro de la máquina de estados*/
static uint8 input=0;
static uint8 currentState_flag=0;


void FSM_signals(uint8 flag_enable) /** Función para llamar la máquina de estados*/
{
	/**Se limpia la bandera para ir al siguiente estado*/
	currentState_flag = 0;
	/**Se manda a llamar a la función dentro del estado*/
	currentState_Wave->ftprSig();

	/**Si la bandera de activación y el botón están encendidos se aumenta la bandera del siguiente estado*/
	input = readFlag_PORTA();
	if(TRUE == flag_enable){
	if (TRUE == input) {
		currentState_flag++;
		clearFlag_PORTA();
	}
}
	/**Se actualiza el siguiente estado*/
	currentState_Wave = currentState_Wave->next[currentState_flag];
}

void square_1()		/**Función para prender los leds del estado y mandar
						a llamar la función para la señal cuadrada*/
{
	GPIO_setPIN(GPIOE, SIGNAL_LED_1);		/** Apagar LED 1 (PTE24)*/
	GPIO_clearPIN(GPIOE, SIGNAL_LED_2);		/** Encender LED 2(PTE25)*/

   square();								/**Llamar a la función para cargar el valor de la señal cuadrada*/
}
void sine_2()		/**Función para prender los leds del estado y mandar
						a llamar la función para la señal senoidal*/
{

	GPIO_clearPIN(GPIOE, SIGNAL_LED_1);		/** Encender LED 1 (PTE24)*/
	GPIO_setPIN(GPIOE, SIGNAL_LED_2);		/** Apagar LED 2 (PTE25)*/

	sine();									/**Llamar a la función para cargar el valor de la señal senoidal*/
}

void triangle_3()	/**Función para prender los leds del estado y mandar
						a llamar la función para la señal triangular*/
{
	GPIO_clearPIN(GPIOE, SIGNAL_LED_1);		/** Encender LED 1 (PTE24)*/
	GPIO_clearPIN(GPIOE, SIGNAL_LED_2);		/** Encender LED 2 (PTE25)*/
    tri();									/**Llamar a la función para cargar el valor de la señal triangular*/
}

void zero_4()		/**Función para apagar los leds y para apagar el PIT que
						que controla el generador de señales*/
{

	GPIO_setPIN(GPIOE, SIGNAL_LED_1);		/** Apagar LED 1 (PTE24)*/
	GPIO_setPIN(GPIOE, SIGNAL_LED_2);		/** Apagar LED 2 (PTE25)*/
	PIT_Disable(PIT_0);						/** Apagar el reloj del PIT*/

}


