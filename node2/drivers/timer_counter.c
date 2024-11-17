#include "timer_counter.h"
#include "motor_controller.h"

void tc_init(uint32_t channel, unsigned long period)
{
  // Enable timer counter clock for TC0
  switch (channel)
  {
    case 0:
      PMC->PMC_PCER0 |= PMC_PCER0_PID27;
      PIOB->PIO_PDR |= (1 << 25);
      PIOB->PIO_ABSR |= (1 << 25);
      break;
    case 1:
      PMC->PMC_PCER0 |= PMC_PCER0_PID28;
      PIOA->PIO_PDR |= (1 << 2);
      PIOA->PIO_ABSR |= (1 << 2);
      break;
    case 2:
      PMC->PMC_PCER0 |= PMC_PCER0_PID29;
      PIOA->PIO_PDR |= (1 << 5);
      PIOA->PIO_ABSR |= (1 << 5);
      break;
    default:
      printf("TIMER_COUNTER ERROR: invalid channel\n\r");
      break;
  }

  // Set waform mode
  TC0->TC_CHANNEL[channel].TC_CMR |= (1 << 15);

  // Set WAVESEL to UP_RC
  TC0->TC_CHANNEL[channel].TC_CMR |= (2 << 13);
  
  // Prescale clock by 32
  TC0->TC_CHANNEL[channel].TC_CMR |= (2 << 0);

  // RA set on TIOA
  TC0->TC_CHANNEL[channel].TC_CMR |= (1 << 16);

  // RC clear in TIOA
  TC0->TC_CHANNEL[channel].TC_CMR |= (2 << 18);

  TC0->TC_CHANNEL[channel].TC_RA = (period * 32) / 2;
  TC0->TC_CHANNEL[channel].TC_RC = (period * 32);

  TC0->TC_CHANNEL[channel].TC_CCR |= (1 << 0) | (1 << 2);

  TC0->TC_CHANNEL[channel].TC_IER |= TC_IER_CPCS;
  
  switch (channel)
  {
    case 0:
      NVIC_EnableIRQ(TC0_IRQn);
      break;
    case 1:
      NVIC_EnableIRQ(TC1_IRQn);
      break;
    case 2:
      NVIC_EnableIRQ(TC2_IRQn);
      break;
    default:
      break;
  }
  return;
}

void TC0_Handler(void)
{
  mc_motor_step();

  uint32_t status = REG_TC0_SR0;
  NVIC_ClearPendingIRQ(TC0_IRQn);
  return;
}

void TC1_Handler(void)
{
  score += 1;

  uint32_t status = REG_TC0_SR1;
  NVIC_ClearPendingIRQ(TC1_IRQn);
  return;
}




