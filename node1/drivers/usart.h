#ifndef _USART_H_
#define _USART_H_

#define FOSC 4915200UL
#define BAUD 9600UL    // Baud rate
#define MYUBRR (FOSC/(16UL*BAUD) - 1UL)

#include <avr/io.h>
#include <stdio.h>
#include <stdint.h>

void USART_Init(unsigned long ubrr);

// Might need to change to char instead of unsigned char
void USART_Transmit(uint8_t data);

uint8_t USART_Receive();

#endif
