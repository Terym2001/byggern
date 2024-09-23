#include "adc.h"


void ADC_InitializeExternalClock(void)
{
  // Set PWM signal on pin PD4 as output
  DDRB = (1 << PD0);

  // set to CTC mode
  TCCR0 |= (1 << WGM01);
  TCCR0 &= ~(1 << WGM00);

  // set PWM toggle on match with internal clock
  TCCR0 &= ~(1 << COM01);
  TCCR0 |= (1 << COM00);

  // set PWM signal to match with internal clock, no prescale
  TCCR0 &= ~(1 << CS02);
  TCCR0 &= ~(1 << CS01);
  TCCR0 |= (1 << CS00);

  // frequency set to 0.5 x F_CPU
  OCR0 = 0;
  return;
}

void ADC_Init(void)
{
  DDRD &= ~(1 << PD5);
  ADC_InitializeExternalClock();
  /*
  volatile char* ext_mem = (char*) ADC_BASE_ADDRESS; 
  for (uint8_t i = 0; i < 4; i++)
  {
   ext_mem[i]; 
  }
*/
  return;
}

 void ADC_Read(uint8_t* data, struct CalibrateADC* cal)
{
  XMEM_Write(0x00, 0x00, ADC_BASE_ADDRESS); 
  //volatile char *adc = (char *) 0x1400; //Base address for ADC
  //adc[0] = 0x04;
  // while (!(PORTD & (1 << PD5))) {printf("heihei\n\r");}
  _delay_ms(FCONV);

  for (uint8_t i = 0; i < 4; i++)
  {
    data[i] = XMEM_Read(0x00, ADC_BASE_ADDRESS);
  }
  //Add offsett to reed value
  data[0] = data[0] - cal->xValue;
  data[2] = data[2] - cal->yValue;
  return;
}


void ADC_Calibrator(struct CalibrateADC* cal)
{
  uint8_t data[4] = {0};
  XMEM_Write(0x00, 0x00, ADC_BASE_ADDRESS); 
  _delay_ms(FCONV);

  for (uint8_t i = 0; i < 4; i++)
  {
    data[i] = XMEM_Read(0x00, ADC_BASE_ADDRESS);
  }
  cal->xValue = data[0] - 127; //Finds the offset of ideal value "127", from read value and calibrates(For x value)
  cal->yValue = data[2] - 127; //Same for y value
  printf("Calibrated values is: {%u,%u} \r \n",cal->xValue,cal->yValue);
  return;
}

void ADC_GetJoystickPosition(uint8_t xRaw, uint8_t yRaw, struct JoystickPosition* Jpos)
{
  //Convert the raw ADC values [0,255] to percentage values [-100,100]
  Jpos->xPercent = ((xRaw * 200)/255) - 100; //Scale 0-255 to -100 to 100
  Jpos->yPercent = ((yRaw * 200)/255) - 100;

  return;
}

enum JoystickDirection ADC_GetJoystickDirection(uint8_t xRaw, uint8_t yRaw)
{
    struct JoystickPosition pos;
    
    // Get the X and Y percentage positions
    ADC_GetJoystickPosition(xRaw, yRaw, &pos);

    // Define thresholds for detecting directions
    int threshold = 30; // Example threshold for determining direction

    if (pos.xPercent < -threshold) {
        return LEFT;
    } else if (pos.xPercent > threshold) {
        return RIGHT;
    } else if (pos.yPercent < -threshold) {
        return DOWN;
    } else if (pos.yPercent > threshold) {
        return UP;
    } else {
        return NEUTRAL;
    }
}