#include "IR_reflect.h"
#include <avr/io.h>
#include <stdint.h>
#include <stdfix.h>

#define LLL_SENSOR_SHIFT (PD4)	//6
#define LL_SENSOR_SHIFT (PD2)	//5
#define L_SENSOR_SHIFT (PD0)	//4
#define R_SENSOR_SHIFT (PB4)	//3
#define RR_SENSOR_SHIFT (PB1)	//2
#define RRR_SENSOR_SHIFT (PB5)	//1

#define SENSOR_MASK_D ((1ul<<LLL_SENSOR_SHIFT)|(1ul<<LL_SENSOR_SHIFT)|(1ul<<L_SENSOR_SHIFT))
#define SENSOR_MASK_B ((1ul<<RRR_SENSOR_SHIFT)|(1ul<<RR_SENSOR_SHIFT)|(1ul<<RR_SENSOR_SHIFT))


void config_ir_reflect()
{
	//IR sensors as input in the on the PDx pins
	DDRD &= ~(SENSOR_MASK_D);
	PORTD |= (SENSOR_MASK_D);
	//IR sensors as input in the  on PB5 pins
	DDRB &= ~(SENSOR_MASK_B);
	PORTB |= (SENSOR_MASK_B);
}


signed short sat accum get_line_position()
//signed short get_line_position()
{

	short sat signed accum sum=0;
	uint8_t num_sensors=0;

	uint8_t sensor_D=get_sensor_value_back_pinD();
	uint8_t sensor_B=get_sensor_value_back_pinB();


	if((sensor_D == 0)&&(sensor_B==0)) return 0;
	
	if( sensor_D & (1ul<<LLL_SENSOR_SHIFT) )
	{
		sum+=3; num_sensors++;
	}
	if( sensor_D & (1ul<<LL_SENSOR_SHIFT) )
	{
		sum+=2; num_sensors++;
	}
	if( sensor_D & (1ul<<L_SENSOR_SHIFT) )
	{
		sum-=1; num_sensors++;
	}
	if( sensor_B & (1ul<<R_SENSOR_SHIFT) )
	{
		sum-=1; num_sensors++;
	}
	if( sensor_B & (1ul<<RR_SENSOR_SHIFT) )
	{
		sum-=2; num_sensors++;
	}
	if( sensor_B & (1ul<<RRR_SENSOR_SHIFT) )
	{
		sum-=3; num_sensors++;
	}
	return sum/num_sensors;
	
}
uint8_t get_sensor_value_back_pinD()
{
	return (SENSOR_MASK_D) & PIND;
}

uint8_t get_sensor_value_back_pinB()
{
	return (SENSOR_MASK_B) & PINB;
}

