/*
 * DAC.h
 *	Descripci�n: Este es un header para la implementaci�n del modulo DAC que se utiliza
 *				 para el generador de se�ales.
 *  Fecha: 17/9/2016
 *  Author: Alejandro Canale
 */

#ifndef SOURCES_DAC_H_
#define SOURCES_DAC_H_

#include "DataTypeDefinitions.h"
#include "MK64F12.h"

/**Prototipo de la funci�n para generar una se�al senoidal*/
void sine();
/**Prototipo de la funci�n para generar una se�al triangular*/
void tri();
/**Prototipo de la funci�n para generar una se�al cuadrada	*/
void square();
/**Prototipo de la funci�n para escribir en el DAC*/
void writeDAC(uint8 valor);

#endif /* SOURCES_DAC_H_ */
