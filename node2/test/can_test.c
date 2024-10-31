#include "can_test.h"

void CANTEST_RecieveSend(void){
  uart_init(F_CPU, 9600);

  can_init((CanInit){.brp = 41, .smp = 0, .phase1 = 6, .phase2 = 5, .sjw = 0, .propag = 1}, 0);
  CanMsg msg;
  uint8_t status = 0;
  printf("Initialize testing --><--\r\n");
  while (1)
  {
    status = can_rx(&msg);
    if (status != 0)
    {
      printf("Received message:\n\r");
      can_printmsg(msg);
      can_tx(msg);
    }
  }
}
