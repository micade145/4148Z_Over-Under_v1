#ifndef MOTION_H
#define MOTION_H
#include "main.h"

// Constants 
extern double DRIVE_INCH_TO_DEG;
extern double DRIVE_DEG_TO_INCH;

// Global variables
extern double drive_target;
extern int max_drive_power;
extern double turn_target;
extern int max_turn_power;

extern void setDrivePID(double target, int maxDrivePower, double turnTarget, int maxTurnPower);

// Auto movement
// extern void move(double driveTarget, double maxDrivePower, double turnTarget, double maxTurnPower, 
//           int maxTime, bool driveSlew, bool turnSlew);
extern void autoMovement();
extern void move();
extern void turn();
extern void moveToPoint();

extern void Turn(double targetAngle, double maxTurnPower, int maxTime);

extern void MoveToPoint(double targetX, double targetY, double endOrientation, double maxTranslatePower, 
                        double maxRotatePower, double maxOrientPower, int maxTime);

#endif