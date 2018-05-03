/*
 * RTC.c
 *
 *  Created on: 29/10/2016
 *      Author: Alexis
 */

#include "RTC.h"
#define DEFAULT_SECONDS 0x80
#define DEFAULT_MINUTES 0x00
#define DEFAULT_HOURS 	0x18
#define DEFAULT_DAY		0x01
#define DEFAULT_MONTH	0x01
#define DEFAULT_YEAR	0x00
#define SECONDS_ADDRESS 0x00
#define MINUTES_ADDRESS 0x01
#define HOURS_ADDRESS 	0x02
#define DAYS_ADDRESS 	0x04
#define MONTHS_ADDRESS 	0x05
#define YEARS_ADDRESS 	0x06
#define MASK_UNIT		0x0F
#define MASK_TENS		0x70
#define H12_24_MASK		0x40
#define AM_FM_MASK		0x20
#define AM_FM_SHIFT		5
#define baudRate_100k 	0x56



static uint8 Days[2];
static uint8 Months[2];
static uint8 Years[2];
static uint8 HourValue[8];
static uint8 DateValue[10];

static uint8 dataFromRTC;
static uint8 FormatFlag = FALSE;


uint8 RTC_get_Seconds( ){
	return RTC_readData(SECONDS_ADDRESS);

}

uint8 RTC_get_Minutes( ){
	return RTC_readData(MINUTES_ADDRESS);
}


uint8 RTC_get_Hour( ){
	return RTC_readData(HOURS_ADDRESS);

}


uint8 RTC_get_Day( ){
	return RTC_readData(DAYS_ADDRESS);

}


uint8 RTC_get_Month(){
	return RTC_readData(MONTHS_ADDRESS);
}


uint8 RTC_get_Year(){
	return RTC_readData(YEARS_ADDRESS);
}

void RTC_Init(){
	I2C_init( I2C_0,  baudRate_100k);

	RTC_writeData(MINUTES_ADDRESS, DEFAULT_MINUTES);
	RTC_writeData(HOURS_ADDRESS, DEFAULT_HOURS);
	RTC_writeData(DAYS_ADDRESS,DEFAULT_DAY);
	RTC_writeData(MONTHS_ADDRESS,DEFAULT_MONTH);
	RTC_writeData(YEARS_ADDRESS,DEFAULT_YEAR);
	RTC_writeData(SECONDS_ADDRESS, DEFAULT_SECONDS);

}

uint8 RTC_readData(uint8 Address){
	I2C_TX_RX_Mode( I2C_0, ENABLE);

			I2C_start(I2C_0);
			delay(300);
			I2C_write_Byte(I2C_0,0xDE);
			I2C_wait(I2C_0);
			I2C_get_ACK(I2C_0);

			I2C_write_Byte(I2C_0,Address);

			I2C_wait(I2C_0);
			I2C_get_ACK(I2C_0);

			I2C_repeted_Start(I2C_0);
			I2C_write_Byte(I2C_0,0xDF);
			I2C_wait(I2C_0);
			I2C_get_ACK(I2C_0);

			I2C_TX_RX_Mode( I2C_0,  DISABLE);
			I2C_NACK(I2C_0);

			dataFromRTC = I2C_read_Byte(I2C_0);
			I2C_wait(I2C_0);

			I2C_stop(I2C_0);

			dataFromRTC = I2C_read_Byte(I2C_0);
			delay(4500);
			return dataFromRTC;
}

void RTC_writeData(uint8 Address, uint8 Data){
	I2C_TX_RX_Mode( I2C_0, ENABLE);

	 	I2C_start(I2C_0);

		I2C_write_Byte(I2C_0,0xDE);
		I2C_wait(I2C_0);
		I2C_get_ACK(I2C_0);

		I2C_write_Byte(I2C_0,Address);
		I2C_wait(I2C_0);
		I2C_get_ACK(I2C_0);

		I2C_write_Byte(I2C_0,Data);
		I2C_wait(I2C_0);
		I2C_get_ACK(I2C_0);
		I2C_stop(I2C_0);
		delay(650);
}


sint8 * RTC_get_String_Date(){
	uint8 Days = RTC_get_Day();
	uint8 Month = RTC_get_Month();
	uint8 Year =RTC_get_Year();
	DateValue[0] = (Days & MASK_UNIT);
	DateValue[1] = (Days & MASK_TENS);
	DateValue[2] = '/';
	DateValue[3] = (Month & MASK_UNIT);
	DateValue[4] = (Month & MASK_TENS);
	DateValue[5] = '/';
	DateValue[6] = (Year & MASK_UNIT);
	DateValue[7] = (Year & MASK_TENS);
	return DateValue[0];
}

sint8 * RTC_get_String_Hour(){
	uint8 Seconds = RTC_get_Seconds();
	uint8 Minutes = RTC_get_Minutes();
	uint8 Hours = RTC_get_Hour();
	HourValue[7] = (Seconds & MASK_UNIT);
	HourValue[6] = (Seconds & MASK_TENS);
	HourValue[5] = ':';
	HourValue[4] = (Minutes & MASK_UNIT);
	HourValue[3] = (Minutes & MASK_TENS);
	HourValue[2] = ':';
	HourValue[1] = (Hours & MASK_UNIT);
	HourValue[0] = (Hours & MASK_TENS);
	return HourValue;
}

void RTC_set_Hour(uint8*  character){
	uint8 value = BCDtoBinary(character);
	RTC_writeData(HOURS_ADDRESS,value);
}

void RTC_set_Minutes(uint8*  character){
	uint8 value = BCDtoBinary(character);
	RTC_writeData(MINUTES_ADDRESS,value);
}

void RTC_set_Day(uint8* character){
	uint8 value = BCDtoBinary(character);
	RTC_writeData(DAYS_ADDRESS,value);
}

void RTC_set_Month(uint8* character){
	uint8 value = BCDtoBinary(character);
	RTC_writeData(MONTHS_ADDRESS,value);
}

void RTC_set_Year(uint8* character){
	uint8 value = BCDtoBinary(character);
	RTC_writeData(YEARS_ADDRESS,value);
}

void RTC_changeFormat(FormatType format){
	uint8 Hours = RTC_get_Hour();
	uint8 seconds = RTC_get_Seconds();
	if(H24 == format){
		FormatFlag = FALSE;
	}else{
		FormatFlag = TRUE;
	}

	RTC_writeData(SECONDS_ADDRESS, FALSE);
	if(TRUE == FormatFlag){
		if(Hours > 12){
			RTC_writeData(HOURS_ADDRESS, H12_24_MASK | AM_FM_MASK | (Hours-0x12));
		}else{
			RTC_writeData(HOURS_ADDRESS, H12_24_MASK );
		}
	}else{
		if(TRUE == ((Hours&AM_FM_MASK)>>AM_FM_SHIFT)){
			RTC_writeData(HOURS_ADDRESS, ((Hours&~(H12_24_MASK | AM_FM_MASK))+0x12));
		}else{
			RTC_writeData(HOURS_ADDRESS, Hours);
		}
	}
	RTC_writeData(SECONDS_ADDRESS, DEFAULT_SECONDS | seconds);
}


