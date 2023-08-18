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

// Opcontrol function
void puncherOpControl() {

}