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
#include "UART.h"
#include "DataTypeDefinitions.h"
#include "GPIO.h"
#include "GlobalFunctions.h"
#include "RTC.h"
#include "Memory.h"

//#define MAIN_SCREEN         &FiniteStateMachineMoore_Screen[0]//deberia quitar si no habrá main creen
#define MENU                &FiniteStateMachineMoore_Screen[0]

#define READ_MEM_I2C        &FiniteStateMachineMoore_Screen[1]
#define WRITE_MEM_I2C       &FiniteStateMachineMoore_Screen[2]
#define SET_HOUR            &FiniteStateMachineMoore_Screen[3]
#define SET_DATE            &FiniteStateMachineMoore_Screen[4]
#define FORMAT_HOUR         &FiniteStateMachineMoore_Screen[5]
#define READ_HOUR           &FiniteStateMachineMoore_Screen[6]
#define READ_DATE           &FiniteStateMachineMoore_Screen[7]
#define COMMUNICATION_T1_T2 &FiniteStateMachineMoore_Screen[8]
#define ECHO_LCD            &FiniteStateMachineMoore_Screen[9]

#define h_KEY               0x068
#define m_KEY               0x06D
#define ENTER               0x0D
#define ASCII				0x30


typedef enum {
	LCD,
	TERMINAL,
}TerminalType;

typedef enum {
	POSITION_1,
	POSITION_2,
	POSITION_3
}PositionType;


typedef enum {
	SAME_STATE,
	NEXT_STATE,
}TransitionType;

typedef enum {
	KEY_0,
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

void screenFSM();
TransitionType main_screenState(UART_ChannelType uartChannel);
TransitionType menuState_UARTx(UART_ChannelType uartChannel);
TransitionType readMemI2c_State(UART_ChannelType uartChannel);
TransitionType writeMemI2c_State(UART_ChannelType uartChannel);
TransitionType setHour_State(UART_ChannelType uartChannel);
TransitionType setDate_State(UART_ChannelType uartChannel);
TransitionType formatHour_State(UART_ChannelType uartChannel);
TransitionType readHour_State(UART_ChannelType uartChannel);
TransitionType readDate_State(UART_ChannelType uartChannel);
TransitionType communicationT1T2_State(UART_ChannelType uartChannel);
TransitionType echoLCD_State(UART_ChannelType uartChannel);

#endif /* SOURCES_MENU_H_ */
