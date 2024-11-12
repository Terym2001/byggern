#include "timer_counter.h"

void (*tc_ptr)(void);

void tc_init(unsigned long period)
{
  // Enable timer counter clock for TC0
  PMC->PMC_PCER0 |= PMC_PCER0_PID27;

  PIOB->PIO_PDR |= (1 << 25);
  PIOB->PIO_ABSR |= (1 << 25);

  // Set waform mode
  TC0->TC_CHANNEL[0].TC_CMR |= (1 << 15);

  // Set WAVESEL to UP_RC
  TC0->TC_CHANNEL[0].TC_CMR |= (2 << 13);
  
  // Prescale clock by 32
  TC0->TC_CHANNEL[0].TC_CMR |= (2 << 0);

  // RA set on TIOA
  TC0->TC_CHANNEL[0].TC_CMR |= (1 << 16);

  // RC clear in TIOA
  TC0->TC_CHANNEL[0].TC_CMR |= (2 << 18);

  TC0->TC_CHANNEL[0].TC_RA = (period * 32) / 2;
  TC0->TC_CHANNEL[0].TC_RC = (period * 32);

  TC0->TC_CHANNEL[0].TC_CCR |= (1 << 0) | (1 << 2);

  REG_TC0_IER0 |= TC_IER_CPCS;
  NVIC_EnableIRQ(TC0_IRQn);

  return;
}

void tc_set_custom(void (*ptr)(void))
{
  tc_ptr = ptr;
  return;
}

void TC0_Handler(void)
{
  // Handle motor controll
  //tc_ptr();

  printf("encoder: %i\n\r", encoder_read());

  uint32_t status = REG_TC0_SR0;
  NVIC_ClearPendingIRQ(TC0_IRQn);
  return;
}




