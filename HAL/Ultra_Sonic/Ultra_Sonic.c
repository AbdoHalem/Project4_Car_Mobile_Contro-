/*
 * Ultra_Sonic.c
 * Driver of ultra sonic sensor
 *  Created on: Feb 11, 2024
 *      Author: Abdo Halem
 */
#include "Ultra_Sonic.h"

static uint16 distance = 0;
static uint8 volatile ICU_flag = 0, Timer1_OVF = 0;
static uint16 volatile t1 = 0, t2 = 0;
static uint16 volatile	t_on = 0;

uint16 Ultrasonic_GetDistance(Dio_ChannelType ultraSonic_sensor){
	Timer1_OVF = 0;
	ICU_flag = 0;
	/* Send Trigger Signal */
	Dio_WriteChannel(ultraSonic_sensor, STD_HIGH);
	_delay_us(10);
	Dio_WriteChannel(ultraSonic_sensor, STD_LOW);
	/* Configure ICU Interrupt */
	TIMER1_ICU_RAISING_EDGE();
	TIMER1_ICU_INTERRUPT_ENABLE();
	TIMER1_OC1A_INTERRUPT_ENABLE();
	while(ICU_flag < 2);
	t_on = t2 - t1 + ((uint32)Timer1_OVF * 19999);
	distance = t_on / 58;
	TIMER1_ICU_INTERRUPT_DISABLE();
	return distance;
}



ISR(TIMER1_CAPT_vect){
	if(0 == ICU_flag){
		t1 = ICR1;
		Timer1_OVF = 0;
		ICU_flag = 1;
		TIMER1_ICU_FALLING_EDGE();
	}
	else if(1 == ICU_flag){
		t2 = ICR1;
		ICU_flag = 2;
		TIMER1_ICU_RAISING_EDGE();
		TIMER1_OC1A_INTERRUPT_DISABLE();
		TIMER1_ICU_INTERRUPT_DISABLE();
	}
}

ISR(TIMER1_COMPA_vect){
	Timer1_OVF++;
}
