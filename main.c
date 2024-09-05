#include <avr/io.h>
#include <util/delay.h>

#define FCPU 4915200

int main(void)
{
  DDRA |= (1 << PD0); 

  while(1)
  {
    PORTA |= (1 << PD0);
    _delay_ms(200);
    PORTA &= ~(1 << PD0);
    _delay_ms(200);
  }
  return 0;
}
