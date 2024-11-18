#include "main.h"
#include "drivers/adc.h"
#include "drivers/can.h"
#include "drivers/oled.h"

struct can_message msg_rec;

#define BUFFER_SIZE 10

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

  // Define buffer for computing the moving average of joystick.xRaw
  uint8_t buffer[BUFFER_SIZE] = {0};
  uint8_t buffer_index = 0;
  uint16_t sum = 0;

  // OLED commands
  struct OLEDPosition position = {0, 0};
  OLED_Init(&position);
  OLED_Home(&position, &game_state);

  while(1)
  {
    switch (game_state)
    {
      case PLAY:
        direction = ADC_GetJoystickDirection(&joystick); 
        joystick_percent = ADC_GetJoystickPercent();
        ADC_ReadSlider(&slider);

        // Comute moving average
        sum -= buffer[buffer_index];
        buffer[buffer_index] = joystick.xRaw;
        sum += buffer[buffer_index];
        buffer_index = (buffer_index + 1) % BUFFER_SIZE;

        msg.data[0] = direction; 
        msg.data[1] = sum / BUFFER_SIZE;
        msg.data[2] = joystick.yRaw;
        printf("x; %u\n\r", joystick.xRaw);

        CAN_Send(&msg, 0, TXB0);
        _delay_ms(20);

        uint8_t status = CAN_Recieve(&msg_rec);
        if (status != 0)
        {
          game_state = MENU; 
          break;
        }
        break;

      case MENU:
        if (msg_rec.data[0] == 0x01)
        {
          OLED_LostScreen(&position, &game_state);
        }
        break;
    }
  }

  return 0;
}
