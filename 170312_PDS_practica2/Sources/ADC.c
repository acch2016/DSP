/*
 * ADC.c
 *
 *		I.	T.	E.	S.	O.
 * Sistemas con Microcontroladores y DSP's
 * Author: Adrián Ramos Pérez, Alejandrino Ponce y Daniel Flores
 * Date:   Octubre 2016
 * @ Implementación del ADC
 */

#include "ADC.h"


uint32 ADC0_inputChannel = 0;
uint32 ADC1_inputChannel = 0;

/** Activa el reloj para el ADC */
void ADC_clkgating(ADC_ChannelType channel)
{
	switch(channel)
	{
	case ADC_0:
		SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK;//reloj del ADC
		break;
	case ADC_1:
		SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK;
		break;
		
	default:
		break;
	}
}
/////////////////////////////////////////////

/** CONFIGURA el tipo de conversion para el ADC */
void ADC_conversionMode(ADC_ChannelType channel, ADC_ConversionModes conversionMode)
{
	switch(channel)
	{
	case ADC_0:
		ADC0_CFG1 |= ADC_CFG1_MODE(conversionMode);//selecciona los bits a convertir
		break;
		
	case ADC_1:
		ADC1_CFG1 |= ADC_CFG1_MODE(conversionMode);
		break;
		
	default:
		break;
	}
}

/** Selecciona el canal de ADC a ser usado */
void ADC_inputChannel(ADC_ChannelType channel, ADC_InputChannels inputChannel)
{
	switch(channel)
		{
		case ADC_0:
			ADC0_inputChannel |= inputChannel;
			break;
			
		case ADC_1:
			ADC1_inputChannel |= inputChannel;
			break;
			
		default:
			break;
		}
}


//Selecciona el tamaño de las muestras de promedio durante la conversion
void ADC_sampleSize(ADC_ChannelType channel, ADC_SampleSizes sampleSize)
{
	switch(channel)
		{
		case ADC_0:
			//seleciona el tamaño de muestras a elegir que exige 32
			ADC0_SC3 |= ADC_SC3_AVGS(sampleSize);
			break;
			
		case ADC_1:
			ADC1_SC3 |= ADC_SC3_AVGS(sampleSize);
			break;
			
		default:
			break;
		}
}

//Activa muestras de promedio de hardware
void ADC_averageEnable(ADC_ChannelType channel, ADC_AverageEnables averageEnable)
{
	switch(channel)
		{
		case ADC_0:
			if(averageEnable == AVERAGE_DISABLE)
				ADC0_SC3 &= ~(ADC_SC3_AVGE_MASK);//
			else if(averageEnable == AVERAGE_ENABLE)
				ADC0_SC3 |= ADC_SC3_AVGE_MASK;
			break;
			
		case ADC_1:
			if(averageEnable == AVERAGE_DISABLE)
				ADC1_SC3 &= ~(ADC_SC3_AVGE_MASK);
			else if(averageEnable == AVERAGE_ENABLE)
				ADC1_SC3 |= ADC_SC3_AVGE_MASK;
			break;
			
		default:
			break;
		}
}

//Activa las interrupciones en las conversiones completas
void ADC_interruptEnable(ADC_ChannelType channel, ADC_InterruptEnables interruptEnable)
{
	switch(channel)
		{
		case ADC_0:
			if(interruptEnable == INTERRUPT_DISABLE)
				ADC0_inputChannel &= ~(ADC_SC1_AIEN_MASK);
			else if(interruptEnable == INTERRUPT_ENABLE)
				///Permite la interrupcion de conversion completas cuando AIEN  esta en alto
				ADC0_inputChannel |= ADC_SC1_AIEN_MASK;
			break;
			
		case ADC_1:
			if(interruptEnable == INTERRUPT_DISABLE)
				ADC1_inputChannel = ADC_SC1_AIEN_MASK;
			else if(interruptEnable == INTERRUPT_ENABLE)
				ADC1_inputChannel |= ADC_SC1_AIEN_MASK;
			break;
			
		default:
			break;
		}
}

/**AQUÍ LA FUNCIÓN DE LECTURA DEVUELVE UN ENTERO DE PRECISIÓN-32 BITS DE LA LECTURA DEL ADC*/
uint32 ADC_read(ADC_ChannelType channel)
{
	switch(channel)
	{
	case ADC_0:
		ADC0_SC1A = ADC0_inputChannel;
		///Cada que termina una conversion levanta la bandera
		while((ADC0_SC1A & ADC_SC1_COCO_MASK) != (ADC_SC1_COCO_MASK)){}
		//resultado de la conversion
		return ADC0_RA;
		break;

	case ADC_1:
		ADC1_SC1A = ADC1_inputChannel;
		while((ADC1_SC1A & ADC_SC1_COCO_MASK) != (ADC_SC1_COCO_MASK)){}
		return ADC1_RA;
		break;
	default:
		break;
	}
}



//Inicializa el ADC usando funciones anteriores
void ADC_init(const ADC_ConfigType* ADCconfig)
{
	ADC_clkgating(ADCconfig->ADC_Channel);
	ADC_conversionMode(ADCconfig->ADC_Channel, ADCconfig->ADC_Bitmode);
	ADC_inputChannel(ADCconfig->ADC_Channel, ADCconfig->ADC_InputCh);
	ADC_sampleSize(ADCconfig->ADC_Channel, ADCconfig->ADC_SampleSz);
	ADC_averageEnable(ADCconfig->ADC_Channel, ADCconfig->ADC_AvgEn);
	ADC_interruptEnable(ADCconfig->ADC_Channel, ADCconfig->ADC_IRQEn);
}

