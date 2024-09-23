#ifndef ADC_H_H
#define ADC_H_H

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "xmem.h"

#define ADC_CLOCK_F 4915200UL
#define N_CHANNELS 4UL 
#define FCONV ((9UL * N_CHANNELS * 2UL)/ADC_CLOCK_F) //Fconv in ms

#define ADC_BASE_ADDRESS 0x1400
#define ADC_MAX_ADDRESS 0x03FF

// TODO
#define JOYSTICK_X 0x1400
#define JOYSTICK_Y 0x1401
#define JOYSTICK_PRESS 0x1402

void ADC_InitializeExternalClock(void);

void ADC_Init(void);

void ADC_Read(uint8_t* data);

#endif
