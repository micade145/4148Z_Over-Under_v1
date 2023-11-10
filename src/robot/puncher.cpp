#include "robot_h/puncher.h"

// Motor encoder pullback constants
// int SHORT_PULLBACK_TICKS = 2500;    // Puncher just behind 5by structure
// int MID_PULLBACK_TICKS = 3900;      // Midway between short and long
// int LONG_PULLBACK_TICKS = 5250;     // Puncher on last few rack teeth

// Rotation sensor pullback constants
int SHORT_PULLBACK_TICKS = 50000;   // In centidegrees (100 * degrees) // 50000
int MID_PULLBACK_TICKS = 85000;     // In centidegrees (100 * degrees) // 78000
int LONG_PULLBACK_TICKS = 110000;    // In centidegrees (100 * degrees) // 110000

// Threshold constants
int PUNCHER_OPEN_THRESHOLD = 80; // 80 ms         // 4 iterations to release puncher (20ms loop * 10 = 200ms)
int PUNCHER_PAUSE_THRESHOLD = 100; // 100 ms       // 5 iterations to pause puncher when open (20ms loop * 10 = 200ms)
int PUNCHER_CLOSE_THRESHOLD = 80; // 80 ms       // 4 iterations to close puncher (20ms loop * 7 = 140ms)
int PUNCHER_PULLBACK_TIMEOUT = 2000; // 2000 ms
int PUNCHER_PULLBACK_THRESHOLD = 2500;  // 2500 - How close we want to get to the pullback value before stopping the puncher (to mitigate overshoot)

// Puncher variables
int puncherOpenCount = 0;
int puncherCloseCount = 0;
int puncherPauseCount = 0;
int puncherPullbackCount = 0;

// Matchload variables
int fireCount = 0;
int fireTarget = 0;

// Helper functions
void setPuncher(int puncherVolt) {
    puncher.move(puncherVolt);
    // PTO conditional
    if(states.driveStateIs(stateMachine::drive_state::TWO_MOTOR)) {
        if(puncherVolt >= 0) {
        // Use 4 PTO motors to pull back puncher but not release
        ptoLeftSide.move(puncherVolt);
        ptoRightSide.move(puncherVolt);
        }
    }
    // use this if we only want to use 100rpm on pto mode
    // if(states.driveStateIs(stateMachine::drive_state::SIX_MOTOR)) {
    //     puncher.move(puncherVolt);
    // }
}
void setPuncherBrakeMode(pros::motor_brake_mode_e puncherBrakeMode) {
    puncher.set_brake_mode(puncherBrakeMode);
    if(states.driveStateIs(stateMachine::drive_state::TWO_MOTOR)) {
        ptoLeftSide.set_brake_modes(puncherBrakeMode);
        ptoRightSide.set_brake_modes(puncherBrakeMode);
    }
}
void stopPuncher(pros::motor_brake_mode_e puncherBrakeMode) {
    setPuncherBrakeMode(puncherBrakeMode);
    puncher.brake();
    if(states.driveStateIs(stateMachine::drive_state::TWO_MOTOR)) {
        // Stop 4 drive motors alongside puncher motor
        ptoLeftSide.brake();
        ptoRightSide.brake();
    }
}

// void firePuncher(int numTimes, int newPullback) { // bad
//     if(newPullback == 1) {
//         states.defaultPullback = stateMachine::puncher_state::SHORT_PULLBACK;
//     }
//     else if(newPullback == 2) {
//         states.defaultPullback = stateMachine::puncher_state::MID_PULLBACK;
//     }
//     else {
//         states.defaultPullback = stateMachine::puncher_state::LONG_PULLBACK;
//     }

//     for(int i = 0; i < numTimes; i++) {
//         states.setPuncherState(stateMachine::puncher_state::FIRE);
//         while(!(states.puncherStateIs(stateMachine::puncher_state::PULLED_BACK))) {
//             pros::delay(5);
//         }
//     }
// }

void setMatchload(int numTimes, bool waitForCompletion) {
    fireCount = 0;
    fireTarget = numTimes;
    matchloadState = true;
    if(waitForCompletion) 
    {
        while(fireCount < fireTarget) {pros::delay(5);}
        matchloadState = false;
        pros::delay(50);
    }
}

// void firePuncher(int numTimes) {
//     matchloadState = true;
//     while(fireCount < numTimes) {
//         pros::delay(5);
//     }
//     matchloadState = false;
//     fireCount = 0;
// }


bool matchloadState = false;
void matchloadOpControl() {
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
        matchloadState = !matchloadState;
        if(matchloadState) {
            states.setDriveState(stateMachine::drive_state::TWO_MOTOR);
            shakeRobot();
        }
        else {
            shakeRobot();
        }
        controller.rumble("-");
    }
}

// Opcontrol functions
int punchPullback = 1;
int lastPunchPullback = 1;
int maxPullback = 3;
void puncherOpControl() {
    // Fires puncher
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
        if(states.puncherStateIs(stateMachine::puncher_state::PULLED_BACK)) {
            states.setPuncherState(stateMachine::puncher_state::FIRE);
        }
    }
    // Button to increment punchPullback
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
        if(states.puncherAngleStateIs(stateMachine::puncher_angle_state::STEEP)) {
            maxPullback = 2;
        }
        else {
            maxPullback = 3;
        }
        if((punchPullback + 1) <= maxPullback) {
            punchPullback ++;
        }
    }
    if(displayInfo) {pros::screen::print(TEXT_MEDIUM_CENTER, 9, "punchPullback: %d, last: %d", punchPullback, lastPunchPullback);}

    // Assigns puncher pullback to respective punchPullback (1 = (Default) SHORT, 2 = MID, 3 = LONG)
    if(lastPunchPullback != punchPullback) {
        if(punchPullback == 2) {
            puncherPullbackCount = 0;
            states.setPuncherState(stateMachine::puncher_state::MID_PULLBACK);
            lastPunchPullback = punchPullback;
        }
        else if(punchPullback == 3) {
            puncherPullbackCount = 0;
            states.setPuncherState(stateMachine::puncher_state::LONG_PULLBACK);
            lastPunchPullback = punchPullback;
        }
    }
    // Resets punchPullback counter to new state when we auto pullback 
    if(states.puncherStateIs(stateMachine::puncher_state::SHORT_PULLBACK)) {
        punchPullback = lastPunchPullback = 1;
    }
    else if(states.puncherStateIs(stateMachine::puncher_state::MID_PULLBACK)) {
        punchPullback = lastPunchPullback = 2;
    }
    else if(states.puncherStateIs(stateMachine::puncher_state::LONG_PULLBACK)) {
        punchPullback = lastPunchPullback = 3;
    }
}

int punchAngle = 1;
int lastPunchAngle = 1;
int maxPunchAngle = 4;
bool downAngle = false;
void puncherAngleOpControl() {
    // Buttons to increment punchAngle up and down
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
        // Limit max puncher angle 
        punchPullback == 3 ? maxPunchAngle = 3 : maxPunchAngle = 4;
        // Only increment if punch anlge it will be less than / equal to max 
        if((punchAngle + 1) <= maxPunchAngle) {
            punchAngle ++;
        }
    }
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
        punchAngle --;
        if(punchAngle < 1) {punchAngle = 1;}
    }

    // Button to switch between 1 (down) and 3 (mid) angles
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
        // If angle is down, then downAngle = true
        states.puncherAngleStateIs(stateMachine::puncher_angle_state::DOWN) ? downAngle = true : downAngle = false;
        // If down angle, toggle to mid angle; else toggle to down angle
        downAngle ? punchAngle = 3 : punchAngle = 1;
    }

    // Assigns puncher angle to respective punchAngle (1 = DOWN, 2 = FLAT, 3 = MID, 4 = STEEP)
    if(lastPunchAngle != punchAngle) {
        if(punchAngle == 1) {
            states.setPuncherAngleState(stateMachine::puncher_angle_state::DOWN);
            lastPunchAngle = punchAngle;
        }
        else if(punchAngle == 2) {
            states.setPuncherAngleState(stateMachine::puncher_angle_state::FLAT);
            lastPunchAngle = punchAngle;
        }
        else if(punchAngle == 3) {
            states.setPuncherAngleState(stateMachine::puncher_angle_state::MID);
            lastPunchAngle = punchAngle;
        }
        else if(punchAngle == 4) {
            states.setPuncherAngleState(stateMachine::puncher_angle_state::STEEP);
            lastPunchAngle = punchAngle;
        }
    }
}

// void puncherTask() {
//     puncher.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
//     while(true) {
//         if(states.puncherStateIs(stateMachine::puncher_state::FIRE)) {
//             pros::screen::print(TEXT_MEDIUM_CENTER, 5, "PUNCH FIRE");
//             puncher.move_relative(-25, 100);
//             // TODO program wait until 
//             // while(std::abs(puncher.get_target_position() - puncher.get_position()) > 5 ) {
//             //     pros::delay(5);
//             // }
//             // puncher.move_relative(25, 80);
//             // while(std::abs(puncher.get_target_position() - puncher.get_position()) > 5 ) {
//             //     pros::delay(5);
//             // }
//             puncher.tare_position();
//             states.setPuncherState(stateMachine::puncher_state::SHORT_PULLBACK);
//         }

//         // else statement necessary???
//         if(states.puncherStateIs(stateMachine::puncher_state::SHORT_PULLBACK)) {
//             pros::screen::print(TEXT_MEDIUM_CENTER, 5, "SHORT PULLBACK");
//             puncher.move_absolute(500, 100);
//             // TODO program wait until
//             // while( !((puncher.get_position() > 495) && (puncher.get_position() < 505)) ) {
//             //     pros::delay(5);
//             // }
//             // puncher.brake();
//             states.setPuncherState(stateMachine::puncher_state::PULLED_BACK);
//         }
//         else if(states.puncherStateIs(stateMachine::puncher_state::MID_PULLBACK)) {
//             pros::screen::print(TEXT_MEDIUM_CENTER, 5, "MID PULLBACK");
//             puncher.move_absolute(700, 100);
//             // TODO program wait until
//             // while( !((puncher.get_position() > 695) && (puncher.get_position() < 705)) ) {
//             //     pros::delay(5);
//             // }
//             // puncher.brake();
//             states.setPuncherState(stateMachine::puncher_state::PULLED_BACK);
//         }
//         else if(states.puncherStateIs(stateMachine::puncher_state::LONG_PULLBACK)) {
//             pros::screen::print(TEXT_MEDIUM_CENTER, 5, "LONG PULLBACK");
//             puncher.move_absolute(950, 100);
//             // TODO program wait until
//             // while( !((puncher.get_position() > 945) && (puncher.get_position() < 955)) ) {
//             //     pros::delay(5);
//             // }
//             // puncher.brake();
//             states.setPuncherState(stateMachine::puncher_state::PULLED_BACK);
//         }
//         if(states.puncherStateIs(stateMachine::puncher_state::PULLED_BACK)) {
//             pros::screen::print(TEXT_MEDIUM_CENTER, 5, "PULLED BACK");
//         }

//     if(states.puncherAngleStateChanged()) {
//         if(states.puncherAngleStateIs(stateMachine::puncher_angle_state::DOWN)) {
//             pros::screen::print(TEXT_MEDIUM_CENTER, 6, "ANGLE DOWN");
//             verticalAngler.set_value(true);
//             tilterAngler.set_value(true);
//         }
//         else if(states.puncherAngleStateIs(stateMachine::puncher_angle_state::FLAT)) {
//             pros::screen::print(TEXT_MEDIUM_CENTER, 6, "ANGLE FLAT");
//             verticalAngler.set_value(true);
//             tilterAngler.set_value(false);
//         }
//         else if(states.puncherAngleStateIs(stateMachine::puncher_angle_state::MID)) {
//             pros::screen::print(TEXT_MEDIUM_CENTER, 6, "ANGLE MID");
//             verticalAngler.set_value(false);
//             tilterAngler.set_value(true);
//         }
//         else if(states.puncherAngleStateIs(stateMachine::puncher_angle_state::STEEP)) {
//             pros::screen::print(TEXT_MEDIUM_CENTER, 6, "ANGLE STEEP");
//             verticalAngler.set_value(false);
//             tilterAngler.set_value(false);
//         }
//         states.oldPuncherAngleState = states.puncherAngleState;
//     }
//     }
//     pros::delay(20);
// }