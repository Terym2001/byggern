#include "sram.h"

int SRAM_CheckAddress(uint16_t addr)
{
  if (addr > SRAM_MAX_ADDRESS) 
  {
    return 0;
  }
  return 1;
}

void SRAM_Write(uint8_t data, uint16_t addr)
{
  if (!SRAM_CheckAddress(addr))
  {
    printf("ERROR-SRAM: Invalid data address!\n\r");
    return;
  } 

  XMEM_Write(data, addr, SRAM_BASE_ADDRESS); 
  return;
}

uint8_t SRAM_Read(uint16_t addr)
{
  if (!SRAM_CheckAddress(addr))
  {
    printf("ERROR: Invalid data address!\n\r");
    return 0;
  }

  return XMEM_Read(addr, SRAM_BASE_ADDRESS);
}
