#define F_CPU 4915200UL

#include <avr/io.h>
#include <util/delay.h>
#include "drivers/usart.h"
#include "drivers/sram.h"
#include "test/sram_test.h"

int main(void)
{
  // Initialize uart with baud rate and frameformat
  USART_Init(MYUBRR);

  // Initialize external memory
  XMEM_Init();

  SRAM_test();
 
  // TODO fix SRAM header file
  // while (1)
  // {
  //   SRAM_Write(0xFF, 0x0500);
  //   printf("Value at 0x0500: %u\n\r", SRAM_Read(0x0500));

  //   _delay_ms(500);

  //   XMEM_Write(0xFF, 0x0500, 0x1800);
  //   printf("Value at 0x0500: %u\n\r", XMEM_Read(0x0500, 0x1800));

  //   _delay_ms(500);

  //   // SRAM_Write(0xFF, 0x0900);
  //   // printf("Value at 0x0900: %u\n\r", SRAM_Read(0x0900));

  //   // _delay_ms(500);

  // }

  return 0;
}
