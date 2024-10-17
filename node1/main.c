#include "main.h"

int main(void) {
  // Initialize uart with baud rate and frameformat
  USART_Init(MYUBRR);

  CAN_Init();

  struct can_message msg;
  msg.id = 0xFF;
  msg.length = 0x08;
  for (int i = 0; i < msg.length; i++)
  {
    msg.data[i] = i;
  }

  CAN_Send(&msg, 0, TXB0);

  struct can_message msg2 = CAN_Recieve();
  printf("------------------\n\r");
  printf("Received message\n\r");
  printf("ID: %x\n\r", msg2.id);
  printf("Length: %x\n\r", msg2.length);

  for (uint8_t i = 0; i < msg2.length; i++)
  {
    printf("Data[%d]: %x\n\r", i, msg2.data[i]);
  }

  return 0;
}
