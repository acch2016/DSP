/*
 * Botones.h
 *
 *  Created on: 13/03/2017
 *      Author: Andrea
 */

#include "pin_mux.h"
#include "board.h"
#include "clock_config.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_debug_console.h"
#include "ADC.h"
#include "DAC.h"
#include "PIT.h"

typedef enum{
	PIN0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,
	PIN8,
}PinType;

bool Flag_ButtonPressed;

void Buttons_Config(void);
void setFlag_ButtonPressed(void);
void clearFlag_ButtonPressed(void);
bool getFlag_ButtonPressed();
void menu_ButtonPressed(uint8_t buttonPressed);
void changeSamplingFrequency(bool changeSamplingFrequency);
void changeSignalAmplitud(bool changeAmplitud);
void change_h1Scaler(bool change_h1Scaler);
void change_h2Scaler(bool change_h2Scaler);
float get_SignalOutput(uint16_t signalInput);
void set_NewSignalInput(uint16_t signalInput);
float convolution_h1();
float convolution_h2();

float get_SignalAmplitudScaler(void);
void set_SignalAmplitudScaler(float newAmplitudScaler);
float get_h1Scaler(void);
void set_h1Scaler(float new_h1Scaler);
float get_h2Scaler(void);
void set_h2Scaler(float new_h2Scaler);


