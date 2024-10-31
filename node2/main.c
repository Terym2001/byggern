#include <stdio.h>
#include <stdarg.h>
#include "sam.h"
#include "drivers/can.h"
#include "drivers/uart.h"
#include "drivers/time.h"
#include "drivers/pio.h"

#define F_CPU 84000000

/*
 * Remember to update the Makefile with the (relative) path to the uart.c file.
 * This starter code will not compile until the UART file has been included in the Makefile. 
 * If you get somewhat cryptic errors referencing functions such as _sbrk, 
 * _close_r, _write_r, _fstat etc, you have most likely not done that correctly.

 * If you get errors such as "arm-none-eabi-gcc: no such file", you may need to reinstall the arm gcc packages using
 * apt or your favorite package manager.
 */
//#include "../path_to/uart.h"

int main()
{
  SystemInit();

  WDT->WDT_MR = WDT_MR_WDDIS; //Disable Watchdog Timer

  adc_init();

  uart_init(F_CPU, 9600);

  can_init((CanInit){.brp = 41, .smp = 0, .phase1 = 6, .phase2 = 5, .sjw = 0, .propag = 1}, 0);
  CanMsg msg;
  uint8_t status = 0;
  printf("Initialize testing --><--\r\n");

  enum JoystickDirection direction = NEUTRAL;
  while (1)
  {
    status = can_rx(&msg);
    if (status != 0)
    {
      direction = (enum JoystickDirection) msg.byte[0];
      char* direction_str = "HMM";
      switch (direction)
      {
        case LEFT:
          direction_str = "LEFT";
          break;
        case RIGHT:
          direction_str = "RIGHT";
          break;
        case UP:
          direction_str = "UP";
          break;
        case DOWN:
          direction_str = "DOWN";
          break;
        case PRESSED:
          direction_str = "PRESSED";
          break;
        case NEUTRAL:
          direction_str = "NEUTRAL";
          break;
      }
      printf("State: %s\n\r", direction_str);
    }
  }
}
