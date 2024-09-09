#define F_CPU 4915200UL

#include <avr/io.h>
#include <util/delay.h>
#include <usart.h>

int main(void)
{
  USART_Init(MYUBBR);
  DDRA |= (1 << PA0);

  while (1)
  {

	  unsigned char c = USART_Receive();
	  switch(c)
	  {
		  case 't':
			  printf("Setting PA0 to state %i\n\r", (PORTA & (1 << PA0)));
			  PORTA ^= (1 << PA0);
			  break;
		  case 'h':
			  printf("Turing PA0 to %i\n\r", 1);

			  PORTA |= (1 << PA0);
			  break;
		  case 'l':
			  printf("Setting PA0 to %i\n\r", 0);

			  PORTA &= ~(1 << PA0);
			  break;
		 default:
			  break;
	  }
  }

  return 0;
}
