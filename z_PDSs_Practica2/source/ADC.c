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


uint32_t ADC0_inputChannel = 0;
uint32_t ADC1_inputChannel = 0;

/** Activa el reloj para el ADC */
void ADC_clkgating(ADC_ChannelType channel)
{
	switch(channel)
	{
	case ADC_0:
		SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;//reloj del ADC
		break;
	case ADC_1:
		SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;
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
		ADC0->CFG1 |= ADC_CFG1_MODE(conversionMode);//selecciona los bits a convertir
		break;
		
	case ADC_1:
		ADC1->CFG1 |= ADC_CFG1_MODE(conversionMode);
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
			ADC0->SC3 |= ADC_SC3_AVGS(sampleSize);
			break;
			
		case ADC_1:
			ADC1->SC3 |= ADC_SC3_AVGS(sampleSize);
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
				ADC0->SC3 &= ~(ADC_SC3_AVGE_MASK);//
			else if(averageEnable == AVERAGE_ENABLE)
				ADC0->SC3 |= ADC_SC3_AVGE_MASK;
			break;
			
		case ADC_1:
			if(averageEnable == AVERAGE_DISABLE)
				ADC1->SC3 &= ~(ADC_SC3_AVGE_MASK);
			else if(averageEnable == AVERAGE_ENABLE)
				ADC1->SC3 |= ADC_SC3_AVGE_MASK;
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
uint32_t ADC_read(ADC_ChannelType channel)
{
	switch(channel)
	{
	case ADC_0:
		ADC0->SC1[0] = ADC0_inputChannel;
		///Cada que termina una conversion levanta la bandera
		while((ADC0->SC1[0] & ADC_SC1_COCO_MASK) != (ADC_SC1_COCO_MASK)){}
		//resultado de la conversion
		return ADC0->R[0];
		break;

	case ADC_1:
		ADC1->SC1[1] = ADC1_inputChannel;
		while((ADC1->SC1[1] & ADC_SC1_COCO_MASK) != (ADC_SC1_COCO_MASK)){}
		return ADC1->R[1];
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

