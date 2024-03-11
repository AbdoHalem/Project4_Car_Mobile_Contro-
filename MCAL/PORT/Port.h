/*
 * Port.h
 *
 *  Created on: Oct 22, 2023
 *      Author: Abdo Halem
 */

#ifndef MCAL_PORT_PORT_H_
#define MCAL_PORT_PORT_H_

/* Includes Section */
#include "Port_Cfg.h"

/* Macros Declarations Section */


/* Function like Macros Section */


/* Data Type Declarations Section */


/* Software Interfaces Section */
void Port_Init(const Port_ConfigType* ConfigPtr);
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction);

#endif /* MCAL_PORT_PORT_H_ */
