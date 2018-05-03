/*
 * GlobalFunctions.c
 *
 *  Created on: Jun 22, 2014
 *      Author: Luis
 */

#include "GlobalFunctions.h"

void delay(uint16 delay)
{
	volatile int counter, counter2;
	
	for(counter2=16; counter2 > 0; counter2--)
	{
		for(counter=delay; counter > 0; counter--); 

	}
}

uint8 mcm(uint16 freqMay, uint16 freqmenor){

	cociente = (freqMay/freqmenor);

	freqMay / ((freqMay/freqmenor)-cociente);

}

