#include "can.h"
#include "mcp2515.h"

// TODO: take mask and data as arguments
void CAN_Init(void) {
  // Initialize SPI
  SPI_MasterInit();
  
  // Reset MCP2515
  MCP2515_Reset();
  
  uint8_t mask = (1 << REQOP2) | (1 << REQOP1) | (1 << REQOP0);
  uint8_t data = (1 << REQOP2);

  // set can controller to loopback mode
  MCP2515_BitModify(CANCTRL, mask, data);
}
