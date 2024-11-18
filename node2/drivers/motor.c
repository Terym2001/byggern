#include "motor.h"

void motor_init(void)
{
  pio_init_pin_as_output(PIOC, 23);
  return;
}

void motor_set_direction(enum JoystickDirection direction)
{
  switch (direction)
  {
    case LEFT:
      pio_set_pin(PIOC, 23);
      break;
    case RIGHT:
      pio_clear_pin(PIOC, 23);
      break;
    default:
      break;
  }
  return;
}

void motor_set_speed(uint32_t speed)
{
  uint32_t speed_abs = abs(speed);
  //printf("Speed: %i\n\r", speed);
  if (speed_abs < 50)
  {
    speed_abs = 0;
  }
  if(speed_abs > 1000)
  {
    printf("Error speed to high\n\r");
    speed_abs = 1000;
  }

  pwm_set_duty_cycle(speed_abs, PWM_MOTOR_CHANNEL);
  return;
}


