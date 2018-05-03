/**
	\file 
	\brief 
		This project shows how to configure FlexTimer in output compare mode. 
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	7/09/2014
	\todo
	    Add configuration structures.
 */

#include "DataTypeDefinitions.h"
#include "MK64F12.h" /* include peripheral declarations */
#include "GPIO.h"
#include "FlexTimer.h"
#include "NVIC.h"
//#include "GlobalFunctions.h"

/**
 * Output compare frequency = (bus clock)/(Prescaler(mod+1)).
 * Note that is the same frequency of the overflow flow.
 */
#include "stdio.h"
#include "MCG.h"
#define CLK_FREQ_HZ 50000000  /* CLKIN0 frequency */
#define SLOW_IRC_FREQ 32768	/*This is the approximate value for the slow irc*/
#define FAST_IRC_FREQ 4000000 /*This is the approximate value for the fast irc*/
#define EXTERNAL_CLOCK 0 /*It defines an external clock*/
#define PLL_ENABLE 1 /**PLL is enabled*/
#define PLL_DISABLE 0 /**PLL is disabled*/
#define CRYSTAL_OSC 1  /*It defines an crystal oscillator*/
#define LOW_POWER 0     /* Set the oscillator for low power mode */
#define SLOW_IRC 0 		/* Set the slow IRC */
#define CLK0_TYPE 0     /* Crystal or canned oscillator clock input */
#define PLL0_PRDIV 25    /* PLL predivider value */
#define PLL0_VDIV 30    /* PLL multiplier value*/

int main(void)
{

    int mcg_clk_hz;
    unsigned char modeMCG = 0;


    mcg_clk_hz=fei_fbi(SLOW_IRC_FREQ,SLOW_IRC);
    mcg_clk_hz=fbi_fbe(CLK_FREQ_HZ,LOW_POWER,EXTERNAL_CLOCK);
    mcg_clk_hz=fbe_pbe(CLK_FREQ_HZ,PLL0_PRDIV,PLL0_VDIV);
    mcg_clk_hz=pbe_pee(CLK_FREQ_HZ);//117.18 KHz ----->60 000 000

    modeMCG = what_mcg_mode();
	/** Configuration for pin 1 on port c. 
	 * Output compare is on option 4 in the pin control register*/
    SIM_SCGC5 |= GPIO_CLOCK_GATING_PORTC;
	PORTC_PCR1   = PORT_PCR_MUX(0x4);      

	/**Initialization of FlexTimer in output compare mode*/
	FTM_Init();
	NVIC_enableInterruptAndPriotity(FTM0_IRQ,PRIORITY_9);


	EnableInterrupts;/** Enabling Global interrupts with PRIMASK bit*/

	for(;;) {	

	   	
	}
	
	return 0;
}
