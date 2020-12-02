
#include <stdfix.h>
#include <stdint.h>

#include "IR_reflect.h"
#include "motor.h"
#include "push_button_A.h"



#define DUTY_CYCLE 20
#define STEER_SCALER 15



int8_t steer_bot = 0;


int main(void)
{
    config_ir_reflect();
	config_motors();
	config_push_button_A();

	uint8_t speed = DUTY_CYCLE;
	set_duty_cycle(speed);
while(!(push_button_A_is_pressed()))
{}
    while (1) 
    {
                        shift_robot(FORWARD);
                       steer_bot = get_line_position();
                        steer(steer_bot*STEER_SCALER);


    }
}

