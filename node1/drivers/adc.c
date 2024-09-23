#include "adc.h"

void ADC_InitializeExternalClock(void)
{
  // Set PWM signal on pin PD4 as output
  DDRD |= (1 << PD4);

  // Set pin to CTC mode
  TCCR3A |= (1 << WGM31);
  TCCR3A &= ~(1 << WGM30);

  // Set PWM toggle on match with internal clock
  TCCR3A &= ~(1 << COM3A1);
  TCCR3A |= (1 << COM3A0);

  // Set clock source with no prescaling 
  TCCR3B &= (1 << CS32); 
  TCCR3B &= (1 << CS31);
  TCCR3B |= (1 << CS30);

  // Set frequency to 0.5 * FCLOCK
  OCR0 = 0;

  return;
}

uint8_t ADC_ReadChannel(uint16_t channel)
{
  if (channel > N_CHANNELS)
  {
    printf("ERROR-ADC: channel must not exceed %u!\n\r", N_CHANNELS); 
    return 0;
  }

  XMEM_Write(channel, channel, ADC_BASE_ADDRESS);

  _delay_us(FCONV);

  uint8_t data = XMEM_Read(channel, ADC_BASE_ADDRESS);

  return data;
}

// time_t prevTime = 0;
// uint8_t ADC_ReadChannel(volatile uint16_t channel)
// {
//   if (channel > N_CHANNELS) 
//   {
//     printf("ERROR-ADC: Invalid channel!\n\r");
//     printf("ERROR-ADC: Must be in range: {0-%u}\n\r", N_CHANNELS);
//     return -1;
//   }
//   //First write to ADC to trigger channel we want to write to 
//   XMEM_Write((uint8_t) channel, channel, ADC_BASE_ADDRESS);
//   //Toggle debug pin
//   DDRD ^= (1 << PD5);
//   //delay so that values are safe
//   _delay_us(FCONV); //TODO: Not sure we can delay since extClock
//   //toggle debug pin
//   DDRD ^= (1 << PD5);
//   //get values
//   uint8_t data = XMEM_Read((uint16_t) channel, ADC_BASE_ADDRESS);
//   return data;
// }
// 
// 
// void ADC_Clock()
// {
//   //Save prev time
//   time_t current_time = time(&current_time);
//   if(current_time - prevTime > 1/ADC_CLOCK_F)
//   {
//     //Toggle clock pin
//     DDRD ^= (1 << PD4);
//     //Update prev time
//     prevTime = current_time;
//   } 
// }


