/*
 * menu.c
 *
 *  Created on: 23/10/2016
 *      Author: alejandrocanale
 */

#include "menu.h"
#include "UART.h"
#define ESC 0x1b

static uint8 enableTerminal_2 = FALSE;
static uint8 redMemFlag = FALSE;
static uint8 setHour_Flag = FALSE;//No se han usado
static uint8 setDate_Flag = FALSE;//No se han usado
static uint8 arrayAux_setHour[2];
static uint8 arrayAux_setMinutes[2];
static uint8 arrayAux_setDay[2];
static uint8 arrayAux_setMonth[2];
static uint8 arrayAux_setYear[4];
static uint8 state_flag = FALSE;
static uint8 state_flag_days = FALSE;
static uint8 state_flag_months = FALSE;
static uint8 set_hour_counter =FALSE;
static uint8 set_minutes_counter = FALSE;
static uint8 set_day_counter = FALSE;
static uint8 set_month_counter = FALSE;
static uint8 set_year_counter = FALSE;
static uint8 printed_flag = FALSE;
static uint8 optionCont;


/**Estructura que contiene apuntador a función y apuntador a esta mísma estructura*/
typedef const struct State {
	TransitionType (*fptrScreen)(UART_ChannelType);
	const struct State* next[10];
} StateType;

/**Máquina de estados general. Es constante porque no queremos que se modifique y esta en memoria de programa*/
const StateType FiniteStateMachineMoore_Screen[10] = {

		//{ main_screenState,{MAIN_SCREEN, MENU}},
		{ menuState_UARTx, { MENU, READ_MEM_I2C, WRITE_MEM_I2C, SET_HOUR, SET_DATE, FORMAT_HOUR, READ_HOUR, READ_DATE, COMMUNICATION_T1_T2, ECHO_LCD } },

		{ readMemI2c_State, { READ_MEM_I2C, MENU, } },
		{ writeMemI2c_State, {WRITE_MEM_I2C, MENU, } },
		{ setHour_State, { SET_HOUR, MENU, } },
		{setDate_State, { SET_DATE,	MENU, } },
		{ formatHour_State, { FORMAT_HOUR, MENU, } },
		{readHour_State, { READ_HOUR, MENU, } },
		{ readDate_State, {	READ_DATE, MENU, } },
		{ communicationT1T2_State, {COMMUNICATION_T1_T2, MENU, } },
		{ echoLCD_State, { ECHO_LCD,MENU, } },

};

//const StateType FiniteStateMachineMoore_Bluetooth[10] = {
//
//		//{ main_screenState,{MAIN_SCREEN, MENU}},
//		{ menuState_UARTx, { MENU, READ_MEM_I2C, WRITE_MEM_I2C, SET_HOUR, SET_DATE,
//				FORMAT_HOUR, READ_HOUR, READ_DATE, COMMUNICATION_T1_T2,
//				ECHO_LCD } },
//
//				{ readMemI2c_State, { READ_MEM_I2C, MENU, } },
//				{ writeMemI2c_State, {WRITE_MEM_I2C, MENU, } },
//				{ setHour_State, { SET_HOUR, MENU, } },
//				{setDate_State, { SET_DATE,	MENU, } },
//				{ formatHour_State, { FORMAT_HOUR, MENU, } },
//				{readHour_State, { READ_HOUR, MENU, } },
//				{ readDate_State, {	READ_DATE, MENU, } },
//				{ communicationT1T2_State, {COMMUNICATION_T1_T2, MENU, } },
//				{ echoLCD_State, { ECHO_LCD,MENU, } },
//
//};

/**Se define el estado actual.*/
StateType* currentState = MENU;
StateType* currentState_Bluetooth = MENU;
TransitionType currentState_flag;
TransitionType currentStateBluetooth_flag;

uint8 flag_screen = FALSE;

/**Función la cual estará llamando continuamente a la máquina de estados en el for infinito del main*/

void screenFSM() {

	/**Se limpia la bandera para ir al siguiente estado*/
	currentState_flag = 0;
	/**Se manda a llamar a la función dentro del estado*/
	currentState_flag = currentState->fptrScreen(UART_0);
	/**Se actualiza el siguiente estado*/
	if(currentState == currentState_Bluetooth && currentState != MENU){
		UART_putString(UART_0, "\033[0;32;40m");
		/*VT100 command for clearing the screen*/
		UART_putString(UART_0, "\033[2J");
		UART_putString(UART_0, "\033[10;10H");
		UART_putString(UART_0, "Otra Terminal lo esta utilizando, intente màs tarde");
		currentState_flag = SAME_STATE;
	}
	currentState = currentState->next[currentState_flag];


}

void screenFSM_Bluetooth() {
	if(TRUE == enableTerminal_2){
		/**Se limpia la bandera para ir al siguiente estado*/
		currentStateBluetooth_flag = 0;
		/**Se manda a llamar a la función dentro del estado*/
		currentStateBluetooth_flag = currentState_Bluetooth->fptrScreen(UART_1);

		if(currentState == currentState_Bluetooth && currentState_Bluetooth != MENU){
			UART_putString(UART_1, "\033[0;32;40m");
			/*VT100 command for clearing the screen*/
			UART_putString(UART_1, "\033[2J");
			UART_putString(UART_1, "\033[10;10H");
			UART_putString(UART_1, "Otra Terminal lo esta utilizando, intente màs tarde");
			currentStateBluetooth_flag = SAME_STATE;
		}
		/**Se actualiza el siguiente estado*/
		currentState_Bluetooth = currentState_Bluetooth->next[currentStateBluetooth_flag];
	}
}


/***/
TransitionType menuState_UARTx(UART_ChannelType uartChannel) {

	//	uint8 readMemI2c_screenArray[] =        "1)Leer Mem I2C";
	//	uint8 writeMemI2c_screenArray[] =       "2)Escr Mem I2C";
	//	uint8 setHour_screenArray[] =           "3)Establ Hora";
	//
	//	uint8 setDate_screenArray[] =           "1)Establ Fecha";
	//	uint8 formatHour_screenArray[] =        "2)Formato hora";
	//	uint8 readHour_screenArray[] =          "3)Leer hora";
	//
	//	uint8 readDate_screenArray[] =          "1)Leer fecha";
	//	uint8 communicationT1T2_screenArray[] = "2)Com terminal";
	//	uint8 echoLCD_screenArray[] =           "3)Eco en LCD";
	//
	//	uint8 regresarAlMenuAlteriorArray[] =   "4)Regresar";

	/**The following sentences send strings to PC using the UART_putString function. Also, the string
	 * is coded with terminal code*/
	if(printed_flag == FALSE){
		/** VT100 command for text in Black and background in Grey*/
		UART_putString(uartChannel, "\033[0;30;47m");
		/**VT100 command for hide cursor*/
		UART_putString(uartChannel, "\e[ ? 25 l");
		/*VT100 command for clearing the screen*/
		UART_putString(uartChannel, "\033[2J");

		/** VT100 command for positioning the cursor in x and y position*/
		UART_putString(uartChannel, "\033[10;10H");
		UART_putString(uartChannel, "Micros y DSPs\r");
		/** VT100 command for positioning the cursor in x and y position*/
		UART_putString(uartChannel, "\033[11;10H");
		UART_putString(uartChannel, "    ITESO\r");
		/** VT100 command for positioning the cursor in x and y position*/

		UART_putString(uartChannel, "\033[13;10H");
		UART_putString(uartChannel, " Opciones:\r");

		UART_putString(uartChannel, "\033[15;10H");
		UART_putString(uartChannel, "  1)  Leer Memoria I2C\r");

		UART_putString(uartChannel, "\033[16;10H");
		UART_putString(uartChannel, "  2)  Escribir memoria I2C\r");

		UART_putString(uartChannel, "\033[17;10H");
		UART_putString(uartChannel, "  3)  Establecer Hora\r");

		UART_putString(uartChannel, "\033[18;10H");
		UART_putString(uartChannel, "  4)  Establecer Fecha\r");

		UART_putString(uartChannel, "\033[19;10H");
		UART_putString(uartChannel, "  5)  Formato de hora\r");

		UART_putString(uartChannel, "\033[20;10H");
		UART_putString(uartChannel, "  6)  Leer hora\r");

		UART_putString(uartChannel, "\033[21;10H");
		UART_putString(uartChannel, "  7)  Leer fecha\r");

		UART_putString(uartChannel, "\033[22;10H");
		UART_putString(uartChannel, "  8)  Comunicación con terminal 2\r");

		UART_putString(uartChannel, "\033[23;10H");
		UART_putString(uartChannel, "  9)  Eco en LCD\r");

		UART_putString(uartChannel, "\033[24;10H");
		UART_putString(uartChannel, "La fecha actual es: \r");

		UART_putString(uartChannel, "\033[25;10H");
		UART_putString(uartChannel, "La hora actual es: \r");
		printed_flag = TRUE;
		UART_putString(uartChannel, "\033[26;10H");
		UART_putString(uartChannel, "Opcion: ");
	}

	UART_putString(uartChannel, "\033[24;29H");
	UART_putString(uartChannel,(RTC_get_String_Date())); //Falta esta func
	UART_putString(uartChannel, "\033[25;29H");
	UART_putString(uartChannel, RTC_get_String_Hour()); //Falta esta func
	UART_putString(uartChannel, "\033[26;18H");
	UART_putChar(uartChannel, optionCont+ASCII);

	if (TRUE == UARTx_statusFlag(uartChannel)) {
		UARTx_clearStatusFlag(uartChannel);
		if(ENTER == UARTx_mailBoxContent(uartChannel)){
			printed_flag = FALSE;
			if (KEY_1 == optionCont) {
				return NEXT_STATE;
			} else if (KEY_2 == optionCont) {
				return (NEXT_STATE + 1);
			} else if (KEY_3 == optionCont) {
				return (NEXT_STATE + 2);
			} else if (KEY_4 == optionCont) {
				return (NEXT_STATE + 3);
			} else if (KEY_5 == optionCont) {
				return (NEXT_STATE + 4);
			} else if (KEY_6 == optionCont) {
				return (NEXT_STATE + 5);
			} else if (KEY_7 == optionCont) {
				return (NEXT_STATE + 6);
			} else if (KEY_8 == optionCont) {
				return (NEXT_STATE + 7);
			} else if (KEY_9 == optionCont) {
				return (NEXT_STATE + 8);

			} else {
				return SAME_STATE;
			}
		}else{
			optionCont = UARTx_mailBoxContent(uartChannel)-ASCII;
			return SAME_STATE;
		}

	} else {
		return SAME_STATE;
	}

}

TransitionType readMemI2c_State( UART_ChannelType uartChannel) {

	/**The following sentences send strings to PC using the UART_putString function. Also, the string
	 * is coded with terminal code*/
	/** VT100 command for text in red and background in cyan*/
	UART_putString(uartChannel, "\033[0;30;47m");
	/*VT100 command for clearing the screen*/
	UART_putString(uartChannel, "\033[2J");

	/** VT100 command for positioning the cursor in x and y position*/
	UART_putString(uartChannel, "\033[10;10H");
	UART_putString(uartChannel, "LEER MEMORIA I2C \r");
	/** VT100 command for positioning the cursor in x and y position*/
	UART_putString(uartChannel, "\033[12;10H");
	UART_putString(uartChannel, "  Dirección de lectura: \r");
	/** VT100 command for positioning the cursor in x and y position*/
	UART_putString(uartChannel, "\033[12;24H");
	//Pedir la direccion a leer en hexadecimal
	//	Memory_Read();//Falta ver si a la hora de recibir el MailBox se tendrá que recibir en un arreglo
	//Devolver con un eco pra que de visualize
	UART_putChar(uartChannel, UARTx_mailBoxContent(uartChannel));
	delay(65000);

	UART_putString(uartChannel, "\033[13;10H");
	UART_putString(uartChannel, "Longitud en bytes: \r");
	/** VT100 command for positioning the cursor in x and y position*/
	UART_putString(uartChannel, "\033[13;24H");
	//Pedir la longitud de los datos a leer
	//datalength();
	//Devolver con un eco pra que de visualize
	UART_putChar(uartChannel, UARTx_mailBoxContent(uartChannel));
	delay(65000);

}

TransitionType writeMemI2c_State( UART_ChannelType uartChannel) {

	/**The following sentences send strings to PC using the UART_putString function. Also, the string
	 * is coded with terminal code*/
	/** VT100 command for text in red and background in cyan*/
	UART_putString(uartChannel, "\033[0;32;40m");
	/*VT100 command for clearing the screen*/
	UART_putString(uartChannel, "\033[2J");
	/** VT100 command for text in red and background in green*/
	UART_putString(uartChannel, "\033[0;32;41m");
	/** VT100 command for positioning the cursor in x and y position*/
	UART_putString(uartChannel, "\033[10;10H");
	UART_putString(uartChannel, "ESCRIBIR MEMORIA I2C \r");
	/** VT100 command for positioning the cursor in x and y position*/
	UART_putString(uartChannel, "\033[12;10H");
	UART_putString(uartChannel, " Dirección de escritura: \r");
	/** VT100 command for positioning the cursor in x and y position*/
	UART_putString(uartChannel, "\033[12;35H");

	UART_putString(uartChannel, "Texto a guardar: \r");

	//Memory_Write(0,&(UARTx_mailBoxContent(uartChannel)));

	UART_putString(uartChannel, "\033[12;35H");
	//condición
	//función que compruebe si el texto ha sido  guardado en la memoria
	UART_putString(uartChannel, "Su texto ha sido guardado... \r");
}

TransitionType setHour_State(UART_ChannelType uartChannel) {
	optionCont = 0;
	uint8 counter_for_shift_screen = 0;
	uint8 result = 0;
	//if (LCD == LCD_or_terminal) {
	/**The following sentences send strings to PC using the UART_putString function. Also, the string
	 * is coded with terminal code*/
	if(FALSE==printed_flag){
		printed_flag = TRUE;
		/** VT100 command for text in red and background in cyan*/
		UART_putString(uartChannel, "\033[0;30;47m");
		/*VT100 command for clearing the screen*/
		UART_putString(uartChannel, "\033[2J");
		/** VT100 command for positioning the cursor in x and y position*/
		UART_putString(uartChannel, "\033[10;10H");
		UART_putString(uartChannel, "ESTABLECER HORA: \r");

		/** VT100 command for positioning the cursor in x and y position*/
		//UART_putString(uartChannel, "\033[10;28H");
		//UART_putString(uartChannel, RTC_get_String_Hour());

		UART_putString(uartChannel, "\033[11;10H");
		UART_putString(uartChannel, "Ingresar hora en el siguiente formato hh:mm :\r");
		UART_putString(uartChannel, "\033[12;10H");
		UART_putString(uartChannel, "Presiona ENTER despues de cada opcion");
		UART_putString(uartChannel, "\033[13;10H");
		UART_putString(uartChannel, "Presiona ESC para salir");
	}


	if (TRUE == UARTx_statusFlag(uartChannel)){
		UARTx_clearStatusFlag(uartChannel);
		if(ESC == UARTx_mailBoxContent(uartChannel)){
			printed_flag = FALSE;
			set_hour_counter = FALSE;
			set_minutes_counter = FALSE;
			state_flag = FALSE;
			return  NEXT_STATE;
		}
		if( (ENTER == UARTx_mailBoxContent(uartChannel)) && (FALSE == state_flag) ){
			state_flag = TRUE;
			result = BCDtoBinary(arrayAux_setHour, 2);
			RTC_set_Hour(result);
			set_hour_counter = FALSE;
			UARTx_Clear_mailBoxContent(uartChannel);
			return SAME_STATE;
		}else if( (set_hour_counter < 2) && (FALSE == state_flag) ){
			arrayAux_setHour[set_hour_counter++] = UARTx_mailBoxContent(uartChannel);
			return SAME_STATE;
		}else if(FALSE == state_flag){

			return SAME_STATE;

		}

		if( (ENTER == UARTx_mailBoxContent(uartChannel)) && (TRUE == state_flag )){
			state_flag =TRUE;
			result = BCDtoBinary(arrayAux_setMinutes,2);
			RTC_set_Minutes(result);
			set_hour_counter = FALSE;
			UARTx_Clear_mailBoxContent(uartChannel);
			printed_flag = FALSE;
			set_hour_counter = FALSE;
			set_minutes_counter = FALSE;
			state_flag = FALSE;
			return NEXT_STATE;
		}else if((set_minutes_counter < 2) && (TRUE == state_flag)){
			arrayAux_setMinutes[set_minutes_counter++] = UARTx_mailBoxContent(uartChannel);
			return SAME_STATE;
		}else if((set_minutes_counter > 2) && (TRUE == state_flag)){
			UART_putString(uartChannel, "\033[K");//UARTx_clearStatusFlag(uartChannel);
			return SAME_STATE;
		}
	}else{
		UART_putString(uartChannel, "\033[11;56H");
		while(counter_for_shift_screen < set_hour_counter){
			UART_putChar(uartChannel, arrayAux_setHour[counter_for_shift_screen]);
			counter_for_shift_screen++;
		}
		counter_for_shift_screen = 0;
		UART_putString(uartChannel, "\033[11;58H");
		UART_putChar(uartChannel,':');
		while(counter_for_shift_screen < set_minutes_counter){
			UART_putChar(uartChannel, arrayAux_setMinutes[counter_for_shift_screen]);
			counter_for_shift_screen++;
		}
		return SAME_STATE;
	}
}

TransitionType setDate_State(UART_ChannelType uartChannel) {
	optionCont = 0;
	uint8 counter_for_shift_screen = 0;
	uint8 result = 0;
	if(FALSE==printed_flag){
		printed_flag = TRUE;
		/**The following sentences send strings to PC using the UART_putString function. Also, the string
		 * is coded with terminal code*/
		/** VT100 command for text in red and background in cyan*/
		UART_putString(uartChannel, "\033[0;30;47m");
		/*VT100 command for clearing the screen*/
		UART_putString(uartChannel, "\033[2J");
		/** VT100 command for positioning the cursor in x and y position*/
		UART_putString(uartChannel, "\033[10;10H");
		UART_putString(uartChannel, "ESTABLECER FECHA: \r");

		/** VT100 command for positioning the cursor in x and y position*/
		UART_putString(uartChannel, "\033[10;28H");

		UART_putString(uartChannel, "\033[11;10H");
		UART_putString(uartChannel, "Ingresa la fecha en el siguiente formato dd/mm/yyyy: \r");
		UART_putString(uartChannel, "\033[12;10H");
		UART_putString(uartChannel, "Presiona ENTER despues de cada opcion");
		UART_putString(uartChannel, "\033[13;10H");
		UART_putString(uartChannel, "Presiona ESC para salir");


	}
	if (TRUE == UARTx_statusFlag(uartChannel)){
		UARTx_clearStatusFlag(uartChannel);
		if(ESC == UARTx_mailBoxContent(uartChannel)){
			printed_flag = FALSE;
			set_day_counter = FALSE;
			set_month_counter = FALSE;
			set_year_counter = FALSE;
			state_flag_days = FALSE;
			state_flag_months = FALSE;
			return  NEXT_STATE;
		}
		if( (ENTER == UARTx_mailBoxContent(uartChannel)) && (FALSE == state_flag_days) ){
			state_flag_days = TRUE;
			result = BCDtoBinary(arrayAux_setDay, 2);
			RTC_set_Day(result);
			UARTx_Clear_mailBoxContent(uartChannel);
			return SAME_STATE;
		}else if( (set_day_counter < 2) && (FALSE == state_flag_days) ){
			arrayAux_setDay[set_day_counter++] = UARTx_mailBoxContent(uartChannel);
			return SAME_STATE;
		}else if(FALSE == state_flag_days){
			return SAME_STATE;

		}

		if( (ENTER == UARTx_mailBoxContent(uartChannel)) && (FALSE == state_flag_months)){
			state_flag_months =TRUE;
			result = BCDtoBinary(arrayAux_setMonth,2);
			RTC_set_Month(result);
			UARTx_Clear_mailBoxContent(uartChannel);
			return SAME_STATE;
		}else if((set_month_counter < 2) && (FALSE == state_flag_months)){
			arrayAux_setMonth[set_month_counter++] = UARTx_mailBoxContent(uartChannel);
			return SAME_STATE;
		}else if(FALSE == state_flag_months){
			return SAME_STATE;
		}

		if( (ENTER == UARTx_mailBoxContent(uartChannel))){
			modifyYears(arrayAux_setYear);
			arrayAux_setYear[0] = arrayAux_setYear[2];
			arrayAux_setYear[1] = arrayAux_setYear[3];
			result = BCDtoBinary(arrayAux_setYear,2);
			RTC_set_Year(result);
			UARTx_Clear_mailBoxContent(uartChannel);
			printed_flag = FALSE;
			state_flag_days = FALSE;
			state_flag_months = FALSE;
			set_day_counter = FALSE;
			set_month_counter = FALSE;
			set_year_counter = FALSE;
			UARTx_clearStatusFlag(uartChannel);
			return NEXT_STATE;
		}else if((set_year_counter < 4)){
			arrayAux_setYear[set_year_counter++] = UARTx_mailBoxContent(uartChannel);
			return SAME_STATE;
		}else{
			return SAME_STATE;
		}


	}else{
		UART_putString(uartChannel, "\033[11;65H");
		while(counter_for_shift_screen < set_day_counter){
			UART_putChar(uartChannel, arrayAux_setDay[counter_for_shift_screen]);
			counter_for_shift_screen++;
		}
		counter_for_shift_screen = 0;
		UART_putString(uartChannel, "\033[11;67H");
		UART_putChar(uartChannel,'/');
		while(counter_for_shift_screen < set_month_counter){
			UART_putChar(uartChannel, arrayAux_setMonth[counter_for_shift_screen]);
			counter_for_shift_screen++;
		}
		counter_for_shift_screen = 0;
		UART_putString(uartChannel, "\033[11;70H");
		UART_putChar(uartChannel,'/');
		while(counter_for_shift_screen < set_year_counter){
			UART_putChar(uartChannel, arrayAux_setYear[counter_for_shift_screen]);
			counter_for_shift_screen++;
		}
		return SAME_STATE;
	}
}

TransitionType formatHour_State(UART_ChannelType uartChannel) {
	uint8 format;
	optionCont = 0;
	if(FALSE == printed_flag){
	/**The following sentences send strings to PC using the UART_putString function. Also, the string
	 * is coded with terminal code*/
	/** VT100 command for text in red and background in cyan*/
	UART_putString(uartChannel, "\033[0;30;47m");
	/*VT100 command for clearing the screen*/
	UART_putString(uartChannel, "\033[2J");

	UART_putString(uartChannel, "\033[9;10H");
	UART_putString(uartChannel, "FORMATO HORA \r");
	/** VT100 command for positioning the cursor in x and y position*/
	UART_putString(uartChannel, "\033[10;10H");
	UART_putString(uartChannel, "Escoge un formato:\r");
	/** VT100 command for positioning the cursor in x and y position*/
	UART_putString(uartChannel, "\033[12;10H");
	UART_putString(uartChannel, "  1)  AM/PM \r");
	/** VT100 command for positioning the cursor in x and y position*/
	UART_putString(uartChannel, "\033[13;10H");
	UART_putString(uartChannel, "  2)  24horas \r");
	UART_putString(uartChannel, "\033[15;10H");
	UART_putString(uartChannel, "Presiona ENTER despues de cada opcion");
	UART_putString(uartChannel, "\033[16;10H");
	UART_putString(uartChannel, "Presiona ESC para salir");
	printed_flag = TRUE;
	}

	if(TRUE == UARTx_statusFlag(uartChannel)){
		UARTx_clearStatusFlag(uartChannel);
		if(ENTER == UARTx_mailBoxContent(uartChannel)){
			RTC_changeFormat(format- ASCII);
			printed_flag = FALSE;
			return NEXT_STATE;
		}else{
			format = UARTx_mailBoxContent(uartChannel);
			return SAME_STATE;
		}

	}else
		UART_putString(uartChannel, "\033[10;29H");
		UART_putChar(uartChannel, format);
		return SAME_STATE;
}

TransitionType readHour_State(UART_ChannelType uartChannel) {

	/**The following sentences send strings to PC using the UART_putString function. Also, the string
	 * is coded with terminal code*/
	/** VT100 command for text in red and background in cyan*/
	UART_putString(uartChannel, "\033[0;32;40m");
	/*VT100 command for clearing the screen*/
	UART_putString(uartChannel, "\033[2J");
	/** VT100 command for text in red and background in green*/
	UART_putString(uartChannel, "\033[0;32;41m");
	/** VT100 command for positioning the cursor in x and y position*/
	UART_putString(uartChannel, "\033[10;10H");
	UART_putString(uartChannel, "Micros y DSPs\r");
	/** VT100 command for positioning the cursor in x and y position*/
	UART_putString(uartChannel, "\033[11;10H");
	UART_putString(uartChannel, "    ITESO\r");
	/** VT100 command for positioning the cursor in x and y position*/

	UART_putString(uartChannel, "\033[13;10H");
	UART_putString(uartChannel, RTC_get_String_Hour());
	return NEXT_STATE;

}

TransitionType readDate_State(UART_ChannelType uartChannel) {

	/**The following sentences send strings to PC using the UART_putString function. Also, the string
	 * is coded with terminal code*/
	/** VT100 command for text in red and background in cyan*/
	UART_putString(uartChannel, "\033[0;32;40m");
	/*VT100 command for clearing the screen*/
	UART_putString(uartChannel, "\033[2J");
	/** VT100 command for text in red and background in green*/
	UART_putString(uartChannel, "\033[0;32;41m");
	/** VT100 command for positioning the cursor in x and y position*/
	UART_putString(uartChannel, "\033[10;10H");
	UART_putString(uartChannel, "Micros y DSPs\r");
	/** VT100 command for positioning the cursor in x and y position*/
	UART_putString(uartChannel, "\033[11;10H");
	UART_putString(uartChannel, "    ITESO\r");
	/** VT100 command for positioning the cursor in x and y position*/

	UART_putString(uartChannel, "\033[13;10H");
	UART_putString(uartChannel, RTC_get_String_Date());

	return NEXT_STATE;
}

TransitionType communicationT1T2_State(UART_ChannelType uartChannel) {

	/**The following sentences send strings to PC using the UART_putString function. Also, the string
	 * is coded with terminal code*/
	/** VT100 command for text in red and background in cyan*/
	UART_putString(uartChannel, "\033[0;32;40m");
	/*VT100 command for clearing the screen*/
	UART_putString(uartChannel, "\033[2J");
	/** VT100 command for text in red and background in green*/
	UART_putString(uartChannel, "\033[0;32;41m");
	/** VT100 command for positioning the cursor in x and y position*/
	UART_putString(uartChannel, "\033[10;10H");
	UART_putString(uartChannel, "Terminal 1:\r");
	/** VT100 command for positioning the cursor in x and y position*/
	UART_putString(uartChannel, "\033[11;10H");

	/** VT100 command for positioning the cursor in x and y position*/
	UART_putString(uartChannel, "\033[13;10H");
	UART_putString(uartChannel, "Terminal 2:\r");

	/** VT100 command for positioning the cursor in x and y position*/
	UART_putString(uartChannel, "\033[13;10H");

	return NEXT_STATE;
}

TransitionType echoLCD_State(UART_ChannelType uartChannel) {

	/**The following sentences send strings to PC using the UART_putString function. Also, the string
	 * is coded with terminal code*/
	/** VT100 command for text in red and background in cyan*/
	UART_putString(uartChannel, "\033[0;32;40m");
	/*VT100 command for clearing the screen*/
	UART_putString(uartChannel, "\033[2J");
	/** VT100 command for text in red and background in green*/
	UART_putString(uartChannel, "\033[0;32;41m");
	/** VT100 command for positioning the cursor in x and y position*/
	UART_putString(uartChannel, "\033[10;10H");
	UART_putString(uartChannel, "Escribir texto:\r");
	/** VT100 command for positioning the cursor in x and y position*/
	UART_putString(uartChannel, "\033[11;10H");
	return NEXT_STATE;

}


