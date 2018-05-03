/**
	\file
	\brief
		This project shows how works the priority in the NVIC using BASEPRI register.
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	27/07/2015
	\todo
 */

#include "MK64F12.h"
#include "GPIO.h"
#include "NVIC.h"

uint8 FlagPortC = FALSE;
uint8 FlagPortA = FALSE;
int main(void)
{

	uint8 portIn = 0;
	uint8 statePortC = 0;
	uint8 statePortA = 0;

	/**Activating the GPIOA, GPIOB and GPIOC clock gating*/
	SIM_SCGC5 = 0x00000200;
	SIM_SCGC5 |= 0x00000400;
	SIM_SCGC5 |= 0x00000800;

	/**Pin control configuration of GPIOB pin21 and pin21 as GPIO by using a special macro contained in Kinetis studio in the MK64F12. h file*/
	PORTB_PCR21 = PORT_PCR_MUX(1);
	PORTB_PCR22 = PORT_PCR_MUX(1);
	/**Pin control configuration of GPIOA pin4 as a GPIO with pull-up resistor and interrupt in falling edge*/
	PORTA_PCR4 = GPIO_MUX1|GPIO_PE|GPIO_PS|INTR_FALLING_EDGE;
	/**Pin control configuration of GPIOC pin6 as a GPIO with pull-up resistor and interrupt in falling edge*/
	PORTC_PCR6 = GPIO_MUX1|GPIO_PE|GPIO_PS|INTR_FALLING_EDGE;


	/**Assigns a safe value to the output pin21 of the GPIOB*/
	GPIOB_PDOR |= 0x00200000;/**Blue led off*/
	GPIOB_PDOR |= 0x00400000;/**Read led off*/

	/**Configures GPIOB pin21 as output*/
	GPIOB_PDDR = 0x00200000;
	/**Configures GPIOB pin22 as output*/
	GPIOB_PDDR |= 0x00400000;
	/**Configures GPIOC pin6 as input*/
	GPIOC_PDDR &=~(0x40);
	/**Sets the threshold for interrupts, if the interrupt has higher priority constant that the BASEPRI, the interrupt will not be attended*/
	NVIC_setBASEPRI_threshold(PRIORITY_9);
	/**Enables and sets a particular interrupt and its priority*/
	NVIC_enableInterruptAndPriotity(PORTC_IRQ,PRIORITY_10);
	/**Enables and sets a particular interrupt and its priority*/
	NVIC_enableInterruptAndPriotity(PORTA_IRQ,PRIORITY_5);

	EnableInterrupts;

    /* This for loop should be replaced. By default this loop allows a single stepping. */
    for (;;) {

    	if(TRUE == FlagPortC){
    		if(statePortC)
    		{
    			GPIOB_PDOR |= 0x00200000;/**Blue led off*/
    		}
    		else
    		{
    			GPIOB_PDOR &= ~(0x00200000);/**Blue led on*/
    		}
    		statePortC = !statePortC;
    		FlagPortC = FALSE;
    	}


    	if(TRUE == FlagPortA){
			if(statePortA)
			{
				GPIOB_PDOR |= 0x00400000;/**Read led off*/
			}
			else
			{
				GPIOB_PDOR &= ~(0x00400000);/**Read led on*/
			}
			statePortA = !statePortA;
			FlagPortA = FALSE;
		}



    }
    /* Never leave main */
    return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
