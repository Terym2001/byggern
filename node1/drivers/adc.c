#include "adc.h"

uint8_t ADC_ReadChannel(volatile uint8_t channel)
{
  if (channel > N_CHANNELS) 
  {
    printf("ERROR-ADC: Invalid channel!\n\r");
    printf("ERROR-ADC: Must be in range: {0-%u}\n\r", N_CHANNELS);
    return -1;
  }
  //First write to ADC to trigger channel we want to write to 
  XMEM_Write(channel,(uint16_t) channel, ADC_BASE_ADDRESS);
  //Toggle debug pin
  //delay so that values are safe
  _delay_ms(500); //TODO: Not sure we can delay since extClock
  //toggle debug pin
  //get values
  uint8_t data = XMEM_Read((uint16_t) channel, ADC_BASE_ADDRESS);
  return data;
}
