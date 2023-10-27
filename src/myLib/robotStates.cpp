#include "myLib_h/robotStates.h"

stateMachine states;

void stateHandler() {
    int loopDelay = 10;
    bool puncherClosePhase = false;
    // bool firstPuncherLoop = false;
    while(true) {
    // ******** Drive state handler ******** //
    if(states.driveStateChanged()) {
        if(states.driveStateIs(stateMachine::drive_state::TWO_MOTOR)) {
            if(displayInfo) {pros::screen::print(TEXT_MEDIUM, 6, "TWO MOTOR DRIVE");} 
            drivePTO.set_value(false);  // piston retracted: 2m drive, 5m puncher
            // controller.rumble("..");  
            controller.clear_line(2);
            controller.print(2, 0, "TWO MOTOR DRIVE");
                // shake robot to help disengage pto
            PUNCHER_PULLBACK_THRESHOLD = 6000;  // higher threshold to prevent overshoot
            
            // Colored box for debugging
            // pros::screen::set_eraser(COLOR_BLACK);
            // pros::screen::erase();
            // pros::screen::set_pen(COLOR_RED);
            // pros::screen::fill_rect(0, 0, 1000, 1000);
        }
        else if(states.driveStateIs(stateMachine::drive_state::SIX_MOTOR)) {
            if(displayInfo) {pros::screen::print(TEXT_MEDIUM_CENTER, 6, "SIX MOTOR DRIVE");}
            controller.rumble("--");
            controller.clear_line(2);
            controller.print(2, 0, "SIX MOTOR DRIVE");
            drivePTO.set_value(true);   // piston expanded: 6m drive, 1m puncher
                // shake robot to help engage pto
            PUNCHER_PULLBACK_THRESHOLD = 2500;  // default threshold

            // pros::screen::set_eraser(COLOR_BLACK);
            // pros::screen::erase();
            // pros::screen::set_pen(COLOR_BLUE);
            // pros::screen::fill_rect(0, 0, 1000, 1000);
        }
        states.oldDriveState = states.driveState;
    }

    // ******** Intake state handler ******** //
    if(states.intakeStateChanged()) {
        if(states.intakeStateIs(stateMachine::intake_state::INTAKING)) {
            spinIntake(127);
            closeCount = openCount = 0;
            if(displayInfo) {pros::screen::print(TEXT_MEDIUM_CENTER, 3, "INTAKING");}
            states.oldIntakeState = states.intakeState;
        }
        else if(states.intakeStateIs(stateMachine::intake_state::OPEN)) {
            spinIntake(-85);    // -65
            if(openCount > INTAKE_OPEN_THRESHOLD) {
                stopIntake(pros::E_MOTOR_BRAKE_BRAKE);
                openCount = 0;
                states.oldIntakeState = states.intakeState;
            }
            openCount += loopDelay;
            closeCount = 0;
            if(displayInfo) {pros::screen::print(TEXT_MEDIUM_CENTER, 3, "INTAKE OPEN");}
        }
        else if(states.intakeStateIs(stateMachine::intake_state::CLOSED)) {
            spinIntake(85); //65
            if(closeCount > INTAKE_CLOSE_THRESHOLD) {
                stopIntake(pros::E_MOTOR_BRAKE_BRAKE);
                closeCount = 0;
                states.oldIntakeState = states.intakeState;
            }
            closeCount += loopDelay;
            openCount = 0;
            if(displayInfo) {pros::screen::print(TEXT_MEDIUM_CENTER, 3, "INTAKE CLOSED");}
        }
    }

    // ******** Puncher state handler ******** //
    if(states.puncherStateChanged()) {
           if(states.puncherStateIs(stateMachine::puncher_state::FIRE)) {
                if(displayInfo) {pros::screen::print(TEXT_MEDIUM_CENTER, 4, "PUNCHER FIRED");}
                if(!puncherClosePhase) {    // Open (release)
                    puncher.move(-127);
                    puncherOpenCount += loopDelay;
                }
                if(puncherOpenCount >= PUNCHER_OPEN_THRESHOLD) {
                    puncherClosePhase = true;
                }
                if(puncherClosePhase) { // Pause, then close (re-engage)
                    puncherPauseCount += loopDelay;
                    if(puncherPauseCount >= PUNCHER_PAUSE_THRESHOLD) {
                        puncher.move(100); //80
                        puncherCloseCount += loopDelay;
                    }
                }
                if(puncherCloseCount >= PUNCHER_CLOSE_THRESHOLD) {  // Stop 
                    puncherClosePhase = false;
                    puncher.brake();
                    // puncher.move(10);
                    puncherEnc.reset_position();
                    puncher.tare_position();
                    puncherCloseCount = puncherOpenCount = puncherPauseCount = puncherPullbackCount = 0;
                    states.setPuncherState(states.defaultPullback); // auto pullback to default pullback
                    // states.setPuncherState(stateMachine::puncher_state::PULLED_BACK); // for testing release
                }
            }

            if(states.puncherStateIs(stateMachine::puncher_state::SHORT_PULLBACK)) {
                if(displayInfo) {pros::screen::print(TEXT_MEDIUM_CENTER, 5, "SHORT PULLBACK, Volt: %d", puncher.get_voltage());}
                setPuncher(127);
                if(puncherEnc.get_position() > (SHORT_PULLBACK_TICKS - PUNCHER_PULLBACK_THRESHOLD) || puncherPullbackCount >= PUNCHER_PULLBACK_TIMEOUT) {
                    // setPuncher(-5);
                    // pros::delay(100);
                    stopPuncher(pros::E_MOTOR_BRAKE_HOLD);
                    states.setPuncherState(stateMachine::puncher_state::PULLED_BACK);
                }
                puncherPullbackCount += loopDelay;
            }
            else if(states.puncherStateIs(stateMachine::puncher_state::MID_PULLBACK)) {
                if(displayInfo) {pros::screen::print(TEXT_MEDIUM_CENTER, 5, "MID PULLBACK, Volt: %d", puncher.get_voltage());}
                setPuncher(127);
                if(puncherEnc.get_position() > (MID_PULLBACK_TICKS - PUNCHER_PULLBACK_THRESHOLD) || puncherPullbackCount >= PUNCHER_PULLBACK_TIMEOUT) {
                    // setPuncher(-5);
                    // pros::delay(100);
                    stopPuncher(pros::E_MOTOR_BRAKE_HOLD);
                    states.setPuncherState(stateMachine::puncher_state::PULLED_BACK);
                }
                puncherPullbackCount += loopDelay;
            }
            else if(states.puncherStateIs(stateMachine::puncher_state::LONG_PULLBACK)) {
                if(displayInfo) {pros::screen::print(TEXT_MEDIUM_CENTER, 5, "LONG PULLBACK, Volt: %d", puncher.get_voltage());}
                setPuncher(127);
                if(puncherEnc.get_position() > (LONG_PULLBACK_TICKS - PUNCHER_PULLBACK_THRESHOLD) || puncherPullbackCount >= PUNCHER_PULLBACK_TIMEOUT) {
                    // setPuncher(-5);
                    // pros::delay(100);
                    stopPuncher(pros::E_MOTOR_BRAKE_HOLD);
                    states.setPuncherState(stateMachine::puncher_state::PULLED_BACK);
                }
                puncherPullbackCount += loopDelay;
            }
            if(states.puncherStateIs(stateMachine::puncher_state::PULLED_BACK)) {
                if(displayInfo) {pros::screen::print(TEXT_MEDIUM_CENTER, 4, "PULLED BACK");}
                puncherPullbackCount = 0;
                states.oldPuncherState = states.puncherState;
            }
    }

    // ******** Puncher Angle state handler ******** //
    if(states.puncherAngleStateChanged()) {
        if(states.puncherAngleStateIs(stateMachine::puncher_angle_state::DOWN)) {
            if(displayInfo) {pros::screen::print(TEXT_MEDIUM_CENTER, 6, "ANGLE DOWN");}
            verticalAngler.set_value(true);
            tilterAngler.set_value(true);
        }
        else if(states.puncherAngleStateIs(stateMachine::puncher_angle_state::FLAT)) {
            if(displayInfo) {pros::screen::print(TEXT_MEDIUM_CENTER, 6, "ANGLE FLAT");}
            verticalAngler.set_value(true);
            tilterAngler.set_value(false);
        }
        else if(states.puncherAngleStateIs(stateMachine::puncher_angle_state::MID)) {
            if(displayInfo) {pros::screen::print(TEXT_MEDIUM_CENTER, 6, "ANGLE MID");}
            verticalAngler.set_value(false);
            tilterAngler.set_value(true);
        }
        else if(states.puncherAngleStateIs(stateMachine::puncher_angle_state::STEEP)) {
            if(displayInfo) {pros::screen::print(TEXT_MEDIUM_CENTER, 6, "ANGLE STEEP");}
            verticalAngler.set_value(false);
            tilterAngler.set_value(false);
        }
        states.oldPuncherAngleState = states.puncherAngleState;
    }
        
    // ******** Wing state handler ******** //
    if(states.wingStateChanged()) {
        if(states.wingStateIs(stateMachine::wing_state::WINGS_STOWED)) {
            if(displayInfo) {pros::screen::print(TEXT_MEDIUM_CENTER, 7, "WINGS IN");}
            leftWing.set_value(false);
            rightWing.set_value(false);
        }
        else if(states.wingStateIs(stateMachine::wing_state::WINGS_OUT)) {
            if(displayInfo) {pros::screen::print(TEXT_MEDIUM_CENTER, 7, "WINGS OUT");}
            leftWing.set_value(true);
            rightWing.set_value(true);
        }
        else if(states.wingStateIs(stateMachine::wing_state::LEFT_OUT)) {
            if(displayInfo) {pros::screen::print(TEXT_MEDIUM_CENTER, 7, "LEFT WING OUT");}
            leftWing.set_value(true);
            rightWing.set_value(false);
        }
        else if(states.wingStateIs(stateMachine::wing_state::RIGHT_OUT)) {
            if(displayInfo) {pros::screen::print(TEXT_MEDIUM_CENTER, 7, "RIGHT WING OUT");}
            leftWing.set_value(false);
            rightWing.set_value(true);
        }
        states.oldWingState = states.wingState;
    }

    // ******** Parking brake state handler ******** //
    // if(states.parkingBrakeStateChanged()) {
    //     if(states.parkingBrakeStateIs(stateMachine::parking_brake_state::BRAKE_OFF)) {
    //         if(displayInfo) {pros::screen::print(TEXT_MEDIUM_CENTER, 8, "BRAKES OFF");}
    //         leftParkingBrake.set_value(false);
    //         rightParkingBrake.set_value(false);
    //         controller.rumble(".");
    //         // if(states.driveStateIs(stateMachine::drive_state::SIX_MOTOR)) {
    //         //     states.setDriveState(stateMachine::drive_state::TWO_MOTOR);
    //         // }
    //     }
    //     else if(states.parkingBrakeStateIs(stateMachine::parking_brake_state::BRAKE_ON)) {
    //         if(displayInfo) {pros::screen::print(TEXT_MEDIUM_CENTER, 8, "BRAKES ON");}
    //         leftParkingBrake.set_value(true);
    //         rightParkingBrake.set_value(true);
    //         controller.rumble(".");
    //         // if(states.driveStateIs(stateMachine::drive_state::TWO_MOTOR)) {
    //         //     states.setDriveState(stateMachine::drive_state::SIX_MOTOR);
    //         // }
    //     }
    //     states.oldParkingBrakeState = states.parkingBrakeState;
    // }
    // Drive Check for engaging Parking Brakes
    // if((std::fabs(leftFrontDrive.get_actual_velocity()) < DRIVE_BRAKE_THRESHOLD) || (std::fabs(rightFrontDrive.get_actual_velocity()) < DRIVE_BRAKE_THRESHOLD)) {
    //     brakeReady = true;
    // } 
    // else {
    //     brakeReady = false;
    // }

    // ******** Odometry ******** //
    if(pros::competition::is_autonomous()) {
        updatePosition();
    }

    // ******** Matchload ******** //
    while(matchloadState) {
        fireCount = 0;
        while(true) {
            // release
            setPuncher(-127);
            pros::delay(200);
            // puncher.move(127);
            setPuncher(127);
            
            // pullback
            pros::delay(100);
            puncherEnc.reset_position();
            // setPuncher(127);
            while(puncherEnc.get_position() < MID_PULLBACK_TICKS - 16000) { //|| puncherLimitSwitch.get_value() == false
                pros::delay(5);
            }
            fireCount++;

            if(!matchloadState) { // || fireCount >= fireTarget
                stopPuncher(pros::E_MOTOR_BRAKE_BRAKE);
                states.setPuncherState(stateMachine::puncher_state::PULLED_BACK);
                // fireCount = fireTarget = 0;
                // matchloadState = false;
                break;
            }
        }
    }

    // ******** DEBUG ******** //
    if(displayInfo) {
    pros::screen::print(TEXT_MEDIUM_CENTER, 10, "Drive Velo: %d", (leftFrontDrive.get_actual_velocity() + rightFrontDrive.get_actual_velocity()) / 2);
    pros::screen::print(TEXT_MEDIUM_CENTER, 11, "Brake Ready?: %s", brakeReady ? "true" : "false");
    pros::screen::print(TEXT_MEDIUM_CENTER, 5, "Puncher Enc: %d", puncherEnc.get_position());
    }
    
    // necessary task delay - do not change
    pros::delay(loopDelay);
    }
}
