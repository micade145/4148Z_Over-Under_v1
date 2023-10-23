#ifndef DRIVE_H
#define DRIVE_H
#include "main.h"

// ******** Drive Constants ******** //
extern double TURN_SENS;
extern double DRIVE_BRAKE_THRESHOLD;

// ******** Drive Helper Functions ******** //
extern void setDrive(int leftVolt, int rightVolt);
extern void setDriveBrakeMode(pros::motor_brake_mode_e driveBrakeMode);
extern void stopDrive(pros::motor_brake_mode_e driveBrakeMode);

// ******** Drive Opcontrol functions  ******** //
extern void splitArcade(pros::motor_brake_mode_e driveBrakeMode);
extern void curveSplitArcade();
extern void drivePtoOpControl(); // PTO Opcontrol

#endif