#ifndef PUNCHER_H
#define PUNCHER_H
#include "main.h"

// Helper functions
extern void setPuncher(int puncherVolt);
extern void stopPuncher(pros::motor_brake_mode_e_t puncherBrakeMode);

// Opcontrol function
extern void puncherOpControl();

#endif