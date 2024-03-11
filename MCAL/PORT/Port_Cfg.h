/*
 * Port_Cfg.h
 *
 *  Created on: Oct 22, 2023
 *      Author: Abdo Halem
 */

#ifndef MCAL_PORT_PORT_CFG_H_
#define MCAL_PORT_PORT_CFG_H_

/* Includes Section */
#include "../DIO/Dio.h"

/* Macros Declarations Section */
#define PORT_PIN_MODE_DIGITAL (Port_PinModeType)0x00
#define PORT_PIN_MODE_ANALOG  (Port_PinModeType)0x01

#define PORT_SELECT  0x00
#define PIN_SELECT   0x01

#define CONFIGURATION_ARRAY_LENGTH 12	// Number of used Pins
/* Function like Macros Section */


/* Data Type Declarations Section */
typedef Dio_ChannelType Port_PinType;
typedef uint8 Port_PinModeType;

typedef enum{
	PORT_PIN_IN = 0,
	PORT_PIN_OUT
}Port_PinDirectionType;

typedef struct{
	Port_PinType PortPin;
	Port_PinDirectionType Direction;
	uint8 Level;
	uint8 Port_or_Pin : 1;				//PORT_SELECT or PIN_SELECT
}Port_ConfigType;

Port_ConfigType PortPins_Cfg[CONFIGURATION_ARRAY_LENGTH];

/* Software Interfaces Section */

#endif /* MCAL_PORT_PORT_CFG_H_ */
