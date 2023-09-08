#include "myLib_h/auto_h/motion.h"
#include <cmath>

// Constants 
double DRIVE_INCH_TO_DEG = 360 / (2.75 * M_PI);
double DRIVE_DEG_TO_INCH = (2.75 * M_PI) / 360;
int DRIVE_SLEW_RATE = 5;    // change later
int TURN_SLEW_RATE = 5;
int SETTLE_THRESHOLD = 6;   // In 20 msec * number
int NEAR_TARGET_THRESHOLD = 2;  // In inches
double DRIVE_SETTLE_THRESHOLD = 1;  // tune later (decide on inches/deg/counts)
double TURN_SETTLE_THRESHOLD = 2;   // Degrees

// Drive PID objects
PID drivePID(.2, 0);
PID translationPID(14, 4);
PID turnPID(1.65, 5.5);

// Auto movement variables //
// move() variables
double drive_target;
double turn_target;
int max_drive_power;
int max_turn_power;
bool drive_slew = false;
bool turn_slew = false;

// moveToPoint() variables
double target_x;
double target_y;
double end_orientation;
int max_translate_power;
int max_rotate_power;
int max_orient_power;

// Universal variables 
bool driveSettled = false;
int max_time = 3000;


// Setters for auto functions //
void setMove(double driveTarget, int maxDrivePower, double turnTarget, int maxTurnPower, int maxTime = 3000, bool driveSlew = false, bool turnSlew = false) {
    // Reset relative position
    rightFrontDrive.tare_position();
    // Set targets
    drive_target = driveTarget;
    turn_target = turnTarget;
    max_drive_power = maxDrivePower;
    max_turn_power = maxTurnPower;
    max_time = maxTime;
    // Set slew
    driveSlew ? drive_slew = true : drive_slew = false;
    turnSlew  ? turn_slew = true : turn_slew = false;
    // Set state
    driveSettled = false;
    states.setDriveAutoState(stateMachine::drive_auto_state::MOVE);
}
void setMove(double driveTarget, int maxDrivePower, double turnTarget, int maxTurnPower, int maxTime = 3000) {
    setMove(driveTarget, maxDrivePower, turnTarget, maxTurnPower, maxTime, false, false);
}

void setMoveToPoint(double targetX, double targetY, double endOrientation, int maxTranslatePower, 
        int maxRotatePower, int maxOrientPower, int maxTime = 3000) {
    // Reset relative position
    // rightFrontDrive.tare_position();
    // Set targets
    target_x = targetX;
    target_y = targetY;
    end_orientation = endOrientation;
    max_translate_power = maxTranslatePower;
    max_rotate_power = maxRotatePower;
    max_orient_power = maxOrientPower;
    max_time = maxTime;
    // Set state
    driveSettled = false;
    states.setDriveAutoState(stateMachine::drive_auto_state::MOVE_TO_POINT);
}

// Auto movement task //
void autoMovementTask() {
    while(true) {
        if(!states.driveAutoStateIs(stateMachine::drive_auto_state::OFF)) {
           if(states.driveAutoStateIs(stateMachine::drive_auto_state::MOVE)) {
                move();
            }
            else if(states.driveAutoStateIs(stateMachine::drive_auto_state::MOVE_TO_POINT)) {
                moveToPoint();
            } 
        }
        pros::delay(20);
    }
}

// Wait for drive completion
void waitUntilSettled(int msecDelay) {
    while(!driveSettled) {
        pros::delay(20);
    }
    pros::delay(20);
    driveSettled = false;
    states.setDriveAutoState(stateMachine::drive_auto_state::OFF);
    drive_target = turn_target = 0;
    target_x = target_x = end_orientation = 0;
    pros::delay(msecDelay);
}

// Auto movement functions //
void move() {
    // Reset drive encoder 
    frontEnc.reset_position();
    rightFrontDrive.tare_position();
    // Initialize timer
    int startTime = pros::c::millis();
    int driveTimer;
    // Local variables 
    int driveError, turnError = 0;
    int drivePower, turnPower;
    int tempDriveMax, tempTurnMax;
    bool stopLoop = false;
    int settleCount = 0;
    // Slew conditionals
    while(!driveSettled) {
        // driveTimer = pros::c::millis() - startTime;
        // driveError = driveTarget - (frontEnc.get_position() * DRIVE_DEG_TO_INCH);
        driveError = int(drive_target - rightFrontDrive.get_position());
        turnError = int(turn_target - inertial.get_heading());

        // Constrain relative turn from 180 to -180
        if(turnError > 180) {turnError -= 360;}
        if(turnError < -180) {turnError += 360;}

        // Calculate PID outputs 
        drivePower = drivePID.calculateOutput(double(driveError));
        turnPower = turnPID.calculateOutput(double(turnError));

        // Slew rate logic
        if(drive_slew) {
            // Only increment if temp drive power is less than max drive power
            if(tempDriveMax <= max_drive_power) {
                tempDriveMax += DRIVE_SLEW_RATE;
                drivePower = constrainValue(drivePower, tempDriveMax, -tempDriveMax);
            }
            else {
                // Drive slew is done
                drive_slew = false;
            }
        }
        if(turn_slew) { 
            // Only increment if temp turn power is less than max turn power
            if(tempTurnMax <= max_turn_power) {
                tempTurnMax += TURN_SLEW_RATE;
                turnPower = constrainValue(turnPower, tempTurnMax, -tempTurnMax);
            }
            else {
                // Turn slew is done
                turn_slew = false;
            } 
        }

        // Constrain PID outputs
        drivePower = constrainVoltage(drivePower, max_drive_power, -max_drive_power);
        turnPower = constrainVoltage(turnPower, max_turn_power, -max_turn_power);
        
        pros::screen::erase_line(0, 1, 200, 1);
        pros::screen::print(TEXT_MEDIUM_CENTER, 1, "Drive Target: %5.1f, Err: %5d, Out: %3d", drive_target, driveError, drivePower);
        pros::screen::erase_line(0, 3, 200, 3);
        pros::screen::print(TEXT_MEDIUM_CENTER, 3, "Turn Tgt: %3.1f, Err: %3d, Out: %3d", turn_target, turnError, turnPower);

        // Exit conditions
        // If drive only, check drive error
        if(std::fabs(drive_target) > 0 && turn_target == 0) {
            if(std::fabs(driveError) <= DRIVE_SETTLE_THRESHOLD) {
                settleCount++;
                // stopLoop = true;
            }
            else {settleCount = 0;}
        }
        // If turn only, check turn error
        if(std::fabs(turn_target) > 0 && drive_target == 0) {
            if(std::fabs(turnError) <= TURN_SETTLE_THRESHOLD) {
                settleCount++;
                // stopLoop = true;
            }
            else {settleCount = 0;}
        }
        // If both drive & turn, check both errors
        if(std::fabs(drive_target) > 0 && std::fabs(turn_target) > 0) {
            if(std::fabs(driveError) <= DRIVE_SETTLE_THRESHOLD && std::fabs(turnError) <= TURN_SETTLE_THRESHOLD) {
                settleCount++;
                // stopLoop = true;
            }
            else {settleCount = 0;}
        }
        if((settleCount >= SETTLE_THRESHOLD) || (pros::c::millis() - startTime) >= max_time) {
            stopDrive(pros::E_MOTOR_BRAKE_BRAKE);
            driveError = turnError = drivePower = turnPower = 0;
            drive_target = turn_target = 0;
            drivePID.reset();
            turnPID.reset();
            driveSettled = true;
            // break;
        }

        // Output to drive
        setDrive(drivePower - turnPower, drivePower + turnPower); // CHANGE LATER

        // necessary delay - do not change
        pros::delay(20);
    }
}

void moveToPoint() {
    // Reset drive encoder 
    // frontEnc.reset_position();
    rightFrontDrive.tare_position();
    // Initialize timer
    int startTime = pros::c::millis();
    int driveTimer;
    // Local variables 
    double translationError, targetAngle, rotationError, orientationError;
    int translationPower, rotationPower, orientationPower;
    double movementScaleFactor;
    double xError = 0.0;
    double yError = 0.0;
    int settleCount = 0;
    bool onTarget = false;
    while(!driveSettled) {
        // Calculate point errors
        xError = round(target_x - globalPose.x);
        yError = round(target_y - globalPose.y);
        targetAngle = fmod((90 - (atan2(yError, xError) * RAD_TO_DEG)), 360);
        // targetAngle = 90 - (atan2(yError, xError) * RAD_TO_DEG);

        // Calculate movement errors
        translationError = hypot(xError, yError);
        rotationError = targetAngle - (globalPose.theta * RAD_TO_DEG);
        // rotationError = constrainAngle180(rotationError);
        if(rotationError > 180) {rotationError -= 360;}
        if(rotationError < -180) {rotationError += 360;}

        // Scale factor to prioritize turning
        movementScaleFactor = cos(fmod(rotationError, 90) * DEG_TO_RAD);

        // Calculate outputs
        translationPower = round(translationPID.calculateOutput(translationError) * movementScaleFactor);
        // translationPower = round(translationPID.calculateOutput(translationError));
        rotationPower = round(turnPID.calculateOutput(rotationError));

        // Constrain outputs
        translationPower = constrainVoltage(translationPower, std::fabs(movementScaleFactor) * max_translate_power, -std::fabs(movementScaleFactor) * max_translate_power);
        // translationPower = constrainVoltage(translationPower, max_translate_power, -max_translate_power);
        if(translationError <= NEAR_TARGET_THRESHOLD) {
            rotationPower = 0;
        }
        rotationPower = constrainVoltage(rotationPower, max_rotate_power, -max_rotate_power);

        // Exit condition
        // if(translationError <= NEAR_TARGET_THRESHOLD - .5) {
        //     settleCount++;
        // }
        // else {
        //     settleCount = 0;
        // }

        if((translationError <= .5) || (pros::c::millis() - startTime) >= max_time) {
            stopDrive(pros::E_MOTOR_BRAKE_BRAKE);
            translationError = translationPower = rotationError = rotationPower = 0;
            driveSettled = true;
        }

        setDrive(-translationPower - rotationPower, -translationPower + rotationPower); // CHANGE LATER
        
        pros::screen::erase_line(0, 0, 200, 0);
        pros::screen::print(TEXT_MEDIUM_CENTER, 0, "Tgt: x: %3.1f, y: %3.1f, theta: %3.1f", target_x, target_y, targetAngle);
        pros::screen::erase_line(0, 4, 200, 4);
        pros::screen::print(TEXT_MEDIUM_CENTER, 4, "dist err: %3.1f, volt: %3d, angle err: %3.1f, volt: %3d", translationError, translationPower, rotationError, rotationPower);

        pros::delay(20);
    }
}

void turn() {
    int turnError;
    int turnPower;
    int startTime = pros::c::millis();
    while(!driveSettled) {
        // Calculate and constrain error
        // turnError = turn_target - inertial.get_heading();
        turnError = constrainAngle180(turn_target - inertial.get_heading());
        
        // Calculate and constrain turn power
        turnPower = turnPID.calculateOutput(turnError);
        turnPower = constrainValue(turnPower, max_turn_power, -max_turn_power);

        // Exit conditions
        if(std::fabs(turnError) <= TURN_SETTLE_THRESHOLD || (pros::c::millis() - startTime) > max_time) {
            stopDrive(pros::E_MOTOR_BRAKE_BRAKE);
            turnPID.reset();
            driveSettled = true;
        }

        rightFrontDrive.move(turnPower);

        pros::screen::erase_line(0, 3, 300, 3);
        pros::screen::print(TEXT_MEDIUM_CENTER, 3, "Turn Target: %i, Error: %i, Output: %i", turn_target, turnError, turnPower);

        // necessary delay - do not change
        pros::delay(20);
    }
}




// the archive :(

// Old turn setter
// void setTurn(double turnTarget, double maxTurnPower, int maxTime, bool turnSlew) {
//     // Reset relative position
//     rightFrontDrive.tare_position();
//     // Set targets
//     turn_target = turnTarget;
//     max_turn_power = maxTurnPower;
//     max_time = maxTime;
//     // Set slew
//     turnSlew  ? turn_slew = true : turn_slew = false;
//     // Set state
//     driveSettled = false;
//     states.setDriveAutoState(stateMachine::drive_auto_state::TURN);
// }

// move() as a function
// void move(double driveTarget, double maxDrivePower, double turnTarget, double maxTurnPower, int maxDriveTime, bool driveSlew, bool turnSlew) {
//     // Reset drive encoder 
//     frontEnc.reset_position();
//     rightFrontDrive.tare_position();
//     // Initialize timer
//     int startTime = pros::c::millis();
//     int driveTimer;
//     // Local variables 
//     bool driveSettled = false;
//     double driveError, turnError, drivePower, turnPower;
//     double driveSlewRate, turnSlewRate, tempDriveMax, tempTurnMax;
//     // Slew conditionals
//     while(true) {
//         // driveTimer = pros::c::millis() - startTime;
//         // driveError = driveTarget - (frontEnc.get_position() * DRIVE_DEG_TO_INCH);
//         // turnError = turnTarget - inertial.get_heading();
//         driveError = driveTarget - rightFrontDrive.get_position();

//         // Constrain relative turn from 180 to -180
//         // if(turnError > 180) {turnError -= 360;}
//         // if(turnError < -180) {turnError += 360;}

//         // Calculate PID outputs 
//         drivePower = drivePID.calculateOutput(driveError);
//         // turnPower = turnPID.calculateOutput(turnError);

//         // Slew rate logic
//         // if(driveSlew) {
//         //     // Only increment if temp drive power is less than max drive power
//         //     if(tempDriveMax <= maxTurnPower) {
//         //         tempDriveMax += driveSlewRate;
//         //         drivePower = constrainValue(drivePower, tempDriveMax, -tempDriveMax);
//         //     }
//         //     else {
//         //         // Drive slew is done
//         //         driveSlew = false;
//         //     }
//         // }
//         // if(turnSlew) { 
//         //     // Only increment if temp turn power is less than max turn power
//         //     if(tempTurnMax <= maxTurnPower) {
//         //         tempTurnMax += turnSlewRate;
//         //         turnPower = constrainValue(turnPower, tempTurnMax, -tempTurnMax);
//         //     }
//         //     else {
//         //         // Turn slew is done
//         //         turnSlew = false;
//         //     } 
//         // }

//         // Constrain PID outputs
//         drivePower = constrainValue(drivePower, maxDrivePower, -maxDrivePower);
//         // turnPower = constrainValue(turnPower, maxTurnPower, -maxTurnPower);
        
//         pros::screen::erase_line(0, 1, 200, 1);
//         pros::screen::print(TEXT_MEDIUM_CENTER, 1, "Drive Target: %1.1d, Error: %1.2d, Output: %1.1d", driveTarget, driveError, drivePower);
        
//         // Output to drive
//         // setDrive(drivePower + turnPower, drivePower - turnPower);
//         rightFrontDrive.move(drivePower);

//         // Exit condition 
//         // if(driveSettled || (pros::c::millis() - startTime) > maxDriveTime) {
//         //     stopDrive(pros::E_MOTOR_BRAKE_BRAKE);
//         //     drivePID.reset();
//         //     break;
//         // }

//         // necessary delay - do not change
//         pros::delay(20);
//     }
// }

// void Turn(double targetAngle, double maxTurnPower, int maxTime) {}
// void MoveToPoint(double targetX, double targetY, double endOrientation, double maxTranslatePower, double maxRotatePower, double maxOrientPower, int maxTime) {}
