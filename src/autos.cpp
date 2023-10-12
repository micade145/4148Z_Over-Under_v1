#include "autos.h"

// ******** Setpoints ******** //
Point leftTriball1(48, 72);		// Left mid - auto line
Point leftTriball2(68, 72);		// Left pole - auto line
Point rightTriball3(76, 72);	// Right pole - auto line
Point rightTriball4(96, 72);	// Right mid - auto line
Point rightTriball5(76, 48);	// Right pole, in line with goal post
Point hangBarTriball(72, 12);	// Underneath hang bar

Point leftMatchload(20, 20);	// In front of left matchload station
Point rightMatchload(124, 20);	// In front of right matchload station

// double ROBOT_X_OFFSET = 6.5
// double ROBOT_Y_OFFSET = 6.5;

void shakeRobot() {
	// Help engage PTO
	setDrive(20, 20);
	pros::delay(250);
	setDrive(-20, -20);
	pros::delay(250);
	stopDrive(pros::E_MOTOR_BRAKE_BRAKE);
}

// ******** Test Autos ******** //
void odomBoxTest() {
    globalPose.setPoint(0.0, 0.0, 0);
    setMoveToPoint(0, 24, 0, 100, 100, 0, 3000);
    waitUntilSettled(20);
    setMoveToPoint(24, 24, 0, 100, 100, 0, 3000);
    waitUntilSettled(20);
    setMoveToPoint(24, 0, 0, 100, 100, 0, 3000);
    waitUntilSettled(20);
    setMoveToPoint(0, 0, 0, 100, 100, 0, 3000);
    waitUntilSettled(500);
}
void odomTriangleTest() {
    globalPose.setPoint(0.0, 0.0, 0);
    setMoveToPoint(20, 20, 0, 100, 100, 0, 4000);
	waitUntilSettled(20);
	setMoveToPoint(40, 0, 0, 100, 100, 0, 4000);
	waitUntilSettled(20);
	setMoveToPoint(0, 0, 0, 100, 100, 0, 4000);
	waitUntilSettled(500);
}

void squigglesTest() {
    globalPose.setPoint(0.0, 0.0, 0);   // Initialize position
    setMove(1600, 45, 100, 80, 3000, false, false); // right curve
	pros::delay(750);
	setMove(1600, 315, 100, 80, 3000, false, false);// left curve
	pros::delay(750);
	setMove(1600, 45, 100, 80, 3000, false, false); // small right curve
	pros::delay(500);
	setMove(800, 0, 100, 80, 3000, false, false);   // straight
	waitUntilSettled(20);
	setMoveToPoint(0, 0, 0, 100, 100, 0, 3000);     // back to origin
	waitUntilSettled(50);
}
void chainedMoveToPoint() {
	// Test: chaining together moveToPoints to run a path
    setMoveToPoint(20, 20, 0, 100, 100, 0, 4000);
	// waitUntilSettled(20);
	pros::delay(700);
	setMoveToPoint(40, 0, 0, 100, 100, 0, 4000);
	waitUntilSettled(20);
	setMoveToPoint(0, 0, 0, 100, 100, 0, 4000);
	waitUntilSettled(500);
}

void oldCurveTest() {
	// OLD CURVE LOGIC
	setMove(10000, 0, 127, 80, 5000, false, false);
	for(int i = 0; i < (360/10) ; i++) {
		turn_target += 10;
		pros::delay(100);
	}
	waitUntilSettled(20);
}
void curveTuning() {
	// CURVE TUNING
	setCurve(30, -180, 6, 100, 100, 5000); // curve direction depends on sign of endangle
	waitUntilSettled(20);
	setCurve(30, 0, 6, 100, 100, 3000);
	waitUntilSettled(20);
	pros::delay(1000);
}

// ******** Match Autos ********// 
/**
 * OFFENSIVE ZONE : YOUR GOAL ON YOUR SIDE
 * 
 * DEFENSIVE ZONE : OPPONENT GOAL ON YOUR SIDE
 * 
*/

void defenseAuto(defense_auto_mode s) {
	// Init
	// pros::delay(20);
	states.setDriveState(stateMachine::drive_state::SIX_MOTOR);
	states.defaultPullback = stateMachine::puncher_state::LONG_PULLBACK;
	states.setPuncherAngleState(stateMachine::puncher_angle_state::FLAT);
	// states.setIntakeState(stateMachine::intake_state::OPEN);
	shakeRobot();
	globalPose.setPoint(30.5, 16.5, 2);

	// First shot
	setMove(46, 66.5, 87, 36, 2000, false, false);	// setCurve(10, 70, 20, 100, 100, 2000);
	// More pullback
		setPuncher(120);
		pros::delay(300);
		stopPuncher(pros::E_MOTOR_BRAKE_HOLD);
	pros::delay(1250-300);	//1200 - working delay for puncher
	
	states.setPuncherState(stateMachine::puncher_state::FIRE);
	waitUntilSettled(20);

	// Mid Ball - Close
	setMove(0, 335, 0, 90, 1000, false, false);
	waitUntilSettled(20);

	states.setPuncherAngleState(stateMachine::puncher_angle_state::DOWN);
	states.setIntakeState(stateMachine::intake_state::OPEN);
	setMove(19, 335, 80, 80, 1200, false, false);
	pros::delay(900);
	states.setIntakeState(stateMachine::intake_state::INTAKING);
	pros::delay(400);
	waitUntilSettled(20);

	setMove(-18, 335, 100, 80, 1000, false, false);
	waitUntilSettled(20);
	setMove(0, 75, 0, 80, 1000, false, false);
	pros::delay(800);
	states.setPuncherAngleState(stateMachine::puncher_angle_state::FLAT);
	waitUntilSettled(20);

	// Fire mid ball
	states.setPuncherState(stateMachine::puncher_state::FIRE);
	states.setIntakeState(stateMachine::intake_state::CLOSED);
		// setMove(12, 75, 100, 80, 800, false, false);	// push triball over barrier
		// pros::delay(600);
	states.setIntakeState(stateMachine::intake_state::OPEN);
	pros::delay(200);
	
	if(s == defense_auto_mode::SOLO){
		// Back to Matchload zone
		setMove(-48, 70, 80, 40, 2300, false, false); // move -49, turn 65
		waitUntilSettled(20);
		setMove(0, 140, 0, 80, 1000, false, false);
		waitUntilSettled(20);
		states.setIntakeState(stateMachine::intake_state::CLOSED);
		states.setWingState(stateMachine::wing_state::RIGHT_OUT);
		pros::delay(100);
		setMove(15, 140, 100, 80, 1000, false, false);	// we want this to timeout before reaching target
		pros::delay(1000);
		setMove(-7, 140, 80, 80, 1000, false, false);
		pros::delay(800);
		states.setWingState(stateMachine::wing_state::WINGS_STOWED);
		waitUntilSettled(20);
		setCurve(25, 95, 27, 75, 70, 2500);
		pros::delay(300);
		states.setIntakeState(stateMachine::intake_state::OPEN);

		waitUntilSettled(20);
		states.setWingState(stateMachine::wing_state::LEFT_OUT);
		states.setIntakeState(stateMachine::intake_state::CLOSED);
	
	}
	else if(s == defense_auto_mode::ELIMS) {
		setMove(-51, 50, 60, 30, 2000, false, false);	// may work better
		// setMoveToPoint(leftMatchload.x, leftMatchload.y, 0, 100, 100, 0, 3000);
		waitUntilSettled(20);
		setMove(0, 45, 0, 100, 3000, false, false);
		waitUntilSettled(20);
		setMove(-15, 45, 50, 50, 1500, false, false);
		states.setPuncherAngleState(stateMachine::puncher_angle_state::MID);
	}
	// distToPoint()
}

void offenseAuto(offense_auto_mode s) {

}

void sixBall() { // out of time L
	// pros::screen::set_eraser(COLOR_BLACK);
	// pros::screen::erase();
	// pros::screen::set_pen(COLOR_GREEN);
	// pros::screen::fill_rect(5,5,240,200);
	// Init
	globalPose.setPoint(hangBarTriball.x + 16, hangBarTriball.y, 60);
	states.defaultPullback = stateMachine::puncher_state::MID_PULLBACK;
	states.setPuncherAngleState(stateMachine::puncher_angle_state::DOWN);

	// Shoot preload
	pros::delay(300);
	states.setIntakeState(stateMachine::intake_state::OPEN);
	pros::delay(200);
	states.setPuncherState(stateMachine::puncher_state::FIRE);
	shakeRobot();
	pros::delay(5);
	
	// Intake hangBarTriball
	setMove(0, 270, 0, 100, 800, false, false);
	states.setIntakeState(stateMachine::intake_state::CLOSED);
	states.setPuncherAngleState(stateMachine::puncher_angle_state::STEEP);
	waitUntilSettled(0);
	states.setIntakeState(stateMachine::intake_state::OPEN);

	setMove(9, 270, 80, 60, 800, false, false);
	pros::delay(600);
	states.setIntakeState(stateMachine::intake_state::CLOSED);
	pros::delay(100);

	setMove(-33, 270, 120, 100, 1500, false, false);
	waitUntilSettled(0);
	setMove(0, 45, 0, 100, 800, false, false);
	waitUntilSettled(0);
	
	// Knock out matchload triball // no more
	// setMove(15, 45, 80, 80, 1000, false, false);
	// states.setWingState(stateMachine::wing_state::RIGHT_OUT);
	// pros::delay(1000);
	// setMove(-10, 70, 80, 100, 1000, false, false);
	// states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	// pros::delay(400);

	// Score preload + hangbar triball
	states.setIntakeState(stateMachine::intake_state::OPEN);
	// setMove(20, 2, 110, 60, 1500, false, false);
	setCurve(10, 2, 27, 100, 80, 1200);
	waitUntilSettled(0);
	setMove(-8, 0, 80, 80, 800, false, false);
	waitUntilSettled(0);
	states.setIntakeState(stateMachine::intake_state::CLOSED);
	setMove(0, 180, 0, 100, 800, false, false);
	waitUntilSettled(0);
	setMove(-15, 180, 100, 80, 800, false, false);
	pros::delay(800);

	// Triball from mid
	setMove(4, 180, 100, 80, 900, false, false);
	waitUntilSettled(0);
	setMoveToPoint(rightTriball5.x + 10, rightTriball5.y - 4, 0, 90, 80, 0, 1800);
	states.setIntakeState(stateMachine::intake_state::OPEN);
	// states.setPuncherAngleState(stateMachine::puncher_angle_state::FLAT);
	pros::delay(1700);
	states.setIntakeState(stateMachine::intake_state::CLOSED);
	pros::delay(100);
	setMove(-10, inertial.get_heading(), 100, 80, 900, false, false);
	pros::delay(800);

	setMove(0, 75, 0, 100, 800, false, false);
	pros::delay(800);
	states.setIntakeState(stateMachine::intake_state::OPEN);

	setMove(15, 75, 100, 80, 1200, false, false);
	pros::delay(800);
	// setMove(-18, 75, 100, 80, 800, false, false);
	// waitUntilSettled(20);

	// states.setIntakeState(stateMachine::intake_state::OPEN);
	setMove(0, 320, 0, 100, 800, false, false);

	// 2 triballs from mid
	pros::delay(800);
	setMove(20, 320, 100, 80, 1100, false, false);
	pros::delay(1000);
	states.setIntakeState(stateMachine::intake_state::CLOSED);
	pros::delay(100);

	setMove(-10, 320, 100, 80, 800, false, false);
	pros::delay(800);
	setMove(0, 92, 0, 100, 800, false, false);
	waitUntilSettled(20);
	setMove(28, 92, 100, 80, 1000, false, false);
	states.setWingState(stateMachine::wing_state::LEFT_OUT);
	pros::delay(200);
	states.setIntakeState(stateMachine::intake_state::OPEN);
	
	pros::delay(1000);
	setMove(-15, 92, 100, 90, 1000, false, false);
	// setMove(-72, 315, 105, 70, 2000, false, false);	// to opponent matchload station
	states.setWingState(stateMachine::wing_state::WINGS_STOWED);
}

void fourBall() {
	// init
	globalPose.setPoint(120, 12, 200);
	states.setPuncherAngleState(stateMachine::puncher_angle_state::STEEP);
	states.defaultPullback = stateMachine::puncher_state::MID_PULLBACK;
	states.setIntakeState(stateMachine::intake_state::OPEN);

	setMove(-28, 180, 100, 60, 1200, false, false);
	waitUntilSettled(20);

	// Mid triball
	setMoveToPoint(rightTriball5.x + 6, rightTriball5.y - 6, 0, 100, 80, 0, 1800);
	pros::delay(1700);
	states.setIntakeState(stateMachine::intake_state::CLOSED);
	pros::delay(100);

	setMove(-10, inertial.get_heading(), 100, 80, 900, false, false);
	pros::delay(800);

	setMove(0, 70, 0, 100, 800, false, false);
	pros::delay(800);

	setMove(24, 70, 100, 80, 1500, false, false);
	waitUntilSettled(0);
	// pros::delay(600);
	states.setIntakeState(stateMachine::intake_state::OPEN);
	pros::delay(100);
	setMove(-14, 70, 120, 100, 1200, false, false);
	waitUntilSettled(0);

	setMove(0, 330, 0, 100, 800, false, false);
	// setMoveToPoint(rightTriball3.x, rightTriball3.y, 0, 0, 100, 0, 800);
	waitUntilSettled(0);

	// 2 triballs from mid
	setMove(18, 330, 100, 80, 1300, false, false);
	pros::delay(1100);
	states.setIntakeState(stateMachine::intake_state::CLOSED);
	pros::delay(100);
	waitUntilSettled(0);

	setMove(-18, 330, 100, 80, 1300, false, false);
	waitUntilSettled(0);
	setMove(0, 92, 0, 100, 800, false, false);
	waitUntilSettled(20);
	setMove(30, 92, 100, 80, 1000, false, false);
	states.setWingState(stateMachine::wing_state::WINGS_OUT);
	pros::delay(200);
	states.setIntakeState(stateMachine::intake_state::OPEN);

	pros::delay(1000);
	setMove(-18, 80, 100, 90, 1000, false, false);
	// setMove(-72, 315, 105, 70, 2000, false, false);	// to opponent matchload station
	states.setWingState(stateMachine::wing_state::WINGS_STOWED);
}

void progSkills() {
	// Init
	globalPose.setPoint(24, 16.5, 330);
	states.setPuncherAngleState(stateMachine::puncher_angle_state::STEEP);
	states.defaultPullback = stateMachine::puncher_state::MID_PULLBACK;

	// Fire 44 matchloads + 4 for error
	setMove(-5, globalPose.theta, 80, 60, 800, false, false);
	waitUntilSettled(20);
	states.setParkingBrakeState(stateMachine::parking_brake_state::BRAKE_ON);
	firePuncher(48, 2);
	pros::delay(500);

	setMoveToPoint(leftTriball1.x, leftTriball1.y, 0, 100, 100, 0, 2000);
	waitUntilSettled(0);
	setMove(0, 0, 0, 100, 800, false, false);
	waitUntilSettled(0);

}





// ******** AUTO ARCHIVE ******** //
void defenseElims() {

}

void offenseSafe() {

}