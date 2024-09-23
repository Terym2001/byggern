#define F_CPU 4915200UL

#include <avr/io.h>
#include <util/delay.h>
#include "drivers/usart.h"
#include "drivers/sram.h"
#include "drivers/adc.h"

int main(void)
{
  // Initialize uart with baud rate and frameformat
  USART_Init(MYUBRR);

  // Initialize external memory
  XMEM_Init();

  ADC_Init();

  uint8_t data[4] = {0};
  while (1)
  {
    ADC_Read(&data[0]);
    printf("ADC Value: {%u,%u,%u,%u}                                      \r", data[0], data[1], data[2], data[3]);
  }

  return 0;
}
