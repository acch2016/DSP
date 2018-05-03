/*
 *\filde FUNC.h
 *\brief Archivo header del generador de señales, esta es una máquina de estados que
 *	utiliza el módulo DAC para generar las señales
 *\date 17/9/2016
 *\author: Alejandro Canale
 */

#ifndef SOURCES_FUNC_H_
#define SOURCES_FUNC_H_

/** Archivos que contienen variables y nombres de registros*/
#include "DataTypeDefinitions.h"
#include "MK64F12.h"




/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	Función para la maquina de estados del generador de señales

 	 \param[uint8]  Este parámetro se utiliza para activar el switch
 	 \return void
 */
void FSM_signals(uint8 flag_enable);


/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	Funcion del estado que activa la onda cuadrada
 	 \return void
 */
void square_1();


/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	Funcion del estado que activa la onda senoidal
 	 \return void
 */
void sine_2();


/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	Funcion del estado que activa la onda triangular
 	 \return void
 */
void triangle_3();


/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	Funcion que desactiva el generador de señales
 	 \return void
 */
void zero_4();

#endif /* SOURCES_FUNC_H_ */
