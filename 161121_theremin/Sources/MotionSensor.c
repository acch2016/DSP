/*
 * MotionSensor.c
 *
 *  Created on: 21/11/2016
 *      Author: Alexis
 */

#include "MotionSensor.h"


static uint16 echo_status;
static uint16 value_Y[3];
static uint16 value_X[4];
static uint8 value_Yreal;
static uint8 value_Xreal;
static uint8 prom_EchoX = FALSE;
static uint8 prom_CounterX = FALSE;
static uint8 prom_EchoY = FALSE;
static uint8 prom_CounterY = FALSE;
static uint8 neg_CounterX = FALSE;
static uint8 frequencyX_Index = FALSE;
static uint8 AmpY_Index = FALSE;

void ConfigurationSensor(){
	GPIO_pinControlRegisterType pinControlRegister = GPIO_MUX1;
	GPIO_pinControlRegisterType pinControlRegisterInput = GPIO_MUX3;
	GPIO_clockGating(GPIOC);
	GPIO_clockGating(GPIOB);
	GPIO_clockGating(GPIOA);
	GPIO_pinControlRegister(GPIOB, BIT18, &pinControlRegisterInput);
	GPIO_pinControlRegister(GPIOC, BIT3, &pinControlRegister);
	GPIO_pinControlRegister(GPIOC, BIT5, &pinControlRegister);
	GPIO_pinControlRegister(GPIOC, BIT7, &pinControlRegister);
	GPIO_pinControlRegister(GPIOC, BIT2, &pinControlRegister);
	GPIO_pinControlRegister(GPIOC, BIT0, &pinControlRegister);
	GPIO_pinControlRegister(GPIOA, BIT2, &pinControlRegister);
	GPIO_pinControlRegister(GPIOC, BIT9, &pinControlRegister);
	GPIO_pinControlRegister(GPIOB, BIT23, &pinControlRegister);
	GPIO_pinControlRegister(GPIOC, BIT8, &pinControlRegister);
	GPIO_dataDirectionPIN(GPIOC, GPIO_OUTPUT, BIT3);
	GPIO_dataDirectionPIN(GPIOC, GPIO_OUTPUT, BIT2);
	GPIO_dataDirectionPIN(GPIOC, GPIO_OUTPUT, BIT5);
	GPIO_dataDirectionPIN(GPIOC, GPIO_OUTPUT, BIT7);
	GPIO_dataDirectionPIN(GPIOC, GPIO_OUTPUT, BIT0);
	GPIO_dataDirectionPIN(GPIOA, GPIO_OUTPUT, BIT2);
	GPIO_dataDirectionPIN(GPIOC, GPIO_OUTPUT, BIT9);
	GPIO_dataDirectionPIN(GPIOB, GPIO_OUTPUT, BIT23);
	GPIO_dataDirectionPIN(GPIOC, GPIO_OUTPUT, BIT8);
	GPIO_clearPIN(GPIOC,BIT3);
	GPIO_clearPIN(GPIOC,BIT2);
	GPIO_clearPIN(GPIOC,BIT5);
	GPIO_clearPIN(GPIOC,BIT7);
	GPIO_clearPIN(GPIOC,BIT0);
	GPIO_clearPIN(GPIOC,BIT9);
	GPIO_clearPIN(GPIOA,BIT2);
	GPIO_clearPIN(GPIOB,BIT23);
	GPIO_clearPIN(GPIOC,BIT8);
	static const FTM_ConfigType FTM2_Config={FTM_2,
			Channel0,
			FLEX_TIMER_0_CLOCK_GATING,
			FALSE,
			FLEX_TIMER_WPDIS,
			FALSE,
			FTM_CnSC_ELSB_MASK | FTM_CnSC_ELSA_MASK |FTM_CnSC_CHIE_MASK,
			FTM_CONF_BDMMODE(3),
			~(FTM_COMBINE_DECAPEN0_MASK | FTM_COMBINE_COMBINE0_MASK)};
	FTM_Init(&FTM2_Config);
}


uint16 readRange(SensorType Sensor){
	clear_echo();
	switch(Sensor){
	case SensorY_0:
		GPIO_clearPIN(GPIOC,BIT5);
		GPIO_clearPIN(GPIOC,BIT7);
		GPIO_clearPIN(GPIOC,BIT2);
		GPIO_clearPIN(GPIOC,BIT0);
		GPIO_clearPIN(GPIOC,BIT9);
		GPIO_clearPIN(GPIOA,BIT2);
		GPIO_clearPIN(GPIOB,BIT23);
		GPIO_clearPIN(GPIOC,BIT8);
		break;
	case SensorY_1:
		GPIO_setPIN(GPIOC,BIT5);
		GPIO_clearPIN(GPIOC,BIT7);
		GPIO_clearPIN(GPIOC,BIT2);
		GPIO_setPIN(GPIOC,BIT0);
		GPIO_clearPIN(GPIOC,BIT9);
		GPIO_clearPIN(GPIOA,BIT2);
		GPIO_clearPIN(GPIOB,BIT23);
		GPIO_clearPIN(GPIOC,BIT8);
		break;
	case SensorY_2:
		GPIO_clearPIN(GPIOC,BIT5);
		GPIO_setPIN(GPIOC,BIT7);
		GPIO_clearPIN(GPIOC,BIT2);
		GPIO_clearPIN(GPIOC,BIT0);
		GPIO_clearPIN(GPIOC,BIT9);
		GPIO_setPIN(GPIOA,BIT2);
		GPIO_clearPIN(GPIOB,BIT23);
		GPIO_clearPIN(GPIOC,BIT8);
		break;
	case SensorX_0:
		GPIO_setPIN(GPIOC,BIT5);
		GPIO_setPIN(GPIOC,BIT7);
		GPIO_clearPIN(GPIOC,BIT2);
		GPIO_clearPIN(GPIOC,BIT0);
		GPIO_clearPIN(GPIOC,BIT9);
		GPIO_clearPIN(GPIOA,BIT2);
		GPIO_clearPIN(GPIOB,BIT23);
		GPIO_setPIN(GPIOC,BIT8);
		break;
	case SensorX_1:
		GPIO_clearPIN(GPIOC,BIT5);
		GPIO_clearPIN(GPIOC,BIT7);
		GPIO_setPIN(GPIOC,BIT2);
		GPIO_clearPIN(GPIOC,BIT0);
		GPIO_setPIN(GPIOC,BIT9);
		GPIO_clearPIN(GPIOA,BIT2);
		GPIO_clearPIN(GPIOB,BIT23);
		GPIO_setPIN(GPIOC,BIT8);
		break;
	case SensorX_2:
		GPIO_setPIN(GPIOC,BIT5);
		GPIO_clearPIN(GPIOC,BIT7);
		GPIO_setPIN(GPIOC,BIT2);
		GPIO_clearPIN(GPIOC,BIT0);
		GPIO_clearPIN(GPIOC,BIT9);
		GPIO_clearPIN(GPIOA,BIT2);
		GPIO_setPIN(GPIOB,BIT23);
		GPIO_setPIN(GPIOC,BIT8);
		break;
	case SensorX_3:

		GPIO_clearPIN(GPIOC,BIT5);
		GPIO_setPIN(GPIOC,BIT7);
		GPIO_setPIN(GPIOC,BIT2);
		GPIO_clearPIN(GPIOC,BIT0);
		GPIO_setPIN(GPIOC,BIT9);
		GPIO_clearPIN(GPIOA,BIT2);
		GPIO_setPIN(GPIOB,BIT23);
		GPIO_setPIN(GPIOC,BIT8);
		break;

	}

	FTM2_CNTIN = FALSE;
	FTM2_CNT = FALSE;
	GPIO_setPIN(GPIOC,BIT3);
	PIT_delay(PIT_0, SYSTEM_CLOCK,PERIOD);

	FTM_Stat_Control(FTM_2, FLEX_TIMER_CLKS_1|FLEX_TIMER_PS_128, ENABLE);
	PIT0_Flag_edit();
	while(status_echo() == FALSE){
				if(FTM2_CNT > 10000){
					set_echo();
				}
	}
	echo_status = time_Value();
	FTM_Stat_Control(FTM_2, FLEX_TIMER_CLKS_1|FLEX_TIMER_PS_128, DISABLE);
	clear_Range_Counter();
	return echo_status;
}

void pos_Value(){
	uint8 counter_cycle;
		value_Y[0] = readRange(SensorY_0)/28;
		delay(1000);
		value_Y[1] = readRange(SensorY_1)/28;
		delay(1000);
		value_Y[2] = readRange(SensorY_2)/28;
		delay(1000);
		if((value_Y[0] <= value_Y[2]) && (value_Y[0] <= value_Y[1])){
			value_Yreal = value_Y[0];
		}else if((value_Y[1] <= value_Y[0]) && (value_Y[1] <= value_Y[2])){
			value_Yreal = value_Y[1];
		}else{
			value_Yreal = value_Y[2];
		}
		if(value_Yreal < 40 && value_Yreal > 0){
			if(prom_CounterX > 2){
				AmpY_Index = value_Yreal/16;
				Modify_Amp(AmpY_Index);
				prom_EchoX = FALSE;
				prom_CounterX = FALSE;
			}
			prom_EchoX += value_Yreal;
			prom_CounterX++;
		}
	value_X[0] = readRange(SensorX_0)/28;
	delay(1000);
	value_X[1] = readRange(SensorX_1)/28;
	delay(1000);
	value_X[2] = readRange(SensorX_2)/28;
	delay(1000);
	value_X[3] = readRange(SensorX_3)/28;
	if((value_X[0] <= value_X[2]) && (value_X[0] <= value_X[1])&&(value_X[0] <= value_X[3])){
		value_Xreal = value_X[0];
	}else if((value_X[1] <= value_X[0]) && (value_X[1] <= value_X[2]) && (value_X[1] <= value_X[3])){
		value_Xreal = value_X[1];
	}else if((value_X[2] <= value_X[0]) && (value_X[2] <= value_X[1]) && (value_X[2] <= value_X[3])){
		value_Xreal = value_X[2];
	}else{
		value_Xreal = value_X[3];
	}


//	if(value_Xreal < 30 && value_Xreal > 0){
//		if(prom_CounterY > 1){
//			write_Frequency( prom_EchoY*300/2,TRUE);
//			prom_EchoY = FALSE;
//			prom_CounterY = FALSE;
//		}
//		prom_EchoY += value_Yreal;
//		prom_CounterY++;
//	}else{
//		write_Frequency(FALSE,FALSE);
//	}

	if(value_Xreal < 30 && value_Xreal > 0){
		while(prom_CounterY > 2){
			counter_cycle = value_Xreal/15;
			while(counter_cycle == frequencyX_Index){
				if(frequencyX_Index > counter_cycle){
					write_Frequency(FALSE,frequencyX_Index);
					frequencyX_Index--;
				}else if(frequencyX_Index < counter_cycle){
					write_Frequency(FSMRange(),frequencyX_Index);
					frequencyX_Index++;
				}
			}
			prom_EchoY = FALSE;
			prom_CounterY = FALSE;
		}
		prom_EchoY += value_Yreal;
		prom_CounterY++;
	}else{
		neg_CounterX++;
		if(neg_CounterX > 2){
			write_Frequency(FALSE,frequencyX_Index);
			neg_CounterX = FALSE;
		}
	}
}
