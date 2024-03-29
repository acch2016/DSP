/**
<event_groups.h>	\file
	\brief
		This project shows how works the emulation of a VT 100 in teraterm.
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	27/07/2015
	\todo
		To implement the UART_init function
 */

#include "MK64F12.h" /* include peripheral declarations */
#include "UART.h"/**UART device driver*/
#include "NVIC.h"/**NVIC device driver*/

#define DEBUG

#ifdef DEBUG
	#include "stdio.h"
#endif
/**This is mail box to received the information from the serial port*/
extern UART_MailBoxType UART0_MailBox;

int main(void)
{
	/**Enables the clock of PortB in order to configures TX and RX of UART peripheral*/
	SIM_SCGC5 = SIM_SCGC5_PORTB_MASK;
	/**Configures the pin control register of pin16 in PortB as UART RX*/
	PORTB_PCR(16) = PORT_PCR_MUX(3);
	/**Configures the pin control register of pin16 in PortB as UART TX*/
	PORTB_PCR(17) = PORT_PCR_MUX(3);
	/**Configures UART 0 to transmit/receive at 11520 bauds with a 21 MHz of clock core*/
	UART_init (UART_0,  21000000, BD_115200);
	//printf("UART is configured");
	//printf("UART is configured");
	/**Enables the UART 0 interrupt*/
	UART0_interruptEnable(UART_0);
	/**Enables the UART 0 interrupt in the NVIC*/
	NVIC_enableInterruptAndPriotity(UART0_IRQ, PRIORITY_10);

	/**The following sentences send strings to PC using the UART_putString function. Also, the string
	 * is coded with terminal code*/
	/** VT100 command for text in red and background in cyan*/
	UART_putString(UART_0,"\033[0;32;40m");
	/*VT100 command for clearing the screen*/
	UART_putString(UART_0,"\033[2J");
	/** VT100 command for text in red and background in green*/
	UART_putString(UART_0,"\033[0;32;41m");
	/** VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0,"\033[10;10H");
	UART_putString(UART_0, "Micros y DSPs\r");
	/** VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0,"\033[10;23H");
	UART_putString(UART_0, "Escribe un caracter: \r");
	/** VT100 command for positioning the cursor in x and y position*/


	UART_putString(UART_0, "\033[13;10H");
	UART_putString(UART_0, " Opciones:\r");

	UART_putString(UART_0, "\033[15;10H");
	UART_putString(UART_0, "  1)  Leer Memoria I2C\r");

	UART_putString(UART_0, "\033[16;10H");
	UART_putString(UART_0, "  2)  Escribir memoria I2C\r");

	UART_putString(UART_0, "\033[17;10H");
	UART_putString(UART_0, "  3)  Establecer Hora\r");

	UART_putString(UART_0, "\033[18;10H");
	UART_putString(UART_0, "  4)  Establecer Fecha\r");

	UART_putString(UART_0, "\033[19;10H");
	UART_putString(UART_0, "  5)  Formato de hora\r");

	UART_putString(UART_0, "\033[20;10H");
	UART_putString(UART_0, "  6)  Leer hora\r");

	UART_putString(UART_0, "\033[21;10H");
	UART_putString(UART_0, "  7)  Leer fecha\r");

	UART_putString(UART_0, "\033[22;10H");
	UART_putString(UART_0, "  8)  Comunicación con terminal 2\r");

	UART_putString(UART_0, "\033[23;10H");
	UART_putString(UART_0, "  9)  Eco en LCD\r");

	UART_putString(UART_0, "\033[24;10H");

	/**Enables interrupts*/
	EnableInterrupts;

	for(;;) {	   

		if(UART0_MailBox.flag)
			{
				/**Sends to the PCA the received data in the mailbox*/
				UART_putChar (UART_0, UART0_MailBox.mailBox);

				/**clear the reception flag*/
				UART0_MailBox.flag =0;
			}
	}
	
	return 0;
}
