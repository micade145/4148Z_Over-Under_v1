#ifndef MOTION_H
#define MOTION_H
#include "main.h"

// Constants 
extern double DRIVE_INCH_TO_DEG;
extern double DRIVE_DEG_TO_INCH;

// Auto movement
extern void Move(double driveTarget, double maxDrivePower, double turnTarget, double maxTurnPower, 
          int maxTime, bool driveSlew, bool turnSlew);

extern void Turn(double targetAngle, double maxTurnPower, int maxTime);

extern void MoveToPoint(double targetX, double targetY, double endOrientation, double maxTranslatePower, 
                        double maxRotatePower, double maxOrientPower, int maxTime);

#endif