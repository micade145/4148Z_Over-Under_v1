#ifndef INTAKE_H
#define INTAKE_H
#include "main.h"

// Variables
extern int openCount;
extern int closeCount;

// Constants
extern int INTAKE_CLOSE_THRESHOLD;
extern int INTAKE_OPEN_THRESHOLD;

// Spin intake
/*! @param intakeVolt Intake voltage from 127 to -127 */
extern void spinIntake(int intakeVolt);

// Stop intake
/*! @param newIntakeBrakeMode New intake brake mode */
extern void stopIntake(pros::motor_brake_mode_e_t newIntakeBrakeMode);

// Opcontrol function 
extern void intakeControl();

#endif