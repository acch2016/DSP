/*
 * I2C.c
 *
 *  Created on: 23/10/2016
 *      Author: Alexis
 */
#include "MK64F12.h"
#include "I2C.h"

volatile uint8* I2Cx_C1[3]={&I2C0_C1, &I2C1_C1, &I2C2_C1};
volatile uint8* I2Cx_S[3]={&I2C0_S, &I2C1_S, &I2C2_S};
volatile uint8* I2Cx_D[3]={&I2C0_D, &I2C1_D, &I2C2_D};

void I2C_clockChannel(I2C_ChannelType channel){
	switch(channel){
	case I2C_0:
		SIM_SCGC4 |= I2C0_CLOCK_GATING;
		break;
	case I2C_1:
		SIM_SCGC4 |= I2C1_CLOCK_GATING;
		break;
	case I2C_2:
		SIM_SCGC1 |= I2C2_CLOCK_GATING;
		break;
	}
}

uint8 I2C_busy(I2C_ChannelType channel){
	uint8 data = *I2Cx_D[channel];
	return ((data&I2Cx_BUS_STATE)>>BUS_BIT);
}

void I2C_MST_OrSLV_Mode(I2C_ChannelType channel, I2CState state){
	if(ENABLE == state){
		*I2Cx_C1[channel] |= I2Cx_MASTER_ENABLE;
	}else{
		*I2Cx_C1[channel] &= I2Cx_MASTER_ENABLE;
	}
}

void I2C_TX_RX_Mode(I2C_ChannelType channel, I2CState state){
	if(ENABLE == state){
		*I2Cx_C1[channel] |= I2Cx_TRANSMITE_ENABLE;
	}else{
		*I2Cx_C1[channel] &= I2Cx_TRANSMITE_ENABLE;
	}
}

void I2C_NACK(){

}

void I2C_repeted_Start(I2C_ChannelType channel){
	*I2Cx_C1[channel] |= I2Cx_REPEAT_START;
}

void I2C_write_Byte(I2C_ChannelType channel,uint8 data){
	*I2Cx_D[channel] = data;
}

uint8  I2C_read_Byte(){

}

void I2C_wait(){

}

uint16 I2C_get_ACK(){

}

void I2C_start(I2C_ChannelType channel){
	*I2Cx_C1[channel] |= I2Cx_ENABLE;
}

void I2C_stop(I2C_ChannelType channel){
	*I2Cx_C1[channel] &= I2Cx_ENABLE;
}

void I2C_init(I2C_ChannelType channel, uint32 systemClock, uint8 baudRate){

}


