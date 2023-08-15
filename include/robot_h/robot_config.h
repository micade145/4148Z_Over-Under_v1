#ifndef ROBOT_CONFIG_H
#define ROBOT_CONFIG_H
#include "main.h"

// Alliance color 
extern bool isRed;

// Constants
// extern double SIDE_ENC_OFFSET;

// Robot
extern pros::Controller controller;

// Drive Motors
extern pros::Motor leftFrontDrive;
extern pros::Motor leftMidDrive;
extern pros::Motor leftBackDrive;
extern pros::Motor rightFrontDrive;
extern pros::Motor rightMidDrive;
extern pros::Motor rightBackDrive;

// Drive Motor Groups
extern pros::Motor_Group leftDrive;
extern pros::Motor_Group rightDrive;

// Misc Motors
extern pros::Motor rightIntake;
extern pros::Motor leftIntake;

// // Sensors
// extern pros::Imu inertial;
// extern pros::Vision vision;
// extern pros::Rotation frontEnc;
// extern pros::Rotation sideEnc;

// // Pneumatics (Digital I/O)
extern pros::ADIDigitalOut drivePTO;
// extern pros::ADIDigitalOut leftWing;
// extern pros::ADIDigitalOut rightWing;
// extern pros::ADIDigitalOut leftParkingBrake;
// extern pros::ADIDigitalOut rightParkingBrake;
// extern pros::ADIDigitalOut verticalAngler;
// extern pros::ADIDigitalOut tilterAngler;

#endif