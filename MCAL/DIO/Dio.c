/*
 * Dio.c
 *
 *  Created on: Oct 18, 2023
 *      Author: Abdo Halem
 */

#include "Dio.h"

Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId){
	Dio_LevelType ret = STD_LOW;
	switch (ChannelId / 8){
		case 0 : ret = READ_BIT(PINA, ChannelId % 8); break;
		case 1 : ret = READ_BIT(PINB, ChannelId % 8); break;
		case 2 : ret = READ_BIT(PINC, ChannelId % 8); break;
		case 3 : ret = READ_BIT(PIND, ChannelId % 8); break;
		default : break;
	}
	return ret;
}

void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level){
	switch (ChannelId / 8){
		case 0 :
			if(STD_LOW == READ_BIT(DDRA, ChannelId % 8)){	//Check the channel direction first
				break;
			}
			if(STD_LOW == Level){
				CLEAR_BIT(PORTA, ChannelId % 8);
			}
			else if(STD_HIGH == Level){
				SET_BIT(PORTA, ChannelId % 8);
			}break;

		case 1 :
			if(STD_LOW == READ_BIT(DDRB, ChannelId % 8)){	//Check the channel direction first
				break;
			}
			if(STD_LOW == Level){
				CLEAR_BIT(PORTB, ChannelId % 8);
			}
			else if(STD_HIGH == Level){
				SET_BIT(PORTB, ChannelId % 8);
			}break;

		case 2 :
			if(STD_LOW == READ_BIT(DDRC, ChannelId % 8)){	//Check the channel direction first
				break;
			}
			if(STD_LOW == Level){
				CLEAR_BIT(PORTC, ChannelId % 8);
			}
			else if(STD_HIGH == Level){
				SET_BIT(PORTC, ChannelId % 8);
			}break;

		case 3 :
			if(STD_LOW == READ_BIT(DDRD, ChannelId % 8)){	//Check the channel direction first
				break;
			}
			if(STD_LOW == Level){
				CLEAR_BIT(PORTD, ChannelId % 8);
			}
			else if(STD_HIGH == Level){
				SET_BIT(PORTD, ChannelId % 8);
			}break;

		default : break;
	}
}

Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId){
	Dio_LevelType ret = 0;
	switch (ChannelId / 8){
		case 0 :
			if(STD_LOW == READ_BIT(DDRA, ChannelId % 8)){
				ret = (READ_BIT(PINA, ChannelId % 8));
			}
			else{
				TOGGLE_BIT(PORTA, ChannelId % 8);
				ret = READ_BIT(PINA, ChannelId % 8);
			}break;

		case 1 :
			if(STD_LOW == READ_BIT(DDRB, ChannelId % 8)){
				ret = (READ_BIT(PINB, ChannelId % 8));
			}
			else{
				TOGGLE_BIT(PORTB, ChannelId % 8);
				ret = READ_BIT(PINB, ChannelId % 8);
			}break;

		case 2 :
			if(STD_LOW == READ_BIT(DDRC, ChannelId % 8)){
				ret = (READ_BIT(PINC, ChannelId % 8));
			}
			else{
				TOGGLE_BIT(PORTC, ChannelId % 8);
				ret = READ_BIT(PINC, ChannelId % 8);
			}break;

		case 3 :
			if(STD_LOW == READ_BIT(DDRD, ChannelId % 8)){
				ret = (READ_BIT(PIND, ChannelId % 8));
			}
			else{
				TOGGLE_BIT(PORTD, ChannelId % 8);
				ret = READ_BIT(PIND, ChannelId % 8);
			}break;

		default : break;
		}
	return ret;
}

Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId){
	Dio_PortLevelType ret = 0x00;
	if(PORT_A == PortId){
		ret = PINA;
	}
	else if(PORT_B == PortId){
		ret = PINB;
	}
	else if(PORT_C == PortId){
		ret = PINC;
	}
	else if(PORT_D == PortId){
		ret = PIND;
	}
	return ret;
}

void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level){
	if(PORT_A == PortId){
		PORTA = Level;
	}
	else if(PORT_B == PortId){
		PORTB = Level;
	}
	else if(PORT_C == PortId){
		PORTC = Level;
	}
	else if(PORT_D == PortId){
		PORTD = Level;
	}
}

