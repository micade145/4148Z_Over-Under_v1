#include "myLib_h/robotStates.h"

stateMachine states;

void stateHandler() {
    while(true) {
        // Drive state handler
        if(states.driveStateIs(states.TWO_MOTOR)) {
            drivePTO.set_value(false);  // piston retracted, 2 motor mode
            // Test
            leftFrontDrive.set_voltage_limit(1000);
            rightFrontDrive.set_voltage_limit(1000);
            pros::screen::set_eraser(COLOR_BLACK);
            pros::screen::erase();
            pros::screen::set_pen(COLOR_RED);
            pros::screen::fill_rect(5,5,240,200);
        }
        else if(states.driveStateIs(states.SIX_MOTOR)) {
            drivePTO.set_value(true);   // piston expanded, 6 motor mode
            // Test
            leftFrontDrive.set_voltage_limit(10000);
            rightFrontDrive.set_voltage_limit(10000);
            pros::screen::set_eraser(COLOR_BLACK);
            pros::screen::erase();
            pros::screen::set_pen(COLOR_BLUE);
            pros::screen::fill_rect(5,5,240,200);
        }

        // Intake state handler
        if(states.intakeStateIs(stateMachine::intake_state::INTAKING)) {
            spinIntake(127);
            closeCount = openCount = 0;
            pros::screen::print(TEXT_MEDIUM_CENTER, 3, "INTAKING");
        }
        else if(states.intakeStateIs(stateMachine::intake_state::OPEN)) {
            spinIntake(-65);
            if(openCount > INTAKE_OPEN_THRESHOLD) {
                stopIntake(pros::E_MOTOR_BRAKE_HOLD);
            }
            openCount++;
            closeCount = 0;
            pros::screen::print(TEXT_MEDIUM_CENTER, 3, "OPEN");
        }
        else if(states.intakeStateIs(stateMachine::intake_state::CLOSED)) {
            spinIntake(65);
            if(closeCount > INTAKE_CLOSE_THRESHOLD) {
                stopIntake(pros::E_MOTOR_BRAKE_HOLD);
            }
            closeCount++;
            openCount = 0;
            pros::screen::print(TEXT_MEDIUM_CENTER, 3, "CLOSED");
        }

        pros::delay(20);
    }
    // return(0);
}
