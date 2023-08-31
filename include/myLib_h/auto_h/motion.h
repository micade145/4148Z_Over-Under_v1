#ifndef MOTION_H
#define MOTION_H
#include "main.h"

// namespace auto_chassis {}
// // PID objects (doesn't work)
// extern PID drivePID;
// extern PID turnPID;

// Constants //
extern double DRIVE_INCH_TO_DEG;
extern double DRIVE_DEG_TO_INCH;
extern int DRIVE_SLEW_RATE;
extern int TURN_SLEW_RATE;
extern double DRIVE_SETTLE_THRESHOLD;
extern double TURN_SETTLE_THRESHOLD;

// Movement variables //
// move() variables
extern double drive_target;
extern double turn_target;
extern int max_drive_power;
extern int max_turn_power;
extern bool drive_slew;
extern bool turn_slew;

// moveToPoint() variables
extern double target_x;
extern double target_y;
extern double end_orientation;
extern int max_translate_power;
extern int max_rotate_power;
extern int max_orient_power;

// Universal variables 
extern bool driveSettled;
extern int max_time;

// Setters for auto functions //
// all parameters
extern void setMove(double driveTarget, int maxDrivePower, double turnTarget, int maxTurnPower, int maxTime, bool driveSlew, bool turnSlew);
// no slew rate
extern void setMove(double driveTarget, int maxDrivePower, double turnTarget, int maxTurnPower, int maxTime);
extern void setMoveToPoint(double targetX, double targetY, double endOrientation, int maxTranslatePower, 
        int maxRotatePower, int maxOrientPower, int maxTime);   
// extern void setTurn(double turnTarget, double maxTurnPower, int maxTime, bool turnSlew);

// Auto movement task //
extern void autoMovementTask();

// Wait function for drive
void waitUntilSettled(int msecDelay);

// Auto movement functions //
extern void move();
extern void moveToPoint();
// extern void turn();

// extern void move(double driveTarget, double maxDrivePower, double turnTarget, double maxTurnPower, 
//           int maxTime, bool driveSlew, bool turnSlew);
// extern void Turn(double targetAngle, double maxTurnPower, int maxTime);
// extern void MoveToPoint(double targetX, double targetY, double endOrientation, double maxTranslatePower, 
//                         double maxRotatePower, double maxOrientPower, int maxTime);

#endif