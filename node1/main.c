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

  struct CalibrateADC calc;
  struct JoystickPosition position;
  ADC_Calibrator(&calc);
  uint8_t data[4] = {0};
  while (1)
  {
    ADC_Read(&data[0], &calc);
    printf("ADC Value: {%u,%u,%u,%u}                                      \r \n", data[0], data[1], data[2], data[3]);
    ADC_GetJoystickPosition(data[0],data[2],&position);
    printf("Joystick Position: X = %d%%, Y = %d%% \r \n", position.xPercent, position.yPercent);
    _delay_ms(200);
    enum JoystickDirection direction = ADC_GetJoystickDirection(data[0],data[2]);
    // Print direction
    switch (direction)
    {
        case LEFT:
            printf("Joystick Direction: LEFT \r \n");
            break;
        case RIGHT:
            printf("Joystick Direction: RIGHT\r \n");
            break;
        case UP:
            printf("Joystick Direction: UP\r \n");
            break;
        case DOWN:
            printf("Joystick Direction: DOWN \r \n");
            break;
        case NEUTRAL:
            printf("Joystick Direction: NEUTRAL \r \n");
            break;
    }
    _delay_ms(200);
  }

  return 0;
}
