#include "main.h"
#include "drivers/adc.h"
#include "drivers/can.h"
#include "drivers/oled.h"


int main(void) {
  // Initialize uart with baud rate and frameformat
  USART_Init(MYUBRR);

  CAN_Init();

  enum GameSate game_state = MENU;

  XMEM_Init();
  ADC_Init();
  struct Joystick joystick = ADC_InitJoystick();
  struct JoystickPositionPercent joystick_percent;
  enum JoystickDirection direction = NEUTRAL;

  struct Slider slider;

  struct can_message msg;
  msg.id = 0x0F;
  msg.length = 0x08;

  struct can_message msg_rec;

  // OLED commands
  struct OLEDPosition position = {0, 0};
  OLED_Init(&position);
  OLED_ClearScreen(&position);
  OLED_Home(&position, &game_state);

  while(1)
  {
    switch (game_state)
    {
      case PLAY:
        direction = ADC_GetJoystickDirection(&joystick); 
        joystick_percent = ADC_GetJoystickPercent();
        ADC_ReadSlider(&slider);

        msg.data[0] = direction; 
        msg.data[1] = joystick.xRaw;
        msg.data[2] = joystick.yRaw;
        printf("x; %u\n\r", joystick.xRaw);

        CAN_Send(&msg, 0, TXB0);
        _delay_ms(20);

        //uint8_t status = CAN_Recieve(&msg_rec);
        //if (status != 0)
        //{
        //  printf("Haha got message?\n\r");
        //  break;
        //}

        // Get points
        break;

      case MENU:

        break;
    }
  }

  return 0;
}
