#ifndef _PWM_H
#define _PWM_H

#include <stdint.h>
#include "sam.h"
#include "pio.h"

#define CALCULATED_CPRD 13125

#define DUTY_CYCLE_LOWER_BOUND  45
#define DUTY_CYCLE_UPPER_BOUND  105 
#define DUTY_CYCLE_MIDDEL       ((DUTY_CYCLE_UPPER_BOUND - DUTY_CYCLE_LOWER_BOUND)/2)


void pwm_init(void);

void pwm_set_duty_cycle(uint16_t cycle_percentage);

#endif
