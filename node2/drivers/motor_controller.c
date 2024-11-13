#include "motor_controller.h"
#include "encoder.h"
#include "motor.h"

extern MotorController motor; //Get the motor from main

void motor_controller_init(MotorController *mc, float Kp, float Ki, float Kd, float r)
{
  mc->pid.Kp = Kp;
  mc->pid.Ki = Ki;
  mc->pid.Kd = Kd;

  mc->setpoint = r;
  mc->state = 0.0;

  mc->error = 0.0;
  mc->error_prev = 0.0;
  mc->integral = 0.0;

  mc->input = 0.0;

  mc->T = 0.02; //TODO: Should lower this with interrupt

  mc->max = 1.0;
  mc->min = -1.0;

  // Assign function pointers
  mc->get_setpoint = &mc_get_setpoint;
  mc->measure_state = &mc_measure_state;
  mc->compute_input = &mc_compute_input;
  mc->compute_error = &mc_compute_error;
  mc->send_input = &mc_send_input;

  return;
}

void mc_compute_input(MotorController *mc)
{
  mc->compute_error(mc); 

  mc->integral += mc->error;

  float proporsional_effect = mc->pid.Kp * mc->error;
  float integral_effect = mc->T * mc->pid.Ki * mc->integral;
  float derivative_effect = (mc->pid.Kd / mc->T) * (mc->error - mc->error_prev);
  
  mc->input = proporsional_effect + integral_effect + derivative_effect;

  return;
}

// Implement function to send input to motor
void mc_send_input(MotorController *mc)
{
  enum JoystickDirection direction = NEUTRAL;
  char* dir_str = "NEUTRAL";

  // TODO: Implement better way to determine direction
  if (mc->input > 0)
  {
    direction = RIGHT;
    dir_str = "RIGHT";
  }
  else if (mc->input < 0)
  {
    direction = LEFT;
    dir_str = "LEFT";
  } 

  motor_set_direction(direction);
  
  uint32_t speed = abs((int32_t)(mc->input * 1000));
  //printf("dir: %s, speed: %u\n\r", dir_str, speed);
  motor_set_speed(speed);
  return;
}

void mc_compute_error(MotorController *mc)
{
  mc->error_prev = mc->error;
  mc->error = mc->setpoint - mc->state;
  return;
}

// Implement function to read actual encoder data
void mc_measure_state(MotorController *mc)
{
  uint16_t y = abs(encoder_read());
  float y_prepr = y/MAX_ENCODER_VALUE; //TODO: Maybe change to double if needed
  mc->state = y_prepr;
  return;
}

void mc_get_setpoint(MotorController *mc)
{
  mc->setpoint = (float) recieved_can.byte[1] / 255;
  return;
}


void mc_motor_step(void)
{
  motor.get_setpoint(&motor);
  motor.measure_state(&motor);
  motor.compute_error(&motor);
  //printf("setpoint: %f2 State: %f2, Error: %f2\n\r", motor.setpoint, motor.state, motor.error);
  motor.compute_input(&motor);
  printf("r: %f, y: %f, u: %f\n\r", motor.setpoint, motor.state, motor.input);
  motor.send_input(&motor);
  return;
}

