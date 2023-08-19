#ifndef PUNCHER_H
#define PUNCHER_H
#include "main.h"

// Puncher contstants
extern int SHORT_PULLBACK_TICKS;
extern int MID_PULLBACK_TICKS;
extern int LONG_PULLBACK_TICKS;
extern int PUNCHER_OPEN_THRESHOLD;
extern int PUNCHER_CLOSE_THRESHOLD;

// Puncher variables
extern int puncherOpenCount;
extern int puncherCloseCount;
extern int puncherPauseCount;

// Constants

// Helper functions
extern void setPuncher(int puncherVolt);
extern void stopPuncher(pros::motor_brake_mode_e_t puncherBrakeMode);

// Puncher 
extern void puncherTask();

// Opcontrol function
extern void puncherOpControl();
extern void puncherAngleOpControl();

#endif