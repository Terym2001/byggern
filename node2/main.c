#include <stdio.h>
#include <stdarg.h>
#include "sam.h"
#include "drivers/can.h"
#include "drivers/uart.h"
#include "drivers/pwm.h"
#include "drivers/time.h"
#include "drivers/pio.h"
#include "drivers/servo.h"
#include "drivers/timer_counter.h"
#include "drivers/encoder.h"
#include "drivers/motor.h"
#include "drivers/motor_controller.h"
#define F_CPU 84000000 

CanMsg recieved_can;
MotorController motor = {0};

int main()
{
  // Initialize the system
  SystemInit();

  //Disable Watchdog Timer
  WDT->WDT_MR = WDT_MR_WDDIS;

  //adc_init();

  uart_init(F_CPU, 9600);

  // Initialize the PWM
  pwm_init();

  // Initialize the CAN
  CanInit canInitParam = {
    .brp    = 41,
    .smp    = 0,
    .phase1 = 6,
    .phase2 = 5,
    .sjw    = 0,
    .propag = 1
  };


  can_init(canInitParam, 0);
  uint8_t status = 0;
  enum JoystickDirection direction = NEUTRAL;

  pio_init_pin_as_output(PIOC, 14);
  pio_set_pin(PIOC, 14);

  motor_init();
  motor_controller_init(&motor, 1.0, 0.0, 0.0, 0.0); //Period T = 1us I think 

  encoder_init();
  tc_set_custom(&mc_motor_step);
  tc_init(F_CPU / (1000 * 50));
  while (1)
  {
    status = can_rx(&recieved_can);
    if (status != 0)
    {
      direction = (enum JoystickDirection) recieved_can.byte[0];
      char* direction_str = "HMM";
      switch (direction)
      {
        case LEFT:
          direction_str = "LEFT";
          break;
        case RIGHT:
          direction_str = "RIGHT";
          break;
        case UP:
          direction_str = "UP";
          break;
        case DOWN:
          direction_str = "DOWN";
          break;
        case PRESSED:
          direction_str = "PRESSED";
          break;
        case NEUTRAL:
          direction_str = "NEUTRAL";
          break;
      }
      //printf("state: %s\n\r", direction_str);

      //printf("setpoint: %f\n\r", motor.setpoint);
      //printf("Direction: %s\n\r", direction_str);
      //servo_set_angle(direction);
      //motor_set_direction(direction);
      //motor_set_speed(recieved_can.byte[1]);
    }
  }
}
