#ifndef FLEXTIMER_H_
#define FLEXTIMER_H_

#include "MK64F12.h"
#include "DataTypeDefinitions.h"
#include "ADC.h"
#include "GPIO.h"

/**Valores de Clock Gating*/
#define FLEX_TIMER_0_CLOCK_GATING 0x01000000
#define FLEX_TIMER_1_CLOCK_GATING 0x02000000
#define FLEX_TIMER_2_CLOCK_GATING 0x04000000
/***/
#define FLEX_TIMER_FAULTIE  0x80
#define FLEX_TIMER_FAULTM_0   0x00
#define FLEX_TIMER_FAULTM_1   0x20
#define FLEX_TIMER_FAULTM_2   0x40
#define FLEX_TIMER_FAULTM_3   0x60
#define FLEX_TIMER_CAPTEST  0x10
#define FLEX_TIMER_PWMSYNC  0x08
#define FLEX_TIMER_WPDIS    0x04
#define FLEX_TIMER_INIT     0x02
#define FLEX_TIMER_FTMEN    0x01

#define FLEX_TIMER_TOF     0x80
#define FLEX_TIMER_TOIE    0x40
#define FLEX_TIMER_CPWMS   0x20
/**Valores para el source clock*/
#define FLEX_TIMER_CLKS_0  0x00
#define FLEX_TIMER_CLKS_1  0x08
#define FLEX_TIMER_CLKS_2  0x10
#define FLEX_TIMER_CLKS_3  0x18

/**Valores del preescaler*/
#define FLEX_TIMER_PS_1    0x00
#define FLEX_TIMER_PS_2    0x01
#define FLEX_TIMER_PS_4    0x02
#define FLEX_TIMER_PS_8    0x03
#define FLEX_TIMER_PS_16    0x04
#define FLEX_TIMER_PS_32    0x05
#define FLEX_TIMER_PS_64    0x06
#define FLEX_TIMER_PS_128    0x07

#define FLEX_TIMER_PWMLOAD_CH0 0x01
#define FLEX_TIMER_PWMLOAD_CH1 0x02
#define FLEX_TIMER_PWMLOAD_CH2 0x04
#define FLEX_TIMER_PWMLOAD_CH3 0x08
#define FLEX_TIMER_PWMLOAD_CH4 0x10
#define FLEX_TIMER_PWMLOAD_CH5 0x20
#define FLEX_TIMER_PWMLOAD_CH6 0x40
#define FLEX_TIMER_PWMLOAD_CH7 0x80
#define FLEX_TIMER_LDOK        0x200

/**Valores de configuración */
#define  FLEX_TIMER_DMA   0x01
#define  FLEX_TIMER_ELSA  0x04
#define  FLEX_TIMER_ELSB  0x08
#define  FLEX_TIMER_MSA   0x10
#define  FLEX_TIMER_MSB   0x20
#define  FLEX_TIMER_CHIE  0x40
#define  FLEX_TIMER_CHF   0x80

/**Tipos enumerados para el canal del Flex timer*/
typedef enum{FTM_0,
			 FTM_1,
			 FTM_2,
}FTMType;

/**Tipos enumerados para comparar la bandera, guardar y poder hacer los cálculos de la frecuencia medida por el flextimer en input capture*/
typedef enum {
	PRIMER_VALOR,
	SEGUNDO_VALOR,
}ValorDefinitionType;

typedef enum{
	ENABLE,
	DISABLE,
}FTMState;
/**Estructura para la configuración del FTM*/
typedef struct
{
	FTMType FTM_Channel;
	uint32 FTM_ClockMask;
	uint32 FTM_SC_Mask;
	uint32 FTM_MODE_Mask;
	uint32 FTM_MOD_Mask;
	uint32 FTM_C0SC_Mask;
	uint32 FTM_CONF_Mask;
	uint32 FTM_COMBINE_Mask;

} FTM_ConfigType;


/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 /* Función de configuración del FTM.
 	 \param[in]    Recibes una dirreccion que corresponde a cada uno de los miembros de la estructura. Esto para guardar valores de configuración
 	 \return void
 */
void FTM_Init(const FTM_ConfigType * FTM_Config);;
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 /* En API menu.c se manda llamar frecuency_value() para mostrar frecuency en el display
 	 \param[in]  void
 	 \return Regresa el valor de frecuencia
 */
float frecuency_value();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 /*	 ClockGating del FTM
 	 \param[in] FTMType FTM  Recibe el canal
 	 \return void
 */
void FTM_ClockGating(FTMType FTM);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 /*Función para configurar el Registro FTMx_SC
 	 \param[in] FTMType FTM, Recibe el canal
 	 \param[in] uint32 mask, Recibe máscara correspondiente
 	 \param[in] FTMState state DISABLE o ENABLE
 	 \return void
 */
void FTM_Stat_Control(FTMType FTM, uint32 mask,FTMState g);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 /*Función para configurar el Registro FTMx_MODE
 	 \param[in] FTMType FTM, Recibe el canal
 	 \param[in] uint32 mask, Recibe máscara correspondiente
 	 \return void
 */
void FTM_MODE(FTMType FTM, uint32 mask);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 /*Función para configurar el Registro FTMx_MOD
 	 \param[in] FTMType FTM, Recibe el canal
 	 \param[in] uint32 mask, Recibe máscara correspondiente
 	 \return void
 */
void FTM_MOD(FTMType FTM, uint32 mask);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 /*Función para configurar el Registro FTMx_C0SC
	 \param[in] FTMType FTM, Recibe el canal
	 \param[in] uint32 mask, Recibe máscara correspondiente
 	 \param[in] FTMState state DISABLE o ENABLE

 	 \return void
 */
void FTM_C0SC(FTMType FTM, uint32 mask, FTMState);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 /* Función para configurar el Registro FTMx_CONF

 	 \param[in] FTMType FTM, Recibe el canal
 	 \param[in] uint32 mask, Recibe máscara correspondiente

 	 \return void
 */
void FTM_CONF(FTMType FTM, uint32 mask);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 /* Función para configurar el Registro FTMx_COMBINE

 	 \param[in] FTMType FTM, Recibe el canal
 	 \param[in] uint32 mask, Recibe máscara correspondiente

 	 \return void
 */
void FTM_COMBINE(FTMType FTM, uint32 mask);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 /* Función para actualizar el Registro CnV
 	 \param[in] FTMType FTM, Recibe el canal

 	 \param[in] Recibe el nuevo valor del channel value

 	 \return void
 */
void FTM_updateCHValue(FTMType FTM, uint16 channelValue);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 /* En API menu.c se manda llamar frecuency_value() para mostrar frecuency en el display

 	 \param[in] void

 	 \return void
 */
float frecuency_value();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 /* En API menu.c se manda llamar temp_value() para mostrar tempValue en el display

 	 \param[in] void

 	 \return tempValue Valor de la temperatura que se mostrará en el display
 */
float temp_value();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 /* En API menu.c se manda llamar clean_frecuency() para resetar el valor de la frecuencia ya que te guarda valores basura mientras esta apagado el frecuencimetro

 	 \param[in] void

 	 \return frecuency Valor de la frecuencia en 0
 */
void clean_frecuency();


#endif /* FLEXTIMER_H_ */
