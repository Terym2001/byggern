/*
 * fonts.h
 *
 * Library of fonts
 * Large: 8x8, normal: 5x7 and small: 4x7
 */
#ifndef FONTS_H_
#define FONTS_H_

#include <avr/pgmspace.h>

extern const unsigned char font8[95][8] PROGMEM;
extern const unsigned char font5[95][5] PROGMEM;
extern const unsigned char font4[95][4] PROGMEM;

#endif /* FONTS_H_ */
