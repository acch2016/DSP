/*

 * DAC.c

 *

 *  Created on: 21/09/2016

 *      Author: Andrea

 */

#include "MK64F12.h"

#include "DAC.h"





void DAC_Init(){


	SIM_SCGC2 |= SIM_SCGC2_DAC0_MASK;

	DAC0_C0 |= CMP_DACCR_DACEN_MASK;
	DAC0_C0 |= DAC_C0_DACRFS_MASK;

}

void DAC_DataRegister(uint32 data){

	DAC0_DAT0L = (data) & DAC_DATL_DATA0_MASK;
	DAC0_DAT0H = (data >> 8) & DAC_DATH_DATA1_MASK;

}

