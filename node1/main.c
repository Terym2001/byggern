#include "main.h"
#include "drivers/oled.h"
#include "drivers/usart.h"
#include "drivers/adc.h"
#include "drivers/xmem.h"

int main(void) {
  // Initialize uart with baud rate and frameformat
  USART_Init(MYUBRR);

  // Initialize external memory
  XMEM_Init();

  // Initialize ADC
  ADC_Init();

  // Initialize OLED 
  struct OLEDPosition oled_position = {.page = 0, .segment = 0};
  OLED_Init(&oled_position);

  OLED_Home(&oled_position);
  return 0;
}
