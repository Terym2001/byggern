#include "XMEM.h"

void XMEM_Init(void)
{
  // Enable external SRAM/XMEM
  MCUCR |= (1 << SRE);

  // PC7-PC4 Released as normal pins when external memory is enabled
  SFIOR |= (1 << XMM2);

  // TODO

  return;
}

void XMEM_Write(uint8_t data, uint16_t addr)
{
  volatile char *ext_mem = (char*) BASE_ADDRESS;
  ext_mem[addr] = data;
  return;
}

uint8_t XMEM_Read(uint16_t addr)
{
  volatile char *ext_mem = (char*) BASE_ADDRESS;
  uint8_t data = ext_mem[addr];
  return data;
}
