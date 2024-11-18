#ifndef _OLED_H_
#define _OLED_H_

#include <util/delay.h>
#include "../main.h"
#include "../resources/fonts.h"
#include "../drivers/adc.h"

#define OLED_COMMAND_BASE_ADDRESS 0x1000
#define OLED_DATA_BASE_ADDRESS 0x1200

#define OLED_MAX_ADDRESS 0x01FF 

// Command definitions
#define S_MEM_ADDRESSING_MODE 0x20

#define SEGMENT_START 0x00
#define SEGMENT_END 0x7F

#define FONT_OFFSET 32

extern struct can_message msg_rec;

struct OLEDPosition {
  uint8_t page;
  uint8_t segment;
};

enum GameSate { MENU, PLAY };

// struct OLEDUser {
//   struct OLEDPosition position;
//   struct ADCValues adc_values;
//   struct JoystickPositionPercent joystick_position;
//   enum JoystickDirection joystick_direction;
// };

void OLED_WriteCommand(volatile char command);

void OLED_WriteData(volatile char data);

void OLED_GotoPage(struct OLEDPosition *position, uint8_t page);

void OLED_ClearPage(struct OLEDPosition *position, uint8_t page);

void OLED_ClearScreen(struct OLEDPosition *position);

void OLED_Init(struct OLEDPosition *position);

void OLED_GotoSegment(struct OLEDPosition *position, uint8_t segment);

void OLED_PrintChar(struct OLEDPosition *position, char chr);

void OLED_PrintString(struct OLEDPosition *position, char* string);

void OLED_LostScreen(struct OLEDPosition *position, enum GameSate *game_state);

void OLED_Reset(struct OLEDPosition *position);

void OLED_HighlightPage(struct OLEDPosition *position, uint8_t page);

void OLED_Home(struct OLEDPosition *position, enum GameSate *game_state);

void OLED_SetBrightness(struct OLEDPosition *position, uint8_t brightness);

#endif
