/*
 * ADC.h
 *
 *  Created on: 08/10/2016
 *      Author: Alexis
 */

#ifndef SOURCES_ADC_H_
#define SOURCES_ADC_H_

#include "MK64F12.h"
#include "GPIO.h"
#include "NVIC.h"
#define NUM_SAMPLE 30.0
#define TEMP_VALUE 200.0

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief  Esta funcion habilita los registros para que el ADC funcione y el pin de salida para la
 				alarma del sistema
 	 \return void
 */
void ADC_Configuration();

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief Esta funcion saca un promedio de 30 muestras tomadas de temperatura que obtiene del ADC 0
 	 \return Es el valor del promedio de 30 muestras de la temperatura.
 */
float Read_Data();

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief Esta funcion retorna el estado de la bandera
 	 \return Es el valor del promedio de 30 muestras de la temperatura.
 */
uint8 FormatFlagValue();
void FormatFlagModifier(uint8 State);
uint8 AlarmValue();
void AlarmValueModifier(sint8 value);
#endif /* SOURCES_ADC_H_ */
