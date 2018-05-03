/**
	\file
	\brief
		This files show how to read inputs through masks.

	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	25/07/2015
	\todo
	    The device driver for the GPIO.
 */


/**Include for register definition in the K64*/
#include "MK64F12.h"
/**Header for data types definitions*/
#include "DataTypeDefinitions.h"

/**This is a prototype function to create a delay using a for-loop*/
void delay(uint16 delay);

int main(void)
{
	/**Variable to capture the input value*/
	uint32 inputValue = 0;

	/**Activating the GPIOB, GPIOC and GPIOE clock gating*/
	SIM_SCGC5 = 0x2C00;
	/**Pin control configuration of GPIOB pin22 and pin21 as GPIO*/
	PORTB_PCR21 = 0x00000100;
	PORTB_PCR22 = 0x00000100;
	/**Pin control configuration of GPIOC pin6 as GPIO with is pull-up resistor enabled*/
	PORTC_PCR6 = 0x00000103;
	/**Pin control configuration of GPIOE pin26 as GPIO*/
	PORTE_PCR26 = 0x00000100;
	/**Assigns a safe value to the output pin21 of the GPIOB*/
	GPIOB_PDOR = 0x00200000;
	/**Assigns a safe value to the output pin22 of the GPIOB*/
	GPIOB_PDOR |= 0x00400000;
	/**Assigns a safe value to the output pin26 of the GPIOE*/
	GPIOE_PDOR |= 0x04000000;

	GPIOC_PDDR &=~(0x40);
	/**Configures GPIOB pin21 as output*/
	GPIOB_PDDR = 0x00200000;
	/**Configures GPIOB pin22 as output*/
	GPIOB_PDDR |= 0x00400000;
	/**Configures GPIOE pin26 as output*/
	GPIOE_PDDR |= 0x04000000;

	for(;;) {
		/**Reads all the GPIOC*/
		inputValue = GPIOC_PDIR;
		/**Masks the GPIOC in the bit of interest*/
		inputValue = inputValue & 0x40;
		/**Note that the comparison is not inputValur == False, because it is safer if we switch the arguments*/
		if(FALSE == inputValue)
		{
			GPIOB_PDOR |= 0x00200000;/**Blue led off*/
			delay(65000);
			GPIOB_PDOR |= 0x00400000;/**Read led off*/
			delay(65000);
			GPIOE_PDOR |= 0x4000000;/**Green led off*/
			delay(65000);
			GPIOB_PDOR &= ~(0x00200000);/**Blue led on*/
			delay(65000);
			GPIOB_PDOR &= ~(0x00400000);/**Read led on*/
			delay(65000);
			GPIOE_PDOR &= ~(0x4000000);/**Green led on*/
			delay(65000);
			GPIOB_PDOR |= 0x00200000;/**Blue led off*/
			delay(65000);
			GPIOB_PDOR |= 0x00400000;/**Read led off*/
			delay(65000);
			GPIOE_PDOR |= 0x4000000;/**Green led off*/
			delay(65000);
		}
		}
    /* Never leave main */
    return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
void delay(uint16 delay)
{
	volatile uint16 counter;

	for(counter=delay; counter > 0; counter--)
	{
	}
}
