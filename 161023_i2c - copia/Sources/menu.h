/*
 * menu.h
 *
 *  Created on: 23/10/2016
 *      Author: alejandrocanale
 */

#ifndef SOURCES_MENU_H_
#define SOURCES_MENU_H_

#include "MK64F12.h"
#include "LCDNokia5110.h"
#include "DataTypeDefinitions.h"
#include "GPIO.h"

#define MAIN_SCREEN         &FiniteStateMachineMoore_Screen[0]
#define MENU                &FiniteStateMachineMoore_Screen[1]

#define READ_MEM_I2C        &FiniteStateMachineMoore_Screen[2]
#define WRITE_MEM_I2C       &FiniteStateMachineMoore_Screen[3]
#define SET_HOUR            &FiniteStateMachineMoore_Screen[4]
#define SET_DATE            &FiniteStateMachineMoore_Screen[5]
#define FORMAT_HOUR         &FiniteStateMachineMoore_Screen[6]
#define READ_HOUR           &FiniteStateMachineMoore_Screen[7]
#define READ_DATE           &FiniteStateMachineMoore_Screen[8]
#define COMMUNICATION_T1_T2 &FiniteStateMachineMoore_Screen[9]
#define ECHO_LCD            &FiniteStateMachineMoore_Screen[10]

typedef enum {
	SAME_STATE,
	NEXT_STATE,
}TransitionType;

typedef enum {
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
}KeyType;

TransitionType main_screenState();
TransitionType menuState();
TransitionType readMemI2c_State();
TransitionType writeMemI2c_State();
TransitionType setHour_State();
TransitionType setDate_State();
TransitionType formatHour_State();
TransitionType readHour_State();
TransitionType readDate_State();
TransitionType communicationT1T2_State();
TransitionType echoLCD_State();

#endif /* SOURCES_MENU_H_ */
