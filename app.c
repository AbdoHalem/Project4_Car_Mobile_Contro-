/*
 * app.c
 *
 *  Created on: Nov 27, 2023
 *      Author: Abdo Halem
 */

#include "app.h"

void Car_ObstacleAvoid();
uint16 Car_CheckLeft();
uint16 Car_CheckRight();
void Car_MoveLeft();
void Car_MoveRight();
void Car_AutoControl();
void Car_ManualControl();
void Car_Stop();

volatile uint8 mode ;

void UART_RXC_InterruptHandler(){
	mode = UART_ReceiveByteNoBlocking();
	if('m' == mode){Car_ManualControl();}
	else if('s' == mode){Car_Stop();}
}

int main(){
	Port_Init(PortPins_Cfg);
	UART_init();
	UART_SetCallBack(UART_RXC_InterruptHandler);

	Timer1_Init(&timer1_obj);
	ServoMotor_SetFrequency(&timer1_obj, 50);		// Set TOP register value (OCR1A)
	Timer1_ICU_Init(ultraSonic_sensor);
	ServoMotor_Turn(90);							// Look forward
	_delay_ms(500);

	while(1){
		if('m' != mode){
			Car_AutoControl();
		}
		else{Car_ManualControl();}
	}
	return 0;
}

void Car_AutoControl(){
	Car_ObstacleAvoid();
}

void Car_ManualControl(){
	CAR_STOP(&motor1, &motor2);
	while('a' != mode){
		mode = UART_ReceiveByte_BLOCKING();
		if('f' == mode){CAR_MOVE_FORWARD(&motor1, &motor2); SET_BIT(PORTA, 5); SET_BIT(PORTA, 6);}
		else if('b' == mode){CAR_MOVE_BACKWARD(&motor1, &motor2); CLEAR_BIT(PORTA, 5); CLEAR_BIT(PORTA, 6);}
		else if('r' == mode){CAR_TURN_RIGHT(&motor1, &motor2); SET_BIT(PORTA, 5); CLEAR_BIT(PORTA, 6);}
		else if('l' == mode){CAR_TURN_LEFT(&motor1, &motor2); CLEAR_BIT(PORTA, 5); SET_BIT(PORTA, 6);}
		else if('s' == mode){CAR_STOP(&motor1, &motor2); CLEAR_BIT(PORTA, 5); CLEAR_BIT(PORTA, 6);}
	}
}

void Car_Stop(){
	CAR_STOP(&motor1, &motor2);
	CLEAR_BIT(PORTA, 5); CLEAR_BIT(PORTA, 6);
	while('s' == mode){
		mode = UART_ReceiveByte_BLOCKING();
	}
	if('m' == mode){Car_ManualControl();}
}

void Car_ObstacleAvoid(){
	uint16 Right_Distance = 0, Left_Distance = 0;
	Front_Distance = Ultrasonic_GetDistance(ultraSonic_sensor);

	/* Check if obstacle is found or not */
	while((Front_Distance > 30) && ('s' != mode)){			// No obstacle on front of the car
		CAR_MOVE_FORWARD(&motor1, &motor2);	SET_BIT(PORTA, 5); SET_BIT(PORTA, 6);
		_delay_ms(3);
		Front_Distance = Ultrasonic_GetDistance(ultraSonic_sensor);
	}
	CAR_STOP(&motor1, &motor2); 	// Obstacle is found in front of the car

	/* Look left and right to find a way */
	Left_Distance = Car_CheckLeft();
	_delay_ms(1000);
	Right_Distance = Car_CheckRight();
	ServoMotor_Turn(90); 			// Turn 0 (center)

	/* Take Decision */
	if((Right_Distance >= Left_Distance) && (Right_Distance > 30)){
		Car_MoveRight(); SET_BIT(PORTA, 5); CLEAR_BIT(PORTA, 6);
	}
	else if((Left_Distance > Right_Distance) && (Left_Distance > 30)){
		Car_MoveLeft(); CLEAR_BIT(PORTA, 5); SET_BIT(PORTA, 6);
	}
	else{	// If the right and left distances are equal, return back for 1s and check again
		while((Left_Distance <= 30) && (Right_Distance <= 30) && ('s' != mode)){
			CAR_MOVE_BACKWARD(&motor1, &motor2); _delay_ms(1000); CLEAR_BIT(PORTA, 5); CLEAR_BIT(PORTA, 6);
			CAR_STOP(&motor1, &motor2);
			Left_Distance = Car_CheckLeft();
			Right_Distance = Car_CheckRight();
		}
		if(Right_Distance >= Left_Distance){
			Car_MoveRight(); SET_BIT(PORTA, 5); CLEAR_BIT(PORTA, 6);
		}
		else{
			Car_MoveLeft(); CLEAR_BIT(PORTA, 5); SET_BIT(PORTA, 6);
		}
	}
}

uint16 Car_CheckLeft(){
	ServoMotor_Turn(0);				// Turn -90 (left)
	uint8 i = 0; uint16 Left_Distance = 0;
	for(i = 0; i < 30; i++){
		_delay_ms(10);
		Left_Distance = Ultrasonic_GetDistance(ultraSonic_sensor);
	}
	return Left_Distance;
}

uint16 Car_CheckRight(){
	ServoMotor_Turn(180);			// Turn 90 (right)
	uint8 i = 0; uint16 Right_Distance = 0;
	for(i = 0; i < 30; i++){
		_delay_ms(10);
		Right_Distance = Ultrasonic_GetDistance(ultraSonic_sensor);
	}
	return Right_Distance;
}

void Car_MoveLeft(){
	CAR_TURN_LEFT(&motor1, &motor2); _delay_ms(400);
	CAR_STOP(&motor1, &motor2);
	CAR_MOVE_FORWARD(&motor1, &motor2);
}

void Car_MoveRight(){
	CAR_TURN_RIGHT(&motor1, &motor2); _delay_ms(400);
	CAR_STOP(&motor1, &motor2);
	CAR_MOVE_FORWARD(&motor1, &motor2);
}
