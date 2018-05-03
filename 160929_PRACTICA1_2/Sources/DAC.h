/*
 *\file DAC.h
 *\brief	Este es un header para la implementación del modulo DAC que se utiliza
 *				 para el generador de señales.
 * \date 17/9/2016
 * \Author Alejandro Canale
 */

#ifndef SOURCES_DAC_H_
#define SOURCES_DAC_H_

#include "DataTypeDefinitions.h"
#include "MK64F12.h"

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	Función que carga los datos de un arreglo con los valores de una señal senoidal al DAC
 	 	 	 de la K64
 	 \return void
 */
void sine();

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	Función que carga los datos de un arreglo con los valores de una señal triangular al DAC
 	 	 	 de la K64
 	 \return void
 */
void tri();


/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	Función que carga los datos de un arreglo con los valores de una señal cuadrada al DAC
 	 	 	 de la K64
 	 \return void
 */
void square();

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	Función que carga datos al DAC de la K64
 	 \return void
 */
void writeDAC(uint8 valor);

#endif /* SOURCES_DAC_H_ */
