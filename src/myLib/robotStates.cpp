#include "myLib_h/robotStates.h"

stateMachine states;

void stateHandler() {
    while(true) {
    // Drive state handler
    if(states.driveStateChanged()) {
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
        states.oldDriveState = states.driveState;
    }

    // Intake state handler
    if(states.intakeStateChanged()) {
        if(states.intakeStateIs(stateMachine::intake_state::INTAKING)) {
            spinIntake(127);
            closeCount = openCount = 0;
            pros::screen::print(TEXT_MEDIUM_CENTER, 3, "INTAKING");
            states.oldIntakeState = states.intakeState;
        }
        else if(states.intakeStateIs(stateMachine::intake_state::OPEN)) {
            spinIntake(-65);
            if(openCount > INTAKE_OPEN_THRESHOLD) {
                stopIntake(pros::E_MOTOR_BRAKE_HOLD);
                states.oldIntakeState = states.intakeState;
            }
            openCount++;
            closeCount = 0;
            pros::screen::print(TEXT_MEDIUM_CENTER, 3, "OPEN");
        }
        else if(states.intakeStateIs(stateMachine::intake_state::CLOSED)) {
            spinIntake(65);
            if(closeCount > INTAKE_CLOSE_THRESHOLD) {
                stopIntake(pros::E_MOTOR_BRAKE_HOLD);
                states.oldIntakeState = states.intakeState;
            }
            closeCount++;
            openCount = 0;
            pros::screen::print(TEXT_MEDIUM_CENTER, 3, "CLOSED");
        }
    }

    // Puncher state handler
    if(states.puncherStateChanged()) {
        if(states.puncherStateIs(stateMachine::puncher_state::FIVE_MOTOR_MODE)) {
           if(states.puncherStateIs(stateMachine::puncher_state::FIRE)) {

            }
            else if(states.puncherStateIs(stateMachine::puncher_state::SHORT_PULLBACK)) {
                // need pullback to be asynchronous
                // may want to outsource pullback to a seperate PID task and set target here
            }
            else if(states.puncherStateIs(stateMachine::puncher_state::LONG_PULLBACK)) {
                
            }
            else if(states.puncherStateIs(stateMachine::puncher_state::PULLED_BACK)) {
                
            } 
        }
        else if(states.puncherStateIs(stateMachine::puncher_state::ONE_MOTOR_MODE)) {
            if(states.puncherStateIs(stateMachine::puncher_state::FIRE)) {

            }
            else if(states.puncherStateIs(stateMachine::puncher_state::SHORT_PULLBACK)) {

            }
            else if(states.puncherStateIs(stateMachine::puncher_state::LONG_PULLBACK)) {
                
            }
            else if(states.puncherStateIs(stateMachine::puncher_state::PULLED_BACK)) {
                
            } 
        }
        states.oldPuncherState = states.puncherState;
    }

    // Puncher Angle state handler
    if(states.puncherAngleStateChanged()) {
        if(states.puncherAngleStateIs(stateMachine::puncher_angle_state::DOWN)) {
            verticalAngler.set_value(true);
            tilterAngler.set_value(true);
        }
        else if(states.puncherAngleStateIs(stateMachine::puncher_angle_state::FLAT)) {
            verticalAngler.set_value(true);
            tilterAngler.set_value(false);
        }
        else if(states.puncherAngleStateIs(stateMachine::puncher_angle_state::MID)) {
            verticalAngler.set_value(false);
            tilterAngler.set_value(true);
        }
        else if(states.puncherAngleStateIs(stateMachine::puncher_angle_state::STEEP)) {
            verticalAngler.set_value(false);
            tilterAngler.set_value(false);
        }
        states.oldPuncherAngleState = states.puncherAngleState;
    }
        
    // Wing state handler
    if(states.wingStateChanged()) {
        if(states.wingStateIs(stateMachine::wing_state::STOWED)) {
            leftWing.set_value(false);
            rightWing.set_value(false);
        }
        else if(states.wingStateIs(stateMachine::wing_state::OUT)) {
            leftWing.set_value(true);
            rightWing.set_value(true);
        }
        states.oldWingState = states.wingState;
    }

    // Parking brake state handler
    if(states.parkingBrakeStateChanged()) {
        if(states.parkingBrakeStateIs(stateMachine::parking_brake_state::BRAKE_OFF)) {
            leftParkingBrake.set_value(false);
            rightParkingBrake.set_value(false);
        }
        else if(states.parkingBrakeStateIs(stateMachine::parking_brake_state::BRAKE_ON)) {
            leftParkingBrake.set_value(true);
            rightParkingBrake.set_value(true);
        }
        states.oldParkingBrakeState = states.parkingBrakeState;
    }

    // necessary task delay - do not change
        pros::delay(20);
    }
}
