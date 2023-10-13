#include "robot_config.h"

// Alliance color 
bool isRed = false;

// Robot
pros::Controller controller(pros::E_CONTROLLER_MASTER);
pros::Controller controller2(pros::E_CONTROLLER_PARTNER);

// Drive Motors
pros::Motor leftFrontDrive(2, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_COUNTS);     // BASE DRIVE
pros::Motor leftMidDrive(3, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_COUNTS);      // PTO MOTOR
pros::Motor leftBackDrive(4, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_COUNTS);      // PTO MOTOR
pros::Motor rightFrontDrive(9, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_DEGREES);  // BASE DRIVE
pros::Motor rightMidDrive(8, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_COUNTS);      // PTO MOTOR
pros::Motor rightBackDrive(7, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_COUNTS);    // PTO MOTOR

// Drive Motor Groups
// pros::Motor_Group leftFullDrive({leftFrontDrive, leftMidDrive, leftBackDrive});
// pros::Motor_Group rightFullDrive({rightFrontDrive, rightMidDrive, rightBackDrive});
pros::Motor_Group ptoLeftSide({leftMidDrive, leftBackDrive});
pros::Motor_Group ptoRightSide({rightMidDrive, rightBackDrive});

// Other motors
pros::Motor puncher(17, pros::E_MOTOR_GEAR_RED, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor leftIntake(1, true);
pros::Motor rightIntake(10, false);

// Sensors
pros::Imu inertial(16);
// pros::Vision vision;
pros::Rotation frontEnc(6, true);       // Main bot: 6 - REVERSED; Mini bot: NORMAL
// pros::Rotation sideEnc(17, false);      // not in use
pros::Rotation puncherEnc(18, true);    // REVERSED

// Digital I/O                                          Digital Expander - PORT 5
pros::ADIDigitalOut drivePTO({5, 'A'}, false);          // PORT 5A 
pros::ADIDigitalOut tilterAngler({5, 'B'}, false);      // PORT 5B
pros::ADIDigitalOut verticalAngler({5, 'C'}, false);    // PORT 5C
pros::ADIDigitalOut leftWing({5, 'D'}, false);          // PORT 5D
pros::ADIDigitalOut rightWing({5, 'E'}, false);         // PORT 5E
pros::ADIDigitalOut leftParkingBrake({5, 'F'}, false);  // PORT 5F
pros::ADIDigitalOut rightParkingBrake({5, 'G'}, false); // PORT 5G
pros::ADIDigitalIn puncherLimitSwitch({5, 'H'});        // PORT 5H

pros::ADIDigitalOut sideClimb('H', false);              // PORT H

// pros::ADIDigitalOut stick('H', false);
