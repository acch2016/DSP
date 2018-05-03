/*
 * MOTOR.c
 *	Descripción: Es el archivo fuente del driver que controla el motor.
 *				 En este modulo está implementada una máquina de estados de estructuras que decide
 *				 las transciciones entre las secuencias del motor
 *  Fecha: 24/9/2016
 *  Autor: Alejandro Canale
 */

/**Archivo que contiene el nombre de los registros y los tipos de datos de la k64*/
#include "DataTypeDefinitions.h"
#include "MK64F12.h"
/**Archivo header de este módulo*/
#include "MOTOR.h"
/**Archivo que incluye las funciones para manejar las interrupciones*/
#include "PIT.h"
/*Archivo que incluye funciones para manejar el GPIO*/
#include "GPIO.h"
/** Definicion para el reloj del sistema que utilizamos para la recarga del PIT*/
#define systemClock 21000000
/**Definiciones para las secuencias dentro del motor*/
#define PERIOD1 1
#define PERIOD3 3
#define PERIOD4 4
/**Definiciones para las fases de cada motor*/
#define FASE1 1
#define FASE2 2
#define FASE3 3
#define FASE4 4
 /**Definciones para los leds y el puerto del motor*/
#define LED1 18
#define LED2 19
#define MOTOR 0x1


/**Banderas utilizadas para saber en que punto de la secuencia estamos*/
uint8 flag_sec_1=1;
uint8 flag_sec_2=1;

/**Estructura utilizada para crear cada uno de nuestros estados*/
typedef struct
{
	uint32 out;			/**Valor que utilizamos para saber que función ejecutar*/
	uint8 next[2];		/**Arreglo que utilizamos para saber a cuales estados nos podemos mover*/
}StateType;


/**Declaración de un arreglo de funciones*/
void(*fptrSeq[3])(void)={sequence_1,sequence_2,sequence_3};


/**Declaración de la máquina de estados*/
const StateType FineStateMachineMoore_Motor[3]=
{
		{SEQUENCE1,{SEQUENCE1, SEQUENCE2}},
		{SEQUENCE2,{SEQUENCE2, SEQUENCE3}},
		{SEQUENCE3,{SEQUENCE3, SEQUENCE1}}
};

/** Variable que utilizamos para movernos entre los estados*/
StateDefinitionType currentState_Motor = SEQUENCE3;

/**Variable que utilizamos para saber si la interrupción del botón se activo*/
static uint32 input=0;
/**Varible que*/
static uint8 currentState_flag=0;


void FSM_Motor(uint8 Flag_Enable) {

	currentState_flag = 0;

	currentState_Motor = FineStateMachineMoore_Motor[currentState_Motor].out;

	(*fptrSeq[currentState_Motor])();

	input=readFlag_PORTC();
	if(TRUE == Flag_Enable){
	if (TRUE == input) {
		currentState_flag++;
		clearFlag_PORTC();
	}
	}
	currentState_Motor = FineStateMachineMoore_Motor[currentState_Motor].next[currentState_flag];

}

void sequence_1(){
	if(TRUE==PIT1_Flag_state()){
		flag_sec_1++;
		PIT1_Flag_edit();
		if (flag_sec_1==5){
			flag_sec_1=1;
		}

		if (FASE1==flag_sec_1){

			GPIO_setPIN(GPIOB, LED1);// LED 1(PTB18) is ON
			GPIO_clearPIN(GPIOB, LED2);// LED 2(PTB19) is OFF
			PIT_delay(PIT_1,systemClock,PERIOD1);//period its one second

			GPIO_setPIN(GPIOC, MOTOR);// motor is ON
		}

		else if(FASE2==flag_sec_1){

			GPIO_setPIN(GPIOB, LED1);// LED 1(PTB18) is ON
			GPIO_clearPIN(GPIOB, LED2);// LED 2(PTB19) is OFF
			PIT_delay(PIT_1,systemClock,PERIOD1);//period its one second

			GPIO_clearPIN(GPIOC, MOTOR);// motor is OFF
		}


		else if(FASE3==flag_sec_1){

			GPIO_setPIN(GPIOB, LED1);// LED 1(PTB18) is ON
			GPIO_clearPIN(GPIOB, LED2);// LED 2(PTB19) is OFF
			PIT_delay(PIT_1,systemClock,PERIOD3);//period its 3 seconds


			GPIO_setPIN(GPIOC, MOTOR);// motor is ON
		}
		else if(FASE4==flag_sec_1){

			GPIO_setPIN(GPIOB, LED1);// LED 1(PTB18) is ON
			GPIO_clearPIN(GPIOB, LED2);// LED 2(PTB19) is OFF
			PIT_delay(PIT_1,systemClock,PERIOD1);//period its one second

			GPIO_clearPIN(GPIOC, MOTOR);// motor is OFF
		}

	}
}
void sequence_2(){
	flag_sec_1=0;
	if(TRUE==PIT1_Flag_state()){
		flag_sec_2++;
		PIT1_Flag_edit();
		if (flag_sec_2==3){
			flag_sec_2=1;
		}

		if (FASE1==flag_sec_2){

			GPIO_clearPIN(GPIOB, LED1);// LED 1(PTB18) is OFF
			GPIO_setPIN(GPIOB, LED2);// LED 2(PTB19) is ON
			PIT_delay(PIT_1,systemClock,PERIOD4);//period its 4 seconds
			GPIO_setPIN(GPIOC, MOTOR);// motor is ON
		}

		else if(FASE2==flag_sec_2){

			GPIO_clearPIN(GPIOB, LED1);// LED 1(PTB18) is OFF
			GPIO_setPIN(GPIOB, LED2);// LED 2(PTB19) is ON
			PIT_delay(PIT_1,systemClock,PERIOD4);//period its 4 seconds
			GPIO_clearPIN(GPIOC, MOTOR);// motor is OFF
		}
	}

}

void sequence_3(){
	flag_sec_2=0;

	GPIO_setPIN(GPIOB, LED1);// LED 1(PTB18) is OFF
	GPIO_setPIN(GPIOB, LED2);// LED 2(PTB19) is OFF
	GPIO_clearPIN(GPIOC, MOTOR);// motor is OFF


}
