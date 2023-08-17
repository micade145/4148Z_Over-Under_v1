#ifndef ROBOT_STATES_H
#define ROBOT_STATES_H
#include "main.h"

struct stateMachine{
private:
public:
    // Subsystem states
    enum drive_state {TWO_MOTOR, SIX_MOTOR} driveState, oldDriveState;
    enum intake_state {INTAKING, OPEN, CLOSED} intakeState, oldIntakeState;
    enum puncher_state {ONE_MOTOR_MODE, FIVE_MOTOR_MODE, FIRE, SHORT_PULLBACK, LONG_PULLBACK, PULLED_BACK} puncherState, oldPuncherState;
    enum puncher_angle_state {STEEP, MID, FLAT, DOWN} puncherAngleState, oldPuncherAngleState;
    enum wing_state {OUT, STOWED} wingState, oldWingState;
    enum parking_brake_state {BRAKE_ON, BRAKE_OFF} parkingBrakeState, oldParkingBrakeState;

    // State changed flags
    bool driveStateChanged() {return(oldDriveState != driveState);}
    bool intakeStateChanged() {return(oldIntakeState != intakeState);}
    bool puncherStateChanged() {return(oldPuncherState != puncherState);}
    bool puncherAngleStateChanged() {return(oldPuncherAngleState != puncherAngleState);}
    bool wingStateChanged() {return(oldWingState != wingState);}
    bool parkingBrakeStateChanged() {return(oldParkingBrakeState != parkingBrakeState);}

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

// Main states object
extern stateMachine states;

// Task to handle all states
extern void stateHandler();

#endif