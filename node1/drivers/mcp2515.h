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
//Macros for setting baud rate
#define CNF1 0x2A //Adress of regsiter
#define CNF2 0x29
#define CNF3 0x28
#define BRP 0x04 - 1//Actually 4 but some data sheet black macic

#define F_osc 16000000UL
#define T_osc 1/F_osc
#define T_q 2*(BRP+1)/F_osc
//Values for registers
#define PS1 0x07 - 1
#define SYNCSEG 0x01
#define PROPSEG 0x02 - 1
#define PS2 0x06 - 1
#define SJW_VAL 0x01
#define SAM_VAL 0x00 //TODO: Maybe 1 idk
#define BTLMODE_VAL 0x01 //TODO: 1 if PS2 < PS1 ?
//CNF1 register
#define SJW 7
//CNF2 register
#define PRSEG2 2
#define PHSEG12 5
#define SAM 6
#define BTLMODE 7
//CNF3 register
#define PHSEG22 2

void MCP2515_Read(uint8_t address, uint8_t *buffer, uint8_t size);

void MCP2515_Write(uint8_t address, uint8_t *data, uint8_t size);

void MCP2515_RequestToSend(uint8_t txBuffer);

void MCP2515_ReadStatus(uint8_t *status, uint8_t size);

void MCP2515_BitModify(uint8_t address, uint8_t mask, uint8_t data);

void MCP2515_Reset(void);

void MCP2515_Init(void);

#endif
