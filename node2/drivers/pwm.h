#ifndef _PWM_H
#define _PWM_H

#include <stdint.h>
#include "sam.h"
#include "pio.h"
#include "can.h"

#define CALCULATED_CPRD 13125

#define DUTY_CYCLE_LOWER_BOUND  45
#define DUTY_CYCLE_UPPER_BOUND  105 
#define DUTY_CYCLE_MIDDEL       75 


void pwm_init(void);

void pwm_set_duty_cycle(uint16_t cycle_percentage);

void pwm_set_servo_angle(enum JoystickDirection direction);

#endif
