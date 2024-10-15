#ifndef _BIT_MACROS_H_
#define _BIT_MACROS_H_

#define set_bit(reg, bit)                 (reg |= (1 << bit)) 
#define set_bit_value(reg, bit, value)    (reg |= (value << bit))
#define clear_bit(reg, bit)               (reg &= ~(1 << bit)) 
#define clear_bit_value(reg, bit, value)  (reg &= ~(value << bit))

#define bit_is_set(reg, bit)    (reg & (1 << bit))
#define bit_is_clear(reg, bit)  (!(reg & (1 << bit)))

#endif
