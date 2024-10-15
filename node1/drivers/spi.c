#include "spi.h"

void SPI_MasterInit(void)
{
  // Set MOSI and SCK output, all others input 
  DDRB |= (1 << MOSI) | (1 << SCK) | (1 << SS);
  DDRB &= ~(1 << MISO); 

  PORTB |= (1 << SS);

  //Enable SPI
  SPCR = (1 << SPE);

  // Set to master mode
  SPCR |= (1 << MSTR);

  // Set clock rate fck/16
  SPCR |= (1 << SPR0);

  return;
}

void SPI_MasterTransmit(uint8_t data)
{
  // Load data into the buffer
  SPDR = data;
  
  // Wait for transmission complete
  while(!(SPSR & (1 << SPIF)));

  return;
}

uint8_t SPI_MasterReceive(void)
{
  SPDR = 0xFF;

  // Wait for reception complete
  while(!(SPSR & (1 << SPIF)));

  // Return Data Register
  return SPDR;
}

