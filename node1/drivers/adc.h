#ifndef ADC_H_H
#define ADC_H_H

#include <stdint.h>
#include <stdio.h>

#define ADC_CLOCK_F 2500000UL
#define N_CHANNELS // TODO
#define FCONV ((9UL * N_CHANNELS * 2UL)/ADC_CLOCK_F)

#define ADC_BASE_ADDRESS 0x1400
#define ADC_MAX_ADDRESS 0x03FF

#define JOYSTICK_X 0x1400
#define JOYSTICK_Y 0x1401
#define JOYSTICK_PRESS 0x1402

int ACD_CheckAddress(uint16_t addr);

uint8_t ADC_ReadChannel(uint8_t channel);

// TODO
// Read aall channels and return array
uint8_t* ADC_ReadAll();

#endif
