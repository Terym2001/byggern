#include "adc.h"

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

uint8_t ADC_ReadChannel(uint16_t channel)
{
  XMEM_Write(0x00, channel, ADC_BASE_ADDRESS);
  _delay_us(FCONV);
  XMEM_Read(ADC_BASE_ADDRESS);
  return
}
