#include "robot_h/puncher.h"

// Helper functions
void setPuncher(int puncherVolt) {
    if(states.puncherStateIs(stateMachine::puncher_state::ONE_MOTOR_MODE)) {
    
    }
    else if(states.puncherStateIs(stateMachine::puncher_state::FIVE_MOTOR_MODE)) {

    }
}
void stopPuncher(pros::motor_brake_mode_e_t puncherBrakeMode) {
    if(states.puncherStateIs(stateMachine::puncher_state::ONE_MOTOR_MODE)) {

    }
    else if(states.puncherStateIs(stateMachine::puncher_state::FIVE_MOTOR_MODE)) {

    }
}

void puncherTask() {
    puncher.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    while(true) {
        if(states.puncherStateIs(stateMachine::puncher_state::FIRE)) {
            puncher.move_relative(-25, 100);
            // TODO program wait until 
            while( !((puncher.get_position() > -30) && (puncher.get_position() < -20)) ) {
                pros::delay(2);
            }
            
            puncher.tare_position();
            states.setPuncherState(stateMachine::puncher_state::SHORT_PULLBACK);
        }

        // else statement necessary???
        if(states.puncherStateIs(stateMachine::puncher_state::SHORT_PULLBACK)) {
            puncher.move_absolute(500, 100);
            // TODO program wait until
            while( !((puncher.get_position() > 495) && (puncher.get_position() < 505)) ) {
                pros::delay(2);
            }

            puncher.brake();
            states.setPuncherState(stateMachine::puncher_state::PULLED_BACK);
        }
        else if(states.puncherStateIs(stateMachine::puncher_state::MID_PULLBACK)) {
            puncher.move_absolute(700, 100);
            // TODO program wait until
            while( !((puncher.get_position() > 695) && (puncher.get_position() < 705)) ) {
                pros::delay(2);
            }

            puncher.brake();
            states.setPuncherState(stateMachine::puncher_state::PULLED_BACK);
        }
        else if(states.puncherStateIs(stateMachine::puncher_state::LONG_PULLBACK)) {
            puncher.move_absolute(950, 100);
            // TODO program wait until
            while( !((puncher.get_position() > 945) && (puncher.get_position() < 955)) ) {
                pros::delay(2);
            }

            puncher.brake();
            states.setPuncherState(stateMachine::puncher_state::PULLED_BACK);
        }
    }
}

// Opcontrol function
int punchAngle = 1;
int lastPunchAngle = 1;
void puncherOpControl() {
    // Fires puncher
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
        if(states.puncherStateIs(stateMachine::puncher_state::PULLED_BACK)) {
            states.setPuncherState(stateMachine::puncher_state::FIRE);
        }
    }
    // Buttons to increment punchAngle up and down
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
        punchAngle ++;
        if(punchAngle > 4) {punchAngle = 4;}
    }
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
        punchAngle --;
        if(punchAngle < 1) {punchAngle = 1;}
    }

    // Assigns puncher angle to respective punchAngle (1 = DOWN, 2 = FLAT, 3 = MID, 4 = STEEP)
    if(lastPunchAngle != punchAngle) {
        switch(punchAngle) {
        case 1:
            states.setPuncherAngleState(stateMachine::puncher_angle_state::DOWN);
            lastPunchAngle = punchAngle;
            break;
        case 2:
            states.setPuncherAngleState(stateMachine::puncher_angle_state::FLAT);
            lastPunchAngle = punchAngle;
            break;
        case 3:
            states.setPuncherAngleState(stateMachine::puncher_angle_state::MID);
            lastPunchAngle = punchAngle;
            break;
        case 4:
            states.setPuncherAngleState(stateMachine::puncher_angle_state::STEEP);
            lastPunchAngle = punchAngle;
            break;
        // default:
        //     states.setPuncherAngleState(stateMachine::puncher_angle_state::DOWN);
        }
    }
}

int punchPullback = 1;
int lastPunchPullback = 1;
void puncherAngleOpControl() {
    // Button to increment punchPullback
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
        punchPullback ++;
        if(punchPullback > 2) {punchPullback = 2;}
    }
    // Resets punchPullback counter to 1 when we auto pullback to short
    if(states.puncherStateIs(stateMachine::puncher_state::SHORT_PULLBACK)) {
        punchPullback = 1;
    }
    
    // Assigns puncher pullback to respective punchPullback (1 = MID, 2 = LONG)
    if(lastPunchPullback != punchPullback) {
        switch(punchPullback) {
        case 1:
            states.setPuncherState(stateMachine::puncher_state::MID_PULLBACK);
            lastPunchPullback = punchPullback;
            break;
        case 2:
            states.setPuncherState(stateMachine::puncher_state::LONG_PULLBACK);
            lastPunchPullback = punchPullback;
            break;
        }
    }
}