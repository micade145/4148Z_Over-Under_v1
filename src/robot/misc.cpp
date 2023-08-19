#include "robot_h/misc.h"

// Wing opcontrol
bool wingsOut = false;
void wingOpControl() {
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
        wingsOut = !wingsOut;
        }
    if(wingsOut) {
        states.setWingState(stateMachine::wing_state::OUT);
    }
    else {
        states.setWingState(stateMachine::wing_state::STOWED);
    }
}

// Parking brake opcontrol
bool parkingBrakeOn = false;
void parkingBrakeOpControl() {
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
        parkingBrakeOn = !parkingBrakeOn;
    }
    if(parkingBrakeOn && states.parkingBrakeStateIs(stateMachine::parking_brake_state::READY)) {
        states.setParkingBrakeState(stateMachine::parking_brake_state::BRAKE_ON);
    }
    else {
        states.setParkingBrakeState(stateMachine::parking_brake_state::BRAKE_ON);
    }
    // if(states.parkingBrakeStateIs(stateMachine::parking_brake_state::READY)) {
    //     if(parkingBrakeOn) {
    //         states.setParkingBrakeState(stateMachine::parking_brake_state::BRAKE_ON);
    //     }
        // else {
        //     states.setParkingBrakeState(stateMachine::parking_brake_state::BRAKE_OFF);
        // }
    // }
}
