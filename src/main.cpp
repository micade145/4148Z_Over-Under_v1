#include "main.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	// pros::lcd::initialize();
	// pros::lcd::set_text(1, "Hello PROS User!");
	// pros::lcd::register_btn1_cb(on_center_button);

	inertial.reset(false);

	// Initialize default states
	states.defaultPullback = stateMachine::puncher_state::MID_PULLBACK;
	states.setPuncherAngleState(stateMachine::puncher_angle_state::STEEP);
	states.setPuncherState(stateMachine::puncher_state::PULLED_BACK);
	states.setDriveState(stateMachine::drive_state::SIX_MOTOR);
	states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	states.setParkingBrakeState(stateMachine::parking_brake_state::BRAKE_OFF);
	states.setDriveAutoState(stateMachine::drive_auto_state::OFF);
	
	// Initialize puncher
	puncher.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	puncher.tare_position();

	// initGUI();
}
// pros::Task initRobot([] {inertial.reset(true);});

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
// Initialize tasks
pros::Task superstruct(stateHandler);
pros::Task autoMovement(autoMovementTask);
void autonomous() {
	// pros::Task trackPosition(updatePosition);
	resetOdomSensors();
	globalPose.setPoint(0.0, 0.0, 0);

	// states.setDriveAutoState(stateMachine::drive_auto_state::OFF);
	pros::delay(20);

	waitUntilSettled(20);
	
	// if(autoToRun == 1) {
	// 	defenseAuto(SOLO);
	// }
	// if(autoToRun == 2) {
	// 	defenseAuto(ELIMS);
	// }
	// if(autoToRun == 3) {
	// 	offenseAuto(SAFE);
	// }
	// if(autoToRun == 4) {
	// 	offenseAuto(RISKY);
	// }
	// if(autoToRun == 5) {
	// 	sixBall();
	// }
	// if(autoToRun == 6) {
	// 	progSkills();
	// }

	defenseAuto(SOLO);
	// defenseAuto(ELIMS);
	// offenseAuto(SAFE);
	// offenseAuto(RISKY);
	// sixBall();
	// progSkills();
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	autoMovement.suspend();
	// states.setDriveState(stateMachine::drive_state::TWO_MOTOR);
	// superstruct.set_priority(TASK_PRIORITY_DEFAULT + 1);
	// states.setPuncherState(stateMachine::puncher_state::PULLED_BACK);
	states.defaultPullback = stateMachine::puncher_state::MID_PULLBACK;
	// states.setPuncherState(states.defaultPullback);
	states.setPuncherAngleState(stateMachine::puncher_angle_state::DOWN);
	states.setDriveState(stateMachine::drive_state::SIX_MOTOR);

	// pros::Task odom(updatePosition);
	// inertial.reset(true);
	// resetOdomSensors();
	// pros::delay(100);
	// globalPose.setPoint(0,0,0);

	while (true) {
		pros::screen::print(TEXT_MEDIUM_CENTER, 5, "AUTO TO RUN %d", autoToRun);
		// Drive controls
		splitArcade(pros::E_MOTOR_BRAKE_COAST);
		drivePtoOpControl();

		// Intake controls
		intakeOpControl();

		// Puncher controls
		puncherOpControl();
		puncherAngleOpControl();

		// Wing toggle
		wingOpControl();

		// Parking Brake toggle
		parkingBrakeOpControl();

		// Side Climb toggle
		sideClimbOpControl();
		
		// Matchload
		// matchloadOpControl();

		// if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
				// 	states.defaultPullback = stateMachine::puncher_state::MID_PULLBACK;
				// 	firePuncher(48, 2);
			
			// while(true) {
			// 	// matchload(2);
			// 	if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A) || controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
			// 		break;
			// 	}
        	// 	states.setPuncherState(stateMachine::puncher_state::FIRE);
        	// 	while(!(states.puncherStateIs(stateMachine::puncher_state::PULLED_BACK))) {
            // 		pros::delay(10);
        	// 	}		
			// }
		// }

		pros::delay(20);
	}
}

// default pros stuff (for reference)
	// pros::Controller master(pros::E_CONTROLLER_MASTER);
	// pros::Motor left_mtr(1);
	// pros::Motor right_mtr(2);

	// pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
	//                  (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
	//                  (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);
	// int left = master.get_analog(ANALOG_LEFT_Y);
	// int right = master.get_analog(ANALOG_RIGHT_Y);

	// left_mtr = left;
	// right_mtr = right;