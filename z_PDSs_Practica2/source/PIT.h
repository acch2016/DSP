/*
 * \filePIT.h
 *	\brief la finalidad de este archivo es proporcionar las funciones que controla el PIT
 * \date Jan 29, 2015
 * \author Luis Pizano
 */
#ifndef PIT_H_
#define PIT_H_

//#define SYSTEM_CLOCK 800000
//#define DELAY 0.000016666
//
#include "MK64F12.h"
/*! This enumerated constant are used to select the PIT to be used*/
typedef enum {PIT_0,PIT_1,PIT_2,PIT_3} PIT_TimerType;



void PIT_init(void);
void set_SamplingFrequency(uint16_t newSamplingFrequency);
uint16_t get_SamplingFrequency(void);
uint16_t get_PeriodUs(void);

#endif /* PIT_H_ */
