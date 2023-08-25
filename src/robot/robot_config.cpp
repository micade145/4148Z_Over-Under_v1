#include "robot_h/robot_config.h"

// Alliance color 
bool isRed = false;

// Constants
// double SIDE_ENC_OFFSET;

// Robot
pros::Controller controller(pros::E_CONTROLLER_MASTER);
pros::Controller controller2(pros::E_CONTROLLER_PARTNER);

// Drive Motors
pros::Motor leftFrontDrive(2, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_COUNTS);    // BASE DRIVE
pros::Motor leftMidDrive(3, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_COUNTS);     // PTO
pros::Motor leftBackDrive(4, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_COUNTS);    // PTO
pros::Motor rightFrontDrive(9, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_DEGREES);   // BASE DRIVE
pros::Motor rightMidDrive(8, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_COUNTS);    // PTO
pros::Motor rightBackDrive(7, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_COUNTS);   // PTO

// Drive Motor Groups
// pros::Motor_Group leftFullDrive({leftFrontDrive, leftMidDrive, leftBackDrive});
// pros::Motor_Group rightFullDrive({rightFrontDrive, rightMidDrive, rightBackDrive});
pros::Motor_Group ptoLeftSide({leftMidDrive, leftBackDrive});
pros::Motor_Group ptoRightSide({rightMidDrive, rightBackDrive});

// Other motors
pros::Motor puncher(6, pros::E_MOTOR_GEAR_RED, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor leftIntake(1, true);
pros::Motor rightIntake(10, false);

// // Sensors
pros::Imu inertial(5);
// pros::Vision vision;
pros::Rotation puncherEnc(17, false);
pros::Rotation frontEnc(16, false);
// pros::Rotation sideEnc;

// // Pneumatics (Digital I/O)
pros::ADIDigitalOut drivePTO('A', false);
pros::ADIDigitalOut verticalAngler('B', true);
pros::ADIDigitalOut tilterAngler('C', false);
pros::ADIDigitalOut leftWing('D', false);
pros::ADIDigitalOut rightWing('E', false);
pros::ADIDigitalOut leftParkingBrake('F', false);
pros::ADIDigitalOut rightParkingBrake('G', false);
pros::ADIDigitalOut stick('H', false);

