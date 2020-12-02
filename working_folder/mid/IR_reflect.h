#ifndef RF_REFLECT_H
#define RF_REFLECT_H


#include <stdint.h>
#include <stdfix.h>

void config_ir_reflect();

signed short sat accum get_line_position();
//signed short get_line_position();


uint8_t get_sensor_value_back_pinD();
uint8_t get_sensor_value_back_pinB();

#endif
