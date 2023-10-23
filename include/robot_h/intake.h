#ifndef INTAKE_H
#define INTAKE_H
#include "main.h"

// ******** Intake Constants ******** //
extern int INTAKE_CLOSE_THRESHOLD;
extern int INTAKE_OPEN_THRESHOLD;

// ******** Intake Variables ******** //
extern int openCount;
extern int closeCount;


// ******** Intake Helper Functions ******** //
/**
 * @brief Spin intake at a specified voltage
 * @param intakeVolt Intake voltage from 127 to -127
*/
extern void spinIntake(int intakeVolt);

/**
 * @brief Stop intake with a specified brake mode
 * @param newIntakeBrakeMode Brake mode: HOLD, BRAKE, or COAST
*/
extern void stopIntake(pros::motor_brake_mode_e_t newIntakeBrakeMode);


// ******** Intake Opcontrol Function ******** //
extern void intakeOpControl();

#endif