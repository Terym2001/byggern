#ifndef _BIT_MACROS_H
#define _BIT_MACROS_H

#define SET_BIT(reg, bit)     (reg |= (1 << bit))
#define CLEAR_BIT(reg, bit)   (reg &= ~(1 << bit))
#define TOGGLE_BIT(reg, bit)  (reg ^= (1 << bit))

#endif
