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
#include "drivers/adc.h"

#define F_CPU 84000000 

CanMsg recieved_can;
CanMsg send_can;

MotorController motor = {0};

bool lostGame = false;
uint8_t score = 0;

int main()
{
  // Initialize the system
  SystemInit();

  //Disable Watchdog Timer
  WDT->WDT_MR = WDT_MR_WDDIS;

  adc_init();

  uart_init(F_CPU, 9600);

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

  pio_init_pin_as_output(PIOC, 16);
  pio_set_pin(PIOC, 16);

  motor_init();
  motor_controller_init(&motor, 0.5, 0.2, 0.0, 0.0); //Period T = 1us I think 

  encoder_init();
  tc_init(0, F_CPU / (1000 * 500));
  tc_init(1, F_CPU / (1000));

  while (1)
  {
    status = can_rx(&recieved_can);
    if (status != 0)
    {
      direction = (enum JoystickDirection) recieved_can.byte[0];
      servo_set_angle(direction);
    }
    if(lostGame){
      printf("You lost the game \n\r");\
      //Send a message to node 1 that the game is lost
      send_can = (CanMsg){
        .id = 1,
        .length = 1,
        .byte = {lostGame, score, 0, 0, 0, 0, 0, 0} //Score should be sent here
      };
      can_tx(send_can);
    }
  }
}
