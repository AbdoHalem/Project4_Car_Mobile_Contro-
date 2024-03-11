# Project4_Car_Mobile_Control
## Robot for object avoidance and mobile control via UART.
In this project we use avr atmega32 MCU to control a car with two modes
object avoidance mode and manual mode.
As a hardware, this is done by using two dc motors for the car with L298 motor driver to drive the motors,
ultrasonic sensor, servo motor to turn the sensor left and right, bluetooth module for UART communication
and 2 leds to inicate the direction of move.
As a software, we use timer1 module in fast pwm mode with OCR1A as top for the timer and ICU unit for the sensor.

## Logic of Code
When the code starts it enters the automatic mode by default.
In automatic mode, the ultrasonic measures the distance in front of him.
If it is more than 30 cm the car move forward, if less than 30 cm the sensor look right and left 
and the car move in the direction with large distance and more than 30 cm at the same time.
if right and left distances are equal the car move back for 1 second then stop and check again.

In manual mode, we send 'm' to the avr via UART communication protocol to enter manual mode
then send 'f' to move forward,
'b' to move backward,
'r' to move right,
'l' to move left.
We can return to automatic mode by send 'a'.

### In the two modes we can send 's' to stop the car.
