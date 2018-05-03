#include "GlobalFunctions.h"

void delay(uint16 delay)
{
	volatile int counter, counter2;
	
	for(counter2=16; counter2 > 0; counter2--)
	{
	for(counter=delay; counter > 0; counter--);

	}
}

uint8 BCDtoBinary(uint8 character[],uint8 numChar){
	uint8 result = FALSE;
	uint8 multiplier = 1;
	while(numChar > 0){
	result += (character[numChar-1] - 48)*multiplier;
	numChar--;
	multiplier*= 10;
	}
	return result;
}
