#include "pwm.h"

void pwm_init(void)
{
  PMC->PMC_WPMR &= ~(2 << 0);
  PMC->PMC_PCER0 = (PMC_PCER0_PID27);
  PMC->PMC_PCER1 = (PMC_PCER1_PID36);
  PMC->PMC_WPMR |= ~(2 << 0);

  // Unlock user interface (value equals "PWM" in ASCII)
  PWM->PWM_WPCR = 0x50574D;

  // TODO: Double check
  // Initialize peripheral clock
  PMC->PMC_PCER0 |= (1 << 13);
  PIOB->PIO_ABSR |= (1 << 13);
  PIOB->PIO_OER |= (1 << 13);    // Enable output on the pin
  PIOB->PIO_PDR |= (1 << 13);    // Enable the pin
  PIOB->PIO_MDDR |= (1 << 13);   // Disable the multi-driver

  // Set prescaler for PWM register b clock to 128 and div to 1
  //PWM->PWM_CLK |= (0b0111 << 24) | (1 << 16);

  // Select clock B for channel 1
  PWM->PWM_CH_NUM[1].PWM_CMR |= (0b0111);
  //PWM->PWM_CH_NUM[1].PWM_CMR |= (1 << 3) | (1 << 2);
  //PWM->PWM_CH_NUM[1].PWM_CMR &= ~(0b11 << 0);

  // Configuration of the waveform alignment
  PWM->PWM_CH_NUM[1].PWM_CMR &= ~(1 << 8);

  // Configuration of the output waveform polarity 
  PWM->PWM_CH_NUM[1].PWM_CMR |= (1 << 9);

  // Selection of the counter event selection
  PWM->PWM_CH_NUM[1].PWM_CMR &= ~(1 << 10);

  // Configuration of the period
  PWM->PWM_CH_NUM[1].PWM_CPRD = CALCULATED_CPRD;

  // Configuration of the duty-cycle
  PWM->PWM_CH_NUM[1].PWM_CDTY = (float) 0.0015;

  // TODO: find out what it does
  // Configuration of the dead-time generator

  // Selection of the synchronous channels
  // PWM->PWM_SCM &= ~(1 << 1);

  // TODO: Interrupt???
  // Selection of the moment when the WRDY flag and the corresponding PDC transfer request are set
  
  // Configuration of the update mode
  // PWM->PWM_SCM &= ~(0 << 16);
  // PWM->PWM_SCM &= ~(0 << 17);

  // TODO: Dont think we need as its not sync
  // Configuration of the update period

  // TODO: Might not need
  // Configuration of the comparisons PC
  
  // TODO: Might need Configuration of the fault inputs polarity 

  // TODO: Configuration of the fault protection 
  
  // TODO: Enable of the Interrupts?!--><--

  // Enable of the PWM channels
  PWM->PWM_ENA |= (1 << 1);
  return;
}
