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


  
  return 0;
}
