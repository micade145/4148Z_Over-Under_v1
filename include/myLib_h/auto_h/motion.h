#ifndef MOTION_H
#define MOTION_H
#include "main.h"

// namespace auto_chassis {}
// // PID objects (doesn't work)
// extern PID drivePID;
// extern PID turnPID;

// Constants //
extern double DRIVE_INCH_TO_DEG_275;
extern double DRIVE_DEG_TO_INCH_275;
extern int DRIVE_SLEW_RATE;
extern int TURN_SLEW_RATE;
extern double DISTANCE_SETTLE_THRESHOLD;
extern double TURN_SETTLE_THRESHOLD;

// Movement variables //
// move() variables
extern double drive_position;
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
/**
 * @brief Setter for the move function: Can set drive only, turn only, or both simultaneously 
 * @param driveTarget Target position for the drive, in inches
 * @param turnTarget Target heading for drive
 * @param maxDrivePower Max power for drive
 * @param maxTurnPower Max power for turn 
 * @param maxTime Maximum time the function is allowed to run for; default 3000 ms
 * @param driveSlew Boolean for using slew rate for drive
 * @param turnSlew Boolean for using slew rate for turn
*/
extern void setMove(double driveTarget, double turnTarget, int maxDrivePower, int maxTurnPower, int maxTime, bool driveSlew, bool turnSlew);

/**
 * @brief Setter for the moveToPoint function
 * @param targetX Target x coordinate, in inches
 * @param targetY Target y coordinate, in inches
 * @param endOrientation End angle after arriving at point
 * @param maxTranslatePower Max power for driving to target
 * @param maxRotatePower Max power for turn to target
 * @param maxOrientPower Max power for end orientation turn
 * @param maxTime Maximum time the function is allowed to run for; default 3000 ms
*/
extern void setMoveToPoint(double targetX, double targetY, double endOrientation, int maxTranslatePower, 
        int maxRotatePower, int maxOrientPower, int maxTime);   

/**
 * @brief Setter for curve function
 * @param distance Distance to move after finishing arc
 * @param endAngle End angle for arc; robot will turn left if negative and turn right if positive
 * @param radius Radius of the arc the robot will travel
 * @param maxDrivePower Max power for drive
 * @param maxTurnPower Max power for turn
 * @param maxTime Maximum time the function is allowed to run for; default 3000 ms
*/
extern void setCurve(double distance, double endAngle, double radius, int maxDrivePower, int maxTurnPower, int maxTime);

// Auto movement task //
extern void autoMovementTask();

/**
 * @brief Delay until movement is finished and drive is settled
 * @param msecDelay Addition delay after the drive is settled 
*/
void waitUntilSettled(int msecDelay);

// Auto movement functions //
extern void move();
extern void moveToPoint();
// extern void turn();

                // archive //
// setter for turn function
// extern void setTurn(double turnTarget, double maxTurnPower, int maxTime, bool turnSlew);
// simplified setter for move function
// extern void setMove(double driveTarget, double turnTarget, int maxDrivePower, int maxTurnPower, int maxTime);


// extern void move(double driveTarget, double maxDrivePower, double turnTarget, double maxTurnPower, 
//           int maxTime, bool driveSlew, bool turnSlew);
// extern void Turn(double targetAngle, double maxTurnPower, int maxTime);
// extern void MoveToPoint(double targetX, double targetY, double endOrientation, double maxTranslatePower, 
//                         double maxRotatePower, double maxOrientPower, int maxTime);

#endif