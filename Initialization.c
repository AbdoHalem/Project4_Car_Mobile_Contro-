/*
 * Initialization.c
 *
 *  Created on: Feb 24, 2024
 *      Author: Abdo Halem
 */

#include "Initialization.h"

timer1_t timer1_obj = {
		.mode = TIMER1_FAST_PWM_OCR1A_TOP_MODE, .prescaler_value = PRESCALER_8,
		.OC1A_mode = NORMAL_PORT_OPERATION, .OC1B_mode = NON_INVERTING_MODE, .interrupt_enabled = 0
};

lcd_4bits_t lcd = {.Rs = PORTB_PIN1, .En = PORTB_PIN3,
				   .lcd_data = {PORTC_PIN0, PORTC_PIN1, PORTC_PIN2, PORTC_PIN3}};

dc_motor_t motor1 = {.pin1 = PORTA_PIN0, .pin2 = PORTA_PIN1};
dc_motor_t motor2 = {.pin1 = PORTA_PIN2, .pin2 = PORTA_PIN3};
uint8 direction = 0;

UltraSonic_TriggerPin ultraSonic_sensor = PORTD_PIN3;
uint16 Front_Distance;
