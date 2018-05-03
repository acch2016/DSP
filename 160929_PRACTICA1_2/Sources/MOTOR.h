/*
 * \file MOTOR.h
 *	\briefDescripci�n: Este es el archivo header para el driver del motor. En este vienen las definiciones
 *					de las funciones.
 *  \date  24/9/2016
 *  \Author  Alejandro Canale
 */

#ifndef SOURCES_MOTOR_H_
#define SOURCES_MOTOR_H_

/**Archivos que contienen los tipos de datos y nombre de los registros de la K64*/
#include "DataTypeDefinitions.h"
#include "MK64F12.h"

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief  Funci�n que contiene la m�quina de estados para hacer
 	 \return uint8
 */
void FSM_Motor(uint8 Flag_Enable);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief  Funci�n que contiene la primera secuencia de encendido de motor
 	 \return uint8
 */
void sequence_1();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief  Funci�n que contiene la segunda secuencia de encendido de motor
 	 \return uint8
 */
void sequence_2();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief  Funci�n que contiene el estado inactivo del motor
 	 \return uint8
 */
void sequence_3();

#endif /* SOURCES_MOTOR_H_ */
