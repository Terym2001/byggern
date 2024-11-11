#include "encoder.h"

void encoder_init(void)
{
  // Enable timer counter clock
  // maybe wird, maybe not
  PMC->PMC_PCER1 |= PMC_PCER1_PID33; // TC6
  
  TC2->TC_WPMR |= (0x54494D << RTC_WPMR_WPKEY_Pos);
  TC2->TC_WPMR &= ~RTC_WPMR_WPEN;

  // Disable pin
  PIOC->PIO_PDR |= (1 << 25);
  PIOC->PIO_PDR |= (1 << 26);

  // Select peripheral B
  PIOC->PIO_ABSR |= (1 << 25);
  PIOC->PIO_ABSR |= (1 << 26);

  TC2->TC_CHANNEL[0].TC_CMR &= ~TC_CMR_WAVE;
  TC2->TC_CHANNEL[0].TC_CMR |= TC_CMR_ETRGEDG_RISING | TC_CMR_ABETRG | TC_CMR_TCCLKS_XC0;

  TC2->TC_BMR |= TC_BMR_QDEN | TC_BMR_POSEN | TC_BMR_EDGPHA;

  // TODO: maybe need some filtering
  //TC2->TC_BMR |= TC_BMR_MAXFILT(0x3);

  TC2->TC_CHANNEL[0].TC_CCR |= TC_CCR_CLKEN;
  TC2->TC_CHANNEL[0].TC_CCR |= TC_CCR_SWTRG;

  TC2->TC_BCR |= TC_BCR_SYNC;
  
  return;
}

int16_t encoder_read(void)
{
  //return TC2->TC_CHANNEL[0].TC_CV;
  return REG_TC2_CV0;
}

