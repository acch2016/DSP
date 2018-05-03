/**
 \file main.c
 \brief Archivo principal de donde se configura, se hacen inicializaciones y se mandan llamar las funciones principales.
 \author Alexis Andalón
 \date 28 de septiembre de 2016
 \todo tal vez se necesite hacer un modulo de inicializaciones
*/

/**Se mandan llamar los archivos que contienen las declaraciones de funciones que usara el módulo */
#include "MK64F12.h"
#include "DataTypeDefinitions.h"

#include "PIT.h"
#include "NVIC.h"
#include "FUNC.h"
#include "GPIO.h"
#include "Matrix.h"
#include "MOTOR.h"

/**Macros de definición. Es para el compilador. Facilita la lectura del código*/
#define SYSTEM_CLOCK 	21000000 //Clock Frequency
#define A 				10
#define B 				11
#define LED1_MOTOR 		18
#define LED2_MOTOR 		19
#define MOTOR 			1
#define BIT0_TECLADO 	2
#define BIT1_TECLADO 	3
#define BIT2_TECLADO 	10
#define BIT3_TECLADO 	11
#define IQR_TECLADO 	20
#define LED_INICIO		11
#define LED_ERROR 		10
#define LED1_WAVE 		24
#define LED2_WAVE 		25
#define SWITCH_2 		6
#define SWITCH_3 		4
#define LED_RGB_RED		22
#define LED_RGB_GREEN	26
#define LED_RGB_BLUE	21

/**Funciones que se utilizan en el modulo*/
uint8 initiation_State();
uint8 wait_Option();
uint8 wait_Password_A();
uint8 wait_Password_B();
uint8 led_Error_A();
uint8 led_Error_B();
uint8 blink_A();
uint8 blink_B();
uint8 wave_Generator();
uint8 motor_Control();
void register_Config();

uint8 password_INIC[4] = {1,2,3,4};
uint8 password_A[4] = {4,5,6,7};
uint8 password_B[4] = {7,8,9,0};
uint8 Flag_Enable_Motor = FALSE;
uint8 Flag_Enable_Generator = FALSE;
uint8 counter_periods = 0;

typedef enum {
	INITIATION,
	WAIT_OPTION,
	WAIT_PASSWORD_A,
	BLINK_A,
	LED_ERROR_A,
	WAIT_PASSWORD_B,
	BLINK_B,
	LED_ERROR_B,
	WAVE_GEN,
	MOTOR_CONTROL,
}StateDefinitionType;

/**Se utilizó tipos enumerados y estructuras para formar la máquina de estados*/
typedef struct
{
	StateDefinitionType function_state;
	uint8 next[3];
}StateType;

/**Máquina de estados general. Es constante porque no queremos que se modifique y esta en memoria de programa*/
const StateType FineStateMachineMoore_Keyboard[10]=
{
		{INITIATION,{INITIATION,WAIT_OPTION}},
		{WAIT_OPTION,{WAIT_OPTION, WAIT_PASSWORD_A,WAIT_PASSWORD_B}},
		{WAIT_PASSWORD_A,{WAIT_PASSWORD_A,BLINK_A,LED_ERROR_A}},
		{BLINK_A,{BLINK_A,MOTOR_CONTROL}},
		{LED_ERROR_A,{LED_ERROR_A,WAIT_PASSWORD_A}},
		{WAIT_PASSWORD_B,{WAIT_PASSWORD_B,BLINK_B,LED_ERROR_B}},
		{BLINK_B,{BLINK_B,WAVE_GEN}},
		{LED_ERROR_B,{LED_ERROR_B,WAIT_PASSWORD_B}},
		{WAVE_GEN,{WAVE_GEN,WAIT_PASSWORD_A}},
		{MOTOR_CONTROL,{MOTOR_CONTROL, WAIT_PASSWORD_B}},
};

//Main del Programa
int main(void)
{

	StateDefinitionType currentState_Keyboard = INITIATION;
	StateDefinitionType newState = 0;
	uint8 (*function_state[10])() = {initiation_State,wait_Option,wait_Password_A,blink_A,led_Error_A,wait_Password_B,blink_B,led_Error_B,wave_Generator,motor_Control};

	register_Config();

	for (;;) {
		currentState_Keyboard = FineStateMachineMoore_Keyboard[currentState_Keyboard].function_state;
		newState = (*function_state[currentState_Keyboard])();
		currentState_Keyboard = FineStateMachineMoore_Keyboard[currentState_Keyboard].next[newState];
		FSM_Motor(Flag_Enable_Motor);
		FSM_signals(Flag_Enable_Generator);

	}

	return 0;
}



//-----------------------------------FUNCTIONS----------------------------------


void register_Config(){
	GPIO_pinControlRegisterType pinControlRegister = GPIO_MUX1;
	GPIO_pinControlRegisterType pinControlRegisterSwitch = GPIO_MUX1|GPIO_PE|GPIO_PS|INTR_FALLING_EDGE;/**Detectan el flanco de bajada del push boton*/
	GPIO_pinControlRegisterType pinControlRegisterTeclado = GPIO_MUX1|GPIO_PE|GPIO_PS|INTR_RISING_EDGE;/**Detectan el flanco de subida del intergado 74C922*/
	GPIO_pinControlRegisterType pinControlRegisterIQR = GPIO_MUX1|GPIO_PE|GPIO_PS|INTR_RISING_EDGE;/**Detectan el flanco de subida del intergado 74C922*/

	SIM_SCGC2  |= SIM_SCGC2_DAC0_MASK;/**Activar el reloj del DAC0*/
	SIM_SCGC6 |= SIM_SCGC6_PIT_MASK; /**Activa reloj del PIT, bit 23 que corresponde a este número hexadecimal 0x800000*/

	/**Inicializaciones del DAC*/
	DAC0_C0 |= DAC_C0_DACEN_MASK;/**Habilitar el pin del DAC*/
	DAC0_C0 |= DAC_C0_DACRFS_MASK;/**Habilitar la referencia en el pin del DAC*/



	PIT_MCR = 0x00;/**Asegurarse que no se deshabilitan los PIT*/


	//Activar el reloj de los puertos que utilizaremos
	GPIO_clockGating(GPIOB);
	GPIO_clockGating(GPIOC);
	GPIO_clockGating(GPIOE);
	GPIO_clockGating(GPIOA);

	/**configurar pines como perifericos de entrada/salida para uso del teclado*/
	GPIO_pinControlRegister(GPIOB, BIT0_TECLADO, &pinControlRegisterTeclado);
	GPIO_pinControlRegister(GPIOB, BIT1_TECLADO, &pinControlRegisterTeclado);
	GPIO_pinControlRegister(GPIOB, BIT2_TECLADO, &pinControlRegisterTeclado);
	GPIO_pinControlRegister(GPIOB, BIT3_TECLADO, &pinControlRegisterTeclado);
	GPIO_pinControlRegister(GPIOB, IQR_TECLADO, &pinControlRegisterIQR);
	/**configurar pines como perifericos de entrada/salida para uso de LEDS iniciales*/
	GPIO_pinControlRegister(GPIOC, LED_INICIO, &pinControlRegister);
	GPIO_pinControlRegister(GPIOC, LED_ERROR, &pinControlRegister);
	/**configurar pines como perifericos de entrada/salida para uso de los LEDS del motor*/
	GPIO_pinControlRegister(GPIOB, LED1_MOTOR, &pinControlRegister);
	GPIO_pinControlRegister(GPIOB, LED2_MOTOR, &pinControlRegister);
	/**configurar pines como perifericos de entrada/salida para uso del LED RGB*/
	GPIO_pinControlRegister(GPIOB, LED_RGB_RED, &pinControlRegister);
	GPIO_pinControlRegister(GPIOB, LED_RGB_BLUE, &pinControlRegister);
	GPIO_pinControlRegister(GPIOE, LED_RGB_GREEN, &pinControlRegister);
	/**configurar pine como perifericos de entrada/salida para uso del motor*/
	GPIO_pinControlRegister(GPIOC, MOTOR, &pinControlRegister);
	/**configurar pines como perifericos de entrada/salida para uso de los leds del generador de señales*/
	GPIO_pinControlRegister(GPIOE, LED1_WAVE, &pinControlRegister);
	GPIO_pinControlRegister(GPIOE, LED2_WAVE, &pinControlRegister);
	/**configurar pines como perifericos de entrada/salida para uso de los switch*/
	GPIO_pinControlRegister(GPIOC, SWITCH_2, &pinControlRegisterSwitch);
	GPIO_pinControlRegister(GPIOA, SWITCH_3, &pinControlRegisterSwitch);

	/**Perifericos como entrada*/
	GPIO_dataDirectionPIN(GPIOB,GPIO_INPUT, BIT0_TECLADO);
	GPIO_dataDirectionPIN(GPIOB,GPIO_INPUT, BIT1_TECLADO);
	GPIO_dataDirectionPIN(GPIOB,GPIO_INPUT, BIT2_TECLADO);
	GPIO_dataDirectionPIN(GPIOB,GPIO_INPUT, BIT3_TECLADO);
	GPIO_dataDirectionPIN(GPIOB,GPIO_INPUT, IQR_TECLADO);
	GPIO_dataDirectionPIN(GPIOC,GPIO_INPUT, SWITCH_2);
	GPIO_dataDirectionPIN(GPIOA,GPIO_INPUT, SWITCH_3);

	/**Perifericos como salida*/
	GPIO_dataDirectionPIN(GPIOC,GPIO_OUTPUT, LED_INICIO);
	GPIO_dataDirectionPIN(GPIOC,GPIO_OUTPUT, LED_ERROR);
	GPIO_dataDirectionPIN(GPIOB,GPIO_OUTPUT, LED1_MOTOR);
	GPIO_dataDirectionPIN(GPIOB,GPIO_OUTPUT, LED2_MOTOR);
	GPIO_dataDirectionPIN(GPIOB,GPIO_OUTPUT, LED_RGB_RED);
	GPIO_dataDirectionPIN(GPIOB,GPIO_OUTPUT, LED_RGB_BLUE);
	GPIO_dataDirectionPIN(GPIOE,GPIO_OUTPUT, LED_RGB_GREEN);
	GPIO_dataDirectionPIN(GPIOE,GPIO_OUTPUT, LED1_WAVE);
	GPIO_dataDirectionPIN(GPIOE,GPIO_OUTPUT, LED2_WAVE);
	GPIO_dataDirectionPIN(GPIOC,GPIO_OUTPUT, MOTOR);


	/**Asignar valor seguro. (Apagar)*/
	GPIO_setPIN(GPIOC, LED_INICIO);
	GPIO_setPIN(GPIOC, LED_ERROR);
	GPIO_setPIN(GPIOE, LED1_WAVE);
	GPIO_setPIN(GPIOE, LED2_WAVE);
	GPIO_setPIN(GPIOE, LED_RGB_GREEN);
	GPIO_setPIN(GPIOB, LED_RGB_BLUE);
	GPIO_setPIN(GPIOB, LED_RGB_RED);
	GPIO_setPIN(GPIOB, LED1_MOTOR);
	GPIO_setPIN(GPIOB, LED2_MOTOR);
	GPIO_clearPIN(GPIOC, MOTOR);

	//Habilitar Interrupciones globales y prioridades
	NVIC_setBASEPRI_threshold(PRIORITY_9);
	NVIC_enableInterruptAndPriotity(PIT_CH2_IRQ, PRIORITY_8);
	NVIC_enableInterruptAndPriotity(PIT_CH1_IRQ, PRIORITY_7);
	NVIC_enableInterruptAndPriotity(PIT_CH0_IRQ, PRIORITY_6);
	NVIC_enableInterruptAndPriotity(PORTC_IRQ, PRIORITY_5);
	NVIC_enableInterruptAndPriotity(PORTA_IRQ, PRIORITY_4);
	NVIC_enableInterruptAndPriotity(PORTB_IRQ, PRIORITY_3);
	EnableInterrupts;




}

uint8 array_Compare(uint8* first, uint8 *second, uint8 index){
	int counter_array_pos;
	for(counter_array_pos = 0; counter_array_pos < index; counter_array_pos++){
		if(*(first + counter_array_pos) != *(second + counter_array_pos)){
			return FALSE;
		}
	}
	return TRUE;
}
/**Función para encender el LED RGB en rojo, considerando lógica inversa y asegurando de apagar el verde y el azul antes*/
void RED_ON(){
	GPIO_setPIN(GPIOE, LED_RGB_GREEN);
	GPIO_setPIN(GPIOB, LED_RGB_BLUE);
	GPIO_clearPIN(GPIOB, LED_RGB_RED);
}
/**Función para encender el LED RGB en verde, considerando lógica inversa y asegurando de apagar el azul y el rojo antes*/
void GREEN_ON(){
	GPIO_clearPIN(GPIOE, LED_RGB_GREEN);
	GPIO_setPIN(GPIOB, LED_RGB_BLUE);
	GPIO_setPIN(GPIOB, LED_RGB_RED);
}
/**Función para encender el LED RGB en azul, considerando lógica inversa y asegurando de apagar el verde y el rojo antes*/
void BLUE_ON(){
	GPIO_setPIN(GPIOE, LED_RGB_GREEN);
	GPIO_clearPIN(GPIOB, LED_RGB_BLUE);
	GPIO_setPIN(GPIOB, LED_RGB_RED);
}

void clean_flags_IQR(){
	clearFlag_PORTA();
	clearFlag_PORTC();
}

/**-----------------------------------State Functions---------------------------------------*/
/********************************************************************************************/
/*!
 \brief  compara la contraseña 1234 y sino prende el LED rojo
 \return void
 */
uint8 initiation_State(){
	uint8* password_check;
	clean_flags_IQR();
	if(TRUE == (FlagPortB_Read())){
		password_check = Password_Handler();
		Password_Pos_Handler();
		FlagPortB_Clear();

		if(TRUE == (array_Compare(password_INIC,password_check,4)) && Password_Pos() == 4){
			Password_Pos_Clear();
			GPIO_clearPIN(GPIOC, LED_INICIO);
			GPIO_setPIN(GPIOC, LED_ERROR);
			return WAIT_OPTION;
		}
		else if(FALSE == (array_Compare(password_INIC,password_check,4)) && Password_Pos() == 4){
			Password_Pos_Clear();
			GPIO_clearPIN(GPIOC, LED_ERROR);
			return INITIATION;

		}else{
			return INITIATION;
		}
	}else{
		return INITIATION;
	}
}
/********************************************************************************************/
/*!
 \brief  espera a que se ingrese A o B para avanzar al siguiente estado
 \return void
 */

uint8 wait_Option(){
	clean_flags_IQR();
	uint8 digit;
	BLUE_ON();
	if(TRUE == (FlagPortB_Read())){
		digit = Digit_Handler();
		FlagPortB_Clear();
	}
	if(digit == A){
		return WAIT_PASSWORD_A - 1;
	}
	else if(digit == B){
		return WAIT_PASSWORD_B - 3;
	}else{
		return WAIT_OPTION - 1;
	}
}

/********************************************************************************************/
/*!
 \brief  si se presionó A, ingresa a comparar arrays de la contraseña para el motor 4567
 \return void
 */

uint8 wait_Password_A(){
	clean_flags_IQR();
	GPIO_setPIN(GPIOC,LED_INICIO);
	uint8* password_check;
	BLUE_ON();
	if(TRUE == (FlagPortB_Read())){
		password_check = Password_Handler();
		Password_Pos_Handler();
		FlagPortB_Clear();

		if(TRUE == (array_Compare(password_A,password_check,4))&& Password_Pos() == 4){
			Password_Pos_Clear();
			return BLINK_A - 2;
		}
		else if(TRUE != (array_Compare(password_A,password_check,4))&& Password_Pos() == 4){
			Password_Pos_Clear();
			return LED_ERROR_A - 2;
		}else{
			return WAIT_PASSWORD_A - 2;
		}
	}else{
		return WAIT_PASSWORD_A - 2;
	}
}

/********************************************************************************************/
/*!
 \brief  si se presionó B, ingresa a comparar arrays de la contraseña para el motor 7890
 \return void
 */

uint8 wait_Password_B(){
	clean_flags_IQR();
	GPIO_setPIN(GPIOC,LED_INICIO);
	uint8* password_check;
	BLUE_ON();
	if(TRUE == (FlagPortB_Read())){
		password_check = Password_Handler();
		Password_Pos_Handler();
		FlagPortB_Clear();

		if(TRUE == (array_Compare(password_B,password_check,4))&& Password_Pos() == 4){
			Password_Pos_Clear();
			return BLINK_B - 5;
		}
		else if(TRUE != (array_Compare(password_B,password_check,4))&& Password_Pos() == 4){
			Password_Pos_Clear();
			return LED_ERROR_B - 5;
		}else{
			return WAIT_PASSWORD_B - 5;
		}
	}else{
		return WAIT_PASSWORD_B - 5;
	}
}

/********************************************************************************************/
/*!
 \brief  si la contraseña A fue erronea , hace blink del led error
 \return void
 */
uint8 led_Error_A(){

	GPIO_setPIN(GPIOC,LED_INICIO);
	if(TRUE == PIT2_Flag_read())
		PIT_delay(PIT_2,SYSTEM_CLOCK,1);
		PIT2_Flag_clear();
		counter_periods++;
		GPIO_tooglePIN(GPIOC,LED_ERROR);
		if(counter_periods == 4){
			counter_periods = 0;
			return WAIT_PASSWORD_A - 1;
	}
		return LED_ERROR_A-4;
}

/********************************************************************************************/
/*!
 \brief  si la contraseña B fue erronea, hace blink del led error
 \return void
 */
uint8 led_Error_B(){
	GPIO_setPIN(GPIOC,LED_INICIO);
	if(TRUE == PIT2_Flag_read())
		PIT_delay(PIT_2,SYSTEM_CLOCK,1);
		PIT2_Flag_clear();
		counter_periods++;
		GPIO_tooglePIN(GPIOC,LED_ERROR);
		if(counter_periods == 4){
			counter_periods = 0;
			return WAIT_PASSWORD_B - 4;
	}
		return LED_ERROR_B-6;
}

/********************************************************************************************/
/*!
 \brief  si la contraseña B fue correcta, hace blink del led Blink_A
 \return void
 */
uint8 blink_A(){

	GPIO_setPIN(GPIOC,LED_INICIO);
	if(TRUE == PIT2_Flag_read())
		PIT_delay(PIT_2,SYSTEM_CLOCK,1);
		PIT2_Flag_clear();
		counter_periods++;
		GPIO_tooglePIN(GPIOC,LED_ERROR);
		if(counter_periods == 4){
			counter_periods = 0;
			return MOTOR_CONTROL - 9;
	}
		return BLINK_A-3;
}

/********************************************************************************************/
/*!
 \brief  si la contraseña B fue verdadera, hace blink del led Blink_B
 \return void
 */
uint8 blink_B(){

	GPIO_setPIN(GPIOC,LED_INICIO);
	if(TRUE == PIT2_Flag_read())
		PIT_delay(PIT_2,SYSTEM_CLOCK,1);
		PIT2_Flag_clear();
		counter_periods++;
		GPIO_tooglePIN(GPIOC,LED_ERROR);
		if(counter_periods == 4){
			counter_periods = 0;
			return WAVE_GEN - 7;
	}
		return BLINK_B-6;
	}


/********************************************************************************************/
/*!
 \brief maneja bandera que habilita boton del control de señales
 \return void
 */
uint8 wave_Generator(){
	uint8 digit;
	Flag_Enable_Generator = TRUE;
	GREEN_ON();
	if(TRUE == (FlagPortB_Read())){
		digit = Digit_Handler();
		FlagPortB_Clear();
	}
	if(A == digit){
		Flag_Enable_Generator = FALSE;
		return WAIT_PASSWORD_A - 1;
	}else{
		return WAVE_GEN - 8;
	}
}

/********************************************************************************************/
/*!
 \brief  maneja bandera que habilita boton del control de motor
 \return void
 */

uint8 motor_Control(){
	uint8 digit;
	Flag_Enable_Motor = TRUE;
	RED_ON();
	if(TRUE == (FlagPortB_Read())){
		digit = Digit_Handler();
		FlagPortB_Clear();
	}
	if(B == digit){
		Flag_Enable_Motor = FALSE;
		return WAIT_PASSWORD_B - 4;
	}else{
		return MOTOR_CONTROL - 9;
	}
}


////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
