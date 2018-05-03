/*
 * ADC.c
 *
 *  Created on: 08/10/2016
 *      Author: Alexis
 */

#include "ADC.h"

static uint8 Mean_counter=0;
static float Mean_value = 0.0f;
static uint32 Adding_counter;
static  uint8 FormatFlag = FALSE;
static uint8 Alarm = 35;

void ADC_Configuration(){
		SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK;		/*Enable the ADC0 Clock*/

		ADC0_CFG1 |= ADC_CFG1_MODE(3);			/*16bits ADC*/
		ADC0_SC1A |= ADC_SC1_ADCH(31);			/*Disable the module, ADCH = 1111 */

		GPIO_pinControlRegisterType pinControlRegister = GPIO_MUX1;
		GPIO_pinControlRegister(GPIOC, BIT3, &pinControlRegister);
		GPIO_dataDirectionPIN(GPIOC,GPIO_OUTPUT, BIT3);
		GPIO_setPIN(GPIOC, BIT3);

}

float Read_Data(){
		ADC0_SC1A = 1 & ADC_SC1_ADCH_MASK; 	//Write to SC1A to start conversion
		while(ADC0_SC2 & ADC_SC2_ADACT_MASK);  			//Conversion in progress
		while(!(ADC0_SC1A & ADC_SC1_COCO_MASK));			//Until conversion complete
		Mean_counter++;
		Adding_counter += ADC0_RA;
		if(NUM_SAMPLE == Mean_counter){
			Mean_value = (Adding_counter/NUM_SAMPLE)/TEMP_VALUE;
			Mean_counter = FALSE;
			Adding_counter = FALSE;
		}
		return Mean_value;
}

uint8 FormatFlagValue(){
	return FormatFlag;
}

void FormatFlagModifier(uint8 State){
	FormatFlag = State;
}

uint8 AlarmValue(){
	return Alarm;
}

void AlarmValueModifier(sint8 value){
	Alarm = Alarm + value;
}

void AlarmModule(){
	if(Mean_value >= Alarm){
		GPIO_clearPIN(GPIOC, BIT3);
	}else{
		GPIO_setPIN(GPIOC, BIT3);
	}
}
