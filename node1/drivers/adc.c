#include "adc.h"

int ACD_CheckAddress(uint16_t addr)
{
  if (addr > ADC_MAX_ADDRESS)
  {
    return 0;
  }
  return 1;
}

uint8_t ADC_Read(uint16_t addr)
{
  if (!ADC_CheckAddress(addr)) 
  {
    printf("ERROR-ADC: Invalid data address!\n\r");
    return -1;
  }
  
  return XMEM_Read(addr, ADC_BASR_ADDRESS);
}
