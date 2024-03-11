/*
 * app.h
 *
 *  Created on: Nov 27, 2023
 *      Author: Abdo Halem
 */

#ifndef APP_H_
#define APP_H_

/* Includes Section */
#include "Initialization.h"

/* Macros Declarations Section */

/* Function like Macros Section */
#define CAR_MOVE_FORWARD(motor1, motor2) \
{\
	dc_motor_MoveRight(motor1); dc_motor_MoveRight(motor2); \
}

#define CAR_MOVE_BACKWARD(motor1, motor2) \
{\
	dc_motor_MoveLeft(motor1); dc_motor_MoveLeft(motor2); \
}

#define CAR_TURN_RIGHT(motor1, motor2) \
{\
	dc_motor_MoveLeft(motor1); dc_motor_MoveRight(motor2); \
}

#define CAR_TURN_LEFT(motor1, motor2) \
{\
	dc_motor_MoveRight(motor1); dc_motor_MoveLeft(motor2); \
}

#define CAR_STOP(motor1, motor2) \
{\
	dc_motor_stop(motor1); dc_motor_stop(motor2); \
}

/* Data Type Declarations Section */
extern timer1_t timer1_obj;
extern lcd_4bits_t lcd;
extern dc_motor_t motor1;
extern dc_motor_t motor2;
extern uint8 direction;
extern UltraSonic_TriggerPin ultraSonic_sensor;
extern uint16 Front_Distance;
/*extern uint8 volatile ICU_flag, Timer1_OVF;
extern uint16 volatile t1, t2, t_on;*/

/* Software Interfaces Section */

#endif /* APP_H_ */
