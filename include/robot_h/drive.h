#ifndef DRIVE_H
#define DRIVE_H
#include "main.h"

// Helper function
extern void setDrive(int leftVolt, int rightVolt);

// Opcontrol functions 
extern void splitArcade();
extern void curveSplitArcade();
// PTO 
extern bool sixMotorMode;
extern void drivePtoOpControl();

// Drive brake modes
extern void driveCoast();
extern void driveBrake();
extern void driveHold();

#endif