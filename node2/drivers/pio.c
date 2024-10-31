#include "pio.h"

void PIO_InitPin(Pio *reg, uint32_t pin)
{
  if (reg != PIOB && reg != PIOA)
  {
    // ERROR:
    printf("Invalid port\n");
    exit(-1);
  }

  PMC->PMC_PCER0 |= (1 << pin);  // Enable the clock for the peripheral
  reg->PIO_ABSR |= (1 << pin);   // Peripheral AB select
  reg->PIO_OER |= (1 << pin);    // Enable output on the pin
  reg->PIO_CODR |= (1 << pin);   // Set the output to low
  reg->PIO_PER |= (1 << pin);    // Enable the pin
  reg->PIO_MDDR |= (1 << pin);   // Disable the multi-driver
  reg->PIO_PUDR |= (1 << pin);   // Disable pull-up

  return ;
}

void PIO_SetPin(Pio *reg, uint32_t pin)
{
  reg->PIO_SODR |= (1 << pin);
  return;
}

void PIO_ClearPin(Pio *reg, uint32_t pin)
{
  reg->PIO_CODR |= (1 << pin);
  return;
}
