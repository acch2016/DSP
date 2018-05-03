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
uint8 flag_sec_1=0;
uint8 flag_sec_2=0;

typedef enum {
	SEQUENCE1,
	SEQUENCE2,
	SEQUENCE3,
}StateDefinitionType;

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
/**Varible que determina en ue estado te encuentras*/
static uint8 currentState_flag=0;


void FSM_Motor(uint8 Flag_Enable)
/**Función que manda a llamar a la máquina de estados para las transciciones de motor*/
{
	/** Se limpia la bandera para mandar a llamar al siguiente estado*/
	currentState_flag = 0;

	/** Se actualiza en el estado en el que está*/
	currentState_Motor = FineStateMachineMoore_Motor[currentState_Motor].out;

	/*Se manda a llamar a la función del estado actual*/
	(*fptrSeq[currentState_Motor])();

	/**Si la bandera de activación y el botón están encendidos se aumenta la bandera del siguiente estado*/
	input=readFlag_PORTC();
	if(TRUE == Flag_Enable){
		if (TRUE == input) {
			currentState_flag++;
			clearFlag_PORTC();
		}
	}

	/**Se manda a llamar al siguiente estado según si l bandera se activo*/
	currentState_Motor = FineStateMachineMoore_Motor[currentState_Motor].next[currentState_flag];

}

void sequence_1()
/**Función que ejecuta la secuencia 1 del motor*/
{
	if(TRUE==PIT1_Flag_state()){		/**No entra a las recargas de la interrupción a menos que la bandera de recarga esté activada*/
		flag_sec_1++;					/**Se aumenta la bandera de la fase que se usa para seleccionar el tiempo de recarga*/
		PIT1_Flag_edit();				/**Se limpia la bandera del motor*/
		if (flag_sec_1==5){				/**Se regresa la bandera a la primera posición cuando termino la secuencia*/
			flag_sec_1=1;
		}
		/**Se enciende el segundo led y se apaga el primero*/
		GPIO_setPIN(GPIOB, LED1);
		GPIO_clearPIN(GPIOB, LED2);

		if (FASE1==flag_sec_1){			/**Tiempo de recarga de 1 segundo cuando la secuencia esta en la primera fase y se enciende el motor*/

			PIT_delay(PIT_1,systemClock,PERIOD1);	/**Recarga del timer para contar un segundo*/
			GPIO_setPIN(GPIOC, MOTOR);				/**Encendido del motor*/
		}

		else if(FASE2==flag_sec_1){		/**Tiempo de recarga de 1 segundo para la segunda fase y apagado del motor*/


			PIT_delay(PIT_1,systemClock,PERIOD1);	/**Recarga del Timer para contar un segundo*/
			GPIO_clearPIN(GPIOC, MOTOR);			/**Apagado del motor*/
		}


		else if(FASE3==flag_sec_1){		/**Tiempo de recarga de 3 segundos para la tercera fase y encendido del motor*/

			PIT_delay(PIT_1,systemClock,PERIOD3);	/**Tiempo de recarga de 3 segundos*/
			GPIO_setPIN(GPIOC, MOTOR);				/**Motor encendido*/
		}

		else if(FASE4==flag_sec_1){		/**Tiempo de recarga de 1 segundo para la segunda fase y apagado del motor*/

			PIT_delay(PIT_1,systemClock,PERIOD1);	/**Recarga del timer para contar un segundo*/
			GPIO_clearPIN(GPIOC, MOTOR);			/**Apagado del motor*/
		}
	}
}
void sequence_2()
/**Secuencia para controlar la segunda secuencia del motor*/
{
	flag_sec_1=0;	/**Se limpia la bandera de posición de la primera secuencia para que comience desde el inicio*/
	if(TRUE==PIT1_Flag_state()){	/**Se checa si la bandera de interrupción del PIT está activada*/
		flag_sec_2++;				/**Se aumenta la bandera para cambiar la fase del motor*/
		PIT1_Flag_edit();			/**Se limpia la bandera del PIT*/
		if (flag_sec_2==3){			/**Se reinicia el contador de las fases si ya acabo con estas*/
			flag_sec_2=1;
		}
		/**Se activan los leds para indicar el estado*/
		GPIO_clearPIN(GPIOB, LED1);	/**Se enciende el led 1*/
		GPIO_setPIN(GPIOB, LED2);	/**Se apaga el led 2*/

		if (FASE1==flag_sec_2){	/**Fase de encendido de motor con recarga de 4 segundos*/


			PIT_delay(PIT_1,systemClock,PERIOD4);	/**Tiempo de recarga de 4 segundos*/
			GPIO_setPIN(GPIOC, MOTOR);				/**Encendido del motor*/
		}

		else if(FASE2==flag_sec_2){	/**Fase de apagado de motor con recarga de 4 segundos*/

			PIT_delay(PIT_1,systemClock,PERIOD4);	/**Recarga del timer para 4 segundos*/
			GPIO_clearPIN(GPIOC, MOTOR);			/**Apagado de motor*/
		}
	}

}

void sequence_3()
/**Secuencia de apgado del motor*/
{
	flag_sec_2=0;	/**La bandera de la secuencia de se limpia para que no guarde la fase en la que se encontraba*/

	GPIO_setPIN(GPIOB, LED1);	/**Se apaga el led 1*/
	GPIO_setPIN(GPIOB, LED2);	/**Se apaga el led 2*/
	GPIO_clearPIN(GPIOC, MOTOR);	/**Se apaga el motor*/


}
