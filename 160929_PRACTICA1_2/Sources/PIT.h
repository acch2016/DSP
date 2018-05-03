/*
 * \filePIT.h
 *	\brief la finalidad de este archivo es proporcionar las funciones que controla el PIT
 * \date Jan 29, 2015
 * \author Luis Pizano
 */
#ifndef PIT_H_
#define PIT_H_


#include "DataTypeDefinitions.h"
#include "MK64F12.h"

/*! This enumerated constant are used to select the PIT to be used*/
typedef enum {PIT_0,PIT_1,PIT_2,PIT_3} PIT_TimerType;


/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function configure the PIT to generate a delay base on the system clock.
 	 Internally it configures the clock gating and enables the PIT module.
 	 It is important to note that this strictly is not device driver since everything is 
 	 contained in a single function, but in general you have to avoid this practices, this only
 	 for the propose of the homework
 	 	  	 	 
 	 \param[in]  pitTimer Port to be configured.
 	 \param[float]  systemClock Default Clock Rate
 	 \param[float]  period Period time for the output signal
 	 \return void
 */
void PIT_delay(PIT_TimerType pitTimer,float systemClock ,float period);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 Esta funcion sirve para apagar el timer

 	 \param[in]  pitTimer Port to be configured.

 	 \return void
 */
void PIT_Disable(PIT_TimerType pitTimer);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 Esta funcion limpia la bandera de la interrupcion del PIT0
 	 \return void
 */
void PIT0_Flag_edit();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 Esta funcion regresa el estado de la bandera de la interrupcion del PIT0

 	 \return uint8
 */
uint8 PIT0_Flag_state();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 Esta funcion regresa el estado de la bandera de la interrupcion del PIT1

 	 \return uint8
 */
uint8 PIT1_Flag_state();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 Esta funcion limpia la bandera de la interrupcion del PIT0
 	 \return void
 */
void PIT1_Flag_edit();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 Esta funcion limpia la bandera de la interrupcion del PIT0
 	 \return void
 */
void PIT2_Flag_clear();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 Esta funcion regresa el estado de la bandera de la interrupcion del PIT2

 	 \return uint8
 */
uint8 PIT2_Flag_read();

#endif /* PIT_H_ */
