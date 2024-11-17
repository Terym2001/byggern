#ifndef _PWM_H
#define _PWM_H

#include <stdint.h>
#include <stdio.h>
#include "sam.h"
#include "pio.h"
#include "can.h"

#define CALCULATED_CPRD 13125

#define DUTY_CYCLE_LOWER_BOUND  45
#define DUTY_CYCLE_UPPER_BOUND  105 
#define DUTY_CYCLE_MIDDEL       75 

#define PWM_SERVO_CHANNEL 1
#define PWM_MOTOR_CHANNEL 0

void pwm_init(void);

void pwm_set_duty_cycle(uint16_t cycle_percentage, uint8_t channel);

//void pwm_set_servo_angle(enum JoystickDirection direction);

#endif
