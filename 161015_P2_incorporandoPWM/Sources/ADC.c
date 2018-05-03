/*
 * ADC.c
 *
 *  Created on: 08/10/2016
 *      Author: Alexis
 */

#include "ADC.h"
#define NUM_SAMPLE 30
#define TEMP_VALUE 200

uint8 Mean_counter=0;
float Mean_value;
uint32 Adding_counter;

void ADC_Configuration(){
		SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK;		/*Enable the ADC0 Clock*/

		ADC0_CFG1 |= ADC_CFG1_MODE(3);			/*16bits ADC*/
		ADC0_SC1A |= ADC_SC1_ADCH(31);			/*Disable the module, ADCH = 1111 */
}

float Read_Data(){
		ADC0_SC1A = 1 & ADC_SC1_ADCH_MASK; 	//Write to SC1A to start conversion
		while(ADC0_SC2 & ADC_SC2_ADACT_MASK);  			//Conversion in progress
		while(!(ADC0_SC1A & ADC_SC1_COCO_MASK));			//Until conversion complete
		Mean_counter++;
		Adding_counter += ADC0_RA;
		if(NUM_SAMPLE == Mean_counter){
			Mean_value = (Adding_counter/NUM_SAMPLE)/TEMP_VALUE;
			Mean_counter = 0;
			Adding_counter = 0;
		}
		return Mean_value;
}


