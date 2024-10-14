#include "can.h"
#include "stdio.h"
#include "mcp2515.h"

// TODO: take mask and data as arguments
void CAN_Init(void) 
{
  // Initialize the MCP2515
  MCP2515_Init();
  
  uint8_t mask = (1 << REQOP2) | (1 << REQOP1) | (1 << REQOP0);
  uint8_t data = (1 << REQOP2);

  // set can controller to loopback mode
  MCP2515_BitModify(MCP_CANCTRL, mask, data);

  // Initialize receiver options
  MCP2515_Write(RXB0CTRL, (1 << RXM1) | (1 << RXM0));
  // TODO: might remove
  MCP2515_Write(RXB1CTRL, (1 << RXM1) | (1 << RXM0));
}

struct can_message CAN_Recieve() 
{
  struct can_message msg;
  // TODO: Implement this function
   
  //while (!(MCP2515_Read(MCP_CANINTF) & (1 << RX0IF))) {}

  uint8_t data = MCP2515_Read(RXB0D0); 
  uint8_t data2 = MCP2515_Read(RXB1D0);
  msg.data[0] = data;
  msg.data[1] = data2;

  return msg;
}

void CAN_Send(struct can_message* msg, uint8_t msg_priority, uint8_t txBuffer) 
{
  // Map txBuffer to TXBnCTRL register
  uint8_t txbnctrl = 0;
  uint8_t txbnsidh = 0;
  uint8_t txbnsidl = 0;
  uint8_t txbndlc = 0;
  switch (txBuffer)
  {
    case TXB0:
      txbnctrl = TXB0CTRL;
      txbnsidh = TXB0SIDH;
      txbnsidl = TXB0SIDL;
      txbndlc  = TXB0DLC;
      break;
    case TXB1:
      txbnctrl = TXB1CTRL;
      txbnsidh = TXB1SIDH;
      txbnsidl = TXB1SIDL;
      txbndlc  = TXB1DLC;
      break;
    case TXB2:
      txbnctrl = TXB2CTRL;
      txbnsidh = TXB2SIDH;
      txbnsidl = TXB2SIDL;
      txbndlc  =  TXB2DLC;
      break;
    default:
      printf("Invalid txBuffer\n\r");
      return;
  }


  // Set message priority
  uint8_t mask = (1 << TXP1) | (1 << TXP0);
  MCP2515_BitModify(txbnctrl, mask, msg_priority);

  // load SIDH and SIDL register
  // load SIDH
  MCP2515_Write(txbnsidh, (msg->id >> 3));

  // load SIDL
  MCP2515_Write(txbnsidl, (msg->id << 5)); 

  // load DLC
  MCP2515_Write(txbndlc, MSG_MAX_LENGTH);

  // load data
  MCP2515_Write(TXB0D0, msg->data[0]);

  // Set TXBnCTRL.TXREQ by sending RTS command
  MCP2515_RequestToSend(txBuffer);

  // Check for errors
  uint8_t reg = MCP2515_Read(txbnctrl);
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
