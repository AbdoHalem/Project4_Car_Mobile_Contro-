/*
 * dc_motor.c
 *
 *  Created on: Nov 30, 2023
 *      Author: Abdo Halem
 */
#include "dc_motor.h"

void dc_motor_MoveRight(const dc_motor_t *motor){
	Dio_WriteChannel(motor->pin1, STD_HIGH);
	Dio_WriteChannel(motor->pin2, STD_LOW);
}

void dc_motor_MoveLeft(const dc_motor_t *motor){
	Dio_WriteChannel(motor->pin1, STD_LOW);
	Dio_WriteChannel(motor->pin2, STD_HIGH);
}

void dc_motor_stop(const dc_motor_t *motor){
	Dio_WriteChannel(motor->pin1, STD_LOW);
	Dio_WriteChannel(motor->pin2, STD_LOW);
}
