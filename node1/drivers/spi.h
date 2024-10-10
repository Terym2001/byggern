#ifndef _SPI_H_
#define _SPI_H_

#include <avr/io.h>

#define SS PB4
#define MOSI PB5
#define MISO PB6
#define SCK PB7

void SPI_MasterInit(void);

unsigned char SPI_MasterTransmit(char data);

#endif
