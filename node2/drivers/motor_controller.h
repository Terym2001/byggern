#ifndef _PID_H_
#define _PID_H_

#include <stdint.h>
#include "sam.h"

#define MAX_ENCODER_VALUE 5580.0
#define MIN_ENCODER_VALUE 0.0

typedef struct Pid_t
{
  float Kp;
  float Ki;
  float Kd;
} Pid;

typedef struct MotorController_t 
{
  Pid pid;

  float setpoint;
  float state;

  float error;
  float error_prev;
  float integral;

  float input;

  float T;

  float max;
  float min;

  void (*measure_state)(struct MotorController_t *mc);
  void (*compute_input)(struct MotorController_t *mc);
  void (*compute_error)(struct MotorController_t *mc);
  void (*send_input)(struct MotorController_t *mc);
  // TODO: compute_step_time not assigned

} MotorController;

void motor_controller_init(MotorController *mc, float Kp, float Ki, float Kd, float r);

// TODO: Can probably run in init
void mc_compute_step_time(MotorController *mc);

void mc_compute_input(MotorController *mc);

void mc_send_input(MotorController *mc);

void mc_measure_state(MotorController *mc);

void mc_compute_error(MotorController *mc);

void mc_motor_step(void);

#endif
