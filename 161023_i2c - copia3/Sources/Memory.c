/*
 * Memory.c
 *
 *  Created on: 30/10/2016
 *      Author: Alexis
 */


#include "Memory.h"
#define BDL_MASK	0xFF
#define BDH_MASK	0xFF00
#define BDH_SHIFT	8

uint8 Data[100];

uint8 * Memory_Read(uint16 Address, uint8 numBytes){

	uint8 ByteCounter;
	uint8 ABDL = (Address&BDL_MASK);
	uint8 ABDH = ((Address&BDL_MASK)>>BDH_SHIFT);
	I2C_TX_RX_Mode( I2C_0, ENABLE);

	I2C_start(I2C_0);
	delay(300);

	I2C_write_Byte(I2C_0,0xA0);
	I2C_wait(I2C_0);
	I2C_get_ACK(I2C_0);

	I2C_write_Byte(I2C_0,ABDH);
	I2C_wait(I2C_0);
	I2C_get_ACK(I2C_0);

	I2C_write_Byte(I2C_0,ABDL);
	I2C_wait(I2C_0);
	I2C_get_ACK(I2C_0);

	I2C_repeted_Start(I2C_0);
	I2C_write_Byte(I2C_0,0xA1);
	I2C_wait(I2C_0);
	I2C_get_ACK(I2C_0);

	I2C_TX_RX_Mode( I2C_0,  DISABLE);

	for(ByteCounter = 0; ByteCounter < numBytes; ++ByteCounter){
		I2C_get_ACK(I2C_0);
		Data[Address + ByteCounter]= I2C_read_Byte(I2C_0);
		I2C_wait(I2C_0);
		Data[Address + ByteCounter]= I2C_read_Byte(I2C_0);
	}
	I2C_NACK(I2C_0);
	I2C_stop(I2C_0);


	delay(4500);
	return Data;
}

void Memory_Write(uint16 Address, uint8 * data){
	uint8 ABDL = (Address&BDL_MASK);
	uint8 ABDH = ((Address&BDL_MASK)>>BDH_SHIFT);
	I2C_TX_RX_Mode( I2C_0, ENABLE);

	I2C_start(I2C_0);

	I2C_write_Byte(I2C_0,0xA0);
	I2C_wait(I2C_0);
	I2C_get_ACK(I2C_0);

	I2C_write_Byte(I2C_0,ABDH);
	I2C_wait(I2C_0);
	I2C_get_ACK(I2C_0);

	I2C_write_Byte(I2C_0,ABDL);
	I2C_wait(I2C_0);
	I2C_get_ACK(I2C_0);
	while(*data){
		I2C_write_Byte(I2C_0,*data++);
		I2C_wait(I2C_0);
		I2C_get_ACK(I2C_0);

	}

	I2C_stop(I2C_0);
	delay(650);
}
