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
	PIT_SetTimerPeriod(PIT, kPIT_Chnl_0,USEC_TO_COUNT(16U, PIT_SOURCE_CLOCK));
	/* Enable timer interrupts for channel 0 */
	PIT_EnableInterrupts(PIT, kPIT_Chnl_0, kPIT_TimerInterruptEnable);
	/* Enable at the NVIC */
	EnableIRQ(PIT_IRQ_ID);
	/* Start channel 0 */
	                                   //PRINTF("\r\nStarting channel No.0 ...");
	PIT_StartTimer(PIT, kPIT_Chnl_0);

}
