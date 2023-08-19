#ifndef PUNCHER_H
#define PUNCHER_H
#include "main.h"

// Helper functions
extern void setPuncher(int puncherVolt);
extern void stopPuncher(pros::motor_brake_mode_e_t puncherBrakeMode);

// Puncher 
extern void puncherTask();

// Opcontrol function
extern void puncherOpControl();
extern void puncherAngleOpControl();

#endif