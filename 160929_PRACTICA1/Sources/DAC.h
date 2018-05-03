/*
 * DAC.h
 *	Descripción: Este es un header para la implementación del modulo DAC que se utiliza
 *				 para el generador de señales.
 *  Fecha: 17/9/2016
 *  Author: Alejandro Canale
 */

#ifndef SOURCES_DAC_H_
#define SOURCES_DAC_H_

#include "DataTypeDefinitions.h"
#include "MK64F12.h"

/**Prototipo de la función para generar una señal senoidal*/
void sine();
/**Prototipo de la función para generar una señal triangular*/
void tri();
/**Prototipo de la función para generar una señal cuadrada	*/
void square();
/**Prototipo de la función para escribir en el DAC*/
void writeDAC(uint8 valor);

#endif /* SOURCES_DAC_H_ */
