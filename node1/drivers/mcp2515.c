#include "mcp2515.h"

void MCP2515_Read(uint8_t address, uint8_t *buffer, uint8_t size) {
  // Select the MCP2515
  PORTB &= ~(1 << SS); 

  // Choose the READ command
  SPI_MasterTransmit(MCP2515_READ);

  // Read the data
  buffer[0] = SPI_MasterTransmit(address);
  for (uint8_t i = 1; i < size; i++)
  {
    // TODO: Check that dummy byte is correct byte to send here
    buffer[i] = SPI_MasterTransmit(0x00);
  }

  // Unslect the MCP2515
  PORTB |= (1 << SS);

  return;
}

void MCP2515_Write(uint8_t address, uint8_t *data, uint8_t size)
{
  // Select the MCP2515
  PORTB &= ~(1 << SS);

  // Choose the WRITE command
  SPI_MasterTransmit(MCP2515_WRITE);

  // Write the address
  SPI_MasterTransmit(address);

  // Write the data
  for (uint8_t i = 0; i < size; i++)
  {
    SPI_MasterTransmit(data);
  }

  // Unselect the MCP2515
  PORTB |= (1 << SS);

  return; 
}

void MCP2515_RequestToSend(uint8_t txBuffer)
{
  // Select the MCP2515
  PORTB &= ~(1 << SS);

  uint8_t rtsCommand = MCP2515_RTS | txBuffer;

  // Choose the RTS command
  SPI_MasterTransmit(rtsCommand);

  // Unselect the MCP2515
  PORTB |= (1 << SS);

  return;
}

void MCP2515_ReadStatus(uint8_t *status, uint8_t size)
{
  // Select the MCP2515
  PORTB &= ~(1 << SS);

  for (uint8_t i = 0; i < size; i++)
  {
    status[i] = SPI_MasterTransmit(MCP2515_READ_STATUS);
  }

  // Unselect the MCP2515
  PORTB |= (1 << SS);

  return;
}

void MCP2515_BitModify(uint8_t address, uint8_t mask, uint8_t data)
{
  // Select the MCP2515
  PORTB &= ~(1 << SS);

  // TODO: Not all addresses are valid for this command

  // Choose the Bit Modify command
  SPI_MasterTransmit(MCP2515_BIT_MODIFY);

  // Choos the address
  SPI_MasterTransmit(address);

  // Choose the bit mask
  SPI_MasterTransmit(mask);

  // choose the data
  SPI_MasterTransmit(data);

  // Unselect the MCP2515
  PORTB &= ~(1 << SS);

  return;
}

void MCP2515_Reset(void)
{
  // Select the MCP2515
  PORTB &= ~(1 << SS);

  // Choose the RESET command
  SPI_MasterTransmit(MCP2515_RESET); 

  // Unselect the MCP2515
  PORTB |= (1 << SS);

  return;
}
