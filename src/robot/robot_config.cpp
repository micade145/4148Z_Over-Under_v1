#include "robot_h/robot_config.h"

// Alliance color 
bool isRed = false;

// Constants
// double SIDE_ENC_OFFSET;

// Robot
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// Drive Motors
pros::Motor leftFrontDrive(9, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_COUNTS);
// pros::Motor leftMidDrive(2, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_COUNTS);
// pros::Motor leftBackDrive(3, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor rightFrontDrive(10, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_COUNTS);
// pros::Motor rightMidDrive(5, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_COUNTS);
// pros::Motor rightBackDrive(6, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_COUNTS);

// Drive Motor Groups
// pros::Motor_Group leftDrive({leftFrontDrive, leftMidDrive, leftBackDrive});
// pros::Motor_Group rightDrive({rightFrontDrive, rightMidDrive, rightBackDrive});

// Misc Motors
pros::Motor rightIntake(7, false);
pros::Motor leftIntake(8, false);

// // Sensors
// pros::Imu inertial;
// pros::Vision vision;
// pros::Rotation frontEnc;
// pros::Rotation sideEnc;

// // Pneumatics (Digital I/O)
pros::ADIDigitalOut drivePTO('A', false);
// pros::ADIDigitalOut leftWing;
// pros::ADIDigitalOut rightWing;
// pros::ADIDigitalOut leftParkingBrake;
// pros::ADIDigitalOut rightParkingBrake;
// pros::ADIDigitalOut verticalAngler;
// pros::ADIDigitalOut tilterAngler;
