#ifndef DRIVE_H
#define DRIVE_H
#include "main.h"

// Helper function
extern void setDrive(int leftVolt, int rightVolt);

// Driver control functions 
extern void splitArcade();
extern void curveSplitArcade();

// PTO function
extern bool sixMotorMode;
extern void drivePTOControl();

// Drive brake modes
extern void driveCoast();
extern void driveBrake();
extern void driveHold();

#endif