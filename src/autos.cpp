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
	setMove(45, 66.5, 87, 36, 2000, false, false);	// setMove(46, 66.5, 87, 36, 2000, false, false);
	// More pullback
		setPuncher(120);
		pros::delay(300);
		stopPuncher(pros::E_MOTOR_BRAKE_HOLD);
	pros::delay(1100-300);	//1200 - working delay for puncher
	
	states.setPuncherState(stateMachine::puncher_state::FIRE);
	waitUntilSettled(0);

	// Mid Ball - Close
	setMove(0, 335, 0, 90, 1000, false, false);
	waitUntilSettled(0);

	states.setPuncherAngleState(stateMachine::puncher_angle_state::DOWN);
	states.setIntakeState(stateMachine::intake_state::OPEN);
	setMove(19, 335, 80, 80, 1200, false, false);
	pros::delay(900);
	states.setIntakeState(stateMachine::intake_state::INTAKING);
	pros::delay(400);
	waitUntilSettled(0);

	setMove(-18, 335, 100, 80, 1000, false, false);
	waitUntilSettled(20);
	setMove(0, 75, 0, 80, 1000, false, false);
	pros::delay(800);
	states.setPuncherAngleState(stateMachine::puncher_angle_state::FLAT);
	waitUntilSettled(0);

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
		waitUntilSettled(0);
		setMove(0, 140, 0, 80, 800, false, false);
		waitUntilSettled(20);
		states.setIntakeState(stateMachine::intake_state::CLOSED);
		states.setWingState(stateMachine::wing_state::RIGHT_OUT);
		pros::delay(100);
		setMove(15, 140, 100, 80, 1000, false, false);	// we want this to timeout before reaching target
		pros::delay(1000);
		setMove(-7, 140, 120, 80, 800, false, false);
		states.setWingState(stateMachine::wing_state::WINGS_STOWED);
		waitUntilSettled(0);
		setCurve(24, 95, 27, 75, 70, 2300);
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

	setMove(0, 315, 0, 100, 800, false, false);
	// setMoveToPoint(rightTriball3.x, rightTriball3.y, 0, 0, 100, 0, 800);
	waitUntilSettled(0);

	// 2 triballs from mid
	setMove(22, 315, 100, 80, 1300, false, false);
	pros::delay(1100);
	states.setIntakeState(stateMachine::intake_state::CLOSED);
	pros::delay(100);
	waitUntilSettled(0);

	setMove(-10, 315, 100, 80, 1300, false, false);
	waitUntilSettled(0);
	setMove(0, 92, 0, 100, 800, false, false);
	waitUntilSettled(20);
	setMove(27, 92, 100, 80, 1000, false, false);
	states.setWingState(stateMachine::wing_state::WINGS_OUT);
	pros::delay(200);
	states.setIntakeState(stateMachine::intake_state::OPEN);

	pros::delay(1000);
	setMove(-18, 80, 100, 100, 1000, false, false);
	// setMove(-72, 315, 105, 70, 2000, false, false);	// to opponent matchload station
	states.setWingState(stateMachine::wing_state::WINGS_STOWED);
}

void shootDropProgSkills() { // shoot and drop at the same time // DIDN'T MOVE AFTER SHOOTING??? ALSO SHOOTING TOOK 45 SECONDS
	// Init
	globalPose.setPoint(24, 16.5, 330);
	states.setPuncherAngleState(stateMachine::puncher_angle_state::STEEP);
	states.defaultPullback = stateMachine::puncher_state::MID_PULLBACK;
	states.setDriveState(stateMachine::drive_state::TWO_MOTOR);
	states.setIntakeState(stateMachine::intake_state::OPEN);

	// Fire 26 matchloads
	setMove(-10, 330, 20, 100, 20000, false, false); // keep robot against pole ??
	setMatchload(22, true);
	
	// Just in case setMatchload won't allow movement
	// setMatchload(22, false);
	// pros::delay(25000);
	// matchloadState = false;
	// fireTarget = 0;

	// Cross under to other side
	states.setDriveState(stateMachine::drive_state::SIX_MOTOR);
	shakeRobot();
	setMove(0, 0, 0, 100, 800, false, false);
	waitUntilSettled(0);
	setMove(18, 0, 100, 100, 1200, false, false);
	waitUntilSettled(0);
	setMove(0, 180, 0, 100, 1000, false, false);
	waitUntilSettled(0);

	// (Hopefull) score triballs on other side
	setMove(-76, 180, 100, 100, 2500, false, false);
	waitUntilSettled(0);
	setMove(-32, 90, 100, 90, 1500, false, false);
	waitUntilSettled(0);
	for(int i=0; i<2; i++) {
		setMove(14, 90, 100, 100, 1000, false, false);
		waitUntilSettled(0);
		setMove(-14, 90, 110, 100, 1000, false, false);
		waitUntilSettled(0);
	}

	// Push balls in from mid
	// globalPose.setPoint(123, 36, 0);
	// pros::delay(40);
	setMove(6, 90, 100, 80, 800, false, false);
	waitUntilSettled(0);
	setMove(0, 180, 0, 100, 800, false, false);
	waitUntilSettled(0);
	setMove(40, 180, 100, 100, 1500, false, false);
	waitUntilSettled(0);

	setMove(0, 90, 0, 100, 800, false, false);
	waitUntilSettled(20);
	setMove(-30, 90, 100, 80, 1500, false, false);
	waitUntilSettled(0);

	setMove(0, 0, 0, 100, 800, false, false);
	waitUntilSettled(0);
	states.setWingState(stateMachine::wing_state::WINGS_OUT);
	setMove(30, 0, 100, 100, 1500, false, false);
	waitUntilSettled(0);

	for(int i=0; i<2; i++) {
		setMove(-15, 0, 100, 100, 1300, false, false);
		waitUntilSettled(0);
		setMove(15, 0, 120, 100, 1300, false, false);
		waitUntilSettled(0);
	}
	setMove(-15, 0, 100, 100, 1500, false, false);
	waitUntilSettled(0);

	states.setWingState(stateMachine::wing_state::WINGS_STOWED);
}

void dropProgSkills() { // no shooting, dropping all triballs
	// Init
	globalPose.setPoint(25, 12, 180);
	states.setPuncherAngleState(stateMachine::puncher_angle_state::STEEP);
	states.defaultPullback = stateMachine::puncher_state::MID_PULLBACK;

	// Sit for 30 seconds
	shakeRobot();
	for(int i=0; i<3; i++) {
	pros::delay(10000);
	setMove(-24, 180, 100, 100, 1500, false, false);
	waitUntilSettled(0);
	setMove(24, 180, 100, 100, 1500, false, false);
	waitUntilSettled(0);
	}

	// Drive to other side
	setMove(-72, 180, 100, 100, 2000, false, false);
	waitUntilSettled(0);
	setMove(0, 0, 45, 100, 800, false, false);
	waitUntilSettled(0);

	// Push some triballs in
	setMove(36, 268, 105, 60, 2000, false, false);
	// setCurve(20, 270, 25, 100, 100, 2000);
	pros::delay(400);
	states.setWingState(stateMachine::wing_state::WINGS_OUT);
	waitUntilSettled(0);
	for(int i=0; i<3; i++) {
		setMove(-14, 270, 100, 80, 1500, false, false);
		waitUntilSettled(0);
		setMove(14, 270, 100, 100, 1500, false, false);
		waitUntilSettled(0);
	}

	// inertial.set_heading(0);
	globalPose.setPoint(123, 36, 0);
	pros::delay(40);
	setMove(-6, 0, 100, 80, 1000, false, false);
	waitUntilSettled(0);
	
	// FOUR BALL
	states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	states.setIntakeState(stateMachine::intake_state::OPEN);
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

void shootProgSkills() {
	// Init
	globalPose.setPoint(24, 16.5, 330);
	states.setPuncherAngleState(stateMachine::puncher_angle_state::STEEP);
	states.defaultPullback = stateMachine::puncher_state::MID_PULLBACK;

	// Fire 44 matchloads + 4 for error
	// setMove(-5, globalPose.theta, 80, 60, 800, false, false);
	// waitUntilSettled(20);
	states.setParkingBrakeState(stateMachine::parking_brake_state::BRAKE_ON);
	firePuncher(48, 2);
	pros::delay(500);

	// Drive to mid
	setMoveToPoint(48, 60, 0, 100, 100, 0, 2000);
	waitUntilSettled(0);
	setMove(0, 0, 0, 100, 800, false, false);
	waitUntilSettled(0);

	// Cross barrier
	setMove(-10, 0, 100, 80, 1500, false, false);
	waitUntilSettled(0);
	setMoveToPoint(84, 60, 0, 100, 100, 0, 5000);
	waitUntilSettled(0);

	// Reset against barrier
	setMove(-15, 0, 80, 80, 1500, false, false);
	waitUntilSettled(0);
	globalPose.setPoint(78.5, 60, 0);

	// Push triballs into goal
	states.setWingState(stateMachine::wing_state::WINGS_OUT);
	pros::delay(200);
	setMove(32, 0, 100, 80, 2000, false, false);
	waitUntilSettled(0);
	states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	setMove(-32, 180, 100, 20, 2000, false, false);
	waitUntilSettled(0);
	setMove(0, 120, 0, 100, 1000, false, false);
	waitUntilSettled(0);
	states.setWingState(stateMachine::wing_state::WINGS_OUT);
	setMove(39, 100, 100, 70, 2000, false, false);
	waitUntilSettled(0);
	states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	setMove(-39, 0, 100, 100, 2000, false, false);
	waitUntilSettled(0);

}



// ******** AUTO ARCHIVE ******** //
void defenseElims() {

}

void offenseSafe() {

}