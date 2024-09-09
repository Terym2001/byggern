#define F_CPU 4915200UL

#include <avr/io.h>
#include <util/delay.h>
#include "drivers/usart.h"

int main(void)
{
  // Initialize uart with baud rate and frameformat
  USART_Init(MYUBBR);

  // Set led pin as output
  DDRA |= (1 << PA0);

  int quit = 0;

  while (1)
  {
    unsigned char ch = USART_Receive();
    switch(ch)
    {
      case 't':
        printf("Toggling value at PA0\n\r");
        PORTA ^= (1 << PA0);
        break;
      case 'h':
        printf("Writing %i to PA0.\n\r", 1);
        PORTA |= (1 << PA0);
        break;
      case 'l':
        printf("Writing %i to PA0.\n\r", 0);
        PORTA &= ~(1 << PA0);
        break;
      case 'Q':
        quit = 1;
        break;
      default:
        continue;
    }
    if (quit){break;}
  }

  return 0;
}
