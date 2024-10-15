#include "usart.h"

void USART_Init(unsigned long ubrr)
{
  // Set baud rate
  UBRR0H = (unsigned char) (ubrr>>8);
  UBRR0L = (unsigned char) (ubrr);

  // Enable transmitter and receiver
  set_bit(UCSR0B, RXEN0); 
  set_bit(UCSR0B, TXEN0); 

  /* Set frame format: 8data, 2stop bit */
  set_bit(UCSR0C, URSEL0);
  set_bit(UCSR0C, USBS0);
  set_bit(UCSR0C, UCSZ00);

  // Link USART to printf
  fdevopen(&USART_Transmit, &USART_Receive);

  return;
}

// Might need to change to char instead of unsigned char
void USART_Transmit(char data)
{
  //Wait for empty transmit buffer( UDRE0 flag is set when ready )
  while( bit_is_clear(UCSR0A, UDRE0) );

  //Put the data in the buffer, sends data
  UDR0 = data;
  return;
}

uint8_t USART_Receive()
{
  //Wait for data to be received 
  while( bit_is_clear(UCSR0A, RXC0) );

  return UDR0;
}
