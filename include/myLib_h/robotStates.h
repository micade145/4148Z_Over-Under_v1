#ifndef ROBOT_STATES_H
#define ROBOT_STATES_H
#include "main.h"

struct stateMachine{
private:

public:
    enum drive_state {TWO_MOTOR, SIX_MOTOR} driveState;
    enum intake_state {CLOSED, OPEN, INTAKING} intakeState, newIntakeState;
    enum puncher_state {FIRE, PULLING_BACK, PULLED_BACK} puncherState, newPuncherState;
    enum puncher_angle_state {STEEP, MID, FLAT, DOWN} puncherAngleState, newPuncherAngleState;
    enum wing_state {OUT, STOWED} wingState, newWingState;
    enum parking_brake_state {BRAKE_ON, BRAKE_OFF} parkingBrakeState, newParkingBrakeState;

    

    void setDriveState(drive_state s) {driveState = s;}
    int getDriveState() {return driveState;}
    bool driveStateIs(drive_state s) {
        return(s == driveState);
    }
    

    void setIntakeState(intake_state s) {intakeState = s;}
    int getIntakeState() {return intakeState;}

    void setPuncherState(puncher_state s) {puncherState = s;}
    int getPuncherState() {return puncherState;}

    void setPuncherAngleState(puncher_angle_state s) {puncherAngleState = s;}
    int getPuncherAnglerState() {return puncherAngleState;}

    void setWingState(wing_state s) {wingState = s;}
    int getWingState() {return wingState;}

    void setParkingBrakeState(parking_brake_state s) {parkingBrakeState = s;}
    int getParkingBrakeState() {return parkingBrakeState;}
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