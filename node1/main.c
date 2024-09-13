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
  //XMEM_Init();

  DDRA |= (1 << PA0) | (1 << PA1) | (1 << PA2) | (1 << PA3);

  DDRE |= (1 << PE1);
  PORTE |= (1 << PE1);

  PORTA |= (1 << PA0) | (1 << PA1) | (1 << PA2) | (1 << PA3);

  _delay_ms(15000);

  PORTE &= ~(1 << PE1);

  PORTA &=  ~(1 << PA0) | ~(1 << PA1) | ~(1 << PA2) | ~(1 << PA3);

  while (1) {}


  //while (1)
  //{
  //  XMEM_Write(0xFF, 0xFFFF); 
  //}

  return 0;
}
