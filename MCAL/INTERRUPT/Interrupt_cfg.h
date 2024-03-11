/*
 * Interrupt_cfg.h
 *
 *  Created on: Nov 30, 2023
 *      Author: Abdo Halem
 */

#ifndef MCAL_INTERRUPT_INTERRUPT_CFG_H_
#define MCAL_INTERRUPT_INTERRUPT_CFG_H_

/* Includes Section */
#include "../DIO/Dio_Cfg.h"

/* Macros Declarations Section */
#define ISR(vector,...)		\
void vector(void) __attribute__ ((signal))__VA_ARGS__; \
void vector(void)

/* Function like Macros Section */
#define GIE_BIT_ENABLE()  (SET_BIT(SREG ,SREG_I))
#define GIE_BIT_DISABLE() (CLEAR_BIT(SREG ,SREG_I))

/* Data Type Declarations Section */

/* Software Interfaces Section */

#endif /* MCAL_INTERRUPT_INTERRUPT_CFG_H_ */
