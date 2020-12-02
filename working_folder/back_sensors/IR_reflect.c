#include "IR_reflect.h"
#include <avr/io.h>
#include <stdint.h>
#include <stdfix.h>

#define LEFT_MOST_SENSOR_SHIFT_BACK (PD4)	//6
#define LEFT_MID_SENSOR_SHIFT_BACK (PD2)	//5
#define RIGHT_MIND_SENSOR_SHIFT_BACK (PD0)	//4
#define RIGHT_MOST_SENSOR_SHIFT_BACK (PB4)	//3
//PB4

#define LEFT_MOST_SENSOR_SHIFT_FRONT (PC0)
#define LEFT_MID_SENSOR_SHIFT_FRONT (PC1)
#define CENTER_SENSOR_SHIFT_FRONT (PC2)
#define RIGHT_MIND_SENSOR_SHIFT_FRONT (PC3)
#define RIGHT_MOST_SENSOR_SHIFT_FRONT (PC4)

#define PIN_C_MASK ((1ul<<LEFT_MOST_SENSOR_SHIFT_FRONT)|(1ul<<LEFT_MID_SENSOR_SHIFT_FRONT)|(1ul<<CENTER_SENSOR_SHIFT_FRONT)|(1ul<<RIGHT_MIND_SENSOR_SHIFT_FRONT)|(1ul<<RIGHT_MOST_SENSOR_SHIFT_FRONT))
#define SENSOR_MASK_D ((1ul<<LEFT_MOST_SENSOR_SHIFT_BACK)|(1ul<<LEFT_MID_SENSOR_SHIFT_BACK)|(1ul<<RIGHT_MIND_SENSOR_SHIFT_BACK))
#define EMITTER_SHIFT (PC5)


void config_ir_reflect()
{
	//set IR sensors as input in the fromt
        DDRC &= ~(PIN_C_MASK);
        PORTC |= (PIN_C_MASK);
	//IR sensors as input in the back on the PDx pins
	DDRD &= ~(SENSOR_MASK_D);
	PORTD |= (SENSOR_MASK_D);
	//IR sensors as input in the back on PB5 pins
	DDRB &= ~(1ul<<RIGHT_MOST_SENSOR_SHIFT_BACK);
	PORTB |= (1ul<<RIGHT_MOST_SENSOR_SHIFT_BACK);
	
	//set the power control line to the IR sensor array led output high
	DDRC |= (1ul<<EMITTER_SHIFT);
	ir_relect_on();
}

void ir_relect_on()
{
	PORTC |= (1ul<<EMITTER_SHIFT);
}
void ir_reflect_off()
{
	PORTC &= ~(1ul<<EMITTER_SHIFT);
}


signed short sat accum get_line_position_back()
//signed short get_line_position()
{

	short sat signed accum sum=0;
	uint8_t num_sensors=0;

	uint8_t sensor_D=get_sensor_value_back_pinD();
	uint8_t sensor_B=get_sensor_value_back_pinB();

	static _Bool last_sensor_over_line_right = 0;
	static _Bool last_sensor_over_line_left = 0;
	static int counter =0;

	if((sensor_D == 0)&&(sensor_B==0)) return 0;
/*	{
		counter = (counter +1)%20;
		if(last_sensor_over_line_left==1)
		{
			return 4;
		}
		if(last_sensor_over_line_right==1)
		{
			return -4;
		}
		if(counter==19)
		{
			return 0;
		}
	}
	
	else{}*/
	if( sensor_D & (1ul<<LEFT_MOST_SENSOR_SHIFT_BACK) )
	{
		sum+=2; num_sensors++;
		last_sensor_over_line_left = 1;
	}
	if( sensor_D & (1ul<<LEFT_MID_SENSOR_SHIFT_BACK) )
	{
		sum+=2; num_sensors++;
		last_sensor_over_line_right = 0;
		last_sensor_over_line_left = 0;
	}
	if( sensor_D & (1ul<<RIGHT_MIND_SENSOR_SHIFT_BACK) )
	{
		sum-=2; num_sensors++;
		last_sensor_over_line_right = 0;
		last_sensor_over_line_left = 0;
	}
	if( sensor_B & (1ul<<RIGHT_MOST_SENSOR_SHIFT_BACK) )
	{
		sum-=2; num_sensors++;
		last_sensor_over_line_right = 1;
	}
	return sum/num_sensors;
	
}
signed short sat accum get_line_position_front()
{
      short sat signed accum sum=0;
      uint8_t num_sensors=0;
      uint8_t sensor=get_sensor_value_front();

      if(sensor == 0) return 0;

      if( sensor & (1ul<<LEFT_MOST_SENSOR_SHIFT_FRONT) )
      {
              sum-=4; num_sensors++;
      }
      if( sensor & (1ul<<LEFT_MID_SENSOR_SHIFT_FRONT) )
      {
              sum-=2; num_sensors++;
      }
      if( sensor & (1ul<<RIGHT_MIND_SENSOR_SHIFT_FRONT) )
      {
              sum+=2; num_sensors++;
      }
      if( sensor & (1ul<<RIGHT_MOST_SENSOR_SHIFT_FRONT) )
      {
              sum+=4; num_sensors++;
      }
        return sum/num_sensors;


}
uint8_t get_sensor_value_back_pinD()
{
	return (SENSOR_MASK_D) & PIND;
}

uint8_t get_sensor_value_back_pinB()
{
	return (1ul<<RIGHT_MOST_SENSOR_SHIFT_BACK) & PINB;
}
uint8_t get_sensor_value_front()
{
	return (PIN_C_MASK) & PINC;
}






























_Bool sensor_is_over_line()
{
	return get_sensor_value_back_pinD() != 0;
}


_Bool intersection_met()
{
	return (PINC & (1ul<<RIGHT_MOST_SENSOR_SHIFT_FRONT) && (PINC & (1ul<<LEFT_MOST_SENSOR_SHIFT_FRONT)));

}

_Bool right_sesor_state()
{
	return (PINC & (1ul<<RIGHT_MOST_SENSOR_SHIFT_FRONT));

}
_Bool left_sensor_state()
{
	return (PINC & (1ul<<LEFT_MOST_SENSOR_SHIFT_FRONT));

}

_Bool center_sesnor_state()
{
	return (PINC & (1ul<<CENTER_SENSOR_SHIFT_FRONT));

}
