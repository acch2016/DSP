/*
 * UART.c
 *
 *  Created on: 11/10/2016
 *      Author: Alexis
 */
#include "UART.h"
#define UART_MASK_C4 0x1F

UART_MailBoxType UART0_MailBox;
UART_MailBoxType UART1_MailBox;

volatile uint8* UARTx_C2[6] = {&UART0_C2, &UART1_C2, &UART2_C2, &UART3_C2, &UART4_C2, &UART5_C2};
volatile uint8* UARTx_C4[6] = {&UART0_C4, &UART1_C4, &UART2_C4, &UART3_C4, &UART4_C4, &UART5_C4};
volatile uint8* UARTx_BDL[6] = {&UART0_BDL, &UART1_BDL, &UART2_BDL,&UART3_BDL, &UART4_BDL, &UART5_BDL};
volatile uint8* UARTx_BDH[6] = {&UART0_BDH, &UART1_BDH, &UART2_BDH,&UART3_BDH, &UART4_BDH, &UART5_BDH};
volatile uint8* UARTx_D[6] = {&UART0_D, &UART1_D, &UART2_D,&UART3_D, &UART4_D, &UART5_D};

void UART0_RX_TX_IRQHandler(){
	while((UART0_S1&UART_S1_RDRF_MASK)){
	UART0_MailBox.mailBox = UART0_D;
	UART0_MailBox.flag = TRUE;
	}
}

void UART1_RX_TX_IRQHandler(){
	while((UART1_S1&UART_S1_RDRF_MASK)){
	UART0_MailBox.mailBox = UART1_D;
	UART0_MailBox.flag = TRUE;
	}
}
uint8 UARTx_statusFlag(UART_ChannelType uartChannel){
	switch(uartChannel){
	case UART_0:
		return UART0_MailBox.flag;
		break;
	case UART_1:
		return UART1_MailBox.flag;
		break;
	default:
		return 0;
	}
}

uint8 UARTx_mailBoxContent(UART_ChannelType uartChannel){
	switch(uartChannel){
	case UART_0:
		return UART0_MailBox.mailBox;
		break;
	case UART_1:
		return UART1_MailBox.mailBox;
		break;
	default:
		return 0;
	}
}

uint8 UARTx_Clear_mailBoxContent(UART_ChannelType uartChannel){
	switch(uartChannel){
	case UART_0:
		UART0_MailBox.mailBox = FALSE;
		break;
	case UART_1:
		UART1_MailBox.mailBox = FALSE;
		break;
	default:
		return 0;
	}
}


uint8 UARTx_S1(UART_ChannelType uartChannel){
	switch(uartChannel){
	case UART_0:
		return UART0_S1;
		break;
	case UART_1:
		return UART1_S1;
		break;
	case UART_2:
		return UART2_S1;
		break;
	case UART_3:
		return UART3_S1;
		break;
	case UART_4:
		return UART4_S1;
		break;
	case UART_5:
		return UART5_S1;
		break;
	}
}

uint8 UARTx_clearStatusFlag(UART_ChannelType uartChannel){
	switch(uartChannel){
	case UART_0:
		UART0_MailBox.flag = FALSE;
		break;
	case UART_1:
		UART1_MailBox.flag = FALSE;
		break;
	default:
		return 0;
	}
}

void UART0_interruptEnable(UART_ChannelType uartChannel){
	*UARTx_C2[uartChannel] |= UART_C2_ILIE_MASK;
}

void UARTx_clockEnable(UART_ChannelType uartChannel){
	switch(uartChannel){
	case UART_0:
		SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;
		break;
	case UART_1:
		SIM_SCGC4 |= SIM_SCGC4_UART1_MASK;
		break;
	case UART_2:
		SIM_SCGC4 |= SIM_SCGC4_UART2_MASK;
		break;
	case UART_3:
		SIM_SCGC4 |= SIM_SCGC4_UART3_MASK;
		break;
	case UART_4:
		SIM_SCGC1 |= SIM_SCGC1_UART4_MASK;
		break;
	case UART_5:
		SIM_SCGC1 |= SIM_SCGC1_UART5_MASK;
		break;
	}
}

void UART_init(UART_ChannelType uartChannel, uint32 systemClk, UART_BaudRateType baudRate){
	uint16 UARTbdrt = systemClk/(16*baudRate);
	uint8 UARTbrfd = (systemClk/(16*baudRate)-UARTbdrt)*32;
	UARTx_clockEnable(uartChannel);
	*UARTx_BDL[uartChannel] = UARTbdrt;
	*UARTx_BDH[uartChannel] = ((UARTbdrt>>8)&(0x1F));
	*UARTx_C4[uartChannel] = (UARTbrfd & UART_MASK_C4);
	*UARTx_C2[uartChannel] |= UART_C2_TE_MASK|UART_C2_RE_MASK;
}

void UART_putChar (UART_ChannelType uartChannel, uint8 character){
	while(!(UARTx_S1(uartChannel) & UART_S1_TDRE_MASK));
	*UARTx_D[uartChannel] = character;
}

void UART_putString(UART_ChannelType uartChannel, sint8* string){
	while (*string){
		UART_putChar(uartChannel, *string++);
	}
}
