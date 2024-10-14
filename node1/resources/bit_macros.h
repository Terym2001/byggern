#ifndef _BIT_MACROS_H_
#define _BIT_MACROS_H_

#define SET_BIT(reg, bit)       (reg |= (1 << bit)) 
#define CLEAR_BIT(reg, bit)     (reg &= ~(1 << bit)) 

#define BIT_IS_SET(reg, bit)    (reg & (1 << bit))
#define BIT_IS_CLEAR(reg, bit)  (!(reg & (1 << bit)))

#endif
