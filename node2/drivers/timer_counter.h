#ifndef _TIMER_COUNTER_H_
#define _TIMER_COUNTER_H_

//#include <stdio.h>
#include <stdint.h>
#include "sam.h"
#include "motor_controller.h"
#include "encoder.h"

extern uint8_t score;

void tc_init(uint32_t channel, unsigned long period);

#endif
