/*
 * Matrix.c
 *
 *  Created on: 24/09/2016
 *      Author: Alexis
 */

#include "MK64F12.h"

#include "DataTypeDefinitions.h"
#include "Matrix.h"

uint8 password[4] = {0,0,0,0};
uint8 password_NULL[4] = {0,0,0,0};
uint8 passwordPos = 0;

uint8 decoder(uint32 PortB_Password){
	switch(PortB_Password){
	case 0:
		return 1;
		break;
	case 1:
		return 2;
		break;
	case 2:
		return 3;
		break;
	case 3:
		return 10;
		break;
	case 4:
		return 4;
		break;
	case 5:
		return 5;
		break;
	case 6:
		return 6;
		break;
	case 7:
		return 11;
		break;
	case 8:
		return 7;
		break;
	case 9:
		return 8;
		break;
	case 10:
		return 9;
		break;
	case 13:
		return 0;
		break;
	default:
		return 14;
		break;
	}
}

void Password_Pos_Handler(){
	passwordPos++;
}

void Password_Pos_Clear(){
	passwordPos = 0;
}

uint8 Password_Pos(){
	return passwordPos;
}

uint32 Digit_Edit(){
	uint32 digit_aux;
	uint32 digit;
	digit = GPIOB_PDIR;
	digit_aux = digit;
	digit = (digit >> 2)&0x00000003;
	digit_aux = (digit_aux >> 8)&0x000000F;
	return (digit | digit_aux);
}
uint8* Password_Handler(){
	uint32 digit;
	digit = Digit_Edit();
	digit = decoder(digit);
	password[passwordPos] = digit;
	if(3 == passwordPos){
		return password;
	}else{
		return password_NULL;
	}
	return password_NULL;

}

uint8 Digit_Handler(){
	uint8 digit;
	digit = Digit_Edit();
	digit = decoder(digit);
	return digit;
}
