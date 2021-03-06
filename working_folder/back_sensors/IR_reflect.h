#ifndef RF_REFLECT_H
#define RF_REFLECT_H


#include <stdint.h>
#include <stdfix.h>

void config_ir_reflect();

signed short sat accum get_line_position_back();
signed short sat accum get_line_position_front();
//signed short get_line_position();


uint8_t get_sensor_value_back_pinD();
uint8_t get_sensor_value_back_pinB();
uint8_t get_sensor_value_front();


void ir_relect_on();
void ir_reflect_off();


_Bool sensor_is_over_line();
_Bool intersection_met();
_Bool right_sesor_state();
_Bool center_sesnor_state();
_Bool left_sensor_state ();
#endif
