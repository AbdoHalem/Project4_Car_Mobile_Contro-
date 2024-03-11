/*
 * timer1.h
 *
 *  Created on: Dec 2, 2023
 *      Author: Abdo Halem
 */

#ifndef MCAL_TIMER1_TIMER1_H_
#define MCAL_TIMER1_TIMER1_H_

/* Includes Section */
#include "../DIO/Dio.h"
#include "../PORT/Port_Cfg.h"
#include "../INTERRUPT/Interrupt_cfg.h"

/* Macros Declarations Section */


/* Function like Macros Section */
#define TIMER1_NORMAL_MODE_ENABLE() \
{\
	TCCR1A &= 0xFC; TCCR1B &= 0xE7; \
}

#define TIMER1_CTC_MODE_OCR1A_TOP_ENABLE() \
{\
	TCCR1A &= 0xFC; TCCR1B = (TCCR1B & 0xEF) | 0x08; \
}

#define TIMER1_FPWM_MODE_ICR1A_TOP_ENABLE() \
{\
	TCCR1A = (TCCR1A & 0xF7) | 0x02; TCCR1B |= 0x18; \
}

#define TIMER1_FPWM_MODE_OCR1A_TOP_ENABLE() \
{\
	TCCR1A |= 0x03; TCCR1B |= 0x18; \
}

#define TIMER1_PHASE_CORRECT_ICR1_TOP_ENABLE() \
{\
	SET_BIT(TCCR1A, WGM11); CLEAR_BIT(TCCR1A, WGM10);\
	SET_BIT(TCCR1B, WGM13); CLEAR_BIT(TCCR1B, WGM12);\
}

#define TIMER1_PHASE_CORRECT_OCR1A_TOP_ENABLE() \
{\
	TCCR1A |= 0x03; TCCR1B = (TCCR1B & 0xF7) | 0x10; \
}

#define TIMER1_CLOCK_DISABLED() 		   	   (TCCR1B &= 0xF8)
#define TIMER1_CLOCK_PRESCALER_1_ENABLE()  	   (TCCR1B = (TCCR1B & 0xF9) | 0x01)
#define TIMER1_CLOCK_PRESCALER_8_ENABLE()      (TCCR1B = (TCCR1B & 0xFA) | 0x02)
#define TIMER1_CLOCK_PRESCALER_64_ENABLE() 	   (TCCR1B = (TCCR1B & 0xFB) | 0x03)
#define TIMER1_CLOCK_PRESCALER_256_ENABLE()    (TCCR1B = (TCCR1B & 0xFC) | 0x04)
#define TIMER1_CLOCK_PRESCALER_1024_ENABLE()   (TCCR1B = (TCCR1B & 0xFD) | 0x05)
#define TIMER1_CLOCK_EXTERNAL_FALLING_ENABLE() (TCCR1B = (TCCR1B & 0xFE) | 0x06)
#define TIMER1_CLOCK_EXTERNAL_RISING_ENABLE()  (TCCR1B |= 0x07)

#define TIMER1_OVERFLOW_INTERRUPT_ENABLE()	   (SET_BIT(TIMSK, TOIE1))
#define TIMER1_OVERFLOW_INTERRUPT_DISABLE()	   (CLEAR_BIT(TIMSK, TOIE1))
#define TIMER1_OC1A_INTERRUPT_ENABLE()	   	   (SET_BIT(TIMSK, OCIE1A))
#define TIMER1_OC1A_INTERRUPT_DISABLE()	   	   (CLEAR_BIT(TIMSK, OCIE1A))
#define TIMER1_OC1B_INTERRUPT_ENABLE()	   	   (SET_BIT(TIMSK, OCIE1B))
#define TIMER1_OC1B_INTERRUPT_DISABLE()	   	   (CLEAR_BIT(TIMSK, OCIE1B))

// ICU => INPUT CAPTURE UNIT Bits
#define TIMER1_DISABLE_ICU_NOISE_CANCELLER()   (CLEAR_BIT(TCCR1B, ICNC1))
#define TIMER1_ENABLE_ICU_NOISE_CANCELLER()    (SET_BIT(TCCR1B, ICNC1))
#define TIMER1_ICU_FALLING_EDGE()	   		   (CLEAR_BIT(TCCR1B, ICES1))
#define TIMER1_ICU_RAISING_EDGE()			   (SET_BIT(TCCR1B, ICES1))
#define TIMER1_ICU_INTERRUPT_DISABLE()		   (CLEAR_BIT(TIMSK, TICIE1))
#define TIMER1_ICU_INTERRUPT_ENABLE()		   (SET_BIT(TIMSK, TICIE1))
#define TIMER1_ICU_INTERRUPT_FLAG_CLEAR()	   (SET_BIT(TIFR, ICF1))

/* Data Type Declarations Section */
typedef enum{
	TIMER1_NORMAL_MODE = 0,
	TIMER1_CTC_MODE_OCR1A_TOP,
	TIMER1_FAST_PWM_ICR1_TOP_MODE,
	TIMER1_FAST_PWM_OCR1A_TOP_MODE,
	TIMER1_PHASE_CORRECT_ICR1_TOP_MODE,
	TIMER1_PHASE_CORRECT_OCR1A_TOP_MODE
}timer1_mode_t;

typedef enum{
	NORMAL_PORT_OPERATION = 0,
	TOGGLE_OC1x_COMPARE_MATCH,
	NON_INVERTING_MODE,
	INVERTING_MODE
}timer1_OCRx_pins_mode_t;

typedef enum{
	NO_CLOCK_SOURCE = 0, 	//Timer will be disabled
	PRESCALER_1,
	PRESCALER_8,
	PRESCALER_64,
	PRESCALER_256,
	PRESCALER_1024,
	EXTERNAL_CLOCK_FALLING_EDGE,
	EXTERNAL_CLOCK_RISING_EDGE
}timer1_clock_t;

typedef struct{
	timer1_mode_t mode;
	timer1_clock_t prescaler_value;
	timer1_OCRx_pins_mode_t OC1A_mode;
	timer1_OCRx_pins_mode_t OC1B_mode;
	uint8 interrupt_enabled: 1;
}timer1_t;

/* Software Interfaces Section */
uint8 Timer1_Init(const timer1_t *timer1);
void Timer1_ICU_Init();
uint8 Timer1_DeInit(const timer1_t *timer1);
uint8 Timer1_OC1A_SetDutyCycle(const timer1_t *timer1 ,uint8 duty);
uint8 Timer1_OC1B_SetDutyCycle(const timer1_t *timer1 ,uint8 duty);
uint8 Timer1_SetTop(const timer1_t *timer1, uint16 TOP_value);

#endif /* MCAL_TIMER1_TIMER1_H_ */
