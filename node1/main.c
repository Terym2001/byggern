#define F_CPU 4915200UL

#include <avr/io.h>
#include <util/delay.h>
#include "drivers/usart.h"
#include "drivers/xmem.h"
#include "test/sram_test.h"

int main(void)
{
  // Initialize uart with baud rate and frameformat
  USART_Init(MYUBRR);

  // Initialize external memory
  XMEM_Init();

  //while (1)
  //{  
  uint16_t seed = rand();

    //SRAM_test();
  srand(seed);
  for (int i = 0; i < 800; i++)
  {
    uint8_t some_value = rand();
    XMEM_Write(some_value, (uint16_t) i);
    uint8_t value = XMEM_Read((uint16_t) i);

    if (some_value != value)
    {
      printf("WRITE ERROR: ext_mem[%u] = 0x%X (should be: 0x%X)\n\r", i, value, some_value);
    }
  }
  printf("Done with writing!!\n\r");

  srand(seed);
  for (int i = 0; i < 800; i++)
  {
    uint8_t some_value = rand();
    uint8_t value = XMEM_Read((uint16_t) i);

    if (some_value != value)
    {
      printf("READ_ERROR: ext_mem[%u] = 0x%X (should be: 0x%X)\n\r", i, value, some_value);
    }
  }
  printf("Done with reading!!\n\r");
//}

  return 0;
}
