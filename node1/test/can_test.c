#include "can_test.h"

void CANTEST_SendReceive()
{
  struct can_message msg;
  msg.id = 0x0F;
  msg.length = 0x08;
  for (int i = 0; i < msg.length; i++)
  {
    msg.data[i] = i+1;
  }

  while(1)
  {
    CAN_Send(&msg, 0, TXB0);
    struct can_message msg_receive = CAN_Recieve();
    printf("Received on Node 1: \n\r");
    printf("ID: %u \n\r", msg_receive.id);
    printf("Length: %u\n\r", msg_receive.length);
    for (uint8_t i = 0; i < msg_receive.length; i++)
    {
      printf("Data[%u]: %u\n\r", i, msg_receive.data[i]);
    }
    _delay_ms(5000);
  }
  return ;
}
