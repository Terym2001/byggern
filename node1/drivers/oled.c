#include "oled.h"

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

void OLED_Init(void)
{
  OLED_WriteCommand(0xAE); // Turn off Display (RESET)

  OLED_WriteCommand(0xA1); // Set Segment Re-map

  OLED_WriteCommand(0xDA); // Set Segment Re-map
  OLED_WriteCommand(0x12); // Set Segment Re-map
  OLED_WriteCommand(0xC8); // Set COM Output Scan Direction

  OLED_WriteCommand(0x20); // Set Memory Addressing Mode
  OLED_WriteCommand(0x02); // Page addressing mode 

  // Set start seg to 3
  OLED_WriteCommand(0x00); // Set Lower Column Start Address for Page Addressing Mode

  // Set start com to 16
  OLED_WriteCommand(0x10); // Set Higher Column Start Address for Page Addressing Mode

  // set start page to 0 
  OLED_WriteCommand(0xB0); // Set Page Start Address for Page Addressing Mode
  
  OLED_WriteData(0xA4); // Resume to RAM content display
  
  OLED_WriteCommand(0xAF); // Turn on Display

  OLED_ClearScreen();
  
  return;
}

void OLED_GotoPage(uint8_t page)
{
  OLED_WriteCommand(0xB0 + page);
  return;
}

void OLED_ClearPage(uint8_t page)
{
  OLED_GotoPage(page);
  for (int i = 0; i < 128; i++)
  {
    OLED_WriteData(0x00);
  }
  return;
}

void OLED_ClearScreen()
{
  for (int i = 0; i < 8; i++)
  {
    OLED_ClearPage(i);
  }
  OLED_GotoPage(0);
  return;
}
