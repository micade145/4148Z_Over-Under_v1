#include "myLib_h/robotStates.h"

stateMachine states;

void stateHandler() {
    while(true) {
        // Drive state handler
        if(states.driveStateIs(states.TWO_MOTOR)) {
            drivePTO.set_value(false);  // piston retracted, 2 motor mode

            leftFrontDrive.set_voltage_limit(1000);
            rightFrontDrive.set_voltage_limit(1000);
            pros::screen::set_eraser(COLOR_BLACK);
            pros::screen::erase();
            pros::screen::set_pen(COLOR_RED);
            pros::screen::fill_rect(5,5,240,200);
        }
        else if(states.driveStateIs(states.SIX_MOTOR)) {
            drivePTO.set_value(true);   // piston expanded, 6 motor mode

            leftFrontDrive.set_voltage_limit(10000);
            rightFrontDrive.set_voltage_limit(10000);
            pros::screen::set_eraser(COLOR_BLACK);
            pros::screen::erase();
            pros::screen::set_pen(COLOR_BLUE);
            pros::screen::fill_rect(5,5,240,200);
        }

        pros::delay(20);
    }
    // return(0);
}
