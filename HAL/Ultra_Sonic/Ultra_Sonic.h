/*
 * Ultra_Sonic.h
 *
 *  Created on: Feb 11, 2024
 *      Author: Abdo Halem
 */

#ifndef HAL_ULTRA_SONIC_ULTRA_SONIC_H_
#define HAL_ULTRA_SONIC_ULTRA_SONIC_H_

/* Includes Section */
#include "../../MCAL/DIO/Dio.h"
#include "../../MCAL/INTERRUPT/Interrupt_cfg.h"
#include "../../MCAL/Timer1/timer1.h"

/* Macros Declarations Section */


/* Function like Macros Section */


/* Data Type Declarations Section */
typedef Dio_ChannelType UltraSonic_TriggerPin;

/* Software Interfaces Section */
uint16 Ultrasonic_GetDistance(Dio_ChannelType ultraSonic_sensor);

#endif /* HAL_ULTRA_SONIC_ULTRA_SONIC_H_ */
