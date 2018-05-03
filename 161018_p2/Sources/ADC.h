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
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 /* Para saber el estado del formato
 	 \param[in]   uint8 State recibe el 1 o 0 y eso indica el estado
 	 \return void
 */
void FormatFlagModifier(uint8 State);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 /* Retornar al display
 	 \param[in]    void
 	 \return uint8 Alarm Se retorna el valor de la alarma al display
 */
uint8 AlarmValue();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 /* Te permite cambiar la hora de la alarma
 	 \param[in]   sint8 value  Recibe el valor anterior de la alarma
 	 \return void
 */
void AlarmValueModifier(sint8 value);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 /* Te permite cambiar la hora de la alarma
 	 \param[in]   sint8 value  Recibe el valor anterior de la alarma
 	 \return void
 */
void AlarmModule();
#endif /* SOURCES_ADC_H_ */
