#include "adc.h"

void ADC_InitializeExternalClock(void) {
  // Set PWM signal on pin PD4 as output
  DDRD |= (1 << PD4);

  // set to CTC mode
  TCCR3B &= ~(1 << WGM33);
  TCCR3B |=  (1 << WGM32);
  TCCR3A &= ~(1 << WGM31);
  TCCR3A &= ~(1 << WGM30);

  // set PWM toggle on match with internal clock
  TCCR3A &= ~(1 << COM3A1);
  TCCR3A |=  (1 << COM3A0);

  // set PWM signal to match with internal clock, no prescale
  TCCR3B &= ~(1 << CS32);
  TCCR3B &= ~(1 << CS31);
  TCCR3B |=  (1 << CS30);

  // frequency set to 0.5 x F_CPU
  OCR3A = 0;
  return;
}

void ADC_Init(void) {
  DDRD &= ~(1 << PD5);
  DDRB &= ~(1 << PB2);
  ADC_InitializeExternalClock();
  return;
}

void ADC_Read(struct ADCValues* data , struct CalibrateADC *cal) {
  XMEM_Write(0x00, 0x00, ADC_BASE_ADDRESS);

  _delay_ms(FCONV);

  for (uint8_t *ptr = &data->xRaw; ptr <= &data->rightSlider; ptr++) {
    *ptr = XMEM_Read(0x00, ADC_BASE_ADDRESS);
  }

  if (data->xRaw < cal->xOffset || data->yRaw < cal->yOffset)
  {
    return;
  }

  // Add offsett to reed value
  data->xRaw -= cal->xOffset;
  data->yRaw -= cal->yOffset;

  return;
}

void ADC_Calibrator(struct CalibrateADC *cal) {
  uint8_t data[4] = {0};
  XMEM_Write(0x00, 0x00, ADC_BASE_ADDRESS);
  _delay_ms(FCONV);

  for (uint8_t i = 0; i < 10; i++) {
    for (uint8_t j = 0; j < 4; j++) {
      data[j] = XMEM_Read(0x00, ADC_BASE_ADDRESS);
    }

    cal->xOffset = (cal->xOffset * i + data[0] - 127) / (i + 1); // Finds the offset of ideal value "127", from
    cal->yOffset = (cal->yOffset * i + data[1] - 127) / (i + 1); // Same for y value
  }

  printf("Calibrated values is: {%d,%d} \r \n", cal->xOffset, cal->yOffset);
  return;
}

void ADC_GetJoystickPosition(uint8_t xRaw, uint8_t yRaw, struct JoystickPositionPercent *Jpos) {
  // Convert the raw ADC values [0,255] to percentage values [-100,100]
  Jpos->xPercent = (((uint16_t) xRaw * 200) / 255) - 100; // Scale 0-255 to -100 to 100
  Jpos->yPercent = (((uint16_t) yRaw * 200) / 255) - 100;

  return;
}

enum JoystickDirection ADC_GetJoystickDirection(uint8_t xRaw, uint8_t yRaw, uint8_t zPressed) {
  struct JoystickPositionPercent pos;

  // Get the X and Y percentage positions
  ADC_GetJoystickPosition(xRaw, yRaw, &pos);

  // TODO: might need to test other thresholds
  // Define thresholds for detecting directions
  int threshold = 60; // Example threshold for determining direction

  if (pos.xPercent < -threshold) {
    return LEFT;
  } else if (pos.xPercent > threshold) {
    return RIGHT;
  } else if (pos.yPercent < -threshold) {
    return DOWN;
  } else if (pos.yPercent > threshold) {
    return UP;
  } else if(!(PINB & (1 << PINB2))) //TODO:FIX THIS SO IT DONT TAKE IN SLIDER VALUE BUT PRESSED BTN 
  {
    return PRESSED;
  }
  else {
    return NEUTRAL;
  }
}
