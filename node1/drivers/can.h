#ifndef _CAN_H_
#define _CAN_H_

#include <avr/io.h>
#include "mcp2515.h"

struct can_message {
  uint16_t id;
  uint8_t length;
  uint8_t data[8];
};

void CAN_Init(void);

uint8_t CAN_Recieve(struct can_message* msg);

void CAN_Send(struct can_message* msg, uint8_t msg_priority, uint8_t txBuffer);

#endif
