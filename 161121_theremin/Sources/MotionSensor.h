/*
 * MotionSensor.h
 *
 *  Created on: 21/11/2016
 *      Author: Alexis
 */

#include "MK64F12.h"
#include "NVIC.h"
#include "GPIO.h"
#include "FlexTimer.h"
#include "GlobalFunctions.h"
#include "PIT.h"
#define SYSTEM_CLOCK 60000000
#define PERIOD 0.00001

#ifndef SOURCES_MOTIONSENSOR_C_
#define SOURCES_MOTIONSENSOR_C_

typedef enum {SensorY_0,SensorY_1,SensorY_2,SensorX_0,SensorX_1,SensorX_2,SensorX_3} SensorType;

void ConfigurationSensor();
uint16 readRange(SensorType);
void SetEchoStatus();
void pos_Value();

#endif /* SOURCES_MOTIONSENSOR_C_ */
