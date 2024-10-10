#include "can.h"
#include "mcp2515.h"

// TODO: take mask and data as arguments
void CAN_Init(void) {
  // Initialize the MCP2515
  MCP2515_Init();
  
  uint8_t mask = (1 << REQOP2) | (1 << REQOP1) | (1 << REQOP0);
  uint8_t data = (1 << REQOP2);

  // set can controller to loopback mode
  MCP2515_BitModify(CANCTRL, mask, data);

  //Init Interupt stuff dont think we need this in loopback mode
  
  //Enable buffers for transmit and receive?

  //More stuff?
}
