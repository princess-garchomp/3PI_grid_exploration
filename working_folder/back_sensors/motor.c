#include "motor.h"


#include <stdint.h>
#include <avr/io.h>

#define _abs(x) ( ((x)<0)?-(x):(x))

#define LEFT_MOTOR_A (PD6)
#define LEFT_MOTOR_B (PD5)
#define LEFT_MOTOR_TIMER 0

#define RIGHT_MOTOR_A (PB3)
#define RIGHT_MOTOR_B (PD3)
#define RIGHT_MOTOR_TIMER (2)

#define MINIMUM_DUTY_CYCLE 0x0A
//maximum dutu cucle
#define INITIAL_DUTY_CYCLE 0x80
#define INITIAL_STEER_POSITION 0
#define INITIAL_ROBOT_SHIFT_STATE STOP
#define LEFT_DUTY_CYCLE_OFFSET 0
#define RIGHT_DUTY_CYCLE_OFFSET 0
#define LEFT_MOTOR_A (PD6)
#define LEFT_MOTOR_B (PD5)
#define LEFT_MOTOR_TIMER 0 

#define RIGHT_MOTOR_A (PB3)
#define RIGHT_MOTOR_B (PD3)
#define RIGHT_MOTOR_TIMER (2)

#define COMxA1 7
#define COMxA0 6
#define COMxB1 5
#define COMxB0 4

static uint8_t duty_cycle = INITIAL_DUTY_CYCLE;
static int8_t steering_position = INITIAL_STEER_POSITION;
static uint8_t robot_shift_state = INITIAL_ROBOT_SHIFT_STATE;

static void config_left();
static void left_stop();
static void left_coast();
static void left_forward();
static void left_reverse();
static void left_duty_cycle_set(uint8_t duty_cycle);

static void config_right();
static void right_stop();
static void right_coast();
static void right_forward();
static void right_reverse();
static void right_duty_cycle_set(uint8_t duty_cycle);

static void update_robot_controls();



void config_motors()
{
	config_left();
	config_right();
	//set the robot to the inital values
	//steer_position
		//	
	//duty cycle
		//
	//robot_shift_state
		//this enables/disables the PWM outputs of OCR0A, OCR0B, OCR2B or OCR2A as needed for forwrd/reverse etc
	update_robot_controls();
	return;
}

void set_duty_cycle(uint8_t value)
{
	if(value < MINIMUM_DUTY_CYCLE)
	duty_cycle = MINIMUM_DUTY_CYCLE;
	else
	duty_cycle = value;
	update_robot_controls();
}

uint8_t get_duty_cycle()
{
	return duty_cycle;
}

_Bool shift_robot(robot_shift new_state)
{
	if(robot_shift_state == new_state || robot_shift_state == STOP || robot_shift_state == COAST || new_state == STOP || new_state == COAST)
	{
		robot_shift_state = new_state;
		update_robot_controls();
		return 1;
	}
	else
	return 0;
}

robot_shift get_robot_shift_state()
{
	return robot_shift_state;
}


//this is the one that we use in main
void steer (int8_t new_steer_position)
{
	//steerint_position is only int this file scope
	steering_position = new_steer_position;
	update_robot_controls();
}

int8_t get_steering()
{
	return steering_position;
}

static void update_robot_controls()
{
	//steer is abs of the vlaue I just passed
	uint8_t steer = _abs (steering_position);
	int16_t duty_cycle_high = duty_cycle + steer;
	int16_t duty_cycle_low = duty_cycle - steer;
	if (duty_cycle_high > 255)
	{
		duty_cycle_high = 255;
		duty_cycle_low = duty_cycle_high - 2*steer;
	}
	else if (duty_cycle_low < MINIMUM_DUTY_CYCLE)
	{
		duty_cycle_low = MINIMUM_DUTY_CYCLE;
		duty_cycle_high = duty_cycle_low + 2*steer;
	}
	if(steering_position > 0 )
	{
		left_duty_cycle_set(duty_cycle_high);
		right_duty_cycle_set(duty_cycle_low);
	}
	else
	{
		left_duty_cycle_set(duty_cycle_low);
		right_duty_cycle_set(duty_cycle_high);
	}
	switch(robot_shift_state)
	{
		case STOP:
		left_stop();
		right_stop();
		break;
		case COAST:
		left_coast();
		right_coast();
		break;
		case FORWARD:
		left_forward();
		right_forward();
		break;
		case REVERSE:
		left_reverse();
		right_reverse();
		break;
		case CW:
		left_forward();
		right_reverse();
		break;
		case CCW:
		left_reverse();
		right_forward();
		break;
		
	}
	return;
}



/*
 * #define LEFT_MOTOR_A (PD6)
#define LEFT_MOTOR_B (PD5)
#define LEFT_MOTOR_TIMER 0

#define RIGHT_MOTOR_A (PB3)
#define RIGHT_MOTOR_B (PD3)
#define RIGHT_MOTOR_TIMER (2)


#define COMxA1 7
#define COMxA0 6
#define COMxB1 5
#define COMxB0 4

 *
 * */


/*
 https://www.sparkfun.com/datasheets/Robotics/TB6612FNG.pdf
	this is the motor H bridge on the 3pi
 
in1 	in2 	PWM	output state
H	L	H	CW
L	H	H	CCW
*/

//follows is left motor
static void config_left()
{
	left_stop();
	//these need to be the contorl logic for the motor driver
	DDRD |= (1UL<<LEFT_MOTOR_A);	//BIN2(PD6)(OC0A)
	DDRD |= (1ul<<LEFT_MOTOR_B);	//BIN1(PD5)(OC0B)
	//
	TCCR0A = 0x03;//fast pwm
	TCCR0B = 0x01;//no prescale
}
static void left_stop()
{
	//set COM to zero
		//COMA
			//Normal port operation, OC0A disconnected.
		//COMB
			//Normal port operation, OC0B disconnected.
	TCCR0A &= ~( 1ul<<COMxA0 | 1ul<<COMxA1 | 1ul<<COMxB0 | 1ul<<COMxB1); // off waveform
	PORTD |= (1ul<<LEFT_MOTOR_A);
	PORTD |= (1ul<<LEFT_MOTOR_B);
}

static void left_coast()
{
	//set com to zeroo
	TCCR0A &= ~( 1ul<<COMxA0 | 1ul<<COMxA1 | 1ul<<COMxB0 | 1ul<<COMxB1); // off waveform
	PORTD &= ~(1ul<<LEFT_MOTOR_A);
	PORTD &= ~(1ul<<LEFT_MOTOR_B);
}
static void left_forward()
{
	//disable compare match PWM generation
	//then enable only OCR0B PWM outpupt
	left_stop();
	//Set OC0A on compare match, clear OC0A at BOTTOM,(inverting mode)
	//IN1 is high IN2 is low, it goes CW
	TCCR0A |= ( 1<<COMxB0 | 1<<COMxB1);
}
static void left_reverse()
{
	//disable compare match PWM generation
	//then enable only OCR0A PWM outpupt
	left_stop();
	//Set OC0B on compare match, clear OC0B at BOTTOM,(inverting mode).
	//IN1 is low IN2 is high, it goes CCW
	TCCR0A |= ( 1<<COMxA0 | 1<<COMxA1);
}
static void left_duty_cycle_set(uint8_t duty_cycle)
{
	//set value in compare registers that are associated with PWM for the left motor
	OCR0A = duty_cycle + LEFT_DUTY_CYCLE_OFFSET;
	OCR0B = duty_cycle + LEFT_DUTY_CYCLE_OFFSET;
}

//right
static void config_right()
{
	right_stop();
	DDRB |= (1UL<<RIGHT_MOTOR_A);	//AIN1(PB3)(OC2A)
	DDRD |= (1ul<<RIGHT_MOTOR_B);	//AIN2(PD3)(OC2B)
	TCCR2A = 0x03;//fast pwm
	TCCR2B = 0x01;//no prescale
}
static void right_stop()
{
	//same as left
	TCCR2A &= ~( 1ul<<COMxA0 | 1ul<<COMxA1 | 1ul<<COMxB0 | 1ul<<COMxB1); // off waveform
	PORTB |= (1ul<<RIGHT_MOTOR_A);
	PORTD |= (1ul<<RIGHT_MOTOR_B);
}

static void right_coast()
{
	//same as left
	TCCR2A &= ~( 1ul<<COMxA0 | 1ul<<COMxA1 | 1ul<<COMxB0 | 1ul<<COMxB1); // off waveform
	PORTB &= ~(1ul<<RIGHT_MOTOR_A);
	PORTD &= ~(1ul<<RIGHT_MOTOR_B);
}
static void right_forward()
{
	right_stop();
	//turns CCW, so it goes forward
	//IN1 low, IN2 high ccw
		//this motor is on the left of the robot, so CCW means that this motor goes forward
	TCCR2A |= ( 1<<COMxB0 | 1<<COMxB1);
}
static void right_reverse()
{
	right_stop();
	TCCR2A |= ( 1<<COMxA0 | 1<<COMxA1);
}
static void right_duty_cycle_set(uint8_t duty_cycle)
{
	//set value in compare registers that are associated with PWM for the right motor
	OCR2A = duty_cycle + RIGHT_DUTY_CYCLE_OFFSET;
	OCR2B = duty_cycle + RIGHT_DUTY_CYCLE_OFFSET;

}



//config the 8bit counter and one of the 16bit counters as PWM outputs
//set the duty cycle for both OCRxA and OCRxB
	//once the timer countes to the number in the OCRxA register, the pins associated with the OCRxA register output a pwm (same for OCRxB)
//to go turn a motor CCW or CW we enable or disabe the PWM ouptu on the corresponing OCRxA or OCRxB pin
