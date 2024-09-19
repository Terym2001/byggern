#include "xmem.h"

void XMEM_Init(void)
{
  // Enable external SRAM/XMEM
  MCUCR |= (1 << SRE);

  // PC7-PC4 Released as normal pins when external memory is enabled
  SFIOR &= ~(0b111 << XMM0);
  SFIOR |= (1 << XMM2);
  return;
}

void XMEM_Write(uint8_t data, uint16_t addr, uint16_t offset)
{
  volatile char *ext_mem = (char*) offset;
  ext_mem[addr] = data;
  return;
}

uint8_t XMEM_Read(uint16_t addr, uint16_t offset)
{
  volatile char *ext_mem = (char*) offset;
  uint8_t data = ext_mem[addr];
  return data;
}
