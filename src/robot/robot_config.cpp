#include "robot_header/robot_config.h"

// Alliance color 
bool isRed = false;

// Constants
// double SIDE_ENC_OFFSET;

// Robot
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// Drive Motors
pros::Motor leftFrontDrive;
pros::Motor leftMidDrive;
pros::Motor leftBackDrive;
pros::Motor rightFrontDrive;
pros::Motor rightMidDrive;
pros::Motor rightBackDrive;

// Drive Motor Groups
pros::Motor_Group leftDrive;
pros::Motor_Group rightDrive;

// Misc Motors
pros::Motor rightIntake;
pros::Motor leftIntake;

// // Sensors
// pros::Imu inertial;
// pros::Vision vision;
// pros::Rotation frontEnc;
// pros::Rotation sideEnc;

// // Pneumatics (Digital I/O)
// pros::ADIDigitalOut leftWing;
// pros::ADIDigitalOut rightWing;
// pros::ADIDigitalOut leftParkingBrake;
// pros::ADIDigitalOut rightParkingBrake;
// pros::ADIDigitalOut verticalAngler;
// pros::ADIDigitalOut tilterAngler;
