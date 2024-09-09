#ifndef _USART_H_
#define _USART_H_

#define F_CPU 4915200UL
#define BAUD 9600UL    // Baud rate
#define MYUBBR (F_CPU/(16UL*BAUD) - 1UL)

#include <avr/io.h>
#include <stdio.h>

void USART_Init(unsigned int ubrr);

int USART_Transmit(char data);

int USART_Receive();

#endif
