/*
 * MOTOR.h
 *
 *  Created on: 24/9/2016
 *      Author: alejandrocanale
 */

#ifndef SOURCES_MOTOR_H_
#define SOURCES_MOTOR_H_

#include "DataTypeDefinitions.h"
#include "MK64F12.h"

typedef enum {
	SEQUENCE1,
	SEQUENCE2,
	SEQUENCE3,
}StateDefinitionType;

void FSM_Motor(uint8 Flag_Enable);
void setModule();
void sequence_1();
void sequence_2();
void sequence_3();

#endif /* SOURCES_MOTOR_H_ */
