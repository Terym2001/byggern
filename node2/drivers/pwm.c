#include "pwm.h"
#include "pio.h"

void pwm_init(void)
{
  // Enable the peripheral PWM clock
  PMC->PMC_PCER1 = (PMC_PCER1_PID36);

  pio_init_pin_for_peripheral(PIOB, 12, PIO_PERIPH_B);
  pio_init_pin_for_peripheral(PIOB, 13, PIO_PERIPH_B);

  // Unlock user interface (value equals "PWM" in ASCII)
  PWM->PWM_WPCR = (0x50574D << 8) | (0b111111 << 2);

  // Disable the write protection
  PWM->PWM_WPCR &= ~((1 << 0) | (1 << 1));

  // Prescale MCK by 128 and select waveform polarity 
  PWM->PWM_CH_NUM[0].PWM_CMR |= (0b0111) | (1 << 9);
  PWM->PWM_CH_NUM[1].PWM_CMR |= (0b0111) | (1 << 9);
  
  // Selection of the counter event selection
  PWM->PWM_CH_NUM[0].PWM_CMR &= ~(1 << 10);
  PWM->PWM_CH_NUM[1].PWM_CMR &= ~(1 << 10);

  // Configuration of the period
  PWM->PWM_CH_NUM[0].PWM_CPRD = CALCULATED_CPRD; 
  PWM->PWM_CH_NUM[1].PWM_CPRD = CALCULATED_CPRD;

  // Configuration of the duty-cycle
  PWM->PWM_CH_NUM[0].PWM_CDTY = (0 * CALCULATED_CPRD) / 1000;
  PWM->PWM_CH_NUM[1].PWM_CDTY = (75 * CALCULATED_CPRD) / 1000;

  // Enable of the PWM channels
  PWM->PWM_ENA |= (1 << 1) | (1 << 0);

  // Enable the write protection
  PWM->PWM_WPCR |= (1 << 0) | (1 << 1);
  return;
}

//Insert dutcy_cycle as a promille value
void pwm_set_duty_cycle(uint16_t cycle_percentage, uint8_t channel)
{
  if (channel != 0 && channel != 1)
  {
    printf("PWM_ERROR: Invalid channel\n\r");
    return;
  }

  if (channel == 1)
  {
    if (cycle_percentage < DUTY_CYCLE_LOWER_BOUND)
    {
      cycle_percentage = DUTY_CYCLE_LOWER_BOUND;
    }
    else if (cycle_percentage > DUTY_CYCLE_UPPER_BOUND)
    {
      cycle_percentage = DUTY_CYCLE_UPPER_BOUND;
    }
  }

  PWM->PWM_CH_NUM[channel].PWM_CDTY = (cycle_percentage * CALCULATED_CPRD) / 1000;
  return;
}

void pwm_set_servo_angle(enum JoystickDirection direction){
  switch (direction)
  {
  case UP:
    pwm_set_duty_cycle(DUTY_CYCLE_MIDDEL + 10, PWM_SERVO_CHANNEL);
    break;
  case DOWN:
    pwm_set_duty_cycle(DUTY_CYCLE_MIDDEL - 10, PWM_SERVO_CHANNEL);
    break;
  case PRESSED:
    pwm_set_duty_cycle(DUTY_CYCLE_MIDDEL, PWM_SERVO_CHANNEL);
    break;
  case NEUTRAL:
    pwm_set_duty_cycle(DUTY_CYCLE_MIDDEL, PWM_SERVO_CHANNEL);
    break;
  default:
    break;
  }
  return;
}
