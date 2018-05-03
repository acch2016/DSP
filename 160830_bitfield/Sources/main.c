/*
 * main implementation: use this 'C' sample to create your own application
 *
 */
#include "derivative.h" /* include peripheral declarations */
#include "DataTypeDefinitions.h"


int main(void)
{
	uint16 inputPort;
	typedef union {
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

	myData portDBits = {0};


	SIM_SCGC5 = 0x1200;

	PORTD_PCR0 = PORT_PCR_MUX(1);
	PORTD_PCR1 = PORT_PCR_MUX(1);
	PORTD_PCR2 = PORT_PCR_MUX(1);
	PORTD_PCR3 = PORT_PCR_MUX(1);
	PORTD_PCR4 = PORT_PCR_MUX(1);
	PORTD_PCR5 = PORT_PCR_MUX(1);

	GPIOD_PDDR =0x3F;

	PORTA_PCR1 = PORT_PCR_MUX(1);
	PORTA_PCR1 |= 0x03;
	GPIOA_PDDR =0;



	for(;;) {

		inputPort = GPIOA_PDIR;
		inputPort = inputPort & 0x02;
		if(!inputPort)
		{
			portDBits.allBits = 0xFF;
			GPIOD_PDOR = portDBits.allBits;
			portDBits.bitField.bit0 = 0;
			GPIOD_PDOR = portDBits.allBits;
			portDBits.bitField.bit1 = BIT_OFF;
			GPIOD_PDOR = portDBits.allBits;
			portDBits.bitField.bit2 = BIT_OFF;
			GPIOD_PDOR = portDBits.allBits;
			portDBits.bitField.bit3 = BIT_OFF;
			portDBits.allBits = 0;
			GPIOD_PDOR = portDBits.allBits;
		}


	}// end for

}// end main
