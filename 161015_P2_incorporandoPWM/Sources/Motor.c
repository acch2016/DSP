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
void motorConfig(){

	GPIO_pinControlRegisterType pinControlRegister = PORT_PCR_MUX(0x3);

	/**Para la señal PWM que controla la velocidad del motor usaremos puerto B*/
	GPIO_clockGating(GPIOB);
	GPIO_pinControlRegister(GPIOB, BIT12, &pinControlRegister);

	/**Para controlar el motor usaremos el FlexTimer configurado de la siguiente forma*/

	/**When write protection is enabled (WPDIS = 0), write protected bits cannot be written.
	 * When write protection is disabled (WPDIS = 1), write protected bits can be written.*/
	FTM_MODE(FTM_1,FLEX_TIMER_WPDIS);

	/**Assigning a default value for modulo register*/
	FTM_MOD(FTM_1, PWM_MOD_VALUE);
	/**Selects the Edge-Aligned PWM mode mode*/
	FTM_C0SC(FTM_1, FLEX_TIMER_MSB);
	FTM_C0SC(FTM_1, FLEX_TIMER_ELSB);

}
void MotorEnable(){
	FTM_Stat_Control(FTM_1,FLEX_TIMER_CLKS_1,ENABLE);
	FTM_Stat_Control(FTM_1,FLEX_TIMER_PS_128,ENABLE);
}
void MotorDisable(){
	FTM_Stat_Control(FTM_1,~FLEX_TIMER_CLKS_3,DISABLE);

}
void Mod_DutyCycle(sint16 channelValue) {

FTM_updateCHValue(FTM_1,channelValue);

}



void MotorControler() {
	uint16 realDutyCycle;
	float temperature= temp_value();
	if (referenceTemp < temperature) {
		uint8 diference = ((temperature - referenceTemp)/2);
		dutyCycle = dutyCycle +  multiplierDutyCycle*(diference);
		if(dutyCycle>100) dutyCycle = 100;
	}
	if (referenceTemp >= temperature) {
		uint8 diference = ((referenceTemp - temperature)/2);
		dutyCycle = dutyCycle -  multiplierDutyCycle*(diference);
		if(dutyCycle<100) dutyCycle = 0;
	}
	realDutyCycle = 65536*(dutyCycle*0.1);
	FTM_updateCHValue(FTM_1,realDutyCycle);
}
