/*
 * UART.c
 *
 *  Created on: 11/10/2016
 *      Author: Alexis
 */
#include "UART.h"

UART_MailBoxType UART0_MailBox;

void UART0_RX_TX_IRQHandler(){
	while((UART0_S1 & UART_S1_RDRF_MASK)){

	UART0_MailBox.mailBox = UART0_D;
	UART0_MailBox.flag = TRUE;
}return 0;
}
void UART0_interruptEnable(UART_ChannelType uartChannel){
//	while(!(UART0_S1&UART_S1_RDRF_MASK));
	UART0_C2 |= 0x20;
}

void UART_init(UART_ChannelType uartChannel, uint32 systemClk, UART_BaudRateType baudRate){
	uint16 UARTbdrt = systemClk/(16*baudRate);
	uint8 UARTbrfd = ((systemClk/(16*baudRate))-UARTbdrt)*32;
	SIM_SCGC4 |= 0x400;
	UART0_C2 &= ~(0xC);

	UART0_BDL = UARTbdrt&(0xFF);
	UART0_BDH = 0x0;//~(0x1F); //(uint8)((UARTbdrt>>8)&(0x1F))
	UART0_C4 |= UARTbrfd&(0x1F);
	UART0_C2 |= 0xC;
}

void UART_putChar (UART_ChannelType uartChannel, uint8 character){
	while(!(UART0_S1 & UART_S1_TC_MASK));
	UART0_D = character;
}

void UART_putString(UART_ChannelType uartChannel, sint8* string){
	while (*string){
		UART_putChar(uartChannel, *string++);
	}
}
