/*
 * Menu.h
 *
 *  Created on: 08/10/2016
 *      Author: Alexis
 */

#ifndef SOURCES_MENU_H_
#define SOURCES_MENU_H_
#include "MK64F12.h"
#include "SPI.h"
#include "LCDNokia5110.h"
#include "ADC.h"
#include "GPIO.h"
#include "stdio.h"
#include "FlexTimer.h"

typedef enum {
	SAME_STATE,
	NEXT_STATE,
}TransitionType;

void Configuration_Menu();
void Screen_Machine();
TransitionType Main_Screen();
TransitionType Menu_Screen();
TransitionType Alarm_Screen();
TransitionType Format_Screen();
TransitionType Decrement_Screen();
TransitionType MControl_Screen();
TransitionType Frecuency_Screen();



#endif /* SOURCES_MENU_H_ */
