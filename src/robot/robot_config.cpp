#include "robot_h/robot_config.h"

// Alliance color 
bool isRed = false;

// Constants
// double SIDE_ENC_OFFSET;

// Robot
pros::Controller controller(pros::E_CONTROLLER_MASTER);
pros::Controller controller2(pros::E_CONTROLLER_PARTNER);

// Drive Motors
pros::Motor leftFrontDrive(9, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_COUNTS);    // BASE DRIVE
pros::Motor leftMidDrive(12, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_COUNTS);     // PTO
pros::Motor leftBackDrive(13, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_COUNTS);    // PTO
pros::Motor rightFrontDrive(10, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_COUNTS);   // BASE DRIVE
pros::Motor rightMidDrive(14, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_COUNTS);    // PTO
pros::Motor rightBackDrive(15, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_COUNTS);   // PTO

// Drive Motor Groups
// pros::Motor_Group leftFullDrive({leftFrontDrive, leftMidDrive, leftBackDrive});
// pros::Motor_Group rightFullDrive({rightFrontDrive, rightMidDrive, rightBackDrive});
pros::Motor_Group ptoLeftSide({leftMidDrive, leftBackDrive});
pros::Motor_Group ptoRightSide({rightMidDrive, rightBackDrive});

// Other motors
pros::Motor puncher(6, pros::E_MOTOR_GEAR_RED, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor rightIntake(8, false);
pros::Motor leftIntake(7, true);

// // Sensors
pros::Imu inertial(16);
// pros::Vision vision;
pros::Rotation puncherEnc(17, false);
pros::Rotation frontEnc(18, false);
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

