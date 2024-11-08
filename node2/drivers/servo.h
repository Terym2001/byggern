#ifndef _SERVO_H_
#define _SERVO_H_

#include <stdint.h>
#include "sam.h"
#include "pio.h"
#include "can.h"
#include "pwm.h"

void servo_set_angle(enum JoystickDirection direction);

#endif
