///*
// * FSMLCD.c
// *
// *  Created on: 1/11/2016
// *      Author: alejandrocanale
// */
//
///**Se mandan llamar los archivos que contienen las declaraciones de funciones que usara el m�dulo */
//#include "MK64F12.h"
//#include "DataTypeDefinitions.h"
//
//
//
//
//
//
///**Se utiliz� tipos enumerados y estructuras para formar la m�quina de estados*/
//typedef const struct State {
//
//	TransitionType (*ftprScreen)();
//	const struct State* next[7];
//} StateType;
//
//
///**M�quina de estados general. Es constante porque no queremos que se modifique y esta en memoria de programa*/
//const StateType FineStateMachineMoore_Keyboard[10]=
//{
//		{ menuLCD, { MENU_LCD, SET_HOUR, SET_DATE, ECHO_LCD }},
//		{ setHour, { SET_HOUR, MENU_LCD }},
//		{ setDate, { SET_DATE, MENU_LCD }},
//		{ echoLCD, { ECHO_LCD, MENU_LCD }},
//
//};
//
//
//StateType* currentState = MENU_LCD;
//TransitionType currentState_flag;
//uint8 flag_screen = FALSE;
