#ifndef MOTION_H
#define MOTION_H
#include "main.h"

namespace auto_chassis {
// Constants //
extern double DRIVE_INCH_TO_DEG;
extern double DRIVE_DEG_TO_INCH;

// PID objects //
extern PID drivePID;
extern PID turnPID;

// Movement variables //
// move() variables
extern double drive_target;
extern double turn_target;
extern bool drive_slew;
extern bool turn_slew;

// turn() variables
extern int max_drive_power;
extern int max_turn_power;

// moveToPoint() variables
double target_x;
double target_y;
double end_orientation;
double max_translate_power;
double max_rotate_power;
double max_orient_power;

// Universal max time
extern int max_time;

// Setters for auto functions //
extern void setMove(double driveTarget, int maxDrivePower, double turnTarget, int maxTurnPower, int maxTime, bool driveSlew, bool turnSlew);
extern void setTurn(double turnTarget, double maxTurnPower, int maxTime);
extern void setMoveToPoint(double targetX, double targetY, double endOrientation, double maxTranslatePower, 
        double maxRotatePower, double maxOrientPower, int maxTime);   

// Auto movement task //
extern void autoMovementTask();

// Auto movement functions //
extern void move();
extern void turn();
extern void moveToPoint();
}

// extern void move(double driveTarget, double maxDrivePower, double turnTarget, double maxTurnPower, 
//           int maxTime, bool driveSlew, bool turnSlew);
// extern void Turn(double targetAngle, double maxTurnPower, int maxTime);
// extern void MoveToPoint(double targetX, double targetY, double endOrientation, double maxTranslatePower, 
//                         double maxRotatePower, double maxOrientPower, int maxTime);

#endif