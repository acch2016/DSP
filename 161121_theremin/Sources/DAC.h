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
#include "FlexTimer.h"



//void sine(uint16 FTM0_0_counter, uint16 FTM0_1_counter, uint16 FTM0_2_counter);
void sine(uint16 FTM0_0_counter, uint16 FTM0_1_counter,uint16 FTM0_2_counter,uint16 FTM0_3_counter,uint16 FTM0_4_counter,uint16 FTM0_5_counter,uint16 FTM0_6_counter,uint16 FTM0_7_counter,uint16 FTM0_8_counter,uint16 FTM0_9_counter,uint16 FTM0_10_counter,uint16 FTM0_11_counter,uint16 FTM0_12_counter,uint16 FTM0_13_counter,uint16 FTM0_14_counter,uint16 FTM0_15_counter);
//void sin(sint8 FTM0_C0SC_counter);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	Función que carga los datos de un arreglo con los valores de una señal senoidal al DAC
 	 	 	 de la K64
 	 \return void
 */
//void sine();

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
void writeDAC(uint16 valor);
sint16 adding_sines(sint8 ftm0ch0, sint8 ftm0ch1, sint8 ftm0ch2, sint8 ftm0ch3, sint8 ftm0ch4, sint8 ftm0ch5, sint8 ftm0ch6, sint8 ftm0ch7,sint8 ftm3ch0, sint8 ftm3ch1, sint8 ftm3ch2, sint8 ftm3ch3, sint8 ftm3ch4, sint8 ftm3ch5, sint8 ftm3ch6, sint8 ftm3ch7);
//

#endif /* SOURCES_DAC_H_ */
