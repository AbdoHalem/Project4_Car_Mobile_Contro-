/*
 * Dio_Cfg.h
 *
 *  Created on: Oct 22, 2023
 *      Author: Abdo Halem
 */

#ifndef MCAL_DIO_DIO_CFG_H_
#define MCAL_DIO_DIO_CFG_H_

/* Includes Section */
#include "../../mcal_std_types.h"
#include "../../Device_cfg.h"

/* Macros Declarations Section */
#define NULL_POINTER_ERROR 0x00
#define INITIALIZATION_DONE 0x01

/* Function like Macros Section */
#define SET_BIT(reg, bit_pos)   	(reg |= (0x01 << bit_pos))
#define CLEAR_BIT(reg, bit_pos) 	(reg &= ~(0x01 << bit_pos))
#define TOGGLE_BIT(reg, bit_pos) 	(reg ^= (0x01 << bit_pos))
#define READ_BIT(reg, bit_pos) 		((reg >> bit_pos) & 0x01)

/* Data Type Declarations Section */
typedef enum{
    STD_LOW = 0,
    STD_HIGH
}Dio_LevelType;

typedef enum{
	PORT_A = 0,
	PORT_B,
	PORT_C,
	PORT_D
}Dio_PortType;

typedef uint8 Dio_PortLevelType;

typedef enum{
	PORTA_PIN0 = 0,
	PORTA_PIN1,
	PORTA_PIN2,
	PORTA_PIN3,
	PORTA_PIN4,
	PORTA_PIN5,
	PORTA_PIN6,
	PORTA_PIN7,
	PORTB_PIN0,
	PORTB_PIN1,
	PORTB_PIN2,
	PORTB_PIN3,
	PORTB_PIN4,
	PORTB_PIN5,
	PORTB_PIN6,
	PORTB_PIN7,
	PORTC_PIN0,
	PORTC_PIN1,
	PORTC_PIN2,
	PORTC_PIN3,
	PORTC_PIN4,
	PORTC_PIN5,
	PORTC_PIN6,
	PORTC_PIN7,
	PORTD_PIN0,
	PORTD_PIN1,
	PORTD_PIN2,
	PORTD_PIN3,
	PORTD_PIN4,
	PORTD_PIN5,
	PORTD_PIN6,
	PORTD_PIN7,
}Dio_ChannelType;

/* Software Interfaces Section */


#endif /* MCAL_DIO_DIO_CFG_H_ */
