#ifndef _PWM_H
#define _PWM_H

#include <stdint.h>
#include "sam.h"
#include "pio.h"

#define CALCULATED_CPRD 13125

void pwm_init(void);

#endif
