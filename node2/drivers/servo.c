#include "servo.h"
#include "pwm.h"

void servo_set_angle(enum JoystickDirection direction){
  //TODO: Change values after testing
  switch (direction)
  {
  case UP:
    pwm_set_duty_cycle(DUTY_CYCLE_MIDDEL + 10, PWM_SERVO_CHANNEL);
    break;
  case DOWN:
    pwm_set_duty_cycle(DUTY_CYCLE_MIDDEL - 10, PWM_SERVO_CHANNEL);
    break;
  case PRESSED:
    pio_clear_pin(PIOC, 14);
    return;
  case NEUTRAL:
    pwm_set_duty_cycle(DUTY_CYCLE_MIDDEL, PWM_SERVO_CHANNEL);
    break;
  default:
    break;
  }
  pio_set_pin(PIOC, 14);
  return;
}
