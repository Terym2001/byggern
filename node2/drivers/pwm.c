#include "pwm.h"

void pwm_init(void)
{
  PMC->PMC_PCER1 = (PMC_PCER1_PID36);
  PMC->PMC_PCER0 |= (1 << 12);

  // Initialize peripheral clock
  PIOB->PIO_ABSR |= (1 << 13);
  PIOB->PIO_PDR |= (1 << 13);    // Enable the pin
  PIOB->PIO_MDDR |= (1 << 13);   // Disable the multi-driver

  // Unlock user interface (value equals "PWM" in ASCII)
  PWM->PWM_WPCR = (0x50574D << 8) | (0b11111 << 2);
  PWM->PWM_WPCR &= ~((1 << 0) | (1 << 1));

  // Set prescaler for PWM register b clock to 128 and div to 1
  //PWM->PWM_CLK |= (0b0111 << 24) | (1 << 16);

  // Select clock B for channel 1
  PWM->PWM_CH_NUM[1].PWM_CMR |= (0b0111) | (1 << 9);
  //PWM->PWM_CH_NUM[1].PWM_CMR |= (1 << 3) | (1 << 2);
  //PWM->PWM_CH_NUM[1].PWM_CMR &= ~(0b11 << 0);
  
  // Configuration of the period
  PWM->PWM_CH_NUM[1].PWM_CPRD = CALCULATED_CPRD;

  // Configuration of the duty-cycle
  PWM->PWM_CH_NUM[1].PWM_CDTY = (75 * CALCULATED_CPRD) / 1000;

  // Configuration of the waveform alignment
  //PWM->PWM_CH_NUM[1].PWM_CMR &= ~(1 << 8);

  // Configuration of the output waveform polarity 
  //PWM->PWM_CH_NUM[1].PWM_CMR |= (1 << 9);

  // Selection of the counter event selection
  PWM->PWM_CH_NUM[1].PWM_CMR &= ~(1 << 10);


  // Enable of the PWM channels
  PWM->PWM_ENA |= (1 << 1);

  PWM->PWM_WPCR |= (1 << 0) | (1 << 1);
  return;
}

void pwm_set_duty_cycle(uint16_t duty_cycle)
{
  if (duty_cycle < DUTY_CYCLE_LOWER_BOUND)
  {
    duty_cycle = DUTY_CYCLE_LOWER_BOUND;
  }
  else if (duty_cycle < DUTY_CYCLE_UPPER_BOUND)
  {
    duty_cycle = DUTY_CYCLE_UPPER_BOUND;
  }

  PWM->PWM_CH_NUM[1].PWM_CDTY = (duty_cycle * CALCULATED_CPRD) / 1000;
  return;
}
