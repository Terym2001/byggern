#ifndef _CAN_H_
#define _CAN_H_

#include <avr/io.h>
#include "mcp2515.h"

#define CANCTRL 0x0F

// CANCTRL register
#define REQOP2 7
#define REQOP1 6
#define REQOP0 5
#define ABAT 4
#define OSM 3
#define CLKEN 2
#define CLKPRE1 1
#define CLKPRE0 0

void CAN_Init(void);

void CAN_Read(uint8_t address, uint8_t* data, uint8_t size);//TODO: IMPLMENT THIS WITH IDS and stuff

void CAN_Write(uint8_t address, uint8_t* data, uint8_t size);//TODO: IMPLMENT THIS WITH IDS and stuff

#endif
