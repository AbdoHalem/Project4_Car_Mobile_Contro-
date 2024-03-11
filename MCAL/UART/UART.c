/*
 * UART.c
 *
 *  Created on: Nov 30, 2023
 *      Author: Abdo Halem
 */

#include "UART.h"

static void (*RXC_InterruptHandler)(void) = NULL;

void UART_init(void){
	UBRRL = 51;   //Buad_rate = Fosc/16(UBBR+1)
	UART_RECEIVER_ENABLE();
	/* Set Data Frame Format */
	UART_8_DATA_BITS_SELECT();
	/* Select Parity Mode */
	UART_DISABLE_PARITY_MODE();
	/* Enable RXC Interrupt */
	GIE_BIT_ENABLE();
	UART_RECEIVER_RXC_INTERRUPT_ENABLE();
}

// Have bugs need to be fixed
void UART_Init(){
	/* Save status register value */
	uint8 interrupt_status= SREG;
	GIE_BIT_DISABLE();
	/* Select USART mode */
#if (UART_ASYNCHRONOUS_MODE_ENABLED == 1)
	UART_ASYNCHRONOUS_MODE_ENABLE();
	/* Select Baud Rate (UBRR value depends on the F_CPU value also) */
	CLEAR_BIT(UBRRH, URSEL);
	UBRRH = (uint8)((51 >> 8) & 0x0F);			// BaudRate = 9600 at 16MHz(UBRR = 103) (UBRR = 51) at 8MHz
	UBRRL = (uint8)(51);

	/* Set Data Frame Format */
	UART_8_DATA_BITS_SELECT();
	UART_1_STOP_BIT_SELECT();

	/* Select Parity Mode */
	#if (UART_PARITY_MODE == 0)
	UART_DISABLE_PARITY_MODE();
	#elif (UART_PARITY_MODE == 1)
	UART_ENABLE_EVEN_PARITY();
	#elif (UART_PARITY_MODE == 2)
	UART_ENABLE_ODD_PARITY();
	#endif

	/* Return SREG Status */
	SREG = interrupt_status;
	/* Select Transmitter or Receiver */
	#if (UART_ASYNCHRONOUS_TRANSMITTER_MODE == 1)
	UART_TRANSMITTER_ENABLE();
	#if (UART_TXC_INTERRUPT_ENABLED == 1)
	GIE_BIT_ENABLE();
	UART_TRANSMITTER_TXC_INTERRUPT_ENABLE();
	#endif
	#endif

	#if (UART_ASYNCHRONOUS_RECEIVER_MODE == 1)
	UART_RECEIVER_ENABLE();
	#if (UART_RXC_INTERRUPT_ENABLED == 1)
	GIE_BIT_ENABLE();
	UART_RECEIVER_RXC_INTERRUPT_ENABLE();		// Enable it again
	#endif
	#endif

#else
	UART_SYNCHRONOUS_MODE_ENABLE();
	// Code for Synchronous configurations
#endif
}

void UART_TransmiteByte_BLOCKING(uint8 data){
	while(!(READ_BIT(UCSRA, UDRE)));
	UDR = data;
}

uint8 UART_ReceiveByte_BLOCKING(){
	while(!(READ_BIT(UCSRA, RXC)));
	return UDR;
}

void UART_SetCallBack(void (*fun)(void)){
	RXC_InterruptHandler = fun;
}

uint8 UART_ReceiveByteNoBlocking(void){
	return UDR;
}

ISR(USART_RXC_vect){
	if(RXC_InterruptHandler != NULL){
		RXC_InterruptHandler();
	}
}
