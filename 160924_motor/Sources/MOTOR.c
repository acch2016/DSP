/*
 * MOTOR.c
 *
 *  Created on: 24/9/2016
 *      Author: alejandrocanale
 */
#include "DataTypeDefinitions.h"
#include "MK64F12.h"
#include "MOTOR.h"
#include "PIT.h"
#include "GPIO.h"
#define systemClock 21000000
#define PERIOD1 1
#define PERIOD3 3
#define PERIOD4 4
#define FASE1 1
#define FASE2 2
#define FASE3 3
#define FASE4 4
#define LED1 18
#define LED2 19
#define MOTOR 0x1
//#define MUX 0x100
//#define MUXPEPU 0x103
#define SWITCH_2 6
#define SWITCH2_PRESSED 0

uint8 flag_sec_1=1;
uint8 flag_sec_2=1;





typedef enum {
	SEQUENCE1,
	SEQUENCE2,
	SEQUENCE3,
}StateDefinitionType;


typedef struct
{
	uint32 out;
	uint8 next[2];
}StateType;


void(*fptrSeq[3])(void)={sequence_1,sequence_2,sequence_3};



const StateType FineStateMachineMoore[3]=
{
		{SEQUENCE1,{SEQUENCE1, SEQUENCE2}},
		{SEQUENCE2,{SEQUENCE2, SEQUENCE3}},
		{SEQUENCE3,{SEQUENCE3, SEQUENCE1}}
};


StateDefinitionType currentState = SEQUENCE3;

GPIO_pinControlRegisterType pinControlRegister = GPIO_MUX1;
GPIO_pinControlRegisterType pinControlRegisterSwitch = GPIO_MUX1|GPIO_PE|GPIO_PS|INTR_FALLING_EDGE;

uint32 output=0,input=0;
uint8 currentState_flag=0;


void FSM_Motor() {

	currentState_flag = 0;

	currentState = FineStateMachineMoore[currentState].out;

	(*fptrSeq[currentState])(); //cambiar el 2. El índice lo indicará la función

	//	input = GPIO_readPORT(GPIOC);
	//	input &= (0x40);
	//	input = input ? 1 : 0;

	input=readFlag_PORTC();

	if (TRUE == input) {
		currentState_flag++;
		clearFlag_PORTC();
	}

	currentState = FineStateMachineMoore[currentState].next[currentState_flag];

}


//Function for setting
void setModule(){

	GPIO_clockGating(GPIOB);
	GPIO_clockGating(GPIOC);


	//set as GPIO
	GPIO_pinControlRegister(GPIOB, LED1, &pinControlRegister);
	GPIO_pinControlRegister(GPIOB, LED2, &pinControlRegister);
	GPIO_pinControlRegister(GPIOC, MOTOR, &pinControlRegister);
	//PORTC_PCR6 = PORT_PCR_MUX(1)|0x03;        //sw2  // =0x0000103;//PS //Pull up
	GPIO_pinControlRegister(GPIOC, SWITCH_2, &pinControlRegisterSwitch);

	//SAFE value
	GPIO_clearPIN(GPIOB, LED1);// LED 1(PTB18) is OFF
	GPIO_clearPIN(GPIOB, LED2);// LED 2(PTB19) is OFF
	GPIO_clearPIN(GPIOC, MOTOR);// motor is OFF

	//Peripherals as outputs
	GPIO_dataDirectionPIN(GPIOB,GPIO_OUTPUT, LED1);
	GPIO_dataDirectionPIN(GPIOB,GPIO_OUTPUT, LED2);
	GPIO_dataDirectionPIN(GPIOC,GPIO_OUTPUT, MOTOR);
	//Peripherals as INPUTS
	GPIO_dataDirectionPIN(GPIOC,GPIO_INPUT, SWITCH_2);


}

void sequence_1(){
	if(TRUE==PIT1_Flag_state()){
		flag_sec_1++;
		PIT1_Flag_edit();
		if (flag_sec_1==5){
			flag_sec_1=1;
		}

		if (FASE1==flag_sec_1){

			GPIO_setPIN(GPIOB, LED1);// LED 1(PTB18) is ON
			GPIO_clearPIN(GPIOB, LED2);// LED 2(PTB19) is OFF
			PIT_delay(PIT_1,systemClock,PERIOD1);//period its one second

			GPIO_setPIN(GPIOC, MOTOR);// motor is ON
		}

		else if(FASE2==flag_sec_1){

			GPIO_setPIN(GPIOB, LED1);// LED 1(PTB18) is ON
			GPIO_clearPIN(GPIOB, LED2);// LED 2(PTB19) is OFF
			PIT_delay(PIT_1,systemClock,PERIOD1);//period its one second

			GPIO_clearPIN(GPIOC, MOTOR);// motor is OFF
		}


		else if(FASE3==flag_sec_1){

			GPIO_setPIN(GPIOB, LED1);// LED 1(PTB18) is ON
			GPIO_clearPIN(GPIOB, LED2);// LED 2(PTB19) is OFF
			PIT_delay(PIT_1,systemClock,PERIOD3);//period its 3 seconds


			GPIO_setPIN(GPIOC, MOTOR);// motor is ON
		}
		else if(FASE4==flag_sec_1){

			GPIO_setPIN(GPIOB, LED1);// LED 1(PTB18) is ON
			GPIO_clearPIN(GPIOB, LED2);// LED 2(PTB19) is OFF
			PIT_delay(PIT_1,systemClock,PERIOD1);//period its one second

			GPIO_clearPIN(GPIOC, MOTOR);// motor is OFF
		}

	}
}
void sequence_2(){
	flag_sec_1=0;
	if(TRUE==PIT1_Flag_state()){
		flag_sec_2++;
		PIT1_Flag_edit();
		if (flag_sec_2==3){
			flag_sec_2=1;
		}

		if (FASE1==flag_sec_2){

			GPIO_clearPIN(GPIOB, LED1);// LED 1(PTB18) is OFF
			GPIO_setPIN(GPIOB, LED2);// LED 2(PTB19) is ON
			PIT_delay(PIT_1,systemClock,PERIOD4);//period its 4 seconds
			GPIO_setPIN(GPIOC, MOTOR);// motor is ON
		}

		else if(FASE2==flag_sec_2){

			GPIO_clearPIN(GPIOB, LED1);// LED 1(PTB18) is OFF
			GPIO_setPIN(GPIOB, LED2);// LED 2(PTB19) is ON
			PIT_delay(PIT_1,systemClock,PERIOD4);//period its 4 seconds
			GPIO_clearPIN(GPIOC, MOTOR);// motor is OFF
		}
	}

}

void sequence_3(){
	flag_sec_2=0;

	GPIO_clearPIN(GPIOB, LED1);// LED 1(PTB18) is OFF
	GPIO_clearPIN(GPIOB, LED2);// LED 2(PTB19) is OFF
	GPIO_clearPIN(GPIOC, MOTOR);// motor is OFF


}
