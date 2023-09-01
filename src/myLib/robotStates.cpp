#include "myLib_h/robotStates.h"

stateMachine states;
bool firstPuncherLoop = false;
bool puncherClosePhase = false;

void stateHandler() {
    while(true) {
    // Drive state handler
    if(states.driveStateChanged()) {
        if(states.driveStateIs(stateMachine::drive_state::TWO_MOTOR)) {
            pros::screen::print(TEXT_MEDIUM_CENTER, 2, "TWO MOTOR DRIVE");
            drivePTO.set_value(true);  // piston retracted, 2 motor mode
            // Colored box for debugging
            // pros::screen::set_eraser(COLOR_BLACK);
            // pros::screen::erase();
            // pros::screen::set_pen(COLOR_RED);
            // pros::screen::fill_rect(5,5,240,200);
        }
        else if(states.driveStateIs(stateMachine::drive_state::SIX_MOTOR)) {
            pros::screen::print(TEXT_MEDIUM_CENTER, 2, "SIX MOTOR DRIVE");
            drivePTO.set_value(false);   // piston expanded, 6 motor mode
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
            spinIntake(-85);    // -65
            if(openCount > INTAKE_OPEN_THRESHOLD) {
                stopIntake(pros::E_MOTOR_BRAKE_BRAKE);
                openCount = 0;
                states.oldIntakeState = states.intakeState;
            }
            openCount++;
            closeCount = 0;
            pros::screen::print(TEXT_MEDIUM_CENTER, 3, "INTAKE OPEN");
        }
        else if(states.intakeStateIs(stateMachine::intake_state::CLOSED)) {
            spinIntake(85); //65
            if(closeCount > INTAKE_CLOSE_THRESHOLD) {
                stopIntake(pros::E_MOTOR_BRAKE_BRAKE);
                closeCount = 0;
                states.oldIntakeState = states.intakeState;
            }
            closeCount++;
            openCount = 0;
            pros::screen::print(TEXT_MEDIUM_CENTER, 3, "INTAKE CLOSED");
        }
    }

    // Puncher state handler
    if(states.puncherStateChanged()) {
           if(states.puncherStateIs(stateMachine::puncher_state::FIRE)) {
                pros::screen::print(TEXT_MEDIUM_CENTER, 4, "PUNCHER FIRED");
                if(!puncherClosePhase) {
                    puncher.move(-127);
                    puncherOpenCount++;
                }
                if(puncherOpenCount > PUNCHER_OPEN_THRESHOLD) {
                    puncherClosePhase = true;
                }
                if(puncherClosePhase) {
                    puncher.move(10);
                    puncherCloseCount++;
                }
                if(puncherCloseCount > PUNCHER_CLOSE_THRESHOLD) {
                    puncherClosePhase = false;
                    puncher.brake();
                    puncherPauseCount++;
                }
                if(puncherPauseCount > 0) {
                    puncher.brake();
                    puncher.tare_position();
                    puncherEnc.reset();
                    puncherCloseCount = puncherOpenCount = puncherPauseCount = 0;
                    states.setPuncherState(states.defaultPullback);
                }
            }
            
            if(states.puncherStateIs(stateMachine::puncher_state::SHORT_PULLBACK)) {
                pros::screen::print(TEXT_MEDIUM_CENTER, 5, "SHORT PULLBACK");
                setPuncher(127);
                if(puncherEnc.get_position() > (SHORT_PULLBACK_TICKS - PUNCHER_PULLBACK_THRESHOLD)) {
                    stopPuncher(pros::E_MOTOR_BRAKE_HOLD);
                    states.setPuncherState(stateMachine::puncher_state::PULLED_BACK);
                }
            }
            else if(states.puncherStateIs(stateMachine::puncher_state::MID_PULLBACK)) {
                pros::screen::print(TEXT_MEDIUM_CENTER, 5, "MID PULLBACK");
                setPuncher(127);
                if(puncherEnc.get_position() > (MID_PULLBACK_TICKS - PUNCHER_PULLBACK_THRESHOLD)) {
                    stopPuncher(pros::E_MOTOR_BRAKE_HOLD);
                    states.setPuncherState(stateMachine::puncher_state::PULLED_BACK);
                }
            }
            else if(states.puncherStateIs(stateMachine::puncher_state::LONG_PULLBACK)) {
                pros::screen::print(TEXT_MEDIUM_CENTER, 5, "LONG PULLBACK");
                setPuncher(127);
                if(puncherEnc.get_position() > (LONG_PULLBACK_TICKS - PUNCHER_PULLBACK_THRESHOLD)) {
                    stopPuncher(pros::E_MOTOR_BRAKE_HOLD);
                    states.setPuncherState(stateMachine::puncher_state::PULLED_BACK);
                }
            }
            if(states.puncherStateIs(stateMachine::puncher_state::PULLED_BACK)) {
                pros::screen::print(TEXT_MEDIUM_CENTER, 4, "PULLED BACK");
                firstPuncherLoop = false;
                states.oldPuncherState = states.puncherState;
            } 
    }

    // Puncher Angle state handler
    if(states.puncherAngleStateChanged()) {
        if(states.puncherAngleStateIs(stateMachine::puncher_angle_state::DOWN)) {
            pros::screen::print(TEXT_MEDIUM_CENTER, 6, "ANGLE DOWN");
            verticalAngler.set_value(true);
            tilterAngler.set_value(true);
        }
        else if(states.puncherAngleStateIs(stateMachine::puncher_angle_state::FLAT)) {
            pros::screen::print(TEXT_MEDIUM_CENTER, 6, "ANGLE FLAT");
            verticalAngler.set_value(true);
            tilterAngler.set_value(false);
        }
        else if(states.puncherAngleStateIs(stateMachine::puncher_angle_state::MID)) {
            pros::screen::print(TEXT_MEDIUM_CENTER, 6, "ANGLE MID");
            verticalAngler.set_value(false);
            tilterAngler.set_value(true);
        }
        else if(states.puncherAngleStateIs(stateMachine::puncher_angle_state::STEEP)) {
            pros::screen::print(TEXT_MEDIUM_CENTER, 6, "ANGLE STEEP");
            verticalAngler.set_value(false);
            tilterAngler.set_value(false);
        }
        states.oldPuncherAngleState = states.puncherAngleState;
    }
        
    // Wing state handler
    if(states.wingStateChanged()) {
        if(states.wingStateIs(stateMachine::wing_state::STOWED)) {
            pros::screen::print(TEXT_MEDIUM_CENTER, 7, "WINGS IN");
            leftWing.set_value(false);
            rightWing.set_value(false);
        }
        else if(states.wingStateIs(stateMachine::wing_state::OUT)) {
            pros::screen::print(TEXT_MEDIUM_CENTER, 7, "WINGS OUT");
            leftWing.set_value(true);
            rightWing.set_value(true);
        }
        states.oldWingState = states.wingState;
    }

    // Parking brake state handler
    if(states.parkingBrakeStateChanged()) {
        if(states.parkingBrakeStateIs(stateMachine::parking_brake_state::BRAKE_OFF)) {
            pros::screen::print(TEXT_MEDIUM_CENTER, 8, "BRAKES OFF");
            leftParkingBrake.set_value(false);
            rightParkingBrake.set_value(false);
        }
        else if(states.parkingBrakeStateIs(stateMachine::parking_brake_state::BRAKE_ON)) {
            pros::screen::print(TEXT_MEDIUM_CENTER, 8, "BRAKES ON");
            leftParkingBrake.set_value(true);
            rightParkingBrake.set_value(true);
        }
        states.oldParkingBrakeState = states.parkingBrakeState;
    }
    if((std::fabs(leftFrontDrive.get_actual_velocity()) < DRIVE_BRAKE_THRESHOLD) || (std::fabs(rightFrontDrive.get_actual_velocity()) < DRIVE_BRAKE_THRESHOLD)) {
        brakeReady = true;
    } 
    else {
        brakeReady = false;
    }
    pros::screen::print(TEXT_MEDIUM_CENTER, 10, "Drive Velo: %d", (leftFrontDrive.get_actual_velocity() + rightFrontDrive.get_actual_velocity()) / 2);
    pros::screen::print(TEXT_MEDIUM_CENTER, 11, "Brake Ready?: %s", brakeReady ? "true" : "false");
    pros::screen::print(TEXT_MEDIUM_CENTER, 0, "Puncher Enc: %d", puncherEnc.get_position());
    
    // necessary task delay - do not change
    pros::delay(20);
    }
}
