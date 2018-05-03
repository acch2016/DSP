#ifndef FLEXTIMER_H_
#define FLEXTIMER_H_

#include "MK64F12.h"
#include "DataTypeDefinitions.h"
#include "GPIO.h"


#define FLEX_TIMER_0_CLOCK_GATING 0x01000000
#define FLEX_TIMER_1_CLOCK_GATING 0x02000000
#define FLEX_TIMER_2_CLOCK_GATING 0x04000000

#define FLEX_TIMER_FAULTIE  0x80
#define FLEX_TIMER_FAULTM_0   0x00
#define FLEX_TIMER_FAULTM_1   0x20
#define FLEX_TIMER_FAULTM_2   0x40
#define FLEX_TIMER_FAULTM_3   0x60
#define FLEX_TIMER_CAPTEST  0x10
#define FLEX_TIMER_PWMSYNC  0x08
#define FLEX_TIMER_WPDIS    0x04
#define FLEX_TIMER_INIT     0x02
#define FLEX_TIMER_FTMEN    0x01

#define FLEX_TIMER_TOF     0x80
#define FLEX_TIMER_TOIE    0x40
#define FLEX_TIMER_CPWMS   0x20
#define FLEX_TIMER_CLKS_0  0x00
#define FLEX_TIMER_CLKS_1  0x08
#define FLEX_TIMER_CLKS_2  0x10
#define FLEX_TIMER_CLKS_3  0x18
#define FLEX_TIMER_PS_1    0x00
#define FLEX_TIMER_PS_2    0x01
#define FLEX_TIMER_PS_4    0x02
#define FLEX_TIMER_PS_8    0x03
#define FLEX_TIMER_PS_16    0x04
#define FLEX_TIMER_PS_32    0x05
#define FLEX_TIMER_PS_64    0x06
#define FLEX_TIMER_PS_128    0x07

#define FLEX_TIMER_PWMLOAD_CH0 0x01
#define FLEX_TIMER_PWMLOAD_CH1 0x02
#define FLEX_TIMER_PWMLOAD_CH2 0x04
#define FLEX_TIMER_PWMLOAD_CH3 0x08
#define FLEX_TIMER_PWMLOAD_CH4 0x10
#define FLEX_TIMER_PWMLOAD_CH5 0x20
#define FLEX_TIMER_PWMLOAD_CH6 0x40
#define FLEX_TIMER_PWMLOAD_CH7 0x80
#define FLEX_TIMER_LDOK        0x200


#define  FLEX_TIMER_DMA   0x01
#define  FLEX_TIMER_ELSA  0x04
#define  FLEX_TIMER_ELSB  0x08
#define  FLEX_TIMER_MSA   0x10
#define  FLEX_TIMER_MSB   0x20
#define  FLEX_TIMER_CHIE  0x40
#define  FLEX_TIMER_CHF   0x80

typedef enum{FTM_0,
			 FTM_1,
			 FTM_2,
}FTMType;

typedef enum{
	ENABLE,
	DISABLE,
}FTMState;

typedef struct
{
	FTMType FTM_Channel;
	uint32 FTM_ClockMask;
	uint32 FTM_SC_Mask;
	uint32 FTM_MODE_Mask;
	uint32 FTM_MOD_Mask;
	uint32 FTM_C0SC_Mask;
	uint32 FTM_CONF_Mask;
	uint32 FTM_COMBINE_Mask;

} FTM_ConfigType;


void FTM0_ISR(void);

void FTM_Init();

float frecuency_value();

void FTM_ClockGating(FTMType FTM);

void FTM_Stat_Control(FTMType FTM, uint32 mask,FTMState g);

void FTM_MODE(FTMType FTM, uint32 mask);

void FTM_MOD(FTMType FTM, uint32 mask);

void FTM_C0SC(FTMType FTM, uint32 mask, FTMState);

void FTM_CONF(FTMType FTM, uint32 mask);

void FTM_COMBINE(FTMType FTM, uint32 mask);

void FTM_updateCHValue(FTMType FTM, uint16 channelValue);

void FTM_Init(const FTM_ConfigType * FTM_Config);

float frecuency_value();

float temp_value();
void clean_frecuency();


#endif /* FLEXTIMER_H_ */
