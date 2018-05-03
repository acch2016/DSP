/*
 * DAC.c
 *
 *  Created on: 17/9/2016
 *      Author: alejandrocanale
 */



#include "DataTypeDefinitions.h"
#include "MK64F12.h"
#include "DAC.h"
#define CIEN_VALORES 100


/** Valores para la senal senoidal */
/*static*/uint8 y_values_for_sine[] = { 127, 135, 143, 151, 159, 167, 174, 182,
		189, 196, 202, 209, 215, 220, 226, 230, 235, 239, 243, 246, 248, 250,
		252, 253, 254, 254, 254, 253, 251, 249, 247, 244, 241, 237, 233, 228,
		223, 218, 212, 206, 199, 192, 185, 178, 170, 163, 155, 147, 139, 131,
		123, 115, 107, 99, 91, 84, 76, 69, 62, 55, 48, 42, 36, 31, 26, 21, 17,
		13, 10, 7, 5, 3, 1, 0, 0, 0, 1, 2, 4, 6, 8, 11, 15, 19, 24, 28, 34, 39,
		45, 52, 58, 65, 72, 80, 87, 95, 103, 111, 119, 127 };

/** Valores para la senal triangular */
uint8 y_values_for_tri[] = { 128, 133, 139, 144, 149, 154, 160, 165, 170, 176,

181, 186, 192, 197, 202, 207, 213, 218, 223, 229,

234, 239, 244, 250, 255,

254, 249, 244, 238, 233, 228, 223, 218, 213, 207,

202, 197, 192, 187, 181, 176, 171, 166, 161, 156,

150, 145, 140, 135, 130, 124, 119, 114, 109, 104,

98, 93, 88, 83, 78, 73, 67, 62, 57, 52,

47, 41, 36, 31, 26, 21, 16, 10, 5, 0,

1, 6, 12, 17, 22, 27, 33, 38, 43, 48,

54, 59, 64, 69, 75, 80, 85, 90, 96, 101,

106, 111, 117, 122, 127 };

/** valores para la senal cuadrada */
uint8 y_values_for_square[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
		255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
		255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
		255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
		255, 255, 255, 255, 255, 255, 255, 255, 255, 255,};




void sine(){
	static uint8 sine_value=0;
	//i++;
	if(CIEN_VALORES==sine_value){

		sine_value=0;
	}
	writeDAC(y_values_for_sine[sine_value]);
	sine_value++;
};

void tri(){
	static uint8 tri_value=0;
	//i++;
	if(CIEN_VALORES==tri_value){

		tri_value=0;
	}
	writeDAC(y_values_for_tri[tri_value]);
	tri_value++;
};

void square(){
	static uint8 square_value=0;
	//i++;
	if(CIEN_VALORES==square_value){

		square_value=0;
	}
	writeDAC(y_values_for_square[square_value]);
	square_value++;
};

void writeDAC(uint8 valor){
	DAC0_DAT0L=valor;
	DAC0_DAT0H=0;
};
