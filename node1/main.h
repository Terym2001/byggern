#ifndef _MAIN_H_
#define _MAIN_H_

#define F_CPU 4915200UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdio.h>

#include "drivers/oled.h"
#include "drivers/usart.h"
#include "drivers/adc.h"
#include "drivers/spi.h"
#include "drivers/mcp2515.h"
#include "drivers/can.h"

#include "resources/bit_macros.h"

#include "test/sram_test.h"

#endif
