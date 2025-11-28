#ifndef STEPPER_CONTROL_H
#define STEPPER_CONTROL_H

#include "BasicStepperDriver.h"

#define STEPPER_PIN_STEP  D3     //motor driver STEP input (1 pulse = 1 step)
#define STEPPER_PIN_DIR   D4     //motor driver DIR input (1=CW, 0 = CCW)
#define STEPPER_PIN_EN    D0     //motor driver EN input (0=ON, 1 = OFF)         To use to disable power to the stepper inbetween movements
//#define STEPPER_PIN_SLEEP      //motor driver SLEEP input (0=SLEEP, 1=ON).   To use for power saving during long off times

#define STEPPER_WAKEUP_TIME (2)            // check wakeup timing
#define STEPPER_MIN_MOVE_ANGLE (0.02)       //Min movement angle to trigger stepper activation
#define STEPPER_STEPS_PER_REV (200.0*50.895)  // 1.8°/step divided by gearbox ratio
#define STEPPER_STEPS_PER_DEGREE (360.0/STEPPER_STEPS_PER_REV)
#define STEPPER_SPEED 2.0     // Steps per second
#define STEPPER_ACCEL 1000.0     // Steps per second^2

extern BasicStepperDriver stepper;
extern bool lastDir;

// Function to initialize stepper motor
void stepper_init();

void stepper_sleep();
void stepper_wakeup();

// Function to move to the target angle (in degrees)
void stepper_moveAngle(double targetAngle, double currentAngle);

#endif
