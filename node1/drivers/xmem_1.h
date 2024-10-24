#ifndef _XMEM_H
#define _XMEM_H

#include "../main.h" 

typedef struct Xmem
{
  void (*write)(uint8_t data, uint16_t addr, uint16_t offset);
  uint8_t (*read)(uint16_t addr, uint16_t offset);
} Xmem;

void xmem_init(void);

void xmem_write(uint8_t data, uint16_t addr, uint16_t offset);

uint8_t xmem_read(uint16_t addr, uint16_t offset);

#endif
