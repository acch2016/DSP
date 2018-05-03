/*
 * Menu.c
 *
 *  Created on: 08/10/2016
 *      Author: Alexis
 */

#include "Menu.h"

#define MAIN_SCREEN &FineStateMachineMoore_Screen[0]
#define MENU_SCREEN &FineStateMachineMoore_Screen[1]
#define ALARM_SCREEN &FineStateMachineMoore_Screen[2]
#define FORMAT_SCREEN &FineStateMachineMoore_Screen[3]
#define DECREMENT_SCREEN &FineStateMachineMoore_Screen[4]
#define MCONTROL_SCREEN &FineStateMachineMoore_Screen[5]
#define FRECUENCY_SCREEN &FineStateMachineMoore_Screen[6]
#define PIN0_PORTC 0
#define PIN2_PORTC 2
#define PIN5_PORTC 5
#define PIN7_PORTC 7
#define PIN8_PORTC 8
#define PIN9_PORTC 9


typedef const struct State
		{

	TransitionType (*ftprScreen)();
	const struct State* next[7];
		}StateType;

		/**Máquina de estados general. Es constante porque no queremos que se modifique y esta en memoria de programa*/
		const StateType FineStateMachineMoore_Screen[7]=
		{
				{Main_Screen,{MAIN_SCREEN,MENU_SCREEN}},
				{Menu_Screen,{MENU_SCREEN,ALARM_SCREEN,FORMAT_SCREEN,DECREMENT_SCREEN,MCONTROL_SCREEN,FRECUENCY_SCREEN,MAIN_SCREEN}},
				{Alarm_Screen,{ALARM_SCREEN,MAIN_SCREEN}},
				{Format_Screen,{FORMAT_SCREEN,MAIN_SCREEN}},
				{Decrement_Screen,{DECREMENT_SCREEN,MAIN_SCREEN}},
				{MControl_Screen,{MCONTROL_SCREEN,MAIN_SCREEN}},
				{Frecuency_Screen,{FRECUENCY_SCREEN,MAIN_SCREEN}},

		};

		StateType* currentState = MAIN_SCREEN;
		TransitionType currentState_flag;
		uint8 flag_screen = FALSE;

		void Screen_Machine(){
			/**Se limpia la bandera para ir al siguiente estado*/
			currentState_flag = 0;
			/**Se manda a llamar a la función dentro del estado*/
			currentState_flag = currentState->ftprScreen();
			/**Se actualiza el siguiente estado*/
			currentState = currentState->next[currentState_flag];
		}


		/***/
		TransitionType Main_Screen(){
			char Temp_text[] = "Temperatura";
			float val = 0.0f;
			char Temp[6];
			Temp[5] = 0;
			char Format[1];
			if(TRUE == FormatFlagValue()){
				Format[0] = 'F';
				val = temp_value()*1.8+32;
			}else{
				val = temp_value();
				Format[0] = 'C';
			}
			BinaryToBCD(Temp,val,2);
			Temp[6] = 0;
			char Motor_text[] = "Velocidad";
			uint16 val2= DutyCycleValue();
			char Motor[3];
			Motor[2] = 0;
			BinaryToBCD(Motor,val2,0);
			Motor[3] = 0;
			char Percentage[] = "%";
			Percentage[1] = 0;
			LCDNokia_gotoXY(0,0);
			LCDNokia_sendString(Temp_text);
			LCDNokia_gotoXY(0,1);
			LCDNokia_sendString(Temp);
			LCDNokia_gotoXY(43,1);
			LCDNokia_sendString(Format);
			LCDNokia_gotoXY(0,2);
			LCDNokia_sendString(Motor_text);
			LCDNokia_gotoXY(0,3);
			LCDNokia_sendString(Motor);
			LCDNokia_gotoXY(22,3);
			LCDNokia_sendString(Percentage);
			if(TRUE == readFlag_Button(Button1)){
				clearFlag_Button(Button1);
				return NEXT_STATE;
			}else{
				return SAME_STATE;
			}

		}
		/***/
		TransitionType Menu_Screen(){

			char Alarm[] = "1)Alarma";
			char Format[] = "2)Formato Temp";
			char Decrement[] = "3)Decremento";
			char MControl[] = "4)Motor Manual";
			char Frecuency[] = "5)Frencimetro";
			char Back[] = "6)Regresar";

			LCDNokia_gotoXY(0,0);
			LCDNokia_sendString(Alarm);
			LCDNokia_gotoXY(0,1);
			LCDNokia_sendString(Format);
			LCDNokia_gotoXY(0,2);
			LCDNokia_sendString(Decrement);
			LCDNokia_gotoXY(0,3);
			LCDNokia_sendString(MControl);
			LCDNokia_gotoXY(0,4);
			LCDNokia_sendString(Frecuency);
			LCDNokia_gotoXY(0,5);
			LCDNokia_sendString(Back);

			if(TRUE == readFlag_Button(Button1)){
				clearFlag_Button(Button1);
				return NEXT_STATE;
			}else if(TRUE == readFlag_Button(Button2)){
				clearFlag_Button(Button2);
				return (NEXT_STATE + 1);
			}else if(TRUE == readFlag_Button(Button3)){
				clearFlag_Button(Button3);
				return (NEXT_STATE + 2);
			}else if(TRUE == readFlag_Button(Button4)){
				clearFlag_Button(Button4);
				return (NEXT_STATE + 3);
			}else if(TRUE == readFlag_Button(Button5)){
				clearFlag_Button(Button5);
				return (NEXT_STATE + 4);
			}else if(TRUE == readFlag_Button(Button6)){
				clearFlag_Button(Button6);
				return (NEXT_STATE + 5);
			}else{
				return SAME_STATE;
			}
		}

		/***/
		TransitionType Alarm_Screen(){
			char Alarm[] = "Alarma";
			uint8 alarmVal;
			char Format[1];

			if(FALSE == FormatFlagValue()){
				alarmVal = AlarmValue();
			}
			else{
				alarmVal = AlarmValue()*1.8+32;
			}
			char Alarm_value[5];
			BinaryToBCD(Alarm_value,alarmVal,2);
			char option[] = "(-)B1 (+)B2 (ok)B3";
			Alarm_value[5] = 0;
			if(TRUE == FormatFlagValue()){
				Format[0] = 'F';
			}else{
				Format[0] = 'C';
			}
			Format[1] = 0;
			LCDNokia_gotoXY(0,0);
			LCDNokia_sendString(Alarm);
			LCDNokia_gotoXY(0,1);
			LCDNokia_sendString(Alarm_value);
			LCDNokia_gotoXY(43,1);
			LCDNokia_sendString(Format);
			LCDNokia_gotoXY(0,2);
			LCDNokia_sendString(option);

			if(TRUE == readFlag_Button(Button1)){
				AlarmValueModifier(-1);
				clearFlag_Button(Button1);
				return SAME_STATE;
			}
			else if(TRUE == readFlag_Button(Button2)){
				AlarmValueModifier(1);
				clearFlag_Button(Button2);
				return SAME_STATE;
			}
			else if(TRUE == readFlag_Button(Button3)){
				clearFlag_Button(Button3);
				return NEXT_STATE;
			}else{
				return SAME_STATE;
			}
		}
		/***/
		TransitionType Format_Screen(){
			char Format[] = "Formato Temp";
			char *Format_value;
			char option[] = "(C)B1 (F)B2 (ok)B3";

			if(TRUE == FormatFlagValue()){
				Format_value = "Farenheit";
			}else{
				Format_value = "Celsius";
			}
			LCDNokia_gotoXY(0,0);
			LCDNokia_sendString(Format);
			LCDNokia_gotoXY(0,1);
			LCDNokia_sendString(Format_value);
			LCDNokia_gotoXY(0,2);
			LCDNokia_sendString(option);

			if(TRUE == readFlag_Button(Button1)){
				clearFlag_Button(Button1);
				FormatFlagModifier(FALSE);
				return SAME_STATE;
			}
			else if(TRUE == readFlag_Button(Button2)){
				clearFlag_Button(Button2);
				FormatFlagModifier(TRUE);
				return SAME_STATE;
			}
			else if(TRUE == readFlag_Button(Button3)){
				clearFlag_Button(Button3);
				return NEXT_STATE;
			}else{
				return SAME_STATE;
			}
		}
		/**Para cambiar cuanto cambia el motor con respecto a la temperatura*/
		TransitionType Decrement_Screen(){

			char Decrement[] = "% de decre";
			char Increment[] = "% de incre";
			char Value[3] = {0,0,0} ;

			uint8 multValue = multiplierDutyCycleValue();
			Value[3] = 0;
			char percentage[1] = "%";
			percentage[1] = 0;
			BinaryToBCD(Value,multValue,0);
			char option[] = "(-)B1 (+)B2 (ok)B3";

			if(FALSE == flag_screen){
				LCDNokia_gotoXY(0,0);
				LCDNokia_sendString(Decrement);
			}else{
				LCDNokia_gotoXY(0,0);
				LCDNokia_sendString(Increment);
			}
			LCDNokia_gotoXY(0,1);
			LCDNokia_sendString(Value);
			LCDNokia_gotoXY(22,1);
			LCDNokia_sendString(percentage);
			LCDNokia_gotoXY(0,2);
			LCDNokia_sendString(option);

			if(TRUE == readFlag_Button(Button1)){
				flag_screen = FALSE;
				multiplierDutyCycleModifier(-5);
				return SAME_STATE;
			}
			else if(TRUE == readFlag_Button(Button2)){
				flag_screen = TRUE;
				multiplierDutyCycleModifier(5);
				return SAME_STATE;
			}
			else if(TRUE == readFlag_Button(Button3)){
				clearFlag_Button(Button3);
				return NEXT_STATE;
			}else{
				return SAME_STATE;
			}
		}
		/**Para controlar manualmente el motor*/
		TransitionType MControl_Screen(){
			char Manual[] = "Ctrl Manual";
			uint8 raw_value = manualDutyCycleValue();
			char Value[3];
			Value[2] = 0;
			BinaryToBCD(Value,raw_value,0);
			Value[3] = 0;
			char Percentage[1] = "%";
			char option[] = "(on)B1 (off)B2 (ok)B3 (-)B4 (+)B5";

			LCDNokia_gotoXY(0,0);
			LCDNokia_sendString(Manual);
			LCDNokia_gotoXY(0,1);
			LCDNokia_sendString(Value);
			LCDNokia_gotoXY(28,1);
			LCDNokia_sendString(Percentage);
			LCDNokia_gotoXY(0,2);
			LCDNokia_sendString(option);

			flagStateMotorModifier(TRUE);
			if(TRUE == readFlag_Button(Button1)){
				MotorEnable();
				clearFlag_Button(Button1);
				return SAME_STATE;
			}else if(TRUE == readFlag_Button(Button2)){
				MotorDisable();
				clearFlag_Button(Button2);
				return SAME_STATE;
			}
			else if(TRUE == readFlag_Button(Button3)){
				clearFlag_Button(Button3);
				MotorEnable();
				manualDutyCycleModifier(50);
				flagStateMotorModifier(FALSE);
				return NEXT_STATE;
			}
			else if(TRUE == readFlag_Button(Button4)){
				manualDutyCycleModifier(-5);
				clearFlag_Button(Button4);
				return SAME_STATE;
			}
			else if(TRUE == readFlag_Button(Button5)){
				manualDutyCycleModifier(5);
				clearFlag_Button(Button5);
				return SAME_STATE;
			}
			else{
				return SAME_STATE;
			}
		}

		/***/
		TransitionType Frecuency_Screen(){

			FTM_C0SC(FTM_0, FTM_CnSC_CHIE_MASK, ENABLE);/**La bandera CHIE tiene que ser activada solo en el momento que se necesita mostrar la frecuencia*/
			char Frecuency[] = "Frecuencia";
			char Value[10] = {0,0,0,0,0,0,0,0,0,0};/**Limpiar valor en memoria*/
			BinaryToBCD(Value, frecuency_value(),2);
			clean_frecuency();
			char Unit[] = "Hz";
			char Back[] = "(ok)B1";

			LCDNokia_gotoXY(0,0);
			LCDNokia_sendString(Frecuency);
			LCDNokia_gotoXY(0,1);
			LCDNokia_sendString(Value);
			LCDNokia_gotoXY(0,2);
			LCDNokia_sendString(Unit);
			LCDNokia_gotoXY(0,3);
			LCDNokia_sendString(Back);
			if(TRUE == readFlag_Button(Button1)){
				FTM_C0SC(FTM_0, ~FTM_CnSC_CHIE_MASK, DISABLE); /**La bandera CHIE tiene que ser activada solo en el momento que se necesita mostrar la frecuencia*/
				clearFlag_Button(Button1);
				return NEXT_STATE;
			}else{
				return SAME_STATE;
			}
		}

		/***/
		void Configuration_Menu(){
			GPIO_clockGating(GPIOC);
			GPIO_pinControlRegisterType pinControlRegisterButton = GPIO_MUX1|GPIO_PE|GPIO_PS|INTR_FALLING_EDGE;/**Detectan el flanco de subida del intergado 74C922*/

			GPIO_pinControlRegister(GPIOC, PIN0_PORTC, &pinControlRegisterButton);
			GPIO_pinControlRegister(GPIOC, PIN2_PORTC, &pinControlRegisterButton);
			GPIO_pinControlRegister(GPIOC, PIN5_PORTC, &pinControlRegisterButton);
			GPIO_pinControlRegister(GPIOC, PIN7_PORTC, &pinControlRegisterButton);
			GPIO_pinControlRegister(GPIOC, PIN8_PORTC, &pinControlRegisterButton);
			GPIO_pinControlRegister(GPIOC, PIN9_PORTC, &pinControlRegisterButton);

			GPIO_dataDirectionPIN(GPIOC,GPIO_INPUT, PIN0_PORTC);
			GPIO_dataDirectionPIN(GPIOC,GPIO_INPUT, PIN2_PORTC);
			GPIO_dataDirectionPIN(GPIOC,GPIO_INPUT, PIN5_PORTC);
			GPIO_dataDirectionPIN(GPIOC,GPIO_INPUT, PIN7_PORTC);
			GPIO_dataDirectionPIN(GPIOC,GPIO_INPUT, PIN8_PORTC);
			GPIO_dataDirectionPIN(GPIOC,GPIO_INPUT, PIN9_PORTC);

			NVIC_enableInterruptAndPriotity(PORTC_IRQ, PRIORITY_8);
		}

		/**Convierte binario a BCD*/
		void BinaryToBCD(char * temp, float binary,uint8 decimals){
			uint32 value;
			sint8 tempe;
			uint8 Flag = FALSE;
			uint8 i = 0,j = 0;
			uint32 multiplier = 10;
			value = binary*(pow(10,decimals));
			while(FALSE != value || i == 0){
				if((pow(10,decimals) > value) && (TRUE != Flag) && (i!=0)){
					temp[i] = 46;
					Flag = TRUE;
				}else{
					temp[i] = (uint8)(value % multiplier) + 48;
					value = value/multiplier;
				}
				i++;
			}

			for(j = 0; j<(i/2);j++){
				i--;
				if(temp[i] == '.'){
					i--;
				}
				tempe = temp[i];
				temp[i] = temp[j];
				temp[j] = tempe;
			}

		}
