/*
 * ADC.c
 *
 *  Created on: 15/10/2016
 *      Author: alejandrocanale
 */

#include <MK64F12.h>
#include "DataTypeDefinitions.h"
#include "ADC.h"

volatile uint32* ADCx_CFG1[3]={&ADC0_CFG1, &ADC1_CFG1};
volatile uint32* ADCx_SC1A[3]={&ADC0_SC1A, &ADC1_SC1A};

/** It activate the clock gating*/
static void ADC_clk(ADC_ChannelType channel)
{
	switch(channel)/** Selecting the SPI for clock enabling*/
			{
			case ADC_0: /** SPI_0 is selected*/
				SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK;
				break;
			case ADC_1: /** SPI_1 is selected*/
				SIM_SCGC3 |= SIM_SCGC3_ADC1_MASK;
				break;

			default: /** all is selected */
				SIM_SCGC6=0xFFFFFFFF;
				SIM_SCGC3=0xFFFFFFFF;
			}// end switch
}
