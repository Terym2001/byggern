#include "motor_controller.h"

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

  mc->T = 0.1;

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

// Implement function to compute step time (noe interrupt greier)
void mc_compute_step_time(MotorController *mc)
{

  return;
}

// Implement function to send input to motor
void mc_send_input(MotorController *mc)
{
  // Send input to motor
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
  mc->state += mc->input;
  return;
}


