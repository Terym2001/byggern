#include "usart.h"

void USART_Init(unsigned int ubrr)
{
  // Set baud rate
  UBRR0H = (unsigned char) (ubrr>>8);
  UBRR0L = (unsigned char) ubrr;

  // Enable transmitter and receiver
  UCSR0B = (1 << RXEN0) | (1 << TXEN0);

  /* Set frame format: 8data, 2stop bit */
  UCSR0C = (1 << URSEL0) | (1 << USBS0) | (3 << UCSZ00);

  // Link USART to printf
  fdevopen(&USART_Transmit, &USART_Receive);

  return;
}

int USART_Transmit(unsigned char data)
{
  //Wait for empty transmit buffer( UDRE0 flag is set when ready )
  while( !( UCSR0A & (1<<UDRE0)) );

  //Put the data in the buffer, sends data
  UDR0 = data;
  return 0;
}

int USART_Receive(void)
{
  //Wait for data to be received 
  while( !(UCSR0A & RXC0) );

  return UDR0;
}
