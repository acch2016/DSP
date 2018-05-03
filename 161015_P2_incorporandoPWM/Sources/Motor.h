/*
 * Motor.h
 *
 *  Created on: 09/10/2016
 *      Author: Alexis
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include "MK64F12.h"
#include "DataTypeDefinitions.h"
#include "FlexTimer.h"

#define PWM_MOD_VALUE 0x00FF

void motorConfig();
void MotorEnable();
void MotorDisable();
void Mod_DutyCycle(sint16 channelValue);
void MotorControler();

#endif /* MOTOR_H_ */
