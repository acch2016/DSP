/*
 * menu.h
 *
 *  Created on: 16/1/2017
 *      Author: alejandrocanale
 */

#ifndef SOURCES_MENU_H_
#define SOURCES_MENU_H_

#include "DataTypeDefinitions.h"
#include "UART.h"

#define MENU        &FiniteStateMachineMoore_Screen[0]
#define CHARACTER       &FiniteStateMachineMoore_Screen[1]
#define OPERATION            &FiniteStateMachineMoore_Screen[2]



typedef enum {
	SAME_STATE,
	NEXT_STATE,
}TransitionType;

TransitionType menu(UART_ChannelType uartChannel);
TransitionType character(UART_ChannelType uartChannel);
TransitionType operation(UART_ChannelType uartChannel);

#endif /* SOURCES_MENU_H_ */
