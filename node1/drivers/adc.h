#ifndef _ADC_H
#define _ADC_H

#include <avr/io.h>
#include <stdio.h>
#include "xmem.h"

#define ADC_CLOCK_F 4915200UL
#define N_CHANNELS 4UL
#define FCONV ((9UL * N_CHANNELS * 2UL) / ADC_CLOCK_F) // Fconv in ms

#define ADC_BASE_ADDRESS 0x1400
#define ADC_MAX_ADDRESS 0x03FF


struct JoystickPositionPercent {
  int8_t xPercent;
  int8_t yPercent;
};

enum JoystickDirection { LEFT, RIGHT, UP, DOWN, PRESSED, NEUTRAL };

struct Joystick{
  //Values from 0 to 255
  uint8_t xRaw;
  uint8_t yRaw;
  //Offset of the joystick
  int8_t xOffset;
  int8_t yOffset;
  //Direction
  enum JoystickDirection direction;
};

struct Slider {
  uint8_t left;
  uint8_t right;
};

void ADC_InitializeExternalClock(void);

void ADC_Init(void);

struct Joystick ADC_InitJoystick(void);

void ADC_Read(struct Joystick *joystick);

void ADC_ReadSlider(struct Slider *slider);

void ADC_ConvertToPercent(uint8_t xRaw, uint8_t yRaw, struct JoystickPositionPercent *Jpos);

struct JoystickPositionPercent ADC_GetJoystickPercent();

enum JoystickDirection ADC_GetJoystickDirection(struct Joystick *joystick);

#endif
