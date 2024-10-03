#ifndef _MCP2515_H_
#define _MCP2515_H_

#include <avr/io.h>
#include <stdint.h>
#include "spi.h"

#define MCP2515_RESET 0xC0
#define MCP2515_READ 0x03
#define MCP2515_WRITE 0x02
#define MCP2515_READ_STATUS 0xA0
#define MCP2515_BIT_MODIFY 0x05

#define MCP2515_RTS 0x80
#define TXB0 0x01
#define TXB1 0x02
#define TXB2 0x04

void MCP2515_Read(uint8_t address, uint8_t *buffer, uint8_t size);

void MCP2515_Write(uint8_t address, uint8_t *data, uint8_t size);

void MCP2515_RequestToSend(uint8_t txBuffer);

void MCP2515_ReadStatus(uint8_t *status, uint8_t size);

void MCP2515_BitModify(uint8_t address, uint8_t mask, uint8_t data);

void MCP2515_Reset(void);

#endif
