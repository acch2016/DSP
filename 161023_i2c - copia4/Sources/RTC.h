/*
 * RTC.h
 *
 *  Created on: 29/10/2016
 *      Author: Alexis
 */


#ifndef SOURCES_RTC_H_
#define SOURCES_RTC_H_

#include "MK64F12.h"
#include "I2C.h"
#include "GlobalFunctions.h"

 typedef enum {
	 H24,
	 H12,
 }FormatRTCType;



void RTC_changeFormat(FormatRTCType format);
sint8 * RTC_get_String_Date();
sint8 * RTC_get_String_Hour();
void RTC_set_Hour(uint8  character);
void RTC_set_Minutes(uint8  character);
void RTC_set_Day(uint8 character);
void RTC_set_Month(uint8 character);
void RTC_set_Year(uint8 character);
void RTC_writeData(uint8 Address, uint8 Data);
uint8 RTC_readData(uint8 Address);
void RTC_Init();
void modifyYears(sint8 yeah[]);



#endif /* SOURCES_RTC_H_ */
