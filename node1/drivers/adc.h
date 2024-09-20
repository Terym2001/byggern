#ifndef ADC_H_H
#define ADC_H_H

#include <stdint.h>
#include <stdio.h>

#define ADC_CLOCK_F 2500000UL
#define N_CHANNELS 4UL 
#define FCONV ((9UL * N_CHANNELS * 2UL)/ADC_CLOCK_F)

#define ADC_BASE_ADDRESS 0x1400
#define ADC_MAX_ADDRESS 0x03FF

// TODO
#define JOYSTICK_X 0x1400
#define JOYSTICK_Y 0x1401
#define JOYSTICK_PRESS 0x1402

uint8_t ADC_ReadChannel(uint8_t channel);

// TODO
// Read aall channels and return array
uint8_t* ADC_ReadAll();

void ADC_ExternalClock();

void ADC_Clock();

#endif
