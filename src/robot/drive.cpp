#include "robot_h/drive.h"

// Helper function
void setDrive(int leftVolt, int rightVolt) {
    leftDrive.move_voltage(leftVolt);
    rightDrive.move_voltage(rightVolt);
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

// Drive brake modes
void driveCoast() {

}
void driveBrake() {

}
void driveHold() {

}