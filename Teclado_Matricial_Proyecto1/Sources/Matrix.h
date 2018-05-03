/*
 *\fileMatrix.h
 *\brief Este modulo contiene las definiciones del driver del teclado matricial.
 * \date 24/09/2016
 * \Author Alexis
 */

#ifndef SOURCES_MATRIX_H_
#define SOURCES_MATRIX_H_

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 Esta funcion limpia la posicion del digito en la contrase�a
 	 \return void
 */
void Password_Pos_Handler();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 Esta funci�n retorna la contrase�a cuando esta ya se introdujo por completo
 	 \return uint8 *
 */
uint8 * Password_Handler();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 Esta funci�n retorna el digito proveniente del teclado matricial
 	 \return uint8
 */
uint8 Digit_Handler();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 Esta retorna la posici�n actual en la que se esta en el arreglo
 	 \return uint8
 */
uint8 Password_Pos();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 Esta limpia la posici�n actual en la que se esta en el arreglo
 	 \return void
 */
void Password_Pos_Clear();


#endif /* SOURCES_MATRIX_H_ */