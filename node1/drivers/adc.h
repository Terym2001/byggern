#ifndef ADC_H_H
#define ADC_H_H

#include <stdint.h>
#include <stdio.h>
#include <time.h>

#define ADC_CLOCK_F 2500000UL
#define N_CHANNELS 4UL 
#define FCONV ((9UL * N_CHANNELS * 2UL)/ADC_CLOCK_F) //Fconv in ms

#define ADC_BASE_ADDRESS 0x1400
#define ADC_MAX_ADDRESS 0x03FF

// TODO
#define JOYSTICK_X 0x1400
#define JOYSTICK_Y 0x1401
#define JOYSTICK_PRESS 0x1402

void ADC_InitializeExternalClock(void);

uint8_t ADC_ReadChannel(volatile uint16_t channel);

#endif
