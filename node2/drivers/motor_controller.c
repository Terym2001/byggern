#include "motor_controller.h"
#include "encoder.h"

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

  mc->T = 0.0005; //TODO: Should lower this with interrupt

  mc->max = 1.0;
  mc->min = -1.0;

  // Assign function pointers
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
  //motor_set_direction();
  //printf("Input before modification: %f\n\r", mc->input);
  int8_t speed = (int8_t)(mc->input * 127);
  //printf("Input: %i\n\r", speed);
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
  int16_t y = encoder_read();
  float y_prepr = y/MAX_ENCODER_VALUE; //TODO: Maybe change to double if needed
  //printf("Encoder: %f\n\r", y_prepr);
  mc->state = y_prepr;
  return;
}


void mc_motor_step(void)
{
  motor.measure_state(&motor);
  motor.compute_error(&motor);
  motor.compute_input(&motor);
  motor.send_input(&motor);
  return;
}

