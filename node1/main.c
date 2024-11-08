#include "main.h"
#include "drivers/can.h"


int main(void) {
  // Initialize uart with baud rate and frameformat
  USART_Init(MYUBRR);

  CAN_Init();

  XMEM_Init();
  ADC_Init();
  struct Joystick joystick = ADC_InitJoystick();

  enum JoystickDirection direction = NEUTRAL;

  struct can_message msg;
  msg.id = 0x0F;
  msg.length = 0x08;

  while(1)
  {
    direction = ADC_GetJoystickDirection(&joystick); 

    // char* direction_str = "HMM";
    // switch (direction)
    // {
    //   case LEFT:
    //     direction_str = "LEFT";
    //     break;
    //   case RIGHT:
    //     direction_str = "RIGHT";
    //     break;
    //   case UP:
    //     direction_str = "UP";
    //     break;
    //   case DOWN:
    //     direction_str = "DOWN";
    //     break;
    //   case PRESSED:
    //     direction_str = "PRESSED";
    //     break;
    //   case NEUTRAL:
    //     direction_str = "NEUTRAL";
    //     break;
    // }
    // printf("State: %s\n\r", direction_str);
    msg.data[0] = direction; 

    // TODO: NEEED WAIT IN CAN_SEND
    CAN_Send(&msg, 0, TXB0);
    _delay_ms(20);
  }

  return 0;
}
