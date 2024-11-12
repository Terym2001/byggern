#ifndef _MOTOR_H_
#define _MOTOR_H_

#include <stdint.h>
#include <stdio.h>
#include "can.h"
#include "sam.h"
#include "pio.h"
#include "pwm.h"

void motor_init(void);

void motor_set_direction(enum JoystickDirection direction);

void motor_set_speed(int8_t speed);

#endif
