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

struct CalibrateADC
{
  uint8_t xValue;
  uint8_t yValue;
};

struct JoystickPosition
{
    int8_t xPercent;
    int8_t yPercent;
};

enum JoystickDirection
{
    LEFT,
    RIGHT,
    UP,
    DOWN,
    NEUTRAL
};

void ADC_InitializeExternalClock(void);

void ADC_Init(void);

void ADC_Read(uint8_t* data, struct CalibrateADC* cal);

void ADC_Calibrator(struct CalibrateADC* cal);

void ADC_GetJoystickPosition(uint8_t xRaw, uint8_t yRaw, struct JoystickPosition* Jpos);

enum JoystickDirection ADC_GetJoystickDirection(uint8_t xRaw, uint8_t yRaw);

#endif
