#include "main.h"

int main(void) {
  // Initialize uart with baud rate and frameformat
  USART_Init(MYUBRR);

  CAN_Init();
  uint16_t cnt = 0;
  struct can_message msg = {.id = 0b10011111, .data = {0x0F, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07}};
  while (1)
  {
    CAN_Send(&msg, 0b11, TXB0);
    struct can_message msgr = CAN_Recieve();
    printf("Message: %u, %u, %u\n\r", msgr.data[0], msgr.data[1], cnt++);
    _delay_ms(100);
  }
  
  return 0;
}
