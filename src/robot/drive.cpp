#include "robot_h/drive.h"

// Drive constants
double TURN_SENS = 0.8;
double DRIVE_BRAKE_THRESHOLD = 45;  // In RPM

// Helper function
void setDrive(int leftVolt, int rightVolt) {
    if(states.parkingBrakeStateIs(stateMachine::parking_brake_state::BRAKE_OFF)) {
    if(states.driveStateIs(stateMachine::drive_state::TWO_MOTOR)) {
        // only two motors
        leftFrontDrive.move(leftVolt);
        rightFrontDrive.move(rightVolt);
    }
    else {
        // all motors
        leftFrontDrive.move(leftVolt);
        rightFrontDrive.move(rightVolt);
        ptoLeftSide.move(leftVolt);
        ptoRightSide.move(rightVolt);
    }
    }
}

// Driver control functions 
void splitArcade() {
    // Read inputs from joysticks 
    double forwardPower = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    double turnPower = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X) * TURN_SENS;
    // Deadzone to prevent drift
    if(fabs(forwardPower) <= 15) { forwardPower = 0;}
    if(fabs(turnPower) <= 15) { turnPower = 0;}
    // Only output joystick values to drive if parking brake is off
    if(states.parkingBrakeStateIs(stateMachine::parking_brake_state::BRAKE_OFF)) {
        setDrive(forwardPower + turnPower, forwardPower - turnPower);
    }
}

void curveSplitArcade() {

}

// PTO function
bool sixMotorMode = false;
void drivePtoOpControl() {
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
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