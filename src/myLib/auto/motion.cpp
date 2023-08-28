#include "myLib_h/auto_h/motion.h"

// Constants 
double DRIVE_INCH_TO_DEG;
double DRIVE_DEG_TO_INCH;

// Drive PID objects
PID drivePID(1, 0);
PID turnPID(1, 0);

// Auto movement variables //
// move() variables
double drive_target;
double turn_target;
bool drive_slew = false;
bool turn_slew = false;

// turn() variables
int max_drive_power;
int max_turn_power;

// moveToPoint() variables
double target_x;
double target_y;
double end_orientation;
double max_translate_power;
double max_rotate_power;
double max_orient_power;

// Universal variables 
bool driveSettled = false;
int max_time;


// Setters for auto functions //
void setMove(double driveTarget, int maxDrivePower, double turnTarget, int maxTurnPower, int maxTime, bool driveSlew, bool turnSlew) {
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
void setTurn(double turnTarget, double maxTurnPower, int maxTime, bool turnSlew) {
    // Reset relative position
    rightFrontDrive.tare_position();
    // Set targets
    turn_target = turnTarget;
    max_turn_power = maxTurnPower;
    max_time = maxTime;
    // Set slew
    turnSlew  ? turn_slew = true : turn_slew = false;
    // Set state
    driveSettled = false;
    states.setDriveAutoState(stateMachine::drive_auto_state::TURN);
}
void setMoveToPoint(double targetX, double targetY, double endOrientation, double maxTranslatePower, 
        double maxRotatePower, double maxOrientPower, int maxTime) {
    // Reset relative position
    rightFrontDrive.tare_position();
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


// Auto movement task
void autoMovementTask() {
    while(true) {
        if(states.driveAutoStateIs(stateMachine::drive_auto_state::MOVE)) {
            move();
        }
        else if(states.driveAutoStateIs(stateMachine::drive_auto_state::TURN)) {
            turn();
        }
        else if(states.driveAutoStateIs(stateMachine::drive_auto_state::MOVE_TO_POINT)) {
            moveToPoint();
        }
        pros::delay(20);
    }
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
    int driveError, turnError;
    int drivePower, turnPower;
    int driveSlewRate, turnSlewRate, tempDriveMax, tempTurnMax;
    // Slew conditionals
    while(!driveSettled) {
        // driveTimer = pros::c::millis() - startTime;
        // driveError = driveTarget - (frontEnc.get_position() * DRIVE_DEG_TO_INCH);
        turnError = turn_target - inertial.get_heading();
        driveError = drive_target - rightFrontDrive.get_position();

        // Constrain relative turn from 180 to -180
        if(turnError > 180) {turnError -= 360;}
        if(turnError < -180) {turnError += 360;}

        // Calculate PID outputs 
        drivePower = drivePID.calculateOutput(driveError);
        turnPower = turnPID.calculateOutput(turnError);

        // Slew rate logic
        if(drive_slew) {
            // Only increment if temp drive power is less than max drive power
            if(tempDriveMax <= max_drive_power) {
                tempDriveMax += driveSlewRate;
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
                tempTurnMax += turnSlewRate;
                turnPower = constrainValue(turnPower, tempTurnMax, -tempTurnMax);
            }
            else {
                // Turn slew is done
                turn_slew = false;
            } 
        }

        // Constrain PID outputs
        drivePower = constrainValue(drivePower, max_drive_power, -max_drive_power);
        turnPower = constrainValue(turnPower, max_turn_power, -max_turn_power);
        
        pros::screen::erase_line(0, 1, 200, 1);
        pros::screen::print(TEXT_MEDIUM_CENTER, 1, "Drive Target: %i, Error: %i, Output: %i", int(drive_target), driveError, drivePower);
        
        // Output to drive
        setDrive(drivePower + turnPower, drivePower - turnPower);
        // rightFrontDrive.move(drivePower);

        // Exit condition 
        if(driveSettled || (pros::c::millis() - startTime) > max_time) {
            stopDrive(pros::E_MOTOR_BRAKE_BRAKE);
            drivePID.reset();
            driveSettled = true;
            // break;
        }

        // necessary delay - do not change
        pros::delay(20);
    }
}

void turn() {

}

void moveToPoint() {

}


// the archive :(

// void setMoveTarget(double target, int maxDrivePower, double turnTarget, int maxTurnPower) {
//     states.setDriveAutoState(stateMachine::drive_auto_state::MOVE);
//     rightFrontDrive.tare_position();
//     drive_target = target;
//     max_drive_power = maxDrivePower;
//     turn_target = turnTarget;
//     max_turn_power = maxTurnPower;
// }
// void setTurnTarget(double targetAngle, double maxTurnPower, int maxTime) {

// }
// void setMoveToPointTarget(double targetX, double targetY, double endOrientation, double maxTranslatePower, double maxRotatePower, double maxOrientPower, int maxTime) {
    
// }

// void setDrivePID(double target, int maxDrivePower, double turnTarget, int maxTurnPower) {
//     rightFrontDrive.tare_position();
//     drive_target = target;
//     max_drive_power = maxDrivePower;
//     turn_target = turnTarget;
//     max_turn_power = maxTurnPower;
// }


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

// void Turn(double targetAngle, double maxTurnPower, int maxTime) {

// }

// void MoveToPoint(double targetX, double targetY, double endOrientation, double maxTranslatePower, double maxRotatePower, double maxOrientPower, int maxTime) {

// }
