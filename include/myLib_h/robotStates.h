#ifndef ROBOT_STATES_H
#define ROBOT_STATES_H
#include "main.h"

struct stateMachine{
private:

public:
    // Subsystem states
    enum drive_state {TWO_MOTOR, SIX_MOTOR} driveState;
    enum intake_state {INTAKING, OPEN, CLOSED} intakeState;
    enum puncher_state {ONE_MOTOR_MODE, FIVE_MOTOR_MODE, FIRE, SHORT_PULLBACK, LONG_PULLBACK, PULLED_BACK} puncherState, newPuncherState;
    enum puncher_angle_state {STEEP, MID, FLAT, DOWN} puncherAngleState, newPuncherAngleState;
    enum wing_state {OUT, STOWED} wingState, newWingState;
    enum parking_brake_state {BRAKE_ON, BRAKE_OFF} parkingBrakeState, newParkingBrakeState;

    // Drive
    void setDriveState(drive_state s) {driveState = s;}
    int getDriveState() {return driveState;}
    bool driveStateIs(drive_state s) {return(s == driveState);}

    // Intake
    void setIntakeState(intake_state s) {intakeState = s;}
    int getIntakeState() {return intakeState;}
    bool intakeStateIs(intake_state s) {return(s == intakeState);}

    // Puncher
    void setPuncherState(puncher_state s) {puncherState = s;}
    int getPuncherState() {return puncherState;}
    bool puncherStateIs(puncher_state s) {return(s == puncherState);}

    // Puncher angle
    void setPuncherAngleState(puncher_angle_state s) {puncherAngleState = s;}
    int getPuncherAnglerState() {return puncherAngleState;}
    bool puncherAngleStateIs(puncher_angle_state s) {return(s == puncherAngleState);}

    // Wing
    void setWingState(wing_state s) {wingState = s;}
    int getWingState() {return wingState;}
    bool wingStateIs(wing_state s) {return(s == wingState);}

    // Parking brake
    void setParkingBrakeState(parking_brake_state s) {parkingBrakeState = s;}
    int getParkingBrakeState() {return parkingBrakeState;}
    bool parkingBrakeStateIs(parking_brake_state s) {return(s == parkingBrakeState);}
};

extern stateMachine states;

extern void stateHandler();


// stateMachine states;

// Drive States (PTO)
// enum driveState{TWO_MOTOR, SIX_MOTOR};

// // Intake States
// enum intakeState{CLOSED, OPEN, INTAKING};

// // Puncher States
// enum puncherState{FIRE, PULLING_BACK, PULLED_BACK};
// enum puncherAngle{HIGH, MID, FLAT, DOWN};

// // Wing States
// enum wingState{OUT, STOWED};

// // Parking Brake States
// enum parkingBrakeState{BRAKE_ON, BRAKE_OFF};


#endif