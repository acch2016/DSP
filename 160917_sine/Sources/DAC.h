/*
 * DAC.h
 *
 *  Created on: 17/9/2016
 *      Author: alejandrocanale
 */

#ifndef SOURCES_DAC_H_
#define SOURCES_DAC_H_

#include "DataTypeDefinitions.h"
#include "MK64F12.h"

/*! This enumerated constant are used to select the PIT to be used*/
typedef enum {DAC_0,DAC_1} DACC_Type;
//typedef enum {SIN,TRI,SQUARE} WAVE_Type;

//void PIT_delay(PIT_TimerType pitTimer,float systemClock ,float period);
//void enableDAC(DAC_Type);

//void sin(uint8 FTM0_C0SC_counter);
void sine();
void tri();
void square();
void writeDAC(uint8 valor);

#endif /* SOURCES_DAC_H_ */
