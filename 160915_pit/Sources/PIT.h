/*
 * PIT.h
 *
 *  Created on: Jan 29, 2015
 *      Author: Luis Pizano
 */

#ifndef PIT_H_
#define PIT_H_


#include "DataTypeDefinitions.h"


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
 	 	  	 	 
 	 \param[in]  portName Port to be configured.
 	 \return void
 */
void PIT_delay(PIT_TimerType pitTimer,float systemClock ,float perior);



#endif /* PIT_H_ */
