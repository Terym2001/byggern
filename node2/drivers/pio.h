#ifndef _PIO_H_
#define _PIO_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "sam.h"

void PIO_InitPin(Pio *reg, uint32_t pin);

void PIO_SetPin(Pio *reg, uint32_t pin);

void PIO_ClearPin(Pio *reg, uint32_t pin);

#endif
