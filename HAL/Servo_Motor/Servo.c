/*
 * Servo.c
 *
 *  Created on: Feb 13, 2024
 *      Author: Abdo Halem
 */

#include "Servo.h"

uint8 ServoMotor_SetFrequency(const timer1_t *timer1, uint16 frequency){
	if(timer1 == NULL){
		return NULL_POINTER_ERROR;
	}
	else{
		uint16 Top = ((float)1 / frequency) * 1000000 - 1;
		Timer1_SetTop(timer1, Top);
	}
	return INITIALIZATION_DONE;
}

void ServoMotor_Turn(uint8 angle){
	//OCR1B = ((uint32)angle * 2000) / 180 + 1999;		//This equation at F_CPU = 16MHz
	OCR1B = ((uint32)angle * 2000) / 180 + 499;			//This equation at F_CPU = 8MHz
}
