#include <../headers/uart.h>

void USART_Init(unsigned int ubrr)
{
  // Set baud rate
  UBBRH = (unsigned char) (ubrr>>8);
  UBRRL = (unsigned char) ubrr;

  // Enable transmitter and receiver
  UCSRB = (1 << RXEN) | (1 << TXEN);

 /* Set frame format: 8data, 2stop bit */
  UCSRC = (1 << URSEL) | (1 << USBS) | (3 << UCSZ0);

  return;
}

void USART_Transmit(unsigned char data )
{
  //Wait for empty transmit buffer( UDRE0 flag is set when ready )
  while( !( UCSRA & (1<<UDRE)) );

  //Put the data in the buffer, sends data
  UDR0 = data;
}

void USART_Receive( void )
{
  //Wait for data to be received 
  while( !(UCSRA & RXC) );

  return UDR
}
