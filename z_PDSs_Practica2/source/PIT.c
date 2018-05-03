///**
//	\file PIT.c
//	\brief Controla las interrupciones del timer PIT y configuraciones de este
//	\author Jose Luis Pizano & Alexis Andalón
//	\date	26/02/2016
// */
//

///**Llamada del header de este modulo*/
#include "PIT.h"
#include "fsl_pit.h"
#include "fsl_debug_console.h"

#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#define PIT_LED_HANDLER PIT0_IRQHandler
#define PIT_IRQ_ID PIT0_IRQn
/* Get source clock for PIT driver */
#define PIT_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_BusClk)
//#define LED_INIT() LED_RED_INIT(LOGIC_LED_ON)
//#define LED_TOGGLE() LED_RED_TOGGLE()


volatile bool pitIsrFlag = false;
static uint16_t samplingFrequency = 40000;

void PIT_LED_HANDLER(void)
{
    /* Clear interrupt flag.*/
    PIT_ClearStatusFlags(PIT, kPIT_Chnl_0, kPIT_TimerFlag);
    pitIsrFlag = true;
}



void PIT_init(){
	/* Structure of initialize PIT */
	pit_config_t pitConfig;
	/* Board pin, clock, debug console init */
	//BOARD_InitHardware();
	PIT_GetDefaultConfig(&pitConfig);
	/* Init pit module */
	PIT_Init(PIT, &pitConfig);
	/* Set timer period for channel 0 */
	PIT_SetTimerPeriod(PIT, kPIT_Chnl_0,USEC_TO_COUNT(get_PeriodUs(), PIT_SOURCE_CLOCK));
	/* Enable timer interrupts for channel 0 */
	PIT_EnableInterrupts(PIT, kPIT_Chnl_0, kPIT_TimerInterruptEnable);
	/* Enable at the NVIC */
	EnableIRQ(PIT_IRQ_ID);
	/* Start channel 0 */
	                                   //PRINTF("\r\nStarting channel No.0 ...");
	PIT_StartTimer(PIT, kPIT_Chnl_0);

}

void set_SamplingFrequency(uint16_t newSamplingFrequency){
	samplingFrequency = newSamplingFrequency;
	PIT_SetTimerPeriod(PIT, kPIT_Chnl_0,USEC_TO_COUNT(get_PeriodUs(), PIT_SOURCE_CLOCK));
}

uint16_t get_SamplingFrequency(){
	return samplingFrequency;
}

uint16_t get_PeriodUs(){
	uint16_t periodUs = 0;

	switch (samplingFrequency){
		case 10000:
			periodUs = 100;
			break;
		case 15000:
			periodUs = 67;
			break;
		case 20000:
			periodUs = 50;
			break;
		case 25000:
			periodUs = 40;
			break;
		case 30000:
			periodUs = 33;
			break;
		case 35000:
			periodUs = 29;
			break;
		case 40000:
			periodUs = 25;
			break;
		case 45000:
			periodUs = 22;
			break;
		case 50000:
			periodUs = 20;
			break;
		case 55000:
			periodUs = 18;
			break;
		case 60000:
			periodUs = 16;
			break;
		default:
			break;
	}

	return periodUs;
}
