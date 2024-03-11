/*
 * Servo.h
 *
 *  Created on: Feb 13, 2024
 *      Author: Abdo Halem
 */

#ifndef HAL_SERVO_MOTOR_SERVO_H_
#define HAL_SERVO_MOTOR_SERVO_H_

/* Includes Section */
#include "../../MCAL/Timer1/timer1.h"

/* Macros Declarations Section */


/* Function like Macros Section */


/* Data Type Declarations Section */


/* Software Interfaces Section */
uint8 ServoMotor_SetFrequency(const timer1_t *timer1, uint16 frequency);
void ServoMotor_Turn(uint8 angle);

#endif /* HAL_SERVO_MOTOR_SERVO_H_ */
