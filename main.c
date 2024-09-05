#include <avr/io.h>
#include <util/delay.h>

#define FCPU 4915200
/*
int main(void)
{
  DDRA |= (1 << PD0); 

  while(1)
  {
    PORTA |= (1 << PD0);
    _delay_ms(2000);
    PORTA &= ~(1 << PD0);
    _delay_ms(2000);
  }
  return 0;
}
*/
int main(void)
{
  USART_Init();
 char greetings[] = "Hello World!";
  USART_Transmit(greetings);

  while (1)
  {
    char ReceivedSignal = USART_Receive();
    printf(ReceivedSignal);
  }
  
}
