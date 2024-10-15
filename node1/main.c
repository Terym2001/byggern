#include "main.h"
#include "drivers/mcp2515.h"

int main(void) {
  // Initialize uart with baud rate and frameformat
  USART_Init(MYUBRR);

  MCP2515_Init(); 

  uint8_t mask = (1 << REQOP2) | (1 << REQOP1) | (1 << REQOP0);
  uint8_t data = (1 << REQOP1);

  // set can controller to loopback mode
  MCP2515_BitModify(0b00111111, mask, data);
  //Set to one shot mode
  MCP2515_BitModify(MCP_CANCTRL,1 << 3, 1 << 3);
  printf("First iteration\n\r");
  while (1)
  {
    printf("mode: %x\n\r", MCP2515_Read(0b00111110));

    MCP2515_Write(TXB0SIDH, 0xAF);
    MCP2515_Write(TXB0SIDL, (0x03 << 5));
    MCP2515_Write(TXB0DLC, 0x0F);
    MCP2515_Write(TXB0D0, 0xAF);
    MCP2515_RequestToSend(MCP_RTS_TX0);

    uint8_t byte = MCP2515_Read(MCP_RXB0SIDH);
    printf("byte: %x\n\r", byte);
    _delay_ms(5000);
  }
  
  return 0;
}
