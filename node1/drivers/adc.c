#include "adc.h"

int ACD_CheckAddress(uint16_t addr)
{
  if (addr > ADC_MAX_ADDRESS)
  {
    return 0;
  }
  return 1;
}

uint8_t ADC_ReadChannel(volatile uint8_t channel)
{
  if (!ADC_CheckAddress(channel)) 
  {
    printf("ERROR-ADC: Invalid data address!\n\r");
    return -1;
  }
  //First write to ADC to trigger channel we want to write to 
  XMEM_Write(channel,(uint16_t)channel,ADC_BASE_ADDRESS);
  //Toggle debug pin
  //delay so that values are safe
  _delay_ms(500); //To do fix this
  //toggle debug pin
  //get values
  uint8_t data = XMEM_Read((uint16_t)channel,ADC_BASE_ADDRESS);
  return data;
}
