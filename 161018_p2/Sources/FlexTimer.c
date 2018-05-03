/**
	\file
	\brief
		This is the starter file of FlexTimer.
		In this file the FlexTimer is configured in overflow mode, and in input capture mode.
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	7/09/2014
	\todo  configurar para más canales
	    Add configuration structures.
 */


#define FTM_FQ 10500000.0 /**Frecuencia del FTM debido a la fuente de reloj SYSTEM CLOCK/2*

#include "FlexTimer.h"

/**Arreglos globales de direcciones*/

volatile uint32* FTMx_SC[3]={&FTM0_SC, &FTM1_SC, &FTM2_SC};
volatile uint32* FTMx_MODE[3]={&FTM0_MODE, &FTM1_MODE, &FTM2_MODE};
volatile uint32* FTMx_MOD[3]={&FTM0_MOD, &FTM1_MOD, &FTM2_MOD};
volatile uint32* FTMx_C0SC[3]={&FTM0_C0SC, &FTM1_C0SC, &FTM2_C0SC};
volatile uint32* FTMx_CONF[3]={&FTM0_CONF, &FTM1_CONF, &FTM2_CONF};
volatile uint32* FTMx_COMBINE[3] = {&FTM0_COMBINE, &FTM1_COMBINE, &FTM2_COMBINE};
volatile sint16* FTMx_C0V[3] = {&FTM0_C0V, &FTM1_C0V, &FTM2_C0V};


/** Variable to contain the FTM0 counter value*/
volatile float cntTimerValue = 0.0f;
volatile float cntTimerValue2 = 0.0f;
volatile uint8 flag = 0;
 float period = 0.0f;
 float  frequency = 0.0f;
 float tempValue = 0.0f;

/**Función que hace el cálculo de la Frecuencia*/
 void freq_per(){
	 	 	 if(cntTimerValue>cntTimerValue2){
	 	 		 period = (65536-cntTimerValue+cntTimerValue2)*(1.0/FTM_FQ);
	 	 	 }else{
	      		period=(cntTimerValue2-cntTimerValue)*(1.0/FTM_FQ);
	 	 	 }

 			frequency=(1.0/period);

 }
/**Vector de interrupciones del FTM0 que se utiliza para el Frecuencímetro*/
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
/**Vector de interrupciones del FTM0 que no se utiliza*/
void FTM2_IRQHandler(){
	//FTM2_SC &= ~FLEX_TIMER_TOF;
	//GPIO_tooglePIN(GPIOB,BIT18);
}
/**de interrupciones del FTM0 que se utiliza para el ADC*/
void FTM1_IRQHandler(){
	FTM1_SC &= ~FLEX_TIMER_TOF;
	tempValue = Read_Data();
}

/**ClockGating del FTM*/
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
/**Función para configurar el Registro FTMx_SC*/
void FTM_Stat_Control(FTMType FTM, uint32 mask, FTMState state) {
	if (ENABLE == state) {
		*FTMx_SC[FTM] |= mask;
	} else if (DISABLE == state) {
		*FTMx_SC[FTM] &= mask;
	}

}
/**Función para configurar el Registro FTMx_MODE*/
void FTM_MODE(FTMType FTM, uint32 mask){
	if(FTM == FTM_2){
		FTM2_MODE &= ~FLEX_TIMER_FTMEN;
	}
	*FTMx_MODE[FTM] |= mask;

}
/**Función para configurar el Registro FTMx_MOD*/
void FTM_MOD(FTMType FTM, uint32 mask){
	*FTMx_MOD[FTM] |= mask;
}
/**Función para configurar el Registro FTMx_C0SC*/
void FTM_C0SC(FTMType FTM, uint32 mask, FTMState state){
	if(FALSE == state){
	*FTMx_C0SC[FTM] |= mask;
	}else{
	*FTMx_C0SC[FTM] &= mask;
	}
}
/**Función para configurar el Registro FTMx_CONF*/
void FTM_CONF(FTMType FTM, uint32 mask){
	*FTMx_CONF[FTM] |= mask;
}
/**Función para configurar el Registro FTMx_COMBINE*/
void FTM_COMBINE(FTMType FTM, uint32 mask){
	*FTMx_COMBINE[FTM] &= mask;
}
/**Función para actualizar el Registro CnV*/
void FTM_updateCHValue(FTMType FTM,uint16 channelValue)
{
	/**Assigns a new value for the duty cycle*/
	FTM2_C0V = channelValue;
}

/**Función de configuración del FTM. Accedes a las miembros de la estructura para guardar valores de configuración*/
void FTM_Init(const FTM_ConfigType * FTM_Config)
{
	FTM_ClockGating(FTM_Config->FTM_Channel);
	FTM_Stat_Control(FTM_Config->FTM_Channel, FTM_Config->FTM_SC_Mask, ENABLE);
	FTM_MODE(FTM_Config->FTM_Channel, FTM_Config->FTM_MODE_Mask);
	FTM_MOD(FTM_Config->FTM_Channel, FTM_Config->FTM_MOD_Mask);
	FTM_C0SC(FTM_Config->FTM_Channel, FTM_Config->FTM_C0SC_Mask,ENABLE);
	FTM_CONF(FTM_Config->FTM_Channel, FTM_Config->FTM_CONF_Mask);
}
/**En API menu.c se manda llamar frecuency_value() para mostrar frecuency en el display*/
float frecuency_value(){
	return frequency;
}
/**En API menu.c se manda llamar temp_value() para mostrar tempValue en el display*/
float temp_value(){

	return tempValue;
}
/**En API menu.c se manda llamar clean_frecuency() para resetar el valor de la frecuencia ya que te guarda valores basura mientras esta apagado el frecuencimetro*/
void clean_frecuency(){
	frequency = 0;
}

