#define F_CPU 4915200UL

#include <avr/io.h>
#include <util/delay.h>
#include <usart.h>

int main(void)
{
  USART_Init(MYUBBR);
  unsigned char greetings[] = "Hello World!\n";

  while (1)
  {
    USART_Transmit('b');
    //for (unsigned char *i = &greetings[0]; *i != '\0'; i++ )
    //{
    //  USART_Transmit(*i);
    //}

    //unsigned char c = USART_Receive();
    //if ( c == 'b' )
    //{
    //  DDRA |= (1 << PD0);
    //} else if (c == 'l')
    //{
    //  DDRA &= ~(1 << PD0);
    //}
    
    //_delay_ms(500);
  }

  return 0;
}
