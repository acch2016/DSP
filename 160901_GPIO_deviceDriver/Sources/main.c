/**
	\file
	\brief
		This is the starter project for Doxygen projects

	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	25/07/2015
	\todo
	    The device driver for the GPIO.
 */


/**Include for register definition in the K64*/
#include "MK64F12.h"
/**Header for data types definitions*/
#include "DataTypeDefinitions.h"
/**Header for GPIO Device Driver*/
#include "GPIO.h"

/**This is a prototype function to create a delay using a for-loop*/
void delay(uint16 delay);

int main(void)
{
	/**Definition of a bitfield*/
	typedef union
	{
		uint8 allBits;
		struct{
			uint8 bit0 :1;
			uint8 bit1 :1;
			uint8 bit2 :1;
			uint8 bit3 :1;
			uint8 bit4 :1;
			uint8 bit5 :1;
		}bitField;
	} myData;

	/**Variable declaration of myData type*/
	myData portDBits = {0};
	/**Variable to capture the input value*/
	uint32 inputValue = 0;

	/**Activating the GPIOD and GPIOC clock gating*/
	SIM_SCGC5 = 0x1800;

	/**Pin control configuration of GPIOD pin0 and pin6 as GPIO by using a special macro contained in Kinetis studio in the MK64F12. h file*/
	PORTD_PCR0 = PORT_PCR_MUX(1);
	PORTD_PCR1 = PORT_PCR_MUX(1);
	PORTD_PCR2 = PORT_PCR_MUX(1);
	PORTD_PCR3 = PORT_PCR_MUX(1);
	PORTD_PCR4 = PORT_PCR_MUX(1);
	PORTD_PCR5 = PORT_PCR_MUX(1);
	/**GPIOA pin control configuration*/
	PORTC_PCR6 = PORT_PCR_MUX(1)|0x03;

	/**Assigns a safe value to GPIOD*/
	GPIOD_PDOR =0x00;

	/**Configures GPIOD pin0-pin5 as output*/
	GPIOD_PDDR =0x3F;
	/**Configures GPIOC pin6 as input*/
	GPIOC_PDDR = 0;

	for(;;) {
		/**Reads all the GPIOC*/
		inputValue = GPIOC_PDIR;
		/**Masks the GPIOC in the bit of interest*/
		inputValue = inputValue & 0x40;
		/**Note that the comparison is not inputValur == False, because it is safer if we switch the arguments*/
		if(FALSE == inputValue)
		{
			/**Assigns all the bitfield*/
			portDBits.allBits = 0xFF;
			GPIOD_PDOR = portDBits.allBits;
			delay(65000);
			/**Assigns only one bit in the bitfield*/
			portDBits.bitField.bit0 = 0;
			/**Assigns all the bitfield to the GPIOD output port*/
			GPIOD_PDOR = portDBits.allBits;
			delay(65000);
			portDBits.bitField.bit1 = BIT_OFF;
			GPIOD_PDOR = portDBits.allBits;
			delay(65000);
			portDBits.bitField.bit2 = BIT_OFF;
			GPIOD_PDOR = portDBits.allBits;
			delay(65000);
			portDBits.bitField.bit3 = BIT_OFF;
			GPIOD_PDOR = portDBits.allBits;
			delay(65000);
			portDBits.bitField.bit4 = BIT_OFF;
			GPIOD_PDOR = portDBits.allBits;
			delay(65000);
			portDBits.bitField.bit5 = BIT_OFF;
			GPIOD_PDOR = portDBits.allBits;
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
