#ifndef _BIT_MACROS_H
#define _BIT_MACROS_H

#define SET_BIT(reg, bit)            (reg |= (1 << bit))
#define CLEAR_BIT(reg, bit)          (reg &= ~(1 << bit))
#define TOGGLE_BIT(reg, bit)         (reg ^= (1 << bit))

// Implement this aswell??
// #define LOOP_TIL_BIT_CLEAR(reg, bit) (while( reg & ~(1 << bit)))
// #define LOOP_TIL_BIT_SET(reg, bit)   (while( reg & ~(1 << bit)))

#endif
