/*
 * SoundGen.h
 *
 *  Created on: 16/11/2016
 *      Author: Alexis
 */

#ifndef SOURCES_SOUNDGEN_H_
#define SOURCES_SOUNDGEN_H_

#include "MK64F12.h"
#include "FlexTimer.h"
#include "DAC.h"
#include "GlobalFunctions.h"
#include "NVIC.h"
#include "GPIO.h"

void SoundGen_modifyFrecuency(uint8 frecuency, FTMType Timer, FTMChannelType channel);
void SoundGen_genFrecuency(uint8 frecuency, FTMType Timer, FTMChannelType channel);


#endif /* SOURCES_SOUNDGEN_H_ */
