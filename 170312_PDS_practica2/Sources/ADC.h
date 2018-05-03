/** adc.h	
 * 		I.	T.	E.	S.	O.
 * Sistemas con Microcontroladores y DSP's
 * Practice No: 2
 * Author: Adrián Ramos Pérez
 * Exp:	   IE692494
 * Date:   April 13th 2015
 * @brief Headers del ADC
 */

#ifndef ADC_H_
#define ADC_H_

#include "DataTypeDefinitions.h"
#include "MK64F12.h"


typedef enum {
	ADC_0,
	ADC_1
}ADC_ChannelType;


typedef enum {
	BITMODE_8_9,
	BITMODE_12_13,
	BITMODE_10_11,
	BITMODE_16_16
}ADC_ConversionModes;


typedef enum {
	DADP0,
	DADP1,
	DADP2,
	AD4,AD5,AD6,AD7,AD8,AD9,AD10, AD11, AD12, AD13, AD14, AD15, AD16, AD17,
	AD18, AD19, AD20, AD21, AD22, AD23, 
	RESERVED,
	RESERVED2,
	RESERVED3,
	TEMP_SENSOR,
	BANDGAP, 
	VREFSH, 
	VREFSL, 
	DISABLE
}ADC_InputChannels;


typedef enum {
	SAMPLES_4,
	SAMPLES_8,
	SAMPLES_16,
	SAMPLES_32
}ADC_SampleSizes;


typedef enum {
	AVERAGE_DISABLE,
	AVERAGE_ENABLE
}ADC_AverageEnables;


typedef enum {
	INTERRUPT_DISABLE,
	INTERRUPT_ENABLE
}ADC_InterruptEnables;


typedef struct {
	ADC_ChannelType ADC_Channel;
	ADC_ConversionModes ADC_Bitmode;
	ADC_InputChannels ADC_InputCh;
	ADC_SampleSizes ADC_SampleSz;
	ADC_AverageEnables ADC_AvgEn;
	ADC_InterruptEnables ADC_IRQEn;
}ADC_ConfigType;


//Activar el reloj para el ADC
void ADC_clkgating(ADC_ChannelType channel);
//Selecciona el tipo de conversion para el ADC
void ADC_conversionMode(ADC_ChannelType channel, ADC_ConversionModes conversionMode);
//Activa muestras de promedio de hardware
void ADC_averageEnable(ADC_ChannelType channel, ADC_AverageEnables averageEnable);
//Selecciona el tamaño de las muestras de promedio durante la conversion
void ADC_sampleSize(ADC_ChannelType channel, ADC_SampleSizes sampleSize);
//Selecciona el canal de ADC a ser usado
void ADC_inputChannel(ADC_ChannelType channel, ADC_InputChannels inputChannel);
//Activa las interrupciones en las conversiones completas
void ADC_interruptEnable(ADC_ChannelType channel, ADC_InterruptEnables interruptEnable);
//Inicializa el ADC usando funciones anteriores
void ADC_init(const ADC_ConfigType* ADCconfig);
//Lee la conversion del ADC
uint32 ADC_read(ADC_ChannelType channel);


#endif /* ADC_H_ */
