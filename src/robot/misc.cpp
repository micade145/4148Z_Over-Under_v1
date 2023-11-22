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

    // if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
    //     if(states.wingStateIs(stateMachine::wing_state::WINGS_OUT)) {
    //         states.setWingState(stateMachine::wing_state::WINGS_STOWED);
    //     }
    //     else if(states.wingStateIs(stateMachine::wing_state::WINGS_STOWED)) {
    //         states.setWingState(stateMachine::wing_state::WINGS_OUT);
    //     }
    // }
}

// Parking Brake opcontrol
bool parkingBrakeOn = false;
void parkingBrakeOpControl() {
    if(brakeReady) {
        if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
            parkingBrakeOn = !parkingBrakeOn;
        }
        if(parkingBrakeOn) {
            states.setParkingBrakeState(stateMachine::parking_brake_state::BRAKE_ON);
        }
        else {
            states.setParkingBrakeState(stateMachine::parking_brake_state::BRAKE_OFF);
        }
    }

    // if(brakeReady && controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
    //     if(states.parkingBrakeStateIs(stateMachine::parking_brake_state::BRAKE_ON)) {
    //         states.setParkingBrakeState(stateMachine::parking_brake_state::BRAKE_OFF);
    //     }
    //     else if(states.parkingBrakeStateIs(stateMachine::parking_brake_state::BRAKE_OFF)) {
    //         states.setParkingBrakeState(stateMachine::parking_brake_state::BRAKE_ON);
    //     }
    // }
}

// Side Climb opcontrol
bool sideClimbState = false;
void sideClimbOpControl() {
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
        sideClimbState = !sideClimbState;
    }
    sideClimb.set_value(sideClimbState);
}
