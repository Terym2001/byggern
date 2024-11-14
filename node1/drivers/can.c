#include <stdio.h>
#include "can.h"
#include "mcp2515.h"

// TODO: take mask and data as arguments
void CAN_Init(void) 
{
  // Initialize the MCP2515
  MCP2515_Init();
  
  uint8_t mask = (1 << REQOP2) | (1 << REQOP1) | (1 << REQOP0);
  uint8_t data = 0x0;

  // set can controller to normal mode
  MCP2515_BitModify(MCP_CANCTRL, mask, data);
}

uint8_t CAN_Recieve(struct can_message* msg) 
{
  //while (!(MCP2515_Read(MCP_CANINTF) & (1 << RX0IF))) {}
  if (!(MCP2515_Read(MCP_CANINTF) & (1 << RX0IF)))
  {
    return 0;
  }

  uint8_t id_high = MCP2515_Read(MCP_RXB0SIDH);
  uint8_t id_low = (MCP2515_Read(MCP_RXB0SIDL) >> 5);
  msg->id = (id_high << 3) | id_low; 
  
  msg->length = (MCP2515_Read(RXB0DLC) & 0x0F);

  for(int i = 0; i < msg->length; i++)
  {
    msg->data[i] = MCP2515_Read(RXB0D0 + i);
  }

  //Reset the interrupt flag
  MCP2515_BitModify(MCP_CANINTF,0x03,0x00); 

  return 1;
}

void CAN_Send(struct can_message* msg, uint8_t msg_priority, uint8_t txBuffer) 
{
  // Map txBuffer to TXBnCTRL register
  // uint8_t txbnctrl = 0;
  // uint8_t txbnsidh = 0;
  // uint8_t txbnsidl = 0;
  // uint8_t txbndlc = 0;
  // switch (txBuffer)
  // {
  //   case TXB0:
  //     txbnctrl = TXB0CTRL;
  //     txbnsidh = TXB0SIDH;
  //     txbnsidl = TXB0SIDL;
  //     txbndlc  = TXB0DLC;
  //     break;
  //   case TXB1:
  //     txbnctrl = TXB1CTRL;
  //     txbnsidh = TXB1SIDH;
  //     txbnsidl = TXB1SIDL;
  //     txbndlc  = TXB1DLC;
  //     break;
  //   case TXB2:
  //     txbnctrl = TXB2CTRL;
  //     txbnsidh = TXB2SIDH;
  //     txbnsidl = TXB2SIDL;
  //     txbndlc  =  TXB2DLC;
  //     break;
  //   default:
  //     printf("Invalid txBuffer\n\r");
  //     return;
  // }

  // Set message priority
  // uint8_t mask = (1 << TXP1) | (1 << TXP0);
  // MCP2515_BitModify(txbnctrl, mask, msg_priority);

  // load SIDH and SIDL register
  // load SIDH
  MCP2515_Write(TXB0SIDH, (msg->id >> 3));

  // load SIDL
  MCP2515_Write(TXB0SIDL, (msg->id << 5)); 

  // load DLC
  MCP2515_Write(TXB0DLC, msg->length);

  // load data
  for (uint8_t i = 0; i < msg->length; i++)
  {
    MCP2515_Write(TXB0D0 + i, msg->data[i]);
  }

  // Set TXBnCTRL.TXREQ by sending RTS command
  MCP2515_RequestToSend(MCP_RTS_TX0);

  // Check for errors
  uint8_t reg = MCP2515_Read(TXB0CTRL);
  if (reg & (1 << TXREQ))
  {
    if (reg & (1 << TXERR))
    {
      // TODO: Implement error handling
      printf("Error \n\r");
    }
    else if (reg & (1 << MLOA))
    {
      // TODO: Implement msg lost handling
      printf("MSG lost\n\r");
    }
  }

  return;
}
