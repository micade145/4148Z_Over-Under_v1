#include "robot_header/drive.h"

// Helper function
void setDrive(int leftVolt, int rightVolt);

// Driver control functions 
extern void splitArcade();
extern void curveSplitArcade();

// Drive brake modes
extern void driveCoast();
extern void driveBrake();
extern void driveHold();