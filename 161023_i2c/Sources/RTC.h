
/**
	\file RTC.h
	\brief RTC
	\author Alexis Andal�n / Alejandro Canale
	\date	29/10/2016
 */

#ifndef SOURCES_RTC_H_
#define SOURCES_RTC_H_

#include "MK64F12.h"
#include "I2C.h"
#include "GlobalFunctions.h"

 typedef enum {
	 H24,
	 H12,
 }FormatRTCType;

 //
 /********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief Lee los segundos del RTC
  	 \param[in] void
  	 \return uint8 El dato que ley� de la RTC
  */
 uint8 RTC_get_Seconds( );
 //
 /********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief obtiene los minutos leyendo del RTC por I2C
  	 \param[in] void
  	 \return uint8 El dato que ley� de la RTC
  */
 uint8 RTC_get_Minutes( );
 //
 /********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief obtiene la hora leyendo del RTC por I2C
  	 \param[in] void
  	 \return uint8 El dato que ley� de la RTC
  */
 uint8 RTC_get_Hour( );
 //
 /********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief obtiene el dia leyendo del RTC por I2C
  	 \param[in] void
  	 \return uint8 El dato que ley� de la RTC
  */
 uint8 RTC_get_Day( );
 //
 /********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief obtiene el mes leyendo del RTC por I2C
  	 \param[in] void
  	 \return uint8 El dato que ley� de la RTC
  */
 uint8 RTC_get_Month();
 //
 /********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief obtiene el a�o leyendo del RTC por I2C
  	 \param[in] void
  	 \return uint8 El dato que ley� de la RTC
  */
 uint8 RTC_get_Year();
 //
 /********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief Cambia entre formato 12 Horas o 24 horas
  	 \param[in] FormatRTCType format un booleano que indicar� cual es el formato deseado.
  	 \return void
  */
void RTC_changeFormat(FormatRTCType format);
//
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief entrega la fecha en un string
 	 \param[in] void
 	 \return sint8 string de la fecha
 */
sint8 * RTC_get_String_Date();
//
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief entrega la hora en un string
 	 \param[in] void
 	 \return sint8 string de la hora
 */
sint8 * RTC_get_String_Hour();
//
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief escribe la hora en el RTC
 	 \param[in] uint8  character es el valor con el cual se establece la hora
 	 \return void
 */
void RTC_set_Hour(uint8  character);
//
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief escribe los minutos en el RTC
 	 \param[in] uint8  character es el valor con el cual se establecen los minutos
 	 \return void
 */
void RTC_set_Minutes(uint8  character);
//
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief escribe el d�a en el RTC
 	 \param[in] uint8  character es el valor con el cual se establece los d�as
 	 \return void
 */
void RTC_set_Day(uint8 character); //
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief escribe el mes en el RTC
 	 \param[in] uint8  character es el valor con el cual se establece el mes
 	 \return void
 */
void RTC_set_Month(uint8 character);
//
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief escribe el a�o en el RTC
 	 \param[in] uint8  character es el valor con el cual se establece el mes
 	 \return void
 */
void RTC_set_Year(uint8 character);
//
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief escribir en el RTC
 	 \param[in] uint8  Address la direcci�n en donde escribir�
 	 \param[in] uint8 Data el dato que escribir�
 	 \return void
 */
void RTC_writeData(uint8 Address, uint8 Data);
//
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief leer del RTC
 	 \param[in] uint8 Address la direcci�n en donde leer�
 	 \return uint8
 */
uint8 RTC_readData(uint8 Address);
//
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief Inicializar el RTC con hora predeterminada
 	 \param[in] void
 	 \return void
 */
void RTC_Init();
//
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief Guardar por separado los nibble
 	 \param[in] the two nibble that corresponds to the year
 	 \return void
 */
void modifyYears(sint8 yeah[]);



#endif /* SOURCES_RTC_H_ */