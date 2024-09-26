#define F_CPU 4915200UL

#include <avr/io.h>
#include <util/delay.h>

#include "drivers/adc.h"
#include "drivers/sram.h"
#include "drivers/usart.h"

int main(void) {
  // Initialize uart with baud rate and frameformat
  USART_Init(MYUBRR);

  // Initialize external memory
  XMEM_Init();

  ADC_Init();

  struct CalibrateADC calc;
  struct JoystickPositionPercent position;
  struct ADCValues data;

  ADC_Calibrator(&calc);
  // _delay_ms(5000);
  while (1) {
    ADC_Read(&data, &calc);
    printf("LS: %d, RS: %d            \r", data.leftSlider, data.rightSlider);
    // enum JoystickDirection direction = ADC_GetJoystickDirection(data.xRaw, data.yRaw);

    // // Print direction
    // switch (direction) {
    //   case LEFT:
    //     printf("Joystick Direction: LEFT      \r");
    //     break;
    //   case RIGHT:
    //     printf("Joystick Direction: RIGHT     \r");
    //     break;
    //   case UP:
    //     printf("Joystick Direction: UP        \r");
    //     break;
    //   case DOWN:
    //     printf("Joystick Direction: DOWN      \r");
    //     break;
    //   case NEUTRAL:
    //     printf("Joystick Direction: NEUTRAL   \r");
    //     break;
    // }
  }

  return 0;
}
