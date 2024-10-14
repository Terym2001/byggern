#include "spi.h"

void SPI_MasterInit(void)
{
  // Set MOSI and SCK output, all others input 
  DDRB |= (1 << MOSI) | (1 << SCK) | (1 << SS);

  PORTB |= (1 << SS);

  //Enable SPI
  SPCR = (1 << SPE);

  // Set to master mode
  SPCR |= (1 << MSTR);

  // Set clock rate fck/16
  SPCR |= (1 << SPR0);

  return;
}

unsigned char SPI_MasterTransmit(char data)
{
  PORTB &= ~(1 << SS);

  // Load data into the buffer
  SPDR = data;
  
  // Wait for transmission complete
  while(!(SPSR & (1 << SPIF)));

  unsigned char data_read = SPDR;

  PORTB |= (1 << SS);

  return data_read;
}