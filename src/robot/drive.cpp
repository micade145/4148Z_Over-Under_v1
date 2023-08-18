#include "robot_h/drive.h"

// Helper function
void setDrive(int leftVolt, int rightVolt) {
    if(states.driveStateIs(stateMachine::drive_state::TWO_MOTOR)) {
        // only two motors
        // leftFrontDrive.move(leftVolt);
        // rightFrontDrive.move(rightVolt);
    }
    else {
        // all motors
        leftFrontDrive.move(leftVolt);
        rightFrontDrive.move(rightVolt);
    }
}

// Driver control functions 
void splitArcade() {
    double forwardPower = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    double turnPower = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X) * TURN_SENS;
    // Deadzone
    if(fabs(forwardPower) <= 15) { forwardPower = 0;}
    if(fabs(turnPower) <= 15) { turnPower = 0;}
    // if(!(states.parkingBrakeStateIs(stateMachine::parking_brake_state::READY)) && (turnPower < 15 || forwardPower < 15)) {
    //     states.setParkingBrakeState(stateMachine::parking_brake_state::READY);
    // }

    if(!states.driveStateIs(stateMachine::drive_state::OFF)) {
        setDrive(forwardPower + turnPower, forwardPower - turnPower);
    }
}

void curveSplitArcade() {

}

// PTO function
bool sixMotorMode = false;
void drivePtoOpControl() {
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
        sixMotorMode = !sixMotorMode;
    }
    if(sixMotorMode) { 
        states.setDriveState(states.SIX_MOTOR);
    }
    else {
        states.setDriveState(states.TWO_MOTOR);
    }
}

// Drive brake modes
void stopDrive() {
    // write stop drive helper function
}
void driveCoast() {

}
void driveBrake() {

}
void driveHold() {

}