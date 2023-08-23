#ifndef DRIVE_H
#define DRIVE_H
#include "main.h"

// Drive constants 
extern double TURN_SENS;
extern double DRIVE_BRAKE_THRESHOLD;

// Helper function
extern void setDrive(int leftVolt, int rightVolt);
extern void setDriveBrakeMode(pros::motor_brake_mode_e driveBrakeMode);
extern void stopDrive(pros::motor_brake_mode_e driveBrakeMode);

// Opcontrol functions 
extern void splitArcade(pros::motor_brake_mode_e driveBrakeMode);
extern void curveSplitArcade();
// PTO 
extern void drivePtoOpControl();

// Drive brake modes
extern void driveCoast();
extern void driveBrake();
extern void driveHold();

#endif