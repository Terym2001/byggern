#ifndef _SRAM_H_
#define _SRAM_H_

#include <stdio.h>
#include "xmem.h"

#define SRAM_BASE_ADDRESS 0x1800
#define SRAM_MAX_ADDRESS 0x0800

int SRAM_CheckAddress(uint16_t addr);

void SRAM_Write(uint8_t data, uint16_t adr);

uint8_t SRAM_Read(uint16_t addr);

#endif
