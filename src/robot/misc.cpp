#include "robot_h/misc.h"

bool brakeReady = false;

// Wing opcontrol
bool wingsOut = false;
void wingOpControl() {
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
        wingsOut = !wingsOut;
        }
    if(wingsOut) {
        states.setWingState(stateMachine::wing_state::WINGS_OUT);
    }
    else {
        states.setWingState(stateMachine::wing_state::WINGS_STOWED);
    }
}

// Parking Brake opcontrol
bool parkingBrakeOn = false;
void parkingBrakeOpControl() {
    if(brakeReady) {
        if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
            parkingBrakeOn = !parkingBrakeOn;
        }
        if(parkingBrakeOn) {
            states.setParkingBrakeState(stateMachine::parking_brake_state::BRAKE_ON);
        }
        else {
            states.setParkingBrakeState(stateMachine::parking_brake_state::BRAKE_OFF);
        }
    }
}

// Side Climb opcontrol
bool sideClimbState = false;
void sideClimbOpControl() {
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
        sideClimbState = !sideClimbState;
    }
    sideClimb.set_value(sideClimbState);
}

// saucy button
int displayCount = 0;
void displayTest() {
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
        displayCount++;
    }
    if(displayCount > 3) {
        displayInfo = false;
        pros::screen::set_eraser(COLOR_BLACK);
        pros::screen::erase();
        pros::screen::set_pen(COLOR_WHITE);
        pros::screen::fill_rect(0, 0, 1000, 1000);
        pros::delay(500000);
    }  
}