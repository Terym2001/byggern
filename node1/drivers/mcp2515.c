#include "mcp2515.h"

uint8_t MCP2515_Read(uint8_t address) {
  // Choose the READ command
  SPI_MasterTransmit(MCP_READ);

  // Read the data
  uint8_t data = SPI_MasterTransmit(address);

  return data;
}

void MCP2515_Write(uint8_t address, uint8_t data)
{
  // Choose the WRITE command
  SPI_MasterTransmit(MCP_WRITE);

  // Write the address
  SPI_MasterTransmit(address);

  // Write the data
  SPI_MasterTransmit(data);
  return; 
}

void MCP2515_RequestToSend(uint8_t txBuffer)
{
  // Choose the RTS command
  SPI_MasterTransmit(txBuffer);
  return;
}

uint8_t MCP2515_ReadStatus(void)
{
  uint8_t status = SPI_MasterTransmit(MCP_READ_STATUS);
  return status;
}

void MCP2515_BitModify(uint8_t address, uint8_t mask, uint8_t data)
{
  // TODO: Not all addresses are valid for this command

  // Choose the Bit Modify command
  SPI_MasterTransmit(MCP_BITMOD);

  // Choos the address
  SPI_MasterTransmit(address);

  // Choose the bit mask
  SPI_MasterTransmit(mask);

  // choose the data
  SPI_MasterTransmit(data);
  return;
}

void MCP2515_Reset(void)
{
  // Choose the RESET command
  SPI_MasterTransmit(MCP_RESET); 
  return;
}

void MCP2515_Init(void)
{
  //Setup SPI
  SPI_MasterInit();

  //Reset MCP2515
  MCP2515_Reset();

  _delay_ms(1); // Mega viktig?

  // Set the baud rate
  // Setup CNF1  
  MCP2515_BitModify(MCP_CNF1, 0b00111111, BRP);
  MCP2515_BitModify(MCP_CNF1, 0b11000000, (1 << SJW1));

  //Setup CNF2
  MCP2515_BitModify(MCP_CNF2, 0b00111000, PS1 << PHSEG10);
  MCP2515_BitModify(MCP_CNF2, 0b00000111, (1 << PRSEG0));

  // TODO: maybe 1 idk
  MCP2515_BitModify(MCP_CNF2, 0b10000000, (0 << SAM));

  MCP2515_BitModify(MCP_CNF2, 0b01000000, (1 << BTLMODE));

  //Setup CNF3
  MCP2515_BitModify(MCP_CNF3, 0b00000111, PS2);
}


