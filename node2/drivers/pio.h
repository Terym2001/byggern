#ifndef _PIO_H_
#define _PIO_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "sam.h"

#define PIO_PERIPH_A 0
#define PIO_PERIPH_B 1

void pio_init_pin_for_peripheral(Pio *reg, uint32_t pin, uint32_t peripheral);

void pio_init_pin_as_output(Pio* reg, uint32_t pin);

void pio_set_pin(Pio *reg, uint32_t pin);

void pio_clear_pin(Pio *reg, uint32_t pin);

#endif
