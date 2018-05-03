/*
 * menu.c
 *
 *  Created on: 23/10/2016
 *      Author: alejandrocanale
 */


#include "menu.h"
#include "uart.h"

/**Estructura que contiene apuntador a función y apuntador a esta mísma estructura*/
typedef const struct State {

	TransitionType (*fptrScreen)();
	const struct State* next[12];

} StateType;


/**Máquina de estados general. Es constante porque no queremos que se modifique y esta en memoria de programa*/
const StateType FiniteStateMachineMoore_Screen[12] = {

		{ main_screenState,{MAIN_SCREEN, MENU}},

		{ menuState,       {MENU, READ_MEM_I2C, WRITE_MEM_I2C, SET_HOUR, SET_DATE, FORMAT_HOUR, READ_HOUR, READ_DATE, COMMUNICATION_T1_T2, ECHO_LCD  } },

		{ readMemI2c_State,        {READ_MEM_I2C,        MENU,} },
		{ writeMemI2c_State,       {WRITE_MEM_I2C,       MENU,} },
		{ setHour_State,           {SET_HOUR,            MENU,} },
		{ setDate_State,           {SET_DATE,            MENU,} },
		{ formatHour_State,        {FORMAT_HOUR,         MENU,} },
		{ readHour_State,          {READ_HOUR,           MENU,} },
		{ readDate_State,          {READ_DATE,           MENU,} },
		{ communicationT1T2_State, {COMMUNICATION_T1_T2, MENU,} },
		{ echoLCD_State,           {ECHO_LCD,            MENU,} },

};

/**Se define el estado actual.*/
StateType* currentState = MAIN_SCREEN;
TransitionType currentState_flag;
uint8 flag_screen = FALSE;

/**Función la cual estará llamando continuamente a la máquina de estados en el for infinito del main*/

void screenFSM() {
	/**Se limpia la bandera para ir al siguiente estado*/
	currentState_flag = 0;
	/**Se manda a llamar a la función dentro del estado*/
	currentState_flag = currentState->fptrScreen();
	/**Se actualiza el siguiente estado*/
	currentState = currentState->next[currentState_flag];
}

TransitionType main_screenState(){
/**Se mostrará la hora*/
}

/***/
TransitionType menuState() {

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
	/** VT100 command for text in red and background in cyan*/
	UART_putString(UART_0, "\033[0;32;46m");
	/*VT100 command for clearing the screen*/
	UART_putString(UART_0, "\033[2J");
	/** VT100 command for text in red and background in green*/
	UART_putString(UART_0, "\033[0;32;41m");
	/** VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0, "\033[10;10H");
	UART_putString(UART_0, "Micros y DSPs\r");
	/** VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0, "\033[11;10H");
	UART_putString(UART_0, "    ITESO\r");
	/** VT100 command for positioning the cursor in x and y position*/


	UART_putString(UART_0, "\033[13;10H");
	UART_putString(UART_0, " Opciones:\r");

	UART_putString(UART_0, "\033[15;10H");
	UART_putString(UART_0, "  1)  Leer Memoria I2C\r");

	UART_putString(UART_0, "\033[16;10H");
	UART_putString(UART_0, "  2)  Escribir memoria I2C\r");

	UART_putString(UART_0, "\033[17;10H");
	UART_putString(UART_0, "  3)  Establecer Hora\r");

	UART_putString(UART_0, "\033[18;10H");
	UART_putString(UART_0, "  4)  Establecer Fecha\r");

	UART_putString(UART_0, "\033[19;10H");
	UART_putString(UART_0, "  5)  Formato de hora\r");

	UART_putString(UART_0, "\033[20;10H");
	UART_putString(UART_0, "  6)  Leer hora\r");

	UART_putString(UART_0, "\033[21;10H");
	UART_putString(UART_0, "  7)  Leer fecha\r");

	UART_putString(UART_0, "\033[22;10H");
	UART_putString(UART_0, "  8)  Comunicación con terminal 2\r");

	UART_putString(UART_0, "\033[23;10H");
	UART_putString(UART_0, "  9)  Eco en LCD\r");

	UART_putString(UART_0, "\033[24;10H");

if(TRUE == UARTx_statusFlag(UART_0)) {
	    UARTx_clearStatusFlag(UART_0);

		if (KEY_1 == UARTx_mailBoxContent) {
			return NEXT_STATE;
		} else if (KEY_2 == UARTx_mailBoxContent) {
			return (NEXT_STATE + 1);
		} else if (KEY_3 == UARTx_mailBoxContent) {
			return (NEXT_STATE + 2);
		} else if (KEY_4 == UARTx_mailBoxContent) {
			return (NEXT_STATE + 3);
		} else if (KEY_5 == UARTx_mailBoxContent) {
			return (NEXT_STATE + 4);
		} else if (KEY_6 == UARTx_mailBoxContent) {
			return (NEXT_STATE + 5);
		} else if (KEY_7 == UARTx_mailBoxContent) {
			return (NEXT_STATE + 6);
		} else if (KEY_8 == UARTx_mailBoxContent) {
			return (NEXT_STATE + 7);
		} else if (KEY_9 == UARTx_mailBoxContent) {
			return (NEXT_STATE + 8);

		} else {
			return SAME_STATE;
		}

}

			UART0_MailBox.mailBox


	if (TRUE == readFlag_Button(Button1)) {
		clearFlag_Button(Button1);
		return NEXT_STATE;
	} else if (TRUE == readFlag_Button(Button2)) {
		clearFlag_Button(Button2);
		return (NEXT_STATE + 1);
	} else if (TRUE == readFlag_Button(Button3)) {
		clearFlag_Button(Button3);
		return (NEXT_STATE + 2);
	} else if (TRUE == readFlag_Button(Button4)) {
		clearFlag_Button(Button4);
		return (NEXT_STATE + 3);

	} else {
		return SAME_STATE;
	}
}
