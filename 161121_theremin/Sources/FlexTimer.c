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


#define FTM_FQ 30000000.0
#define CIEN_PUNTOS 148
#define DIEZ_MIL_ARREGLO 10000
#include "FlexTimer.h"

//array of frecuencies
uint16 frequency[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

float Amp[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

float step[16];



volatile uint32* FTMx_SC[4]={&FTM0_SC, &FTM1_SC, &FTM2_SC};
volatile uint32* FTMx_MODE[4]={&FTM0_MODE, &FTM1_MODE, &FTM2_MODE};
volatile uint32* FTMx_MOD[4]={&FTM0_MOD, &FTM1_MOD, &FTM2_MOD};
volatile uint32* FTMx_CONF[4]={&FTM0_CONF, &FTM1_CONF, &FTM2_CONF};
volatile uint32* FTMx_COMBINE[4] = {&FTM0_COMBINE, &FTM1_COMBINE, &FTM2_COMBINE};

volatile uint32* FTMx_CnV[4][8] =  {{&FTM0_C0V,&FTM0_C1V,&FTM0_C2V,&FTM0_C3V,&FTM0_C4V,&FTM0_C5V,&FTM0_C6V,&FTM0_C7V},
		{&FTM1_C0V,&FTM1_C1V},
		{&FTM2_C0V,&FTM2_C1V},
		{&FTM3_C0V,&FTM3_C1V,&FTM3_C2V,&FTM3_C3V,&FTM3_C4V,&FTM3_C5V,&FTM3_C6V,&FTM3_C7V}};

volatile uint32* FTMx_CnSC[4][8] = {{&FTM0_C0SC,&FTM0_C1SC,&FTM0_C2SC,&FTM0_C3SC,&FTM0_C4SC,&FTM0_C5SC,&FTM0_C6SC,&FTM0_C7SC},
		{&FTM1_C0SC,&FTM1_C1SC},
		{&FTM2_C0SC,&FTM2_C1SC},
		{&FTM3_C0SC,&FTM3_C1SC,&FTM3_C2SC,&FTM3_C3SC,&FTM3_C4SC,&FTM3_C5SC,&FTM3_C6SC,&FTM3_C7SC}};







/**VARIABLE COUNTERS*/

static float FTM0_0_counter = 0;
static float FTM0_1_counter =  0;
static float FTM0_2_counter =  0;
static float FTM0_3_counter =  0;
static float FTM0_4_counter =  0;
static float FTM0_5_counter =  0;
static float FTM0_6_counter =  0;
static float FTM0_7_counter =  0;
static float FTM0_8_counter =  0;
static float FTM0_9_counter =  0;
static float FTM0_10_counter =  0;
static float FTM0_11_counter =  0;
static float FTM0_12_counter =  0;
static float FTM0_13_counter =  0;
static float FTM0_14_counter =  0;
static float FTM0_15_counter =  0;

static volatile uint8 Range_counter = FALSE;
static volatile uint16 old_Counter_Channel = FALSE;
static volatile uint16 new_Counter_Channel = FALSE;
static volatile uint16 time_value;
static volatile uint16  echo_status;

void freq_per(){

}


void FTM0_IRQHandler(){

	FTM0_SC &=~(FLEX_TIMER_TOF);

	uint8 counter;
	for(counter = 0; counter < 15; counter++){
		step[counter] = frequency[counter]/4;
	}

	FTM0_0_counter=FTM0_0_counter+step[0];
	if( DIEZ_MIL_ARREGLO <= FTM0_0_counter ){
		FTM0_0_counter=FTM0_0_counter-10000;
	}

	//si asgreagamos mas lineas se desajusta la frecuencia


	FTM0_1_counter=FTM0_1_counter+step[1];
	if( DIEZ_MIL_ARREGLO <= FTM0_1_counter ){
		FTM0_1_counter=(FTM0_1_counter-10000);
	}

	FTM0_2_counter=FTM0_2_counter+step[2];
	if( DIEZ_MIL_ARREGLO <= FTM0_2_counter ){
		FTM0_2_counter=(FTM0_2_counter-10000);
	}

	FTM0_3_counter=FTM0_3_counter+step[3];
	if( DIEZ_MIL_ARREGLO <= FTM0_3_counter ){
		FTM0_3_counter=(FTM0_3_counter-10000);
	}

	FTM0_4_counter=FTM0_4_counter+step[4];
	if( DIEZ_MIL_ARREGLO <= FTM0_4_counter ){
		FTM0_4_counter=(FTM0_4_counter-10000);
	}

	FTM0_5_counter=FTM0_5_counter+step[5];
	if( DIEZ_MIL_ARREGLO <= FTM0_5_counter ){
		FTM0_5_counter=(FTM0_5_counter-10000);
	}

	FTM0_6_counter=FTM0_6_counter+step[6];
	if( DIEZ_MIL_ARREGLO <= FTM0_6_counter ){
		FTM0_6_counter=(FTM0_6_counter-10000);
	}
	FTM0_7_counter=FTM0_7_counter+step[7];
	if( DIEZ_MIL_ARREGLO <= FTM0_7_counter ){
		FTM0_7_counter=(FTM0_7_counter-10000);
	}

	FTM0_8_counter=FTM0_8_counter+step[8];
	if( DIEZ_MIL_ARREGLO <= FTM0_8_counter ){
		FTM0_8_counter=(FTM0_8_counter-10000);
	}

	FTM0_9_counter=FTM0_9_counter+step[9];
	if( DIEZ_MIL_ARREGLO <= FTM0_9_counter ){
		FTM0_9_counter=(FTM0_9_counter-10000);
	}

	FTM0_10_counter=FTM0_10_counter+step[10];
	if( DIEZ_MIL_ARREGLO <= FTM0_10_counter ){
		FTM0_10_counter=(FTM0_10_counter-10000);
	}

	FTM0_11_counter=FTM0_11_counter+step[11];
	if( DIEZ_MIL_ARREGLO <= FTM0_11_counter ){
		FTM0_11_counter=(FTM0_11_counter-10000);
	}

	FTM0_12_counter=FTM0_12_counter+step[12];
	if( DIEZ_MIL_ARREGLO <= FTM0_12_counter ){
		FTM0_12_counter=(FTM0_12_counter-10000);
	}
	FTM0_13_counter=FTM0_13_counter+step[13];
	if( FTM0_13_counter <= FTM0_13_counter ){
		FTM0_13_counter=(FTM0_13_counter-10000);
	}

	FTM0_14_counter=FTM0_14_counter+step[14];
	if( DIEZ_MIL_ARREGLO <= FTM0_14_counter ){
		FTM0_14_counter=(FTM0_14_counter-10000);
	}

	FTM0_15_counter=FTM0_15_counter+step[15];
	if( DIEZ_MIL_ARREGLO <= FTM0_15_counter ){
		FTM0_15_counter=(FTM0_15_counter-10000);
	}
	sine(Amp[0]*FTM0_0_counter,Amp[1]*FTM0_1_counter, Amp[2]*FTM0_2_counter, Amp[3]*FTM0_3_counter, Amp[4]*FTM0_4_counter, Amp[5]*FTM0_5_counter, Amp[6]*FTM0_6_counter, Amp[7]*FTM0_7_counter, Amp[8]*FTM0_8_counter, Amp[9]*FTM0_9_counter, Amp[10]*FTM0_10_counter, Amp[11]*FTM0_11_counter, Amp[12]*FTM0_12_counter, Amp[13]*FTM0_13_counter, Amp[14]*FTM0_14_counter, Amp[15]*FTM0_15_counter);
}

void FTM1_IRQHandler(){
	FTM1_SC &= ~FLEX_TIMER_TOF;
	sine( FTM0_0_counter,  FTM0_1_counter, FTM0_2_counter, FTM0_3_counter, FTM0_4_counter, FTM0_5_counter, FTM0_6_counter, FTM0_7_counter, FTM0_8_counter, FTM0_9_counter, FTM0_10_counter, FTM0_11_counter, FTM0_12_counter, FTM0_13_counter, FTM0_14_counter, FTM0_15_counter);
}



void FTM2_IRQHandler(){
	Range_counter ++;
	old_Counter_Channel = new_Counter_Channel;
	new_Counter_Channel = FTM2_C0V;
	if(Range_counter >= 2){
		if(old_Counter_Channel > new_Counter_Channel){
			time_value = (MAX_VALUE_16B - old_Counter_Channel) + new_Counter_Channel;
		}else{
			time_value = new_Counter_Channel - old_Counter_Channel;
		}
		old_Counter_Channel = FALSE;
		new_Counter_Channel = FALSE;
		Range_counter = FALSE;
		echo_status = TRUE;
	}
	FTM2_SC &= ~(FLEX_TIMER_TOF);
	FTM2_C0SC &= ~(FLEX_TIMER_CHF);
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
	case FTM_3:
		SIM_SCGC3 |= FLEX_TIMER_3_CLOCK_GATING;
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

void FTM_CnSC(FTMType FTM, FTMChannelType channel, uint32 mask, FTMState state){
	if(FALSE == state){
		*FTMx_CnSC[FTM][channel] |= mask;
	}else{
		*FTMx_CnSC[FTM][channel] &= mask;
	}
}

void FTM_CnV(FTMType FTM, FTMChannelType channel, uint32 mask){
	*FTMx_CnV[FTM][channel] = mask;

}


void FTM_CONF(FTMType FTM, uint32 mask){
	*FTMx_CONF[FTM] |= mask;
}

void FTM_COMBINE(FTMType FTM, uint32 mask){
	*FTMx_COMBINE[FTM] &= mask;
}

void FTM_updateCHValue(FTMType FTM,FTMChannelType channel, uint16 channelValue)
{
	/**Assigns a new value for the duty cycle*/
	*FTMx_CnV[FTM][channel] = channelValue;
}


void FTM_Init(const FTM_ConfigType * FTM_Config)
{
	FTM_ClockGating(FTM_Config->FTM);
	FTM_Stat_Control(FTM_Config->FTM, FTM_Config->FTM_SC_Mask, ENABLE);
	FTM_MODE(FTM_Config->FTM, FTM_Config->FTM_MODE_Mask);
	FTM_MOD(FTM_Config->FTM, FTM_Config->FTM_MOD_Mask);
	FTM_CnSC(FTM_Config->FTM,FTM_Config->FTM_Channel, FTM_Config->FTM_CnSC_Mask,ENABLE);
	FTM_CONF(FTM_Config->FTM, FTM_Config->FTM_CONF_Mask);
}

uint16 time_Value(){
	return time_value;
}

uint8 status_echo(){
	return echo_status;
}

void clear_echo(){
	echo_status = FALSE;
}

void set_echo(){
	echo_status = TRUE;
}

void clear_Range_Counter(){
	Range_counter = FALSE;
}

void write_Frequency(uint16 frecuency, uint8 partial){
	frequency[partial] = frecuency;
}

void Modify_Amp( uint8 armonic){
	uint8 counter;
	for(counter = 0; counter < 16; counter++){
		Amp[counter] = 0.5;
	}
	Amp[armonic] = TRUE;
}

