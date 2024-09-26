#include "main.h"
#include "drivers/oled.h"
#include "drivers/usart.h"
#include "drivers/xmem.h"

int main(void) {
  // Initialize uart with baud rate and frameformat
  USART_Init(MYUBRR);

  // Initialize external memory
  XMEM_Init();

  // Initialize OLED 
  OLED_Init();

  uint8_t alpha[8] = {0b00111110,0b01111111,0b01000001,0b01011101,0b01011101,0b00011111,0b00011110,0b00000000};

  for (int i = 0; i < 8; i++)
  {
    OLED_WriteData(alpha[i]);
  }

  return 0;
}
