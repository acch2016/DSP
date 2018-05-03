/*
 * menu.c
 *
 *  Created on: 16/1/2017
 *      Author: alejandrocanale
 */

#include "menu.h"

typedef const struct State {
	TransitionType (*fptr)(UART_ChannelType);
	const struct State* next[3];
} StateType;


/**Máquina de estados general. Es constante porque no queremos que se modifique y esta en memoria de programa*/
const StateType FiniteStateMachineMoore_Screen[3] = {


		{ menu,      { MENU, CHARACTER, OPERATION } },
		{ character, { CHARACTER, MENU} },
		{ operation, { OPERATION, MENU } },

};


TransitionType menu(UART_ChannelType uartChannel) {
	uint8 var_enter=0;
	//if( 2 != counter_char && 13 != var_enter ){
	if( 13 != var_enter ){

		/** VT100 command for text in Black and background in Grey*/
		UART_putString(uartChannel, "\033[0;30;47m");
		/**VT100 command for hide cursor*/
		UART_putString(uartChannel, "\e[ ? 25 l");
		/*VT100 command for clearing the screen*/
		UART_putString(uartChannel, "\033[2J");

		/** VT100 command for positioning the cursor in x and y position*/
		UART_putString(uartChannel, "\033[10;10H");
		UART_putString(uartChannel, "Programa para ingresar caracteres o para sumar y restar un número");

		UART_putString(uartChannel, "\033[12;10H");
		UART_putString(uartChannel, "Presiona enter para avanzar en el menú");

	}else{return NEXT_STATE;}

}


TransitionType character(UART_ChannelType uartChannel) {

	/** VT100 command for text in Black and background in Grey*/
	UART_putString(uartChannel, "\033[0;30;47m");
	/**VT100 command for hide cursor*/
	UART_putString(uartChannel, "\e[ ? 25 l");
	/*VT100 command for clearing the screen*/
	UART_putString(uartChannel, "\033[2J");

	/** VT100 command for positioning the cursor in x and y position*/
	UART_putString(uartChannel, "\033[10;10H");
	UART_putString(uartChannel, "Ingresa caracter");



}
