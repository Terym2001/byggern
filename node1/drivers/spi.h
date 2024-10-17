#ifndef _SPI_H_
#define _SPI_H_

#include <avr/io.h>
#include <stdint.h>

#define SS PB4
#define MOSI PB5
#define MISO PB6
#define SCK PB7

#define SPI_setSS   PORTB |= (1 << SS)
#define SPI_clearSS PORTB &= ~(1 << SS)

void SPI_MasterInit(void);

void SPI_MasterTransmit(uint8_t data);

uint8_t SPI_MasterReceive(void);

#endif
