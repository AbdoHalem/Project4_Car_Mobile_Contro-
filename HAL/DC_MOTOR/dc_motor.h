/*
 * dc_motor.h
 *
 *  Created on: Nov 30, 2023
 *      Author: Abdo Halem
 */

#ifndef HAL_DC_MOTOR_DC_MOTOR_H_
#define HAL_DC_MOTOR_DC_MOTOR_H_

/* Includes Section */
#include "../../MCAL/DIO/Dio.h"

/* Macros Declarations Section */

/* Function like Macros Section */

/* Data Type Declarations Section */
typedef struct{
	Dio_ChannelType pin1;
	Dio_ChannelType pin2;
}dc_motor_t;

/* Software Interfaces Section */
void dc_motor_MoveRight(const dc_motor_t *motor);
void dc_motor_MoveLeft(const dc_motor_t *motor);
void dc_motor_stop(const dc_motor_t *motor);

#endif /* HAL_DC_MOTOR_DC_MOTOR_H_ */
