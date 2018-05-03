/*
 * FUNC.h
 *	Descripci�n: Archivo header del generador de se�ales, esta es una m�quina de estados que
 *	utiliza el m�dulo DAC para generar las se�ales
 *  Fecha: 17/9/2016
 *      Author: alejandrocanale
 */

#ifndef SOURCES_FUNC_H_
#define SOURCES_FUNC_H_

/** Archivos que contienen variables y nombres de registros*/
#include "DataTypeDefinitions.h"
#include "MK64F12.h"


/**Prototipo de funci�n para la maquina de estados del generador de se�ales*/
void FSM_signals(uint8 flag_enable);

/**Prototipo de la funcion del estado que activa la onda cuadrada*/
void square_1();
/**Prototipo de la funcion del estado que activa la onda senoidal*/
void sine_2();
/**Prototipo de la funcion del estado que activa la onda triangular*/
void triangle_3();
/**Prototipo de la funci�n del estado para apagar el reloj*/
void zero_4();



#endif /* SOURCES_FUNC_H_ */
