/*
 * EXT_Interrupt.h
 *
 *  Created on: Nov 27, 2023
 *      Author: Abdo Halem
 */

#ifndef INTERRUPT_EXT_INTERRUPT_H_
#define INTERRUPT_EXT_INTERRUPT_H_

/* Includes Section */
#include "../DIO/Dio_Cfg.h"
#include "Interrupt_cfg.h"

/* Macros Declarations Section */

/* Function like Macros Section */
#define EXT_INT_RISING_EDGE()  (MCUCR |= 0x03)
#define EXT_INT_FALLING_EDGE() (MCUCR = (MCUCR & 0xFE) | 0x02)

/* Data Type Declarations Section */
typedef enum{
	EXT_INT0 = 0,
	EXT_INT1,
	EXT_INT2
}EXT_IntType;

/* Software Interfaces Section */
void EXT_Interrupt_Enable(EXT_IntType interrupt);
void EXT_Interrupt_Disable(EXT_IntType interrupt);

#endif /* INTERRUPT_EXT_INTERRUPT_H_ */
