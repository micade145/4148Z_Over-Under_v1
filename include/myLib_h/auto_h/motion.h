#ifndef MOTION_H
#define MOTION_H
#include "main.h"
#include <vector>

// namespace AUTO {}

// enum class auto_movement_flag {NONE, FULL, REV} currentMovementFlag;

// ******** Movement Constants ******** //
extern int DRIVE_SLEW_RATE;
extern int TURN_SLEW_RATE;
extern double DISTANCE_SETTLE_THRESHOLD;
extern double TURN_SETTLE_THRESHOLD;

// ******** Movement Variables ******** //
// move() variables
extern double drive_position;
extern double drive_error;
extern double drive_target;
extern double turn_target;
extern int max_drive_power;
extern int max_turn_power;
extern bool drive_slew;
extern bool turn_slew;

// moveToPoint() variables
extern double translation_error;
extern double target_x;
extern double target_y;
extern double end_orientation;
extern int max_translate_power;
extern int max_rotate_power;
extern int max_orient_power;
extern bool movement_reversed;

// Universal variables 
extern bool driveSettled;
extern bool full_power;
extern int max_time;


// **************** Setters for Movement Functions **************** //

// ******** Move Function ******** //
/**
 * @brief Full setter for the move function: Set drive only, turn only, or both simultaneously 
 * @param driveTarget Target position for the drive, in inches  @param turnTarget Target heading for drive
 * @param maxDrivePower Max power for drive @param maxTurnPower Max power for turn 
 * @param maxTime Maximum time the function is allowed to run for; default 2000 ms
 * @param fullPower If true, drive at full power instead of using PID 
 * @param driveSlew Boolean for using slew rate for drive @param turnSlew Boolean for using slew rate for turn
*/
extern void setMove(double driveTarget, double turnTarget, int maxDrivePower, int maxTurnPower, int maxTime, bool fullPower, bool driveSlew, bool turnSlew);

/**
 * @brief Wrapped setter for the move function: Use full power
 * @param driveTarget Target position for the drive, in inches  @param turnTarget Target heading for drive
 * @param maxDrivePower Max power for drive @param maxTurnPower Max power for turn 
 * @param maxTime Maximum time the function is allowed to run for; default 2000 ms
 * @param fullPower If true, drive at full power instead of using PID
*/
extern void setMove(double driveTarget, double turnTarget, int maxDrivePower, int maxTurnPower, int maxTime, bool fullPower);

/**
 * @brief Wrapped setter for the move function: No slew rate
 * @param driveTarget Target position for the drive, in inches  @param turnTarget Target heading for drive
 * @param maxDrivePower Max power for drive @param maxTurnPower Max power for turn 
 * @param maxTime Maximum time the function is allowed to run for; default 2000 ms
*/
extern void setMove(double driveTarget, double turnTarget, int maxDrivePower, int maxTurnPower, int maxTime);

/**
 * @brief Wrapped setter for the move function: Only drive / turn target and timeout
 * @param driveTarget Target position for the drive, in inches  @param turnTarget Target heading for drive
 * @param maxTime Maximum time the function is allowed to run for; default 2000 ms
*/
extern void setMove(double driveTarget, double turnTarget, int maxTime);


// ******** MoveToPoint Function ******** //
/**
 * @brief Full setter for the moveToPoint function
 * @param targetX Target x coordinate, in inches @param targetY Target y coordinate, in inches
 * @param endOrientation End angle after arriving at point
 * @param maxTranslatePower Max power for driving to target @param maxRotatePower Max power for turn to target
 * @param maxOrientPower Max power for end orientation turn
 * @param maxTime Maximum time the function is allowed to run for; default 2000 ms
 * @param reversed If true, reverse movement. False (forward) by default
*/
extern void setMoveToPoint(double targetX, double targetY, double endOrientation, int maxTranslatePower, 
        int maxRotatePower, int maxOrientPower, int maxTime, bool reversed);
        
/**
 * @brief Wrapped setter for the moveToPoint function: No end orientation
 * @param targetX Target x coordinate, in inches @param targetY Target y coordinate, in inches
 * @param maxTranslatePower Max power for driving to target @param maxRotatePower Max power for turn to target
 * @param maxTime Maximum time the function is allowed to run for; default 2000 ms
 * @param reversed If true, reverse movement. False (forward) by default
*/
extern void setMoveToPoint(double targetX, double targetY, int maxTranslatePower, int maxRotatePower,  int maxTime, bool reversed);

/**
 * @brief Wrapped setter for the moveToPoint function: Only target x, y and timeout
 * @param targetX Target x coordinate, in inches @param targetY Target y coordinate, in inches
 * @param maxTime Maximum time the function is allowed to run for; default 2000 ms
 * @param reversed If true, reverse movement. False (forward) by default
*/
extern void setMoveToPoint(double targetX, double targetY, int maxTime, bool reversed);


// ******** Curve Function ******** //
/**
 * @brief Setter for curve function
 * @param distance Distance to move after finishing arc
 * @param endAngle End angle for arc; robot will turn left if negative and turn right if positive
 * @param radius Radius of the arc the robot will travel
 * @param maxDrivePower Max power for drive
 * @param maxTurnPower Max power for turn
 * @param maxTime Maximum time the function is allowed to run for; default 2000 ms
*/
extern void setCurve(double distance, double endAngle, double radius, int maxDrivePower, int maxTurnPower, int maxTime);

// ******** Chained Movement Functions ******** //

extern void chainMove(std::vector<double> target1, std::vector<double> power1, int maxTime1, 
                std::vector<double> target2, std::vector<double> power2, int maxTime2, double threshold);
extern void chainMoveToPoint(std::vector<double> pose1, std::vector<double> power1, int maxTime1, 
                        std::vector<double> pose2, std::vector<double> power2, int maxTime2, double threshold);

// ******** Wait Functions ******** //
/**
 * @brief Delay until movement is finished and drive is settled
 * @param msecDelay Addition delay after the drive is settled 
*/
extern void waitUntilSettled(int msecDelay);
/**
 * @brief Delay until robot is near target distance or pose
 * @param threshold Error threshold for robot to be considered near target
 * @param msecDelay Addition delay after robot is near target 
*/
extern void waitUntilNear(double threshold, int msecDelay);

/**
 * @brief Forces the drive to stop and switch autoMovementState to OFF; 
 * used for when running at full power
 * @param mode Brake mode to stop drive in
*/
extern void forceStopDrive(pros::motor_brake_mode_e mode);

// ******** Auto Movement Task ******** //
extern void autoMovementTask();


// ******** Movement Functions ******** //
extern void move();
extern void moveToPoint();
// extern void turn();




// ******** Archive ******** //

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