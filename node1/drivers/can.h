#ifndef _CAN_H_
#define _CAN_H_

#include <avr/io.h>
#include "mcp2515.h"

#define MSG_MAX_LENGTH 0xFF

struct can_message {
  uint16_t id;
  uint8_t length;
  uint8_t data[8];
};

void CAN_Init(void);

struct can_message CAN_Recieve();//TODO: IMPLMENT THIS WITH IDS and stuff

void CAN_Send(struct can_message* msg, uint8_t msg_priority, uint8_t txBuffer);

#endif
