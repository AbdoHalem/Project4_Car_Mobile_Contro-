/*
 * timer1.c
 *
 *  Created on: Dec 2, 2023
 *      Author: Abdo Halem
 */

#include "timer1.h"
static void Timer1_OC1A_ModeSelect(timer1_OCRx_pins_mode_t mode);
static void Timer1_OC1B_ModeSelect(timer1_OCRx_pins_mode_t mode);
static void Timer1_InterruptConfigurations(const timer1_t *timer1);

/* Type: User function
 * Function: Initialize Timer1
 * timer1: Pointer to timer1 configurations
 */
uint8 Timer1_Init(const timer1_t *timer1){
	if(timer1 == NULL){
		return NULL_POINTER_ERROR;
	}
	else{
		uint8 temp_SREG = SREG;
		GIE_BIT_DISABLE();
		/* Set Timer1 Mode */
		switch(timer1->mode){
			case TIMER1_NORMAL_MODE : TIMER1_NORMAL_MODE_ENABLE(); break;
			case TIMER1_CTC_MODE_OCR1A_TOP : TIMER1_CTC_MODE_OCR1A_TOP_ENABLE(); break;
			case TIMER1_FAST_PWM_ICR1_TOP_MODE: TIMER1_FPWM_MODE_ICR1A_TOP_ENABLE(); break;
			case TIMER1_FAST_PWM_OCR1A_TOP_MODE: TIMER1_FPWM_MODE_OCR1A_TOP_ENABLE(); break;
			case TIMER1_PHASE_CORRECT_ICR1_TOP_MODE : TIMER1_PHASE_CORRECT_ICR1_TOP_ENABLE(); break;
			case TIMER1_PHASE_CORRECT_OCR1A_TOP_MODE : TIMER1_PHASE_CORRECT_OCR1A_TOP_ENABLE(); break;
			default : break;
		}
		/* Set Prescaler Value */
		switch(timer1->prescaler_value){
			case PRESCALER_1 : TIMER1_CLOCK_PRESCALER_1_ENABLE(); break;
			case PRESCALER_8 : TIMER1_CLOCK_PRESCALER_8_ENABLE(); break;
			case PRESCALER_64 : TIMER1_CLOCK_PRESCALER_64_ENABLE(); break;
			case PRESCALER_256 : TIMER1_CLOCK_PRESCALER_256_ENABLE(); break;
			case PRESCALER_1024 : TIMER1_CLOCK_PRESCALER_1024_ENABLE(); break;
			case EXTERNAL_CLOCK_FALLING_EDGE : TIMER1_CLOCK_EXTERNAL_FALLING_ENABLE(); break;
			case EXTERNAL_CLOCK_RISING_EDGE : TIMER1_CLOCK_EXTERNAL_RISING_ENABLE(); break;
			default : break;
		}
		/* OC1A and OC1B Configurations */
		Timer1_OC1A_ModeSelect(timer1->OC1A_mode);
		Timer1_OC1B_ModeSelect(timer1->OC1B_mode);
		/* Restore SREG Status */
		SREG = temp_SREG;
		/* Interrupt Configurations */
		Timer1_InterruptConfigurations(timer1);
	}
	return INITIALIZATION_DONE;
}

/* Type: User function
 * Function: Initialize the Input Capture Unit
 * timer1: Pointer to timer1 configurations
 */
void Timer1_ICU_Init(){
	/* Configure ICP pin as input */
	CLEAR_BIT(DDRD, PIN6);
	/* Configure Input Capture Noise Canceler feature */
	TIMER1_DISABLE_ICU_NOISE_CANCELLER();
	/* Select the edge that used as a trigger */
	TIMER1_ICU_RAISING_EDGE();
	/* Enable ICU Interrupt */
	GIE_BIT_ENABLE();
	TIMER1_ICU_INTERRUPT_ENABLE();
}

/* Type: User function
 * Function: Disable the Input Capture Unit
 * timer1: Pointer to timer1 configurations
 */
uint8 Timer1_DeInit(const timer1_t *timer1){
	if(timer1 == NULL){
		return NULL_POINTER_ERROR;
	}
	else{
		TIMER1_CLOCK_DISABLED();
		TCNT1 = 0;
		if(timer1->interrupt_enabled){
			TIMSK &= 0xC3;
		}
		return INITIALIZATION_DONE;
	}
}

/* Type: User function
 * Function: Set duty cycle of OC1A pin of timer1
 * timer1: Pointer to timer1 configurations
 * duty: Value of duty cycle
 */
uint8 Timer1_OC1A_SetDutyCycle(const timer1_t *timer1 ,uint8 duty){
	if(timer1 == NULL){
		return NULL_POINTER_ERROR;
	}
	else{
		if((TIMER1_FAST_PWM_ICR1_TOP_MODE == timer1->mode) && (NON_INVERTING_MODE == timer1->OC1A_mode)){
			OCR1A = (uint16)( (((float)duty/100.0) * (ICR1+1)) - 1 );
		}
		else if((TIMER1_FAST_PWM_ICR1_TOP_MODE == timer1->mode) && (INVERTING_MODE == timer1->OC1A_mode)){
			OCR1A = (uint16)(ICR1 - ((float)duty/100.0) * (ICR1+1));
		}
		else if((TIMER1_FAST_PWM_ICR1_TOP_MODE == timer1->mode) && (TOGGLE_OC1x_COMPARE_MATCH == timer1->OC1B_mode)){
			OCR1A = (uint16)(((float)duty/100.0) * (ICR1 + 1));
		}

		else if((TIMER1_PHASE_CORRECT_ICR1_TOP_MODE == timer1->mode) && (NON_INVERTING_MODE == timer1->OC1A_mode)){
			OCR1A = (uint16)(((float)duty/100.0) * ICR1);
		}
		else if((TIMER1_PHASE_CORRECT_ICR1_TOP_MODE == timer1->mode) && (INVERTING_MODE == timer1->OC1A_mode)){
			OCR1A = (uint16)((1 - (float)duty/100.0) * ICR1);
		}
		else if((TIMER1_PHASE_CORRECT_ICR1_TOP_MODE == timer1->mode) && (TOGGLE_OC1x_COMPARE_MATCH == timer1->OC1A_mode)){
			OCR1A = (uint16)(((float)duty/100.0) * ICR1);
		}

		else if((TIMER1_PHASE_CORRECT_OCR1A_TOP_MODE == timer1->mode) && (NON_INVERTING_MODE == timer1->OC1A_mode)){
			OCR1A = (uint16)(((float)duty/100.0) * OCR1A);
		}
		else if((TIMER1_PHASE_CORRECT_OCR1A_TOP_MODE == timer1->mode) && (INVERTING_MODE == timer1->OC1A_mode)){
			OCR1A = (uint16)((1 - (float)duty/100.0) * OCR1A);
		}
		else if((TIMER1_PHASE_CORRECT_OCR1A_TOP_MODE == timer1->mode) && (TOGGLE_OC1x_COMPARE_MATCH == timer1->OC1A_mode)){
			OCR1A = (uint16)(((float)duty/100.0) * OCR1A);
		}
		return INITIALIZATION_DONE;
	}
}

/* Type: User function
 * Function: Set duty cycle of OC1B pin of timer1
 * timer1: Pointer to timer1 configurations
 * duty: Value of duty cycle
 */
uint8 Timer1_OC1B_SetDutyCycle(const timer1_t *timer1 ,uint8 duty){
	if(timer1 == NULL){
		return NULL_POINTER_ERROR;
	}
	else{
		if((TIMER1_FAST_PWM_ICR1_TOP_MODE == timer1->mode) && (NON_INVERTING_MODE == timer1->OC1B_mode)){
			OCR1B = (uint16)( (((float)duty/100.0) * (ICR1+1)) - 1 );
		}
		else if((TIMER1_FAST_PWM_ICR1_TOP_MODE == timer1->mode) && (INVERTING_MODE == timer1->OC1B_mode)){
			OCR1B = (uint16)(ICR1 - ((float)duty/100.0) * (ICR1+1));
		}
		else if((TIMER1_PHASE_CORRECT_ICR1_TOP_MODE == timer1->mode) && (NON_INVERTING_MODE == timer1->OC1B_mode)){
			OCR1B = (uint16)(((float)duty/100.0) * ICR1);
		}
		else if((TIMER1_PHASE_CORRECT_ICR1_TOP_MODE == timer1->mode) && (INVERTING_MODE == timer1->OC1B_mode)){
			OCR1B = (uint16)((1 - (float)duty/100.0) * ICR1);
		}
		/*else if((TIMER1_PHASE_CORRECT_ICR1_TOP_MODE == timer1->mode) && (TOGGLE_OC1x_COMPARE_MATCH == timer1->OC1B_mode)){
			OCR1B = (uint16)(((float)duty/100.0) * ICR1);
		}*/
		else if((TIMER1_PHASE_CORRECT_OCR1A_TOP_MODE == timer1->mode) && (NON_INVERTING_MODE == timer1->OC1B_mode)){
			OCR1B = (uint16)(((float)duty/100.0) * OCR1A);
		}
		else if((TIMER1_PHASE_CORRECT_OCR1A_TOP_MODE == timer1->mode) && (INVERTING_MODE == timer1->OC1B_mode)){
			OCR1B = (uint16)((1 - (float)duty/100.0) * OCR1A);
		}
		return INITIALIZATION_DONE;
	}
}

/* Type: User function
 * Function: Set the TOP register in timer1
 * timer1: Pointer to timer1 configurations
 * TOP_value: Value of TOP
 */
uint8 Timer1_SetTop(const timer1_t *timer1 ,uint16 TOP_value){
	if(timer1 == NULL){
		return NULL_POINTER_ERROR;
	}
	else{
		if(TIMER1_CTC_MODE_OCR1A_TOP == timer1->mode){OCR1A = TOP_value;}
		else if(TIMER1_FAST_PWM_ICR1_TOP_MODE == timer1->mode){ICR1 = TOP_value;}
		else if(TIMER1_FAST_PWM_OCR1A_TOP_MODE == timer1->mode){OCR1A = TOP_value;}
		else if(TIMER1_PHASE_CORRECT_ICR1_TOP_MODE == timer1->mode){ICR1 = TOP_value;}
		else if(TIMER1_PHASE_CORRECT_OCR1A_TOP_MODE == timer1->mode){OCR1A = TOP_value;}
		return INITIALIZATION_DONE;
	}
}

/* Type: Helper function
 * Function: Select mode of OC1A pin of timer1
 * OC1A_mode: Type of mode
 */
static void Timer1_OC1A_ModeSelect(timer1_OCRx_pins_mode_t OC1A_mode){
	switch(OC1A_mode){
		case NORMAL_PORT_OPERATION : {TCCR1A &= 0x3F; break;}
		case TOGGLE_OC1x_COMPARE_MATCH : {TCCR1A = (TCCR1A & 0x7F) | 0x40; break;}
		case NON_INVERTING_MODE : {TCCR1A = (TCCR1A & 0xBF) | 0x80; break;}
		case INVERTING_MODE : {TCCR1A |= 0xC0; break;}
		default : break;
	}
}

/*static void Timer1_OC1B_ModeSelect(timer1_OCRx_pins_mode_t OC1B_mode){
	switch(OC1B_mode){
		case NORMAL_PORT_OPERATION : {TCCR1A &= 0xCF; break;}
		case TOGGLE_OC1x_COMPARE_MATCH :
			SET_BIT(TCCR1A, COM1B0); CLEAR_BIT(TCCR1A, COM1B1);
			break;
		case NON_INVERTING_MODE :
			SET_BIT(TCCR1A, COM1B1); CLEAR_BIT(TCCR1A, COM1B0);
			break;
		case INVERTING_MODE :
			SET_BIT(TCCR1A, COM1B1); SET_BIT(TCCR1A, COM1B0);
			break;
		default : break;
	}
}*/

/* Type: Helper function
 * Function: Select mode of OC1B pin of timer1
 * OC1A_mode: Type of mode
 */
static void Timer1_OC1B_ModeSelect(timer1_OCRx_pins_mode_t mode){
	switch(mode){
		case NORMAL_PORT_OPERATION : {TCCR1A &= 0xCF; break;}
		case TOGGLE_OC1x_COMPARE_MATCH : {TCCR1A = (TCCR1A & 0xDF) | 0x10; break;}
		case NON_INVERTING_MODE : {TCCR1A = (TCCR1A & 0x7F) | 0x20; break;}
		case INVERTING_MODE : {TCCR1A |= 0x30; break;}
		default : break;
	}
}

/* Type: Helper function
 * Function: Configure interrupts of timer1
 * timer1: Pointer to timer1 configurations
 * OC1A_mode: Type of mode
 */
static void Timer1_InterruptConfigurations(const timer1_t *timer1){
	if(timer1->interrupt_enabled == 1){
		GIE_BIT_ENABLE();
		switch(timer1->mode){
				case TIMER1_NORMAL_MODE : {SET_BIT(TIMSK, TOIE1); break;}
				case TIMER1_CTC_MODE_OCR1A_TOP : {SET_BIT(TIMSK, OCIE1B); break;}
				case TIMER1_FAST_PWM_ICR1_TOP_MODE : {SET_BIT(TIMSK, OCIE1A); break;}
				case TIMER1_FAST_PWM_OCR1A_TOP_MODE : {SET_BIT(TIMSK, OCIE1B); break;}
				case TIMER1_PHASE_CORRECT_ICR1_TOP_MODE :
					if(timer1->OC1A_mode != NORMAL_PORT_OPERATION){SET_BIT(TIMSK, OCIE1A);}
					else{CLEAR_BIT(TIMSK, OCIE1A);}
					if(timer1->OC1B_mode != NORMAL_PORT_OPERATION){SET_BIT(TIMSK, OCIE1B);}
					else{CLEAR_BIT(TIMSK, OCIE1B);}
					break;
				case TIMER1_PHASE_CORRECT_OCR1A_TOP_MODE :
					/*if(timer1->OC1A_mode != NORMAL_PORT_OPERATION){SET_BIT(TIMSK, OCIE1A);}
					else{CLEAR_BIT(TIMSK, OCIE1A);}*/
					if(timer1->OC1B_mode != NORMAL_PORT_OPERATION){SET_BIT(TIMSK, OCIE1B);}
					else{CLEAR_BIT(TIMSK, OCIE1B);}
					break;
				default : break;
		}
	}
	else{
		/* Disable Timer1 Interrupts */
		TIMSK &= 0xC3;
	}
}
