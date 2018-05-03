#include "GlobalFunctions.h"

void delay(uint16 delay)
{
	volatile int counter, counter2;
	
	for(counter2=16; counter2 > 0; counter2--)
	{
		for(counter=delay; counter > 0; counter--); 

	}
}

uint8 BCDtoBinary(uint8* character){
	uint8 result = FALSE;
	while(*character){
	result += (*character - 48);
	}
	return result;
}
