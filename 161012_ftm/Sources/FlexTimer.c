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


typedef enum {
	PRIMER_VALOR,
	SEGUNDO_VALOR
} ValorDefinitionType;

/** Variable to contain the FTM0 counter value*/
volatile float cntTimerValue = 0.0f;
volatile float cntTimerValue2 = 0.0f;

volatile uint8 flag = 0;
float period = 0.0f;
float frequency = 0.0f;

void FTM0_IRQHandler() {

	FTM0_C0SC &= ~FLEX_TIMER_CHF;

	if (PRIMER_VALOR == flag) {
		cntTimerValue = (float) FTM0_C0V;
		flag++;
	} else if (SEGUNDO_VALOR == flag) {
		cntTimerValue2 = (float) FTM0_C0V;

		freq_per();

		flag = 0;
	}

}
void freq_per() {
	period = ((cntTimerValue2 - cntTimerValue) * (1.0 / FTM_FQ));
	frequency = (1.0 / period);

}
void FTM_Init() {
	/**Clock gating for FlexTimer*/
	SIM_SCGC6 |= FLEX_TIMER_0_CLOCK_GATING;

	/**Apagar el registro. Apagar todos los timers*/
	FTM0_SC = 0x00;

	/**When write protection is enabled (WPDIS = 0), write protected bits cannot be written. 
	 * When write protection is disabled (WPDIS = 1), write protected bits can be written.*/
	FTM0_MODE |= FLEX_TIMER_WPDIS;

	FTM0_COMBINE &= ~(FTM_COMBINE_DECAPEN0_MASK | FTM_COMBINE_COMBINE0_MASK);

	/**Channel Interrupt Enable / Enables channel interrupts*/
	FTM0_C0SC |= FTM_CnSC_CHIE_MASK;

	/**Selects the FTM behavior in BDM mode.In this case in functional mode*/
	FTM0_CONF |= FTM_CONF_BDMMODE(3);

	/**Configure FlexTimer in INPUT CAPTURE*/
	FTM0_C0SC |= FTM_CnSC_ELSA_MASK;

	/**Select clock source and prescaler*/
	FTM0_SC |= FLEX_TIMER_CLKS_1 | FLEX_TIMER_PS_2;
}

