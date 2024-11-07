#include "pio.h"

void pio_init_pin_for_peripheral(Pio *reg, uint32_t pin, uint32_t peripheral)
{
  // Check that correct peripheral is choosen 
  if (reg == PIOA) {
      PMC->PMC_PCER0 |= PMC_PCER0_PID11;
  } else if (reg == PIOB) {
      PMC->PMC_PCER0 |= PMC_PCER0_PID12;
  } else {
    printf("Invalid port\n\r");
    return;
  }

  // Check that either peripheral A or B is choosen 
  if (peripheral != 0 && peripheral != 1) {
    printf("Invalid peripheral\n\r");
    return;
  }

  reg->PIO_ABSR |= (1 << pin);   // Peripheral AB select
  reg->PIO_PDR |= (1 << pin);             // Enable the pin
  reg->PIO_MDDR |= (1 << pin);            // Disable the multi-driver
  return ;
}

void pio_init_pin_as_output(Pio* reg, uint32_t pin)
{
  if (reg == PIOA) {
      PMC->PMC_PCER0 |= PMC_PCER0_PID11;
  } else if (reg == PIOB) {
      PMC->PMC_PCER0 |= PMC_PCER0_PID12;
  } else if (reg == PIOC) {
      PMC->PMC_PCER0 |= PMC_PCER0_PID13;
  } else if (reg == PIOD) {
      PMC->PMC_PCER0 |= PMC_PCER0_PID14;
  } else {
    printf("Invalid port\n\r");
    return;
  }

  reg->PIO_PER  |= (1 << pin);
  reg->PIO_OER  |= (1 << pin);
  reg->PIO_MDDR |= (1 << pin);
  return;
}

void pio_set_pin(Pio *reg, uint32_t pin)
{
  reg->PIO_SODR |= (1 << pin);
  return;
}

void pio_clear_pin(Pio *reg, uint32_t pin)
{
  reg->PIO_CODR |= (1 << pin);
  return;
}
