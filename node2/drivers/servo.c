#include "servo.h"

void servo_set_angle(enum JoystickDirection direction){
  //TODO: Change values after testing
  switch (direction)
  {
  case LEFT:
    pwm_set_duty_cycle(DUTY_CYCLE_LOWER_BOUND);
    break;
  case RIGHT:
    pwm_set_duty_cycle(DUTY_CYCLE_UPPER_BOUND);
    break;
  case UP:
    pwm_set_duty_cycle(DUTY_CYCLE_MIDDEL + 10);
    break;
  case DOWN:
    pwm_set_duty_cycle(DUTY_CYCLE_MIDDEL - 10);
    break;
  case PRESSED:
    pio_clear_pin(PIOC, 16);
    return;
  case NEUTRAL:
    pwm_set_duty_cycle(DUTY_CYCLE_MIDDEL);
    break;
  default:
    break;
  }
  pio_set_pin(PIOC, 16);
  return;
}
