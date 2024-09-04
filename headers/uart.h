#ifndef _UART_H_
#define _UART_H_

#include <arv/io.h>
#include <utils/delay.h>

#define FOSC 4915200 // Clock speed
#define BAUD 250000    // Baud rate
#define MYUBBR FOSC/(16*BAUD) - 1

void uart_init(unsigned int ubrr);

// void uart_send();
// char* uart_recive(void);

#endif
