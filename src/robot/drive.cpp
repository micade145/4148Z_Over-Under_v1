#include "robot_h/drive.h"

// Helper function
void setDrive(int leftVolt, int rightVolt) {
    leftFrontDrive.move(leftVolt);
    rightFrontDrive.move(rightVolt);
}

// Driver control functions 
void splitArcade() {
    double forwardPower = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    double turnPower = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X) * TURN_SENS;
    // Deadzone
    if(fabs(forwardPower) <= 15) { forwardPower = 0;}
    if(fabs(turnPower) <= 15) { turnPower = 0;}
    setDrive(forwardPower + turnPower, forwardPower - turnPower);
}

void curveSplitArcade() {

}

// PTO function
bool sixMotorMode = false;
void drivePTOControl() {
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
void driveCoast() {

}
void driveBrake() {

}
void driveHold() {

}