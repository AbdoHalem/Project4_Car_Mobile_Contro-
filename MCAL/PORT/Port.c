/*
 * Port.c
 *
 *  Created on: Oct 22, 2023
 *      Author: Abdo Halem
 */

//Port_ConfigType PortPins_Cfg[]
#include "Port.h"

static void Port_SetPortDirection(Port_PinType Port, Port_PinDirectionType Direction);

/**
 * @brief: Function to initialize all the ports and pins
 * @param ConfigPtr: Pointer to all the port pins configurations
 * @return: void
 */
void Port_Init(const Port_ConfigType* ConfigPtr){
	//uint8 arr_length = sizeof(ConfigPtr)/sizeof(ConfigPtr[0]);
	uint8 arr_length = CONFIGURATION_ARRAY_LENGTH;
	uint8 counter = 0;
	for(counter = 0; counter < arr_length; counter++){
		if(PORT_SELECT == ConfigPtr[counter].Port_or_Pin){
			Port_SetPortDirection(ConfigPtr[counter].PortPin, ConfigPtr[counter].Direction);
			Dio_WritePort((ConfigPtr[counter].PortPin) / 8, ConfigPtr[counter].Level);
		}
		else if(PIN_SELECT == ConfigPtr[counter].Port_or_Pin){
			Port_SetPinDirection(ConfigPtr[counter].PortPin, ConfigPtr[counter].Direction);
			Dio_WriteChannel(ConfigPtr[counter].PortPin, ConfigPtr[counter].Level);
		}
	}
}

/**
 * @brief: Function to set the port pin direction
 * @param Pin: The port pin number
 * @param Direction: The port pin direction
 * @return: void
 */
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction){
	switch(Pin / 8){
		case 0 :
			if(PORT_PIN_OUT == Direction){
				SET_BIT(DDRA, Pin % 8);
			}
			else if(PORT_PIN_IN == Direction){
				CLEAR_BIT(DDRA, Pin % 8);
			}break;

		case 1 :
			if(PORT_PIN_OUT == Direction){
				SET_BIT(DDRB, Pin % 8);
			}
			else if(PORT_PIN_IN == Direction){
				CLEAR_BIT(DDRB, Pin % 8);
			}break;

		case 2 :
			if(PORT_PIN_OUT == Direction){
				SET_BIT(DDRC, Pin % 8);
			}
			else if(PORT_PIN_IN == Direction){
				CLEAR_BIT(DDRC, Pin % 8);
			}break;

		case 3 :
			if(PORT_PIN_OUT == Direction){
				SET_BIT(DDRD, Pin % 8);
			}
			else if(PORT_PIN_IN == Direction){
				CLEAR_BIT(DDRD, Pin % 8);
			}break;

		default : break;
	}
}

/**
 * @brief: Helper function to set the port direction
 * @param Port: The port number
 * @param Direction: The port direction
 * @return: void
 */
static void Port_SetPortDirection(Port_PinType Port, Port_PinDirectionType Direction){
	switch(Port / 8){
		case 0 :
			if(PORT_PIN_OUT == Direction){
				DDRA = (uint8)0xFF;
			}
			else if(PORT_PIN_IN == Direction){
				DDRA = (uint8)0x00;
			}
			break;

		case 1 :
			if(PORT_PIN_OUT == Direction){
				DDRB = (uint8)0xFF;
			}
			else if(PORT_PIN_IN == Direction){
				DDRB = (uint8)0x00;
			}
			break;

		case 2 :
			if(PORT_PIN_OUT == Direction){
				DDRC = (uint8)0xFF;
			}
			else if(PORT_PIN_IN == Direction){
				DDRC = (uint8)0x00;
			}
			break;

		case 3 :
			if(PORT_PIN_OUT == Direction){
				DDRD = (uint8)0xFF;
			}
			else if(PORT_PIN_IN == Direction){
				DDRD = (uint8)0x00;
			}
			break;

		default : break;
	}
}
