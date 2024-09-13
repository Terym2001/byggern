#ifndef _XMEM_H
#define _XMEM_H

#include <avr/io.h>

#define BASE_ADDRESS 0x1800

void XMEM_Init(void);

void XMEM_Write(uint8_t data, uint16_t addr);

uint8_t XMEM_Read(uint16_t addr);

#endif
