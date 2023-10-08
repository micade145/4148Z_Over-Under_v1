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


void shakeRobot() {
	// Help engage PTO
	setDrive(10, 10);
	pros::delay(250);
	setDrive(-10, -10);
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
	// inertial.set_heading(45);
	// globalPose.setPoint(30.5, 11, 55); // Original setpoint
	globalPose.setPoint(30.5, 6.5, 2);
	pros::delay(20);

	setCurve(12, 65, 24, 100, 100, 2000);
	waitUntilSettled(20);

	// First shot
	states.setPuncherAngleState(stateMachine::puncher_angle_state::FLAT);
	pros::delay(250);
	states.defaultPullback = stateMachine::puncher_state::MID_PULLBACK;
	states.setPuncherState(stateMachine::puncher_state::FIRE);
	pros::delay(20);

	// Mid Ball - Close
	states.setPuncherAngleState(stateMachine::puncher_angle_state::DOWN);
	states.setIntakeState(stateMachine::intake_state::OPEN);
	setMoveToPoint(leftTriball1.x, leftTriball1.y - 8, 0, 100, 80, 0, 3000);
	waitUntilSettled(20);
	states.setIntakeState(stateMachine::intake_state::INTAKING);
	pros::delay(400);
	states.setIntakeState(stateMachine::intake_state::CLOSED);

	setMove(-6, 0, 100, 80, 1000, false, false);
	waitUntilSettled(20);
	setMove(0, 90, 0, 80, 1000, false, false);
	waitUntilSettled(20);

	states.setPuncherAngleState(stateMachine::puncher_angle_state::FLAT);

	// Mid Ball - Near Bar
	states.setWingState(stateMachine::wing_state::WINGS_OUT);
	setMove(30, 90, 100, 70, 1200, false, false);
	pros::delay(200);
	
	states.setPuncherState(stateMachine::puncher_state::FIRE);
	pros::delay(1000);
	setMove(-24, 90, 100, 80, 1500, false, false);
	// pros::delay(500);
	waitUntilSettled(20);
	states.setWingState(stateMachine::wing_state::WINGS_STOWED);

	if(s == defense_auto_mode::SOLO){
		// Back to Matchload zone
		setMoveToPoint(leftMatchload.x - 6, leftMatchload.y, 0, 100, 80, 0, 3000);
		waitUntilSettled(20);
		setMove(0, 135, 0, 80, 2000, false, false);
		waitUntilSettled(20);
		states.setWingState(stateMachine::wing_state::RIGHT_OUT);
		pros::delay(100);
		setCurve(36, 90, 6, 100, 80, 3000);
		pros::delay(500);
		states.setWingState(stateMachine::wing_state::WINGS_STOWED);
		states.setIntakeState(stateMachine::intake_state::OPEN);

		waitUntilSettled(20);

		// Hang Bar
		states.setIntakeState(stateMachine::intake_state::CLOSED);
	}
	else if(s == defense_auto_mode::ELIMS) {
		setMoveToPoint(leftMatchload.x, leftMatchload.y, 0, 100, 100, 0, 3000);
		waitUntilSettled(20);
		setMove(0, 45, 0, 100, 3000, false, false);
		waitUntilSettled(20);
		setMove(-15, 45, 50, 50, 1500, false, false);
	}
	
	// distToPoint()
}

void offenseAuto(offense_auto_mode s) {

}

void sixBall() {
	// Init
	globalPose.setPoint(hangBarTriball.x + 12, hangBarTriball.y, 45);

	// Shoot preload
	states.setPuncherAngleState(stateMachine::puncher_angle_state::FLAT);
	pros::delay(200);
	states.defaultPullback = stateMachine::puncher_state::MID_PULLBACK;
	states.setPuncherState(stateMachine::puncher_state::FIRE);
	

	// Intake hangBarTriball
	setMove(0, 270, 0, 100, 1500, false, false);
	states.setPuncherAngleState(stateMachine::puncher_angle_state::DOWN);
	states.setIntakeState(stateMachine::intake_state::OPEN);
	waitUntilSettled(20);

	setMove(12, 270, 80, 60, 1500, false, false);
	pros::delay(800);
	states.setIntakeState(stateMachine::intake_state::INTAKING);
	pros::delay(500);

	setMove(-12, 270, 100, 80, 1500, false, false);
	waitUntilSettled(20);
	setMove(0, 45, 0, 100, 1500, false, false);
	waitUntilSettled(20);
	states.setPuncherState(stateMachine::puncher_state::FIRE);

	// Knock out matchload triball
	setMove(0, 90, 0, 80, 1500, false, false);
	waitUntilSettled(20);
	setMove(46, 90, 100, 80, 2000, false, false);
	waitUntilSettled(20);
	setCurve(30, 1, 12, 100, 100, 2000);
	states.setWingState(stateMachine::wing_state::RIGHT_OUT);
	waitUntilSettled(20);

	// Triball from mid
	setMove(-12, 0, 100, 80, 1500, false, false);
	waitUntilSettled(20);
	setMoveToPoint(rightTriball5.x + 6, rightTriball5.y - 6, 0, 100, 80, 0, 2500);
	states.setIntakeState(stateMachine::intake_state::OPEN);


}


// ******** AUTO ARCHIVE ******** //
void defenseElims() {

}

void offenseSafe() {

}