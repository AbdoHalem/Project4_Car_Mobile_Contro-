/*
 * EXT_Interrupt.c
 *
 *  Created on: Nov 27, 2023
 *      Author: Abdo Halem
 */

#include "EXT_Interrupt.h"

void EXT_Interrupt_Enable(EXT_IntType interrupt){
	switch(interrupt){
		case EXT_INT0 : {SET_BIT(GICR, 6); break;}
		case EXT_INT1 : {SET_BIT(GICR, 7); break;}
		case EXT_INT2 : {SET_BIT(GICR, 5); break;}
		default : break;
	}
}

void EXT_Interrupt_Disable(EXT_IntType interrupt){
	switch(interrupt){
		case EXT_INT0 : {CLEAR_BIT(GICR, 6); break;}
		case EXT_INT1 : {CLEAR_BIT(GICR, 7); break;}
		case EXT_INT2 : {CLEAR_BIT(GICR, 5); break;}
		default : break;
	}
}

void __vector_1() __attribute__ ((signal));
void __vector_1(){
	TOGGLE_BIT(PORTC, 0);
}
