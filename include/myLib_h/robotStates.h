#ifndef ROBOT_STATES_H
#define ROBOT_STATES_H
#include "main.h"

struct stateMachine{
private:
public:
    // Subsystem states
    enum drive_state {TWO_MOTOR, SIX_MOTOR} driveState, oldDriveState;
    enum intake_state {INTAKING, OPEN, CLOSED} intakeState, oldIntakeState;
    enum puncher_state {ONE_MOTOR_MODE, FIVE_MOTOR_MODE, FIRE, SHORT_PULLBACK, MID_PULLBACK, LONG_PULLBACK, PULLED_BACK} puncherState, oldPuncherState, defaultPullback = SHORT_PULLBACK;
    enum puncher_angle_state {STEEP, MID, FLAT, DOWN} puncherAngleState, oldPuncherAngleState;
    enum wing_state {OUT, STOWED} wingState, oldWingState;
    enum parking_brake_state {BRAKE_ON, BRAKE_OFF} parkingBrakeState, oldParkingBrakeState;
    // Drive auto states
    enum drive_auto_state{MOVE, TURN, MOVE_TO_POINT} driveAutoState;
    // Alliance color
    enum alliance_color {RED_ALLIANCE, BLUE_ALLIANCE} allianceColor, oldAllianceColor; 

    // Drive
    void setDriveState(drive_state s) {driveState = s;}
    // int getDriveState() {return driveState;}
    bool driveStateIs(drive_state s) {return(s == driveState);}
    bool driveStateChanged() {return(oldDriveState != driveState);}

    // Intake
    void setIntakeState(intake_state s) {intakeState = s;}
    // int getIntakeState() {return intakeState;}
    bool intakeStateIs(intake_state s) {return(s == intakeState);}
    bool intakeStateChanged() {return(oldIntakeState != intakeState);}

    // Puncher
    void setPuncherState(puncher_state s) {puncherState = s;}
    // int getPuncherState() {return puncherState;}
    bool puncherStateIs(puncher_state s) {return(s == puncherState);}
    bool puncherStateChanged() {return(oldPuncherState != puncherState);}

    // Puncher angle
    void setPuncherAngleState(puncher_angle_state s) {puncherAngleState = s;}
    // int getPuncherAnglerState() {return puncherAngleState;}
    bool puncherAngleStateIs(puncher_angle_state s) {return(s == puncherAngleState);}
    bool puncherAngleStateChanged() {return(oldPuncherAngleState != puncherAngleState);}

    // Wing
    void setWingState(wing_state s) {wingState = s;}
    // int getWingState() {return wingState;}
    bool wingStateIs(wing_state s) {return(s == wingState);}
    bool wingStateChanged() {return(oldWingState != wingState);}

    // Parking brake
    void setParkingBrakeState(parking_brake_state s) {parkingBrakeState = s;}
    // int getParkingBrakeState() {return parkingBrakeState;}
    bool parkingBrakeStateIs(parking_brake_state s) {return(s == parkingBrakeState);}
    bool parkingBrakeStateChanged() {return(oldParkingBrakeState != parkingBrakeState);}
    
    // Drive auto states
    void setDriveAutoState(drive_auto_state s) {driveAutoState = s;}
    bool driveAutoStateIs(drive_auto_state s) {return(s == driveAutoState);}

    // Alliance color
    void setAllianceColor(alliance_color s) {allianceColor = s;}
    bool allianceColorIs(alliance_color s) {return(s == allianceColor);}
    bool allianceColorChanged() {return(oldAllianceColor != allianceColor);}
};

// Main states object
extern stateMachine states;

// Task to handle all states
extern void stateHandler();

#endif