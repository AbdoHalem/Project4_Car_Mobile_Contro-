/*
 * UART_cfg.h
 *
 *  Created on: Nov 30, 2023
 *      Author: Abdo Halem
 */

#ifndef MCAL_UART_UART_CFG_H_
#define MCAL_UART_UART_CFG_H_

/* Includes Section */

/* Macros Declarations Section */
#define UART_ASYNCHRONOUS_TRANSMITTER_MODE 1		// 1 => Enabled, 0 => Disabled
#define UART_ASYNCHRONOUS_RECEIVER_MODE    1

#define UART_TXC_INTERRUPT_ENABLED   0
#define UART_UDRIE_INTERRUPT_ENABLED 0
#define UART_RXC_INTERRUPT_ENABLED   1

#define UART_ASYNCHRONOUS_MODE_ENABLED 1
#define UART_PARITY_MODE 0						   // 0 => Disabled, 1 => Even Parity, 2 => Odd Parity

#define UART_9600_BAUDRATE 1

/* Function like Macro Section */


/* Data Type Declarations Section */


/* Software Interfaces Section */


#endif /* MCAL_UART_UART_CFG_H_ */
