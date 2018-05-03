/*
 * FREQ_SELECT.c
 *
 *  Created on: 29/11/2016
 *      Author: alejandrocanale
 */



#include "FREQ_SELECT.h"


#define LOWER_LIMIT_RANGE1 200.0
#define UPPER_LIMIT_RANGE1 343.75
#define LOWER_LIMIT_RANGE2 343.76
#define UPPER_LIMIT_RANGE2 590.83
#define LOWER_LIMIT_RANGE3 590.84
#define UPPER_LIMIT_RANGE3 1015.51
#define LOWER_LIMIT_RANGE4 1015.52
#define UPPER_LIMIT_RANGE4 1745.43
#define LOWER_LIMIT_RANGE5 1745.44
#define UPPER_LIMIT_RANGE5 3000.0

#define DIFERENCIA_1 143.75
#define DIFERENCIA_2 247.08
#define DIFERENCIA_3 424.67
#define DIFERENCIA_4 729.92
#define DIFERENCIA_5 1254.57


//#define LOWER_LIMIT_C0V_1 0
float LIMIT_C0V_1 = 13107.0;
//#define LOWER_LIMIT_C0V_2 13108
float LIMIT_C0V_2 = 26214.0;
//#define LOWER_LIMIT_C0V_3 26215
float LIMIT_C0V_3 = 39321.0;
//#define LOWER_LIMIT_C0V_4 39322
float LIMIT_C0V_4 = 52428.0;
//#define LOWER_LIMIT_C0V_5 52429
#define UPPER_LIMIT_C0V_5 65536

float percentage_1 = 0.2;
float percentage_2 = 0.2;
float percentage_3 = 0.2;
float percentage_4 = 0.2;
float percentage_5 = 0.2;
float percentage_6 = 0.2;

#define RANGE1 &FiniteStateMachineMoore[0]
#define RANGE2 &FiniteStateMachineMoore[1]
#define RANGE3 &FiniteStateMachineMoore[2]
#define RANGE4 &FiniteStateMachineMoore[3]
#define RANGE5 &FiniteStateMachineMoore[4]


/** Estructura para construir cada uno de los estados, está contiene un apuntador función y
 * apuntadores para las transciciones a los siguiente estados*/
typedef const struct State
{
	uint16 (*fptrRange)();
	const struct State* next[5];
}StateType;

/** Declaración de la máquina de estados*/
const StateType FiniteStateMachineMoore[5]=
{
		{range1,    {RANGE1, RANGE2, RANGE3, RANGE4, RANGE5}},
		{range2,    {RANGE1, RANGE2, RANGE3, RANGE4, RANGE5}},
		{range3,    {RANGE1, RANGE2, RANGE3, RANGE4, RANGE5}},
		{range4,    {RANGE1, RANGE2, RANGE3, RANGE4, RANGE5}},
		{range5,    {RANGE1, RANGE2, RANGE3, RANGE4, RANGE5}},
};


/**Declaración del estado inicial*/
StateType * currentState_range = RANGE1;

/**Declaración para el control de transcición dentro de la máquina de estados*/
static uint16 inputC0V=0;/**Usamos Uint 16 porque se usará CnV el cual tiene de 0 a 65536*/
static uint8 currentState=0;
static uint8 confirm_Flag = FALSE;
static uint16 Frequency_value;

uint16 FSMRange() /** Función para llamar la máquina de estados*/
{
	/**Se limpia la bandera para ir al siguiente estado*/
	currentState = 0;
	/**Se manda a llamar a la función dentro del estado*/
	inputC0V = FTM0_C0V;
	while(confirm_Flag == FALSE){
		Frequency_value = currentState_range->fptrRange();

	/**Si la bandera de activación y el botón están encendidos se aumenta la bandera del siguiente estado*/
	/**Se actualiza el siguiente estado*/
	currentState_range = currentState_range->next[currentState];
}
	return Frequency_value;
}
uint16 range1(){

	LIMIT_C0V_1=UPPER_LIMIT_C0V_5*percentage_1;

	if ( LIMIT_C0V_1 >= inputC0V){

		percentage_1 = percentage_1 - 0.04;
		percentage_2 = percentage_2 + 0.01;
		percentage_3 = percentage_3 + 0.01;
		percentage_4 = percentage_4 + 0.01;
		percentage_5 = percentage_5 + 0.01;
		confirm_Flag = TRUE;
		return ((inputC0V/LIMIT_C0V_1)*DIFERENCIA_1)+LOWER_LIMIT_RANGE1;

	}currentState++;
	return FALSE;
}

uint16 range2(){

	LIMIT_C0V_2=UPPER_LIMIT_C0V_5*percentage_2;
	LIMIT_C0V_2=LIMIT_C0V_1+LIMIT_C0V_2;


	if ( LIMIT_C0V_1 <= inputC0V && LIMIT_C0V_2 >= inputC0V ){

		percentage_1 = percentage_1 + 0.01;
		percentage_2 = percentage_2 - 0.04;
		percentage_3 = percentage_3 + 0.01;
		percentage_4 = percentage_4 + 0.01;
		percentage_5 = percentage_5 + 0.01;
		confirm_Flag = TRUE;
		return (((inputC0V-LIMIT_C0V_1)/(LIMIT_C0V_2-LIMIT_C0V_1))*DIFERENCIA_2)+LOWER_LIMIT_RANGE2;

	}currentState++;
	return FALSE;
}

uint16 range3(){

	LIMIT_C0V_3=UPPER_LIMIT_C0V_5*percentage_3;
	LIMIT_C0V_3=LIMIT_C0V_2+LIMIT_C0V_3;

	if ( LIMIT_C0V_2 <=inputC0V && LIMIT_C0V_3 >=inputC0V ){

		percentage_1 = percentage_1 + 0.01;
		percentage_2 = percentage_2 + 0.01;
		percentage_3 = percentage_3 - 0.04;
		percentage_4 = percentage_4 + 0.01;
		percentage_5 = percentage_5 + 0.01;
		confirm_Flag = TRUE;
		return (((inputC0V-LIMIT_C0V_2)/(LIMIT_C0V_3-LIMIT_C0V_2))*DIFERENCIA_3)+LOWER_LIMIT_RANGE3;

	}currentState++;
	return FALSE;
}

uint16 range4(){

	LIMIT_C0V_4=UPPER_LIMIT_C0V_5*percentage_4;
	LIMIT_C0V_4=LIMIT_C0V_3+LIMIT_C0V_4;

	if ( LIMIT_C0V_3 <=inputC0V && LIMIT_C0V_4 >=inputC0V ){

		percentage_1 = percentage_1 + 0.01;
		percentage_2 = percentage_2 + 0.01;
		percentage_3 = percentage_3 + 0.01;
		percentage_4 = percentage_4 - 0.04;
		percentage_5 = percentage_5 + 0.01;
		confirm_Flag = TRUE;
		return (((inputC0V-LIMIT_C0V_3)/(LIMIT_C0V_4-LIMIT_C0V_3))*DIFERENCIA_4)+LOWER_LIMIT_RANGE4;

	}currentState++;
	return FALSE;
}

uint16 range5(){

		percentage_1 = percentage_1 + 0.01;
		percentage_2 = percentage_2 + 0.01;
		percentage_3 = percentage_3 + 0.01;
		percentage_4 = percentage_4 + 0.01;
		percentage_5 = percentage_5 - 0.04;
		confirm_Flag = TRUE;
		return (((inputC0V-LIMIT_C0V_4)/(UPPER_LIMIT_C0V_5-LIMIT_C0V_4))*DIFERENCIA_5)+LOWER_LIMIT_RANGE5;


}
