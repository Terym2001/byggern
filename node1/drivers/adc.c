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

  volatile char* ext_mem = (char*) ADC_BASE_ADDRESS; 
  for (uint8_t i = 0; i < 4; i++)
  {
   ext_mem[i] = 0; 
  }

  return;
}

 void ADC_Read(uint8_t* data)
{
  XMEM_Write(0x00, 0x00, ADC_BASE_ADDRESS); 

  // while (!(PORTD & (1 << PD5))) {printf("heihei\n\r");}
  _delay_ms(FCONV);

  for (uint8_t i = 0; i < 4; i++)
  {
    data[i] = XMEM_Read(0x00, ADC_BASE_ADDRESS);
  }

  return;
}

