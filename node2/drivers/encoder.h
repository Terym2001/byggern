#ifndef _ENCODER_H_
#define _ENCODER_H_

#include <stdio.h>
#include <stdint.h>
#include "sam.h"

void encoder_init(void);

int16_t encoder_read(void);

#endif 
