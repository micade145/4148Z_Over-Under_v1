#ifndef PUNCHER_H
#define PUNCHER_H
#include "main.h"
#include <string>

// Puncher contstants
extern int SHORT_PULLBACK_TICKS;
extern int MID_PULLBACK_TICKS;
extern int LONG_PULLBACK_TICKS;
extern int PUNCHER_OPEN_THRESHOLD;
extern int PUNCHER_CLOSE_THRESHOLD;
extern int PUNCHER_PAUSE_THRESHOLD;
extern int PUNCHER_PULLBACK_THRESHOLD;
extern int PUNCHER_PULLBACK_TIMEOUT;

// Puncher variables
extern int puncherOpenCount;
extern int puncherCloseCount;
extern int puncherPauseCount;
extern int puncherPullbackCount;

extern int punchPullback;

// Matchload variables
extern int fireCount;
extern int fireTarget;


// Helper functions
extern void setPuncher(int puncherVolt);
extern void setPuncherBrakeMode(pros::motor_brake_mode_e puncherBrakeMode);
extern void stopPuncher(pros::motor_brake_mode_e puncherBrakeMode);

// Puncher 
extern void firePuncher(int numTimes, int newPullback);
extern void setMatchload(int numTimes, bool waitForCompletion);
extern void matchloadOpControl();
extern bool matchloadState;

extern void puncherTask();

// Opcontrol function
extern void puncherOpControl();
extern void puncherAngleOpControl();

#endif