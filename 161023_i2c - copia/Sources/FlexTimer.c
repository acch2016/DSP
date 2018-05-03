/**
	\file
	\brief
		This is the starter file of FlexTimer.
		In this file the FlexTimer is configured in overflow mode.
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	7/09/2014
	\todo
	    Add configuration structures.
 */


#define FTM_FQ 10500000.0

#include "FlexTimer.h"

//uint8 hola = FALSE;

volatile uint32* FTMx_SC[3]={&FTM0_SC, &FTM1_SC, &FTM2_SC};
volatile uint32* FTMx_MODE[3]={&FTM0_MODE, &FTM1_MODE, &FTM2_MODE};
volatile uint32* FTMx_MOD[3]={&FTM0_MOD, &FTM1_MOD, &FTM2_MOD};
volatile uint32* FTMx_C0SC[3]={&FTM0_C0SC, &FTM1_C0SC, &FTM2_C0SC};
volatile uint32* FTMx_CONF[3]={&FTM0_CONF, &FTM1_CONF, &FTM2_CONF};
volatile uint32* FTMx_COMBINE[3] = {&FTM0_COMBINE, &FTM1_COMBINE, &FTM2_COMBINE};
volatile sint16* FTMx_C0V[3] = {&FTM0_C0V, &FTM1_C0V, &FTM2_C0V};

typedef enum {
	PRIMER_VALOR,
	SEGUNDO_VALOR,
}ValorDefinitionType;

/** Variable to contain the FTM0 counter value*/
volatile float cntTimerValue = 0.0f;
volatile float cntTimerValue2 = 0.0f;
volatile uint8 flag = 0;
 float period = 0.0f;
 float  frequency = 0.0f;
 float tempValue = 0.0f;


 void freq_per(){
	 	 	 if(cntTimerValue>cntTimerValue2){
	 	 		 period = (65536-cntTimerValue+cntTimerValue2)*(1.0/FTM_FQ);
	 	 	 }else{
	      		period=(cntTimerValue2-cntTimerValue)*(1.0/FTM_FQ);
	 	 	 }

 			frequency=(1.0/period);

 }

void FTM0_IRQHandler(){

	FTM0_C0SC &= ~FLEX_TIMER_CHF;

	if (PRIMER_VALOR == flag){
		cntTimerValue = (float)FTM0_C0V;
		flag++;
	} else if (SEGUNDO_VALOR == flag) {
		cntTimerValue2 = (float)FTM0_C0V;

		freq_per();

		flag = 0;
	}

}

void FTM2_IRQHandler(){
	FTM2_SC &= ~FLEX_TIMER_TOF;
	GPIO_tooglePIN(GPIOB,BIT18);
}

void FTM1_IRQHandler(){

}


void FTM_ClockGating(FTMType FTM){
	switch(FTM){
	case FTM_0:
		SIM_SCGC6 |= FLEX_TIMER_0_CLOCK_GATING;
		break;
	case FTM_1:
		SIM_SCGC6 |= FLEX_TIMER_1_CLOCK_GATING;
		break;
	case FTM_2:
		SIM_SCGC6 |= FLEX_TIMER_2_CLOCK_GATING;
		break;
	}
}

void FTM_Stat_Control(FTMType FTM, uint32 mask, FTMState state) {
	if (ENABLE == state) {
		*FTMx_SC[FTM] |= mask;
	} else if (DISABLE == state) {
		*FTMx_SC[FTM] &= mask;
	}

}

void FTM_MODE(FTMType FTM, uint32 mask){
	if(FTM == FTM_2){
		FTM2_MODE &= ~FLEX_TIMER_FTMEN;
	}
	*FTMx_MODE[FTM] |= mask;

}

void FTM_MOD(FTMType FTM, uint32 mask){
	*FTMx_MOD[FTM] |= mask;
}

void FTM_C0SC(FTMType FTM, uint32 mask, FTMState state){
	if(FALSE == state){
	*FTMx_C0SC[FTM] |= mask;
	}else{
	*FTMx_C0SC[FTM] &= mask;
	}
}

void FTM_CONF(FTMType FTM, uint32 mask){
	*FTMx_CONF[FTM] |= mask;
}

void FTM_COMBINE(FTMType FTM, uint32 mask){
	*FTMx_COMBINE[FTM] &= mask;
}

void FTM_updateCHValue(FTMType FTM,uint16 channelValue)
{
	/**Assigns a new value for the duty cycle*/
	FTM2_C0V = channelValue;
}


void FTM_Init(const FTM_ConfigType * FTM_Config)
{
	FTM_ClockGating(FTM_Config->FTM_Channel);
	FTM_Stat_Control(FTM_Config->FTM_Channel, FTM_Config->FTM_SC_Mask, ENABLE);
	FTM_MODE(FTM_Config->FTM_Channel, FTM_Config->FTM_MODE_Mask);
	FTM_MOD(FTM_Config->FTM_Channel, FTM_Config->FTM_MOD_Mask);
	FTM_C0SC(FTM_Config->FTM_Channel, FTM_Config->FTM_C0SC_Mask,ENABLE);
	FTM_CONF(FTM_Config->FTM_Channel, FTM_Config->FTM_CONF_Mask);
}

float frecuency_value(){
	return frequency;
}

float temp_value(){

	return tempValue;
}

void clean_frecuency(){
	frequency = 0;
}

