#include <../headers/uart.h>

void uart_init(unsigned int ubrr)
{
  // Set baud rate
  UBBRH = (unsigned char) (ubrr>>8);
  UBRRL = (unsigned char) ubrr;

  // Enable transmitter and receiver
  UCSRB = (1<<RXEN) | (1<<TXEN);

  // Set frame format


  return;
}
