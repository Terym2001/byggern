#define F_CPU 4915200UL

#include <avr/io.h>
#include <util/delay.h>
#include "drivers/usart.h"
#include "drivers/xmem.h"
#include "test/sram_test.h"

int main(void)
{
  // Initialize uart with baud rate and frameformat
  USART_Init(MYUBRR);

  // Initialize external memory
  XMEM_Init();

  while(1)
  {
    XMEM_Write(0xFF, 0xFFFF);
    _delay_ms(5000);

    XMEM_Write(0xFF, 0x12FF);
    _delay_ms(5000);

    XMEM_Write(0xFF, 0x14FF);
    _delay_ms(5000);

  }
  
  return 0;
}
