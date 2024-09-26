#ifndef _OLED_H_
#define _OLED_H_

#include "../main.h"
//#include "../resources/fonts.h"

#define OLED_COMMAND_BASE_ADDRESS 0x1000
#define OLED_DATA_BASE_ADDRESS 0x1200

#define OLED_MAX_ADDRESS 0x01FF 

// Command definitions
#define S_MEM_ADDRESSING_MODE 0x20

struct OLED_position {
  uint8_t row;
  uint8_t coloumn;
};

void OLED_Init(void);

void OLED_Reset();

void OLED_Home();

void OLED_GotoPage(uint8_t page);

void OLED_ClearPage(uint8_t page);

void OLED_Position(struct OLED_position position);

void OLED_WriteCommand(volatile char command);

void OLED_WriteData(volatile char data);

void OLED_Print(char* string);

void OLED_SetBrightness(uint8_t brightness);

void OLED_ClearScreen();

#endif
