/*
 * Port_Cfg.c
 *
 *  Created on: Oct 22, 2023
 *      Author: Abdo Halem
 */

#include "Port_Cfg.h"

Port_ConfigType PortPins_Cfg[] = {
		/* DC-Motor1 Pins */
		[0] = {.PortPin = PORTA_PIN0, .Direction = PORT_PIN_OUT, .Port_or_Pin = PIN_SELECT, .Level = STD_LOW},
		[1] = {.PortPin = PORTA_PIN1, .Direction = PORT_PIN_OUT, .Port_or_Pin = PIN_SELECT, .Level = STD_LOW},
		/* DC-Motor2 Pins */
		[2] = {.PortPin = PORTA_PIN2, .Direction = PORT_PIN_OUT, .Port_or_Pin = PIN_SELECT, .Level = STD_LOW},
		[3] = {.PortPin = PORTA_PIN3, .Direction = PORT_PIN_OUT, .Port_or_Pin = PIN_SELECT, .Level = STD_LOW},
		/* Timer1 OC1A and OC1B Pins */
		[4] = {.PortPin = PORTD_PIN4, .Direction = PORT_PIN_OUT, .Port_or_Pin = PIN_SELECT, .Level = STD_LOW},
		[5] = {.PortPin = PORTD_PIN5, .Direction = PORT_PIN_OUT, .Port_or_Pin = PIN_SELECT, .Level = STD_LOW},
		/* Test Board */
		[6] = {.PortPin = PORTA_PIN5, .Direction = PORT_PIN_OUT, .Port_or_Pin = PIN_SELECT, .Level = STD_LOW},
		[7] = {.PortPin = PORTA_PIN6, .Direction = PORT_PIN_OUT, .Port_or_Pin = PIN_SELECT, .Level = STD_LOW},
		/* USART pins TX, RX */
		[8] = {.PortPin = PORTD_PIN0, .Direction = PORT_PIN_IN, .Port_or_Pin = PIN_SELECT, .Level = STD_LOW},
		[9] = {.PortPin = PORTD_PIN1, .Direction = PORT_PIN_OUT, .Port_or_Pin = PIN_SELECT, .Level = STD_LOW},
		/* Ultra_Sonic Trigger pin */
		[10] = {.PortPin = PORTD_PIN6, .Direction = PORT_PIN_IN, .Port_or_Pin = PIN_SELECT, .Level = STD_LOW},
		[11] = {.PortPin = PORTD_PIN3, .Direction = PORT_PIN_OUT, .Port_or_Pin = PIN_SELECT, .Level = STD_LOW}

};
