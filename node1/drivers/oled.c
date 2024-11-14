#include "oled.h"
#include "adc.h"

void OLED_WriteCommand(volatile char command)
{
  volatile char *oled_command = (char *) OLED_COMMAND_BASE_ADDRESS;
  oled_command[0] = command;
  return;
}

void OLED_WriteData(volatile char data)
{
  volatile char *oled_data = (char *) OLED_DATA_BASE_ADDRESS;
  oled_data[0] = data;
  return;
}

void OLED_GotoPage(struct OLEDPosition *position, uint8_t page)
{
  position->page = page;
  OLED_WriteCommand(0xB0 + page);
  return;
}

void OLED_ClearPage(struct OLEDPosition *position, uint8_t page)
{
  OLED_GotoPage(position, page);
  OLED_GotoSegment(position, 0);
  for (int i = 0; i <= SEGMENT_END; i++)
  {
    OLED_WriteData(0x00);
  }
  position->segment = SEGMENT_START;
  return;
}

void OLED_ClearScreen(struct OLEDPosition *position)
{
  for (int i = 0; i < 8; i++)
  {
    OLED_ClearPage(position, i);
  }
  OLED_GotoPage(position, 0);
  return;
}

void OLED_Init(struct OLEDPosition *position)
{
  OLED_WriteCommand(0xAE); // Turn off Display (RESET)

  OLED_WriteCommand(0xA1); // Set Segment Re-map

  OLED_WriteCommand(0xDA); // Set Segment Re-map
  OLED_WriteCommand(0x12); // Set Segment Re-map
  OLED_WriteCommand(0xC8); // Set COM Output Scan Direction

  OLED_WriteCommand(0x20); // Set Memory Addressing Mode
  OLED_WriteCommand(0x02); // Page addressing mode 

  // Set start seg to 0
  OLED_WriteCommand(0x00 + (SEGMENT_START & 0x0F)); // Set Lower Column Start Address for Page Addressing Mode
  OLED_WriteCommand(0x10 + (SEGMENT_START >> 4)); // Set Higher Column Start Address for Page Addressing Mode

  // set start page to 0 
  OLED_WriteCommand(0xB0); // Set Page Start Address for Page Addressing Mode
  
  OLED_WriteData(0xA4); // Resume to RAM content display
  
  OLED_WriteCommand(0xAF); // Turn on Display

  OLED_ClearScreen(position);

  return;
}

void OLED_GotoSegment(struct OLEDPosition *position, uint8_t segment)
{
  position->segment = segment;
  OLED_WriteCommand(0x00 + (segment & 0x0F));
  OLED_WriteCommand(0x10 + (segment >> 4));
  return;
}

void OLED_PrintChar(struct OLEDPosition *position, char chr)
{
  for (uint8_t i = 0; i < 5; i++)
  {
    char byte = pgm_read_byte(&font5[chr - FONT_OFFSET][i]);
    OLED_WriteData(byte);
    position->segment++;
    position->segment = (position->segment > 127) ? 0 : position->segment;
  }
  return;
}

void OLED_PrintString(struct OLEDPosition *position, char *str)
{
  while (*str != '\0')
  {
    switch (*str)
    {
      case '\n':
        OLED_GotoPage(position, position->page + 1);
        OLED_GotoSegment(position, SEGMENT_START);
        break;
      default:
        OLED_PrintChar(position, *str);
        break;
    }
    str++;
    }
  return;
}

void OLED_HighlightPage(struct OLEDPosition *position, uint8_t page)
{
  // clear line
  OLED_GotoSegment(position, 0);
  for (int i = 0; i < 127; i++)
  {
    OLED_WriteData(0b00000000);
  }

  OLED_GotoSegment(position, 0);
  OLED_GotoPage(position, page);
  for (int i = 0; i < 127; i++)
  {
    OLED_WriteData(0b00000001);
  }

  return;
}
void OLED_SubScreen(struct OLEDPosition *position)
{
  OLED_ClearScreen(position);

  OLED_PrintString(position, "Some new string! \n\n");
  OLED_PrintString(position, "Some other new string! \n\n");
  OLED_PrintString(position, "Secret \n\n");

  OLED_GotoPage(position, 1);

  struct Joystick joststick = ADC_InitJoystick();
  enum JoystickDirection direction = NEUTRAL;

  //Function pointer to start new sub-menu
  void (*ChangeScreen)(struct OLEDPosition *position);
  ChangeScreen = NULL;
  while (1)
  {
    ADC_Read(&joststick);       
    direction = ADC_GetJoystickDirection(&joststick); //TODO: Change name of adc_values 
    switch(direction)
    {
      case UP:
        if (position->page > 1)
        {
          position->page -= 2; 
        }
        printf("UP\n\r");
        OLED_HighlightPage(position, position->page);
        break;
      case DOWN:
        if (position->page < 4)
        {
          position->page += 2;
        }
        printf("DOWN\n\r");
        OLED_HighlightPage(position, position->page);
        break;
      case PRESSED:
        ChangeScreen = OLED_Home;
        printf("Changing back to Home \n\r");
        _delay_ms(5000); //TODO: This can be removed when it checks btn
      default:
        break;
    }
      // Call the function if the function pointer has been set
    if (ChangeScreen != NULL)
    {
      ChangeScreen(position);  // Call OLED_SubScreen
      return;  // Exit the current loop after changing the screen
    }
    _delay_ms(500);
  }
}

void OLED_Home(struct OLEDPosition *position, enum GameSate *game_state)
{
  OLED_ClearScreen(position);

  OLED_PrintString(position, "Play Game!\n\n");
  OLED_PrintString(position, "Secret game!\n\n");
  OLED_PrintString(position, "Options\n\n");

  OLED_GotoPage(position, 1);

  struct Joystick joystick = ADC_InitJoystick(); //TODO: When I think about it this could cause problems with cal if joystick is not in ideal position
  enum JoystickDirection direction = NEUTRAL;

  //Function pointer to start new sub-menu
  void (*ChangeScreen)(struct OLEDPosition *position);
  ChangeScreen = NULL;
  while (1)
  {
    ADC_Read(&joystick);       
    direction = ADC_GetJoystickDirection(&joystick); //TODO: Change name of adc_values 
    switch(direction)
    {
      case UP:
        if (position->page > 1)
        {
          position->page -= 2; 
        }
        OLED_HighlightPage(position, position->page);
        break;
      case DOWN:
        if (position->page < 4)
        {
          position->page += 2;
        }
        OLED_HighlightPage(position, position->page);
        break;
      //TODO:Implement so that this only happens when we are at correct page
      case PRESSED:
        if (position->page == 1)
        {
          printf("Launching Game!! \n\r");//TODO: This can be removed when it checks btn
          *game_state = PLAY;
          return;
        }
      default:
        break;
    }
    // Call the function if the function pointer has been set
    //if (ChangeScreen != NULL)
    //{
    //  ChangeScreen(position);  // Call OLED_SubScreen
    //  return;  // Exit the current loop after changing the screen
    //}
    _delay_ms(500);
  }
  return;
}
