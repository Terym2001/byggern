#include "mcp2515.h"

void MCP2515_Reset(void)
{
  SPI_clearSS;

  // Choose the RESET command
  SPI_MasterTransmit(MCP_RESET); 

  SPI_setSS;
  return;
}

void MCP2515_Init(void)
{
  //Setup SPI
  SPI_MasterInit();

  //Reset MCP2515
  MCP2515_Reset();

  _delay_ms(1); // Mega viktig?
  
  uint8_t status = MCP2515_Read(MCP_CANSTAT);
  if ((status & MODE_MASK) != MODE_CONFIG) 
  {
    printf("MCP2515 is NOT in configuration mode after reset!, CANSTAT: %x\n\t", status);
  }

  MCP2515_BitModify(MCP_CANINTE, 0b00011111, 0);

  // // Set the baud rate
  // // Setup CNF1  
  // MCP2515_BitModify(MCP_CNF1, 0b00111111, BRP);
  // MCP2515_BitModify(MCP_CNF1, 0b11000000, (1 << SJW1));

  // //Setup CNF2
  // MCP2515_BitModify(MCP_CNF2, 0b00111000, PS1 << PHSEG10);
  // MCP2515_BitModify(MCP_CNF2, 0b00000111, (1 << PRSEG0));

  // // TODO: maybe 1 idk
  // MCP2515_BitModify(MCP_CNF2, 0b10000000, (0 << SAM));
  // MCP2515_BitModify(MCP_CNF2, 0b01000000, (1 << BTLMODE));

  // //Setup CNF3
  // MCP2515_BitModify(MCP_CNF3, 0b00000111, PS2);

  return;
}

uint8_t MCP2515_Read(uint8_t address) {
  SPI_clearSS;

  // Choose the READ command
  SPI_MasterTransmit(MCP_READ);

  // Read the data
  SPI_MasterTransmit(address);
  uint8_t data = SPI_MasterReceive();

  SPI_setSS;

  return data;
}

void MCP2515_Write(uint8_t address, uint8_t data)
{
  SPI_clearSS;
  
  // Choose the WRITE command
  SPI_MasterTransmit(MCP_WRITE);

  // Write the address
  SPI_MasterTransmit(address);

  // Write the data
  SPI_MasterTransmit(data);

  SPI_setSS;

  return; 
}

void MCP2515_RequestToSend(uint8_t txBuffer)
{
  SPI_clearSS;

  // Choose the RTS command
  SPI_MasterTransmit(txBuffer);

  SPI_setSS;

  return;
}

uint8_t MCP2515_ReadStatus(void)
{
  SPI_clearSS;

  SPI_MasterTransmit(MCP_READ_STATUS);
  uint8_t status = SPI_MasterReceive();

  SPI_setSS;

  return status;
}

void MCP2515_BitModify(uint8_t address, uint8_t mask, uint8_t data)
{
  SPI_clearSS;

  // Choose the Bit Modify command
  SPI_MasterTransmit(MCP_BITMOD);

  // Choos the address
  SPI_MasterTransmit(address);

  // Choose the bit mask
  SPI_MasterTransmit(mask);

  // choose the data
  SPI_MasterTransmit(data);

  SPI_setSS;

  return;
}
