#include "myLib_h/robotStates.h"

stateMachine states;

void stateHandler() {
    while(true) {
        // Drive state handler
        if(states.driveStateIs(states.TWO_MOTOR)) {
            drivePTO.set_value(false);  // piston retracted, 2 motor mode
        }
        else if(states.driveStateIs(states.SIX_MOTOR)) {
            drivePTO.set_value(true);   // piston expanded, 6 motor mode
        }


        pros::delay(20);
    }
    // return(0);
}
