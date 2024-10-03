#include "main.h"
#include "drivers/spi.h"

int main(void) {
  // Initialize uart with baud rate and frameformat
  USART_Init(MYUBRR);

  // Initialize external memory
  XMEM_Init();

  // Initialize ADC
  ADC_Init();

  SPI_MasterInit();

  while (1)
  {
    unsigned char read = SPI_MasterTransmit(0b10101010);
    _delay_ms(2);
  }

  return 0;
}
