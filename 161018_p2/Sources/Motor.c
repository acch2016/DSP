/*
 * Motor.c
 *
 *  Created on: 09/10/2016
 *      Author: Alexis
 */

#include "Motor.h"
#include "DataTypeDefinitions.h"
#include "MK64F12.h" /* include peripheral declarations */
#include "GPIO.h"
#include "FlexTimer.h"
#include "NVIC.h"

uint16 channelValue=0;
uint8 referenceTemp = 28;
uint8 multiplierDutyCycle = 15;
sint16 dutyCycle = 80;
sint16 manualDutyCycle = 50;
uint16 realDutyCycle;
uint8 flagStateMotor = FALSE;

void MotorEnable(){
	FTM_Stat_Control(FTM_2,FLEX_TIMER_CLKS_1,ENABLE);
	FTM_Stat_Control(FTM_2,FLEX_TIMER_PS_128,ENABLE);
}
void MotorDisable(){
	FTM_updateCHValue(FTM_2,0);
	delay(1000);
	FTM_Stat_Control(FTM_2,~FLEX_TIMER_CLKS_3,DISABLE);

}
void Mod_DutyCycle(sint16 channelValue) {

FTM_updateCHValue(FTM_2,channelValue);

}

void motorConfig(){

	GPIO_pinControlRegisterType pinControlRegister = PORT_PCR_MUX(0x3);
	uint16 duty = dutyCycle*0.01*0x00FF;
	/**Para la señal PWM que controla la velocidad del motor usaremos puerto B*/
	GPIO_clockGating(GPIOB);
	GPIO_pinControlRegister(GPIOB, BIT18, &pinControlRegister);
	Mod_DutyCycle(duty);

}
void MotorControler() {
if(FALSE == flagStateMotor){
	sint16 temperature= (sint16)temp_value();
	if (referenceTemp < temperature) {
		sint8 diference = ((temperature - referenceTemp)/2);
		realDutyCycle = dutyCycle +  multiplierDutyCycle*(diference);
		if(realDutyCycle>100) realDutyCycle = 100;
	}
	if (referenceTemp >= temperature) {
		uint8 diference = ((referenceTemp - temperature)/2);
		realDutyCycle = dutyCycle -  multiplierDutyCycle*(diference);
		if(realDutyCycle<0) realDutyCycle = 0;
	}
	realDutyCycle = 0x00FF*(realDutyCycle*0.01);
	FTM_updateCHValue(FTM_2,realDutyCycle);
}else{
	realDutyCycle = manualDutyCycle;
	realDutyCycle = 0x00FF*(realDutyCycle*0.01);
	FTM_updateCHValue(FTM_2,realDutyCycle);
}
}

uint8 manualDutyCycleValue(){
	return manualDutyCycle;
}

void manualDutyCycleModifier(sint8 value){
	manualDutyCycle += value;
	if(manualDutyCycle > 100) {
		manualDutyCycle = 100;
	}
	else if(manualDutyCycle<0){
		manualDutyCycle = 0;
	}

}

uint8 flagStateMotorState(){
	return flagStateMotor;
}

void flagStateMotorModifier(uint8 State){
	flagStateMotor = State;
}

uint16 DutyCycleValue(){
	return ((realDutyCycle+1)*100/0x00FF);
}

uint8 multiplierDutyCycleValue(){
	return multiplierDutyCycle;
}

void multiplierDutyCycleModifier(sint8 value){
	multiplierDutyCycle += value;
	if(multiplierDutyCycle > 100) {
		multiplierDutyCycle = 100;
	}
	else if(multiplierDutyCycle<0){
		multiplierDutyCycle = 0;
	}
}
