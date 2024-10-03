#ifndef _XMEM_H
#define _XMEM_H

#include "../main.h" 

void XMEM_Init(void);

void XMEM_Write(uint8_t data, uint16_t addr, uint16_t offset);

uint8_t XMEM_Read(uint16_t addr, uint16_t offset);

#endif
