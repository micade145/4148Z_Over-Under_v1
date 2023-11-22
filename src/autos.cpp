#include "autos.h"


// ******** Setpoints ******** //
Point leftTriball1(48, 72);		// Left mid - auto line (48, 72)
Point leftTriball2(68, 72);		// Left pole - auto line (68, 72)
Point rightTriball3(76, 72);	// Right pole - auto line (76, 72)
Point rightTriball4(96, 72);	// Right mid - auto line (96, 72)
Point rightTriball5(76, 48);	// Right pole, in line with goal post (76, 48)
Point hangBarTriball(72, 12);	// Underneath hang bar (72, 12)

Point leftBottomMatchload(20, 20);		// In front of left bottom matchload station (20, 20)
Point rightBottomMatchload(124, 20);	// In front of right bottom matchload station (124, 20)
Point leftTopMatchload(20, 124);		// In front of left top matchload station (20, 124)
Point rightTopMatchload(124, 124);		// In front of right top matchload  (124, 124)

// double ROBOT_X_OFFSET = 6.5
// double ROBOT_Y_OFFSET = 6.5;


// Shake robot to help engage PTO, 200 ms
void shakeRobot() {
	// Help engage PTO
	setDrive(60, 60);
	pros::delay(200);
	// setDrive(-40, -40);
	// pros::delay(200);
	stopDrive(pros::E_MOTOR_BRAKE_BRAKE);
}

// ******** Test Autos ******** //
void odomBoxTest() {
    globalPose.setPoint(0.0, 0.0, 0);
    setMoveToPoint(0, 24, 1500, false);
    waitUntilSettled(20);
    setMoveToPoint(24, 24, 1500, false);
    waitUntilSettled(20);
    setMoveToPoint(24, 0, 1500, false);
    waitUntilSettled(20);
    setMoveToPoint(0, 0, 1500, false);
    waitUntilSettled(500);
}
void odomTriangleTest() {
    globalPose.setPoint(0.0, 0.0, 0);
    setMoveToPoint(20, 20, 2000, false);
	waitUntilSettled(20);
	setMoveToPoint(40, 0, 2000, false);
	waitUntilSettled(20);
	setMoveToPoint(0, 0, 2000, false);
	waitUntilSettled(500);
}

void squigglesTest() {
    globalPose.setPoint(0.0, 0.0, 0);   // Initialize position
    setMove(1600, 45, 100, 80, 3000); // right curve
	pros::delay(750);
	setMove(1600, 315, 100, 80, 3000);// left curve
	pros::delay(750);
	setMove(1600, 45, 100, 80, 3000); // small right curve
	pros::delay(500);
	setMove(800, 0, 100, 80, 3000);   // straight
	waitUntilSettled(20);
	setMoveToPoint(0, 0, 1500, false);     // back to origin
	waitUntilSettled(50);
}
void chainedMoveToPoint() {
	// Test: chaining together moveToPoints to run a path
    setMoveToPoint(20, 20, 1500, false);
	// waitUntilSettled(20);
	pros::delay(700);
	setMoveToPoint(40, 0, 1500, false);
	waitUntilSettled(20);
	setMoveToPoint(0, 0, 1500, false);
	waitUntilSettled(500);
}

void oldCurveTest() {
	// OLD CURVE LOGIC
	setMove(10000, 0, 127, 80, 5000);
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


void newTestProg() { 
	// init
	globalPose.setPoint(27.5, 9, 60);
	states.setIntakeState(stateMachine::intake_state::OPEN);
	states.setPuncherAngleState(stateMachine::puncher_angle_state::STEEP);

	// **** Shoot triballs over **** //
	states.setDriveState(stateMachine::drive_state::TWO_MOTOR);
	shakeRobot();
	setMove(-10, 60, 20, 100, 20000); // keep robot against pole, time to shoot - 10000
	// setMatchload(29, false);
	matchloadState = true;
	pros::delay(30000); // 30 seconds, ~ 34 shots
	matchloadState = false;
	fireTarget = 0;
	pros::delay(100);
	states.setDriveState(stateMachine::drive_state::SIX_MOTOR);
	// states.setPuncherState(stateMachine::puncher_state::FIRE);

	// **** Cross over field **** //
	shakeRobot();
	setDrive(120, 120);
	pros::delay(120);
	setDrive(0, 0);
	states.setIntakeState(stateMachine::intake_state::CLOSED);
	setMove(0, 270, 0, 128, 1100);
	waitUntilSettled(0);
	setMoveToPoint(108, 13, 100, 128, 2000, true); // setMoveToPoint(121, 13, 100, 128, 2000, false);
	waitUntilSettled(0);

	// **** Score from side of goal **** //
	setMoveToPoint(130, 24, 110, 128, 900, true);
	waitUntilSettled(0);
	setMoveToPoint(132, 72, 100, 128, 1200, true); // setMoveToPoint(132, 55, 100, 128, 1200, true);
	waitUntilSettled(0);

	// push 1
	setMove(12, 175, 128, 80, 1000);
	waitUntilSettled(0);
	for(int i=0; i<2; i++) {
		setMove(-24, 180, 128, 120, 900);
		waitUntilSettled(0);
		setMove(18, 185, 128, 100, 800);
		waitUntilSettled(0);
	}
	setMove(-24, 180, 128, 128, 900);
	waitUntilSettled(0);
	setMove(4, 200, 128, 80, 800);
	waitUntilSettled(0);

	// **** Score triballs from middle of field **** //
	setMoveToPoint(80, 36, 1300, false); // setMoveToPoint(84, 36, 1300, false);
	waitUntilSettled(0);
	setMoveToPoint(80, 63, 100, 128, 1200, false); // setMoveToPoint(84, 48, 100, 128, 1200, false);
	waitUntilSettled(0);

	setMove(0, 90, 0, 120, 800);
	waitUntilSettled(0);
	states.setWingState(stateMachine::wing_state::WINGS_OUT);
	pros::delay(100);
	setMoveToPoint(124, 72, 128, 80, 2000, false);
	waitUntilSettled(0);

	// push
	setMove(-24, 90, 1000);
	waitUntilSettled(0);
	// for(int i=0; i<2; i++) {
		setMove(28, 90, 128, 100, 1200, true);
		pros::delay(1200);
		setMove(-16, 90, 128, 100, 800);
		pros::delay(800);
	// }
	states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	setMoveToPoint(82, 78, 128, 128, 1100, true); 
	waitUntilSettled(0);
	
	
	// ******** Score from other side of goal ******* //
	setMove(0, 0, 0, 100, 700);
	waitUntilSettled(0);
	states.setWingState(stateMachine::wing_state::LEFT_OUT);
	
	setMoveToPoint(120, 115, 128, 128, 1600, false); // setMoveToPoint(120, 124, 128, 128, 1600, false);
	waitUntilSettled(0);
	setMove(0, 330, 600);
	waitUntilSettled(0);
	// setMoveToPoint(130, 110, 128, 128, 1000, true);
	// waitUntilSettled(0);
	// setMoveToPoint(130, 72, 128, 128, 1000, true);
	// waitUntilSettled(0);
	// setMove(12, 0, 128, 128, 1000);
	// waitUntilSettled(0);

	setMoveToPoint(140, 80, 128, 128, 1500, true);
	waitUntilSettled(0);
	setMove(12, 300, 128, 128, 1000);
	waitUntilSettled(0);
}


void testProg() { // pushes with back of robot
	// init
	globalPose.setPoint(27.5, 9, 60);
	states.setIntakeState(stateMachine::intake_state::OPEN);
	states.setPuncherAngleState(stateMachine::puncher_angle_state::STEEP);

	// **** Shoot triballs over **** //
	states.setDriveState(stateMachine::drive_state::TWO_MOTOR);
	shakeRobot();
	setMove(-10, 60, 20, 100, 20000); // keep robot against pole, time to shoot - 10000
	matchloadState = true; 	// setMatchload(29, false);
	pros::delay(30000); // 30 seconds, ~ 34 shots
	matchloadState = false;
	fireTarget = 0;
	states.setDriveState(stateMachine::drive_state::SIX_MOTOR);
	pros::delay(100);
	// states.setPuncherState(stateMachine::puncher_state::FIRE);

	// **** Cross over field **** //
	// shakeRobot();
	setDrive(120, 120);
	pros::delay(100);  
	setDrive(0, 0);
	setMove(6.5, 60, 128, 128, 1500);
	waitUntilSettled(0);
	states.setIntakeState(stateMachine::intake_state::CLOSED);
	setMove(0, 280, 0, 128, 1100); // 275
	waitUntilSettled(0);
	setMoveToPoint(108, 13, 100, 128, 2000, true); // setMoveToPoint(121, 13, 100, 128, 2000, false);
	waitUntilSettled(0);

	// **** Push triball in from side of goal **** //
	setMoveToPoint(130, 24, 110, 128, 900, true);
	waitUntilSettled(0);
	setMoveToPoint(132, 72, 120, 128, 1200, true); // setMoveToPoint(132, 55, 100, 128, 1200, true);
	waitUntilSettled(0);

	// push
	setMove(16, 180, 128, 80, 1000);
	waitUntilSettled(0);

	setMove(-30, 180, 128, 128, 900); // setMove(-12, 180, 128, 128, 1000, true);
	waitUntilSettled(0);
	setMove(16, 180, 128, 80, 900);
	waitUntilSettled(0);
	setMove(-30, 180, 128, 128, 900); // setMove(-12, 180, 128, 128, 1000, true);
	waitUntilSettled(0);
	setMove(16, 180, 128, 80, 900);
	waitUntilSettled(0);
	setMove(-30, 180, 128, 128, 900); // setMove(-12, 180, 128, 128, 1000, true);
	waitUntilSettled(0);
	setMove(4, 180, 128, 80, 800);
	waitUntilSettled(0);

	// **** Score triballs from middle of field **** //
	setMoveToPoint(81, 36, 100, 120, 1300, false); // setMoveToPoint(84, 36, 1300, false);
	waitUntilSettled(0);
	setMoveToPoint(82, 58, 100, 128, 1200, false); // setMoveToPoint(84, 48, 100, 128, 1200, false);
	waitUntilSettled(0);

	setMove(0, 90, 0, 120, 700);
	waitUntilSettled(0);
	states.setWingState(stateMachine::wing_state::WINGS_OUT);
	pros::delay(100);
	states.setIntakeState(stateMachine::intake_state::OPEN);
	setMoveToPoint(124, 72, 128, 80, 2000, false);
	waitUntilSettled(0);

	// setMove(0, 0, 0, 100, 900);
	// waitUntilSettled(0);
	// setMove(70, 90, 127, 90, 2000);
	// pros::delay(200);
	// states.setWingState(stateMachine::wing_state::WINGS_OUT);
	// waitUntilSettled(0);

	// push
	setMove(-24, 90, 1000);
	waitUntilSettled(0);
	// for(int i=0; i<2; i++) {
		setMove(28, 90, 128, 100, 1100, true); // wait 1200
		pros::delay(1100); // delay 1200
		setMove(-16, 90, 128, 100, 800);
		pros::delay(800);
		setMove(28, 90, 128, 100, 1100, true); // 1200
		pros::delay(1100); // 1200
		setMove(-20, 90, 128, 100, 800);
		states.setWingState(stateMachine::wing_state::WINGS_STOWED);
		pros::delay(800);
	// }
	// states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	// setMoveToPoint(82, 72, 128, 128, 1100, true); // setMoveToPoint(90, 72, 128, 128, 1200, true);
	// waitUntilSettled(0);
	// setMoveToPoint(82, 104, 100, 128, 1300, true); // (90, 96)
	// waitUntilSettled(0);
	// setMove(0, 115, 600);
	// waitUntilSettled(0);
	// states.setWingState(stateMachine::wing_state::WINGS_OUT);
	// pros::delay(100);
	// setMoveToPoint(128, 72, 128, 90, 1900, false);
	// waitUntilSettled(0);
	// setMoveToPoint(90, 72, 128, 128, 1200, true);
	// states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	// waitUntilSettled(0);
	
	// ******** Score from other side of goal ******* //
	// setMoveToPoint(120, 128, 128, 128, 1600, false); // setMoveToPoint(120, 124, 128, 128, 1600, false);
	// waitUntilSettled(0);
	// setMove(0, 330, 600);
	// waitUntilSettled(0);

	// setMoveToPoint(140, 80, 128, 128, 1500, true);
	// waitUntilSettled(0);
	// setMove(12, 300, 128, 128, 1000);
	// waitUntilSettled(0);
}


// ******** Match Autos ********// 
/**
 * OFFENSIVE ZONE : YOUR GOAL ON YOUR SIDE
 * 
 * DEFENSIVE ZONE : OPPONENT GOAL ON YOUR SIDE
 * 
*/

// void defenseAuto(defense_auto_mode s) {
// 	// Init
// 	globalPose.setPoint(30.5, 16.5, 2);
// 	states.setDriveState(stateMachine::drive_state::SIX_MOTOR);
// 	states.defaultPullback = stateMachine::puncher_state::MID_PULLBACK;
// 	states.setPuncherAngleState(stateMachine::puncher_angle_state::FLAT);

// 	// First shot
// 	shakeRobot();
// 	setMove(42, 66.5, 87, 36, 2000);	// setMove(45, 66.5, 87, 36, 2000);
// 	while(drive_position < 20) {pros::delay(5);}
// 	for(int i=0; i < 14; i++) { //13 iterations for deaccel
// 		max_drive_power -= 87/14;
// 		pros::delay(40);
// 	}
	
// 	// More pullback
// 	// 	setPuncher(120);
// 	// 	pros::delay(300);
// 	// 	stopPuncher(pros::E_MOTOR_BRAKE_HOLD);
// 	// pros::delay(1100-300);	//1200 - working delay for puncher
	
// 	states.setPuncherState(stateMachine::puncher_state::FIRE);
// 	waitUntilSettled(0);

// 	// Mid Ball - Close
// 	setMove(0, 345, 0, 100, 800); //angle 335
// 	waitUntilSettled(0);

// 	states.setPuncherAngleState(stateMachine::puncher_angle_state::DOWN);
// 	states.setIntakeState(stateMachine::intake_state::OPEN);
// 	setMove(20, 345, 80, 80, 1200); //19.5, 335
// 	pros::delay(900);
// 	states.setIntakeState(stateMachine::intake_state::INTAKING);
// 	waitUntilSettled(0);

// 	if(s == defense_auto_mode::SOLO){
// 		setMove(-24, 345, 100, 80, 1100); //move -18, angle 335
// 		waitUntilSettled(0);
// 		setMove(0, 75, 0, 100, 800);
// 		pros::delay(700);
// 		states.setPuncherAngleState(stateMachine::puncher_angle_state::MID);
// 		// pros::delay(200);
// 		// states.setPuncherAngleState(stateMachine::puncher_angle_state::FLAT);
// 		// pros::delay(300);
// 		waitUntilSettled(0);

// 		// Fire mid ball
// 		states.setPuncherState(stateMachine::puncher_state::FIRE);
// 		states.setIntakeState(stateMachine::intake_state::CLOSED);
// 		pros::delay(200);

// 		// Back to Matchload zone
// 		// setMove(-43, 67, 100, 60, 2300); // move -48, turn 70
// 		setMoveToPoint(18, 24, 128, 128, 1300, true);
// 		waitUntilSettled(0);
// 		setMove(0, 140, 0, 100, 800); // turn 140
// 		waitUntilSettled(0);
// 		states.setWingState(stateMachine::wing_state::RIGHT_OUT);
// 		pros::delay(100);
// 		setMove(12, 140, 128, 80, 1000);	// we want this to timeout before reaching target
// 		pros::delay(1000);
// 		setMove(-7, 140, 120, 80, 800);
// 		states.setWingState(stateMachine::wing_state::WINGS_STOWED);
// 		waitUntilSettled(0);
// 		setCurve(24.3, 95, 27, 75, 70, 2300); //24.2
// 		pros::delay(300);
// 		states.setIntakeState(stateMachine::intake_state::OPEN);

// 		waitUntilSettled(0);
// 		states.setWingState(stateMachine::wing_state::LEFT_OUT);
// 		states.setIntakeState(stateMachine::intake_state::CLOSED);
	
// 	}
// 	else if(s == defense_auto_mode::ELIMS) {
// 		// setMove(-6, 335, 100, 80, 1000);
// 		// waitUntilSettled(20);
// 		setMove(0, 120, 0, 80, 1000);
// 		pros::delay(1600);
// 		states.setPuncherAngleState(stateMachine::puncher_angle_state::MID);
// 		pros::delay(400);

// 		// Fire mid ball
// 		states.setPuncherState(stateMachine::puncher_state::FIRE);
// 			// setMove(12, 75, 100, 80, 800);	// push triball over barrier
// 			// pros::delay(600);
// 		states.setIntakeState(stateMachine::intake_state::OPEN);
// 		setMove(0, 70, 0, 100, 1000);
// 		pros::delay(500);

// 		// setMove(-18, 90, 80, 120, 1400); //75
// 		// waitUntilSettled(0);
// 		// // setMoveToPoint(leftTriball2.x-2, leftTriball2.y - 10, 0, 90, 90, 0, 1200);
// 		// setMove(0, 60, 0, 100, 800);
// 		// pros::delay(600);
// 		setMove(10, 70, 80, 100, 1400);
// 		states.setPuncherAngleState(stateMachine::puncher_angle_state::DOWN);
// 		pros::delay(1000);
// 		states.setIntakeState(stateMachine::intake_state::INTAKING);
// 		waitUntilSettled(0);

// 		setMove(-26, 0, 100, 90, 1200);
// 		waitUntilSettled(0);
// 		setMove(0, 100, 0, 100, 800);
// 		waitUntilSettled(0);
// 		states.setPuncherAngleState(stateMachine::puncher_angle_state::MID);
// 		pros::delay(400);
// 		states.setPuncherState(stateMachine::puncher_state::FIRE);

// 		setMove(-12, 100, 100, 100, 1200);
// 		waitUntilSettled(0);
// 		// states.setIntakeState(stateMachine::intake_state::CLOSED);

// 		// setMove(-44, 70, 90, 90, 2000);
// 		// waitUntilSettled(0);

// 		// // knock out matchload object
// 		// setMove(0, 140, 0, 80, 800);
// 		// waitUntilSettled(20);
// 		// states.setIntakeState(stateMachine::intake_state::CLOSED);
// 		// states.setWingState(stateMachine::wing_state::RIGHT_OUT);
// 		// pros::delay(100);
// 		// setMove(15, 140, 100, 80, 1000);	// we want this to timeout before reaching target
// 		// pros::delay(1000);
// 		// setMove(-7, 140, 120, 80, 800);
// 		// states.setWingState(stateMachine::wing_state::WINGS_STOWED);
// 		// waitUntilSettled(0);
// 		// // setCurve(0, 95, 27, 75, 70, 2300);
// 		// setMove(15, 135, 80, 80, 1000);
// 		// states.setIntakeState(stateMachine::intake_state::OPEN);
// 		// pros::delay(300);
// 		// states.setIntakeState(stateMachine::intake_state::CLOSED);

// 	// yikes dont touch this
// 		// move back to matchload
// 			// setMove(-51, 50, 60, 30, 2000);	// may work better
// 			// // setMoveToPoint(leftMatchload.x, leftMatchload.y, 0, 100, 100, 0, 3000);
// 			// waitUntilSettled(20);
// 			// setMove(0, 45, 0, 100, 3000);
// 			// waitUntilSettled(20);
// 			// setMove(-15, 45, 50, 50, 1500);
// 			// states.setPuncherAngleState(stateMachine::puncher_angle_state::MID);
// 	}
// 	// distToPoint()
// }

void defenseAuto(defense_auto_mode s) {
// Init
	// globalPose.setPoint(24, 12, 160);
	globalPose.setPoint(25, 15.5, 180); 
	// actual x offset is 24 inches, but for reference we assume the edge of the first tile is 24 inches
	// so if measuring from wall, add around one inch

	states.setDriveState(stateMachine::drive_state::SIX_MOTOR);
	states.defaultPullback = stateMachine::puncher_state::MID_PULLBACK;

	// shakeRobot();
	// setMove(-24, 160, 128, 100, 1300);
	// waitUntilSettled(0);

	// help pto engage
	setMove(-29, 150, 100, 90, 1400); // setMove(-31, 135, 100, 90, 1500);
	pros::delay(550);
	turn_target = 182;
	waitUntilSettled(0);

	if(s == defense_auto_mode::SOLO) {
		// setMoveToPoint(27.5, 18, 1500, false);
		// pros::delay(500);
		// states.setWingState(stateMachine::wing_state::RIGHT_OUT);
		// waitUntilSettled(0);

			// setMove(30, 145, 100, 80, 1500);
			// pros::delay(500);
			// states.setWingState(stateMachine::wing_state::RIGHT_OUT);
			// waitUntilSettled(0);

			// setMove(-8, 140, 800);
			// states.setWingState(stateMachine::wing_state::WINGS_STOWED);
			// waitUntilSettled(0);
	
	setMoveToPoint(23.5, 25, 900, false); // setMoveToPoint(26, 24, 900, false);
	waitUntilSettled(0);
	setMove(0, 140, 800);
	waitUntilSettled(0);
	states.setWingState(stateMachine::wing_state::RIGHT_OUT);
	pros::delay(100);

	setMove(12, 140, 110, 128, 1300);
	waitUntilSettled(0);
	states.setWingState(stateMachine::wing_state::WINGS_STOWED);

	setMove(-7, 140, 128, 128, 1300);
	waitUntilSettled(0);

	setMoveToPoint(62, 7.5, 90, 128, 1200, false); // setMoveToPoint(65, 8.5, 90, 128, 1200, false);
	pros::delay(150);
	states.setWingState(stateMachine::wing_state::LEFT_OUT);
	waitUntilSettled(0);
	setMove(5, 90, 60, 100, 10000);
	waitUntilSettled(0);
	setDrive(50, 0);
	}
	else if(s == defense_auto_mode::ELIMS) {
	setMoveToPoint(23, 24, 1200, false); // setMoveToPoint(28, 24, 1200, false);
	waitUntilSettled(0);
	setMove(0, 85, 700);
	waitUntilSettled(0);
	setMove(-3, 85, 1000);
	waitUntilSettled(0);
	states.setDriveState(stateMachine::drive_state::TWO_MOTOR);
	setDrive(-80, -80);
	pros::delay(150);
	setDrive(0, 0);
	}
}

void defense3Ball() {
	// Init
	globalPose.setPoint(24, 12, 160);
	states.setDriveState(stateMachine::drive_state::SIX_MOTOR);
	states.defaultPullback = stateMachine::puncher_state::MID_PULLBACK;
	// states.setPuncherAngleState(stateMachine::puncher_angle_state::DOWN);
	// states.setIntakeState(stateMachine::intake_state::OPEN);

	shakeRobot();
	setMove(-30, 160, 120, 100, 1300);
	waitUntilSettled(0);
	setMove(36, 15, 100, 70, 1300);
	waitUntilSettled(0);

	// actual scoring
	// setMoveToPoint(leftTriball1.x , leftTriball1.y - 10, 90, 100, 1300, false);
	// pros::delay(1200);
	// states.setIntakeState(stateMachine::intake_state::INTAKING);
	// pros::delay(100);
	// waitUntilSettled(0);
	// setMove(-24, 330, 1400);
	// waitUntilSettled(0);
	// setMove(0, 60, 800);
	// waitUntilSettled(0);
	// pros::delay(400);
	// states.setPuncherAngleState(stateMachine::puncher_angle_state::FLAT);
	// pros::delay(500);
	// states.setIntakeState(stateMachine::intake_state::OPEN);
	// states.setPuncherState(stateMachine::puncher_state::FIRE);

	// setMoveToPoint(36, 36, 128, 100, 1000, false);
	// waitUntilSettled(0);


	// setMove(0, 150, 0, 100, 1000);
	// waitUntilSettled(0);
	// setMove(-30, 150, 100, 100, 1400);
	// waitUntilSettled(0);
	// // states.setIntakeState(stateMachine::intake_state::OPEN);
	// states.setPuncherAngleState(stateMachine::puncher_angle_state::DOWN);
	// // setMoveToPoint(leftTriball2.x - 14, leftTriball2.y, 0, 90, 100, 0, 1600);
	// setMove(38, 80, 70, 100, 1300);
	// pros::delay(1000);
	// states.setIntakeState(stateMachine::intake_state::INTAKING);
	
	// setMove(0, 90, 0, 100, 1000);
	// waitUntilSettled(0);
	// pros::delay(600);
	// states.setPuncherAngleState(stateMachine::puncher_angle_state::FLAT);
	// pros::delay(400);
	// states.setIntakeState(stateMachine::intake_state::OPEN);
	// states.setPuncherState(stateMachine::puncher_state::FIRE);
}

void defenseSafe() {
	globalPose.setPoint(30, 12, 320); // parallel to matchload bar, spaced so that edge of wing clears
	states.defaultPullback = stateMachine::puncher_state::MID_PULLBACK;
	states.setDriveState(stateMachine::drive_state::SIX_MOTOR);

	states.setWingState(stateMachine::wing_state::LEFT_OUT);
	pros::delay(100);
	setMove(20, 320, 80, 100, 1300);
	waitUntilSettled(0);
	states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	setMove(-20, 320, 1200);
	waitUntilSettled(0);

	setMove(0, 110, 0, 100, 900);
	waitUntilSettled(0);
	setMove(28.5, 110, 1700); // 30 in
	pros::delay(700); // 600 ms
	turn_target = 90;
	states.setWingState(stateMachine::wing_state::LEFT_OUT);
	waitUntilSettled(0);
	
	setDrive(50, 0);
}

void offenseAuto(offense_auto_mode s) {

}

void sixBall() { // actually five ball, maybe four ball
	// Init
	globalPose.setPoint(118.5, 17, 0); // in line w/ top right corner of tiles next to matchload 
	// globalPose.setPoint(120, 12.5, 320); // new+
	states.defaultPullback = stateMachine::puncher_state::MID_PULLBACK;
	states.setDriveState(stateMachine::drive_state::SIX_MOTOR);
	// states.setPuncherAngleState(stateMachine::puncher_angle_state::STEEP);

	// **** Push preload **** //
	states.setWingState(stateMachine::wing_state::RIGHT_OUT);
	// shakeRobot();
	pros::delay(100);
	states.setWingState(stateMachine::wing_state::WINGS_STOWED);

	// **** Rush Mid **** //
	// setMoveToPoint(118.5, 26, 128, 128, 500);
	states.setIntakeState(stateMachine::intake_state::OPEN);
	// setMoveToPoint(110, 48, 110, 128, 1450, false);
	// pros::delay(450);
	// target_x = 89; //89
	// target_y = 64; //64
	setMoveToPoint(rightTriball3.x + 13, rightTriball3.y - 8, 118, 128, 1450, false); // setMoveToPoint(rightTriball3.x + 13, rightTriball3.y - 8, 118, 128, 1450, false)
	// setMoveToPoint(87, 63, 128, 128, 1400);
	waitUntilSettled(0);
	states.setIntakeState(stateMachine::intake_state::CLOSED);
	// pros::delay(100); // 400ms
	// Score
	setMove(0, 90, 0, 110, 700); // 800ms
	pros::delay(625); // 700 ms
	states.setWingState(stateMachine::wing_state::WINGS_OUT);
	waitUntilSettled(0);
	// pros::delay(50);
		// states.setWingState(stateMachine::wing_state::WINGS_OUT);
		// pros::delay(200);
	// setMoveToPoint(116, 62, 1500);
	setMove(30, 90, 128, 100, 1300); 
	pros::delay(900);
	states.setIntakeState(stateMachine::intake_state::OPEN);
	waitUntilSettled(0);

	// **** 3rd triball from mid **** //
	setMove(-12, 60, 128, 128, 1100); // defauly 100, 100 power, 1300 ms
	states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	waitUntilSettled(0);
	setMove(0, 235, 700); // 800ms
	waitUntilSettled(0);
	// setMove(8, 235, 128, 100, 1500);
	setMoveToPoint(rightTriball5.x + 11, rightTriball5.y - 1, 128, 128, 950, false); // setMoveToPoint(rightTriball5.x + 11, rightTriball5.y, 128, 128, 950, false);
	pros::delay(850);
	states.setIntakeState(stateMachine::intake_state::CLOSED);
	waitUntilSettled(0);
	pros::delay(50);

	// **** Score 3rd triball and get triball from hang bar **** //
	setMove(0, 70, 700); // 900ms
	waitUntilSettled(0);
	setMoveToPoint(120, 62, 128, 80, 1300, false); //setMoveToPoint(119, 62, 128, 100, 1300, false);
	states.setIntakeState(stateMachine::intake_state::OPEN);
	waitUntilSettled(0);

		// Move function to get near hang bar lane
		// setMove(-12, 0, 90, 128, 800);
		// pros::delay(700);
		// setMove(-55, 0, 100, 100, 1700);
		// pros::delay(1600);

	setMoveToPoint(114, 7.4, 128, 128, 1500, true); // setMoveToPoint(114, 8.5, 128, 128, 1450, true);
	pros::delay(800);

	states.setIntakeState(stateMachine::intake_state::CLOSED);
	waitUntilSettled(0);
	// globalPose.setPoint(114, 8, 0);
	// pros::delay(20);
	setMoveToPoint(81, 13, 50, 128, 1300, false);  // setMoveToPoint(80, 10, 100, 128, 1300, false); // setMoveToPoint(82, 9, 60, 128, 1300, false) // setMoveToPoint(82, 15, 50, 128, 1300, false);
	// states.setPuncherAngleState(stateMachine::puncher_angle_state::FLAT);
	pros::delay(500);
	states.setIntakeState(stateMachine::intake_state::OPEN);
	max_translate_power = 128;
	waitUntilSettled(0);
	states.setIntakeState(stateMachine::intake_state::CLOSED);
	pros::delay(100);

		// push triball near side of goal
		// setMove(0, 110, 900);
		// waitUntilSettled(0);
		// states.setIntakeState(stateMachine::intake_state::OPEN);
		// setMoveToPoint(117, 41, 128, 100, 700); // 	setMoveToPoint(107, 38, 128, 100, 700);
		// waitUntilSettled(0);
		// setMoveToPoint(107, 12, 100, 128, 1000);
		// pros::delay(900);
		// setMoveToPoint(77, 20, 100, 128, 2000);
		// waitUntilSettled(0);
		// states.setIntakeState(stateMachine::intake_state::CLOSED);
		// pros::delay(200);

	// 12040 ms: 12 s

	// **** Push remaining triballs in **** //
	setMoveToPoint(116, 15, 128, 128, 1100, true);
	waitUntilSettled(0);
	setMove(0, 70, 0, 110, 700);
	waitUntilSettled(0);
	setMove(60, 70, 100, 128, 1500);
	pros::delay(500);
	turn_target = 4;  // 1 
	max_drive_power = 128;
	states.setIntakeState(stateMachine::intake_state::OPEN);
	waitUntilSettled(0);
	setMove(-20, 0, 128, 100, 700);
	waitUntilSettled(0);


	// 3200 for necessary movement, 700 for back up
	// 3900 ms: 4.0 s

	// **** Total Time **** //
	// 11650 for initial movements (3 balls from mid)
	// 3200 for final movements (hangBar triball + push 2 in goal)
	// ~500 to back up from goal (last movement)
	// 140 for movement setter delay (10ms per function call, 14 calls)
	// *******************
	// 15490 ms w/ back up, 14990 w/o back up
	// TARGET: 14900 ms, 14.9s
	// CUT AT LEAST 90 ms (no back up) or CUT 590 ms (back up) 
}

void fourBall() {
	// init
	globalPose.setPoint(120, 12, 200);
	states.setDriveState(stateMachine::drive_state::SIX_MOTOR);
	states.setPuncherAngleState(stateMachine::puncher_angle_state::STEEP);
	states.defaultPullback = stateMachine::puncher_state::MID_PULLBACK;
	states.setIntakeState(stateMachine::intake_state::OPEN);

	setMove(-28, 180, 100, 60, 1200);
	waitUntilSettled(0);

	// Mid triball
	setMoveToPoint(rightTriball5.x + 6, rightTriball5.y - 6, 0, 100, 80, 0, 1800, false);
	pros::delay(1700);
	states.setIntakeState(stateMachine::intake_state::CLOSED);
	waitUntilSettled(0);

	setMove(-10, inertial.get_heading(), 100, 80, 900);
	waitUntilSettled(0);
	setMove(0, 65, 0, 100, 800); //setMove(0, 70, 0, 100, 800);
	waitUntilSettled(0);

	setMove(24, 65, 100, 80, 1200); // setMove(24, 70, 100, 80, 1200);
	pros::delay(400);
	states.setIntakeState(stateMachine::intake_state::OPEN);
	waitUntilSettled(0);
	setMove(-14, 70, 120, 100, 1200);
	waitUntilSettled(0);

	setMove(0, 325, 0, 100, 800); // setMove(0, 315, 0, 100, 800);
	// setMoveToPoint(rightTriball3.x, rightTriball3.y, 0, 0, 100, 0, 800);
	waitUntilSettled(0);

	// 2 triballs from mid
	setMove(22, 325, 100, 80, 1300);
	pros::delay(1100);
	states.setIntakeState(stateMachine::intake_state::CLOSED);
	pros::delay(100);
	waitUntilSettled(0);

	setMove(-6, 325, 100, 80, 1000);
	waitUntilSettled(0);
	setMove(0, 88, 0, 100, 800); // setMove(0, 92, 0, 100, 800);
	pros::delay(600);
	states.setWingState(stateMachine::wing_state::WINGS_OUT);
	waitUntilSettled(0);
	setMove(27, 88, 100, 80, 1000);
	pros::delay(200);
	states.setIntakeState(stateMachine::intake_state::OPEN);

	waitUntilSettled(0);
	setMove(-18, 80, 100, 100, 1000);
	// setMove(-72, 315, 105, 70, 2000);	// to opponent matchload station
	states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	waitUntilSettled(0);
}

void shootDropProgSkills() { // working !!! 
	// Init
	globalPose.setPoint(24, 16.5, 330);
	states.setPuncherAngleState(stateMachine::puncher_angle_state::STEEP);
	states.defaultPullback = stateMachine::puncher_state::MID_PULLBACK;
	states.setDriveState(stateMachine::drive_state::TWO_MOTOR);
	states.setIntakeState(stateMachine::intake_state::OPEN);

	// Fire 26 matchloads
	shakeRobot();
	setMove(-10, 330, 20, 100, 20000); // keep robot against pole ??
	// setMatchload(2, true);
	
	// Just in case setMatchload won't allow movement
	setMatchload(29, false);
	pros::delay(30000);
	matchloadState = false;
	fireTarget = 0;
	states.setDriveState(stateMachine::drive_state::SIX_MOTOR);
	pros::delay(500);

	// Cross under to other side
	shakeRobot();
	pros::delay(200);
	setMove(18, 15, 80, 100, 1200);
	waitUntilSettled(0);
	// setMove(0, 185, 0, 100, 1000);
	// waitUntilSettled(0);

	// (Hopefull) score triballs on other side
	setMove(80, 5, 85, 100, 2500);
	waitUntilSettled(0);
	setMove(32, 275, 100, 90, 1500);
	waitUntilSettled(0);
	setMove(-12, 270, 100, 100, 1200);
	waitUntilSettled(0);
	setMove(0, 90, 0, 110, 1000);
	waitUntilSettled(0);
	for(int i=0; i<2; i++) {
		setMove(-20, 90, 120, 100, 1000);
		waitUntilSettled(0);
		setMove(14, 90, 110, 100, 1000);
		waitUntilSettled(0);
	}

	// Push balls in from mid
	// globalPose.setPoint(123, 36, 0);
	// pros::delay(40);
	// setMove(6, 90, 100, 80, 800);
	// waitUntilSettled(0);
	setMove(0, 200, 0, 100, 1000);
	waitUntilSettled(0);
	// // curve score??
	// setMove(120, 330, 90, 45, 3000);
	// pros::delay(500);
	// states.setWingState(stateMachine::wing_state::WINGS_OUT);
	// waitUntilSettled(0);

	// regular scoring
	setMove(43, 200, 100, 100, 1500);
	waitUntilSettled(0);

	setMove(0, 90, 0, 100, 800);
	waitUntilSettled(0);
	setMove(-35, 90, 100, 80, 1500);
	waitUntilSettled(0);

	setMove(0, 0, 0, 100, 800);
	waitUntilSettled(0);
	states.setWingState(stateMachine::wing_state::WINGS_OUT);
	setMove(30, 0, 100, 100, 1500);
	waitUntilSettled(0);


	for(int i=0; i<2; i++) {
		setMove(-20, 0, 110, 100, 1300);
		waitUntilSettled(0);
		setMove(20, 0, 120, 100, 1300);
		waitUntilSettled(0);
	}
	setMove(-23.5, 0, 100, 100, 1500);
	waitUntilSettled(0);
	setMove(25, 340, 100, 100, 1500);
	waitUntilSettled(0);
	setMove(-24, 0, 100, 100, 1500);
	// states.setWingState(stateMachine::wing_state::WINGS_STOWED);

	// setMove(0, 310, 0, 100, 800);
	// states.setIntakeState(stateMachine::intake_state::CLOSED);
	// waitUntilSettled(0);
	// // setMove(48)
	// setMove(59, 310, 100, 100, 2000);
	// waitUntilSettled(0);

	// setMove(0, 245, 0, 100, 800);
	// waitUntilSettled(0);
	// for(int i=0; i<2; i++) {
	// 	setMove(-24, 245, 120, 100, 1300);
	// 	waitUntilSettled(0);
	// 	setMove(24, 245, 120, 100, 1400);
	// 	waitUntilSettled(0);
	// }

	// setMove(24, 245, 120, 100, 1300);
	// waitUntilSettled(0);
}




// ************ AUTO ARCHIVE ************ //
void defenseElims() {

}

void offenseSafe() {

}

// void sixBall() { // out of time L
// 	// pros::screen::set_eraser(COLOR_BLACK);
// 	// pros::screen::erase();
// 	// pros::screen::set_pen(COLOR_GREEN);
// 	// pros::screen::fill_rect(5,5,240,200);
// 	// Init
// 	globalPose.setPoint(hangBarTriball.x + 16, hangBarTriball.y, 60);
// 	states.defaultPullback = stateMachine::puncher_state::MID_PULLBACK;
// 	states.setPuncherAngleState(stateMachine::puncher_angle_state::DOWN);

// 	// Shoot preload
// 	pros::delay(300);
// 	states.setIntakeState(stateMachine::intake_state::OPEN);
// 	pros::delay(200);
// 	states.setPuncherState(stateMachine::puncher_state::FIRE);
// 	shakeRobot();
// 	pros::delay(5);
	
// 	// Intake hangBarTriball
// 	setMove(0, 270, 0, 100, 800);
// 	states.setIntakeState(stateMachine::intake_state::CLOSED);
// 	states.setPuncherAngleState(stateMachine::puncher_angle_state::STEEP);
// 	waitUntilSettled(0);
// 	states.setIntakeState(stateMachine::intake_state::OPEN);

// 	setMove(9, 270, 80, 60, 800);
// 	pros::delay(600);
// 	states.setIntakeState(stateMachine::intake_state::CLOSED);
// 	pros::delay(100);

// 	setMove(-33, 270, 120, 100, 1500);
// 	waitUntilSettled(0);
// 	setMove(0, 45, 0, 100, 800);
// 	waitUntilSettled(0);
	
// 	// Knock out matchload triball // no more
// 	// setMove(15, 45, 80, 80, 1000);
// 	// states.setWingState(stateMachine::wing_state::RIGHT_OUT);
// 	// pros::delay(1000);
// 	// setMove(-10, 70, 80, 100, 1000);
// 	// states.setWingState(stateMachine::wing_state::WINGS_STOWED);
// 	// pros::delay(400);

// 	// Score preload + hangbar triball
// 	states.setIntakeState(stateMachine::intake_state::OPEN);
// 	// setMove(20, 2, 110, 60, 1500);
// 	setCurve(10, 2, 27, 100, 80, 1200);
// 	waitUntilSettled(0);
// 	setMove(-8, 0, 80, 80, 800);
// 	waitUntilSettled(0);
// 	states.setIntakeState(stateMachine::intake_state::CLOSED);
// 	setMove(0, 180, 0, 100, 800);
// 	waitUntilSettled(0);
// 	setMove(-15, 180, 100, 80, 800);
// 	pros::delay(800);

// 	// Triball from mid
// 	setMove(4, 180, 100, 80, 900);
// 	waitUntilSettled(0);
// 	setMoveToPoint(rightTriball5.x + 10, rightTriball5.y - 4, 0, 90, 80, 0, 1800);
// 	states.setIntakeState(stateMachine::intake_state::OPEN);
// 	// states.setPuncherAngleState(stateMachine::puncher_angle_state::FLAT);
// 	pros::delay(1700);
// 	states.setIntakeState(stateMachine::intake_state::CLOSED);
// 	pros::delay(100);
// 	setMove(-10, inertial.get_heading(), 100, 80, 900);
// 	pros::delay(800);

// 	setMove(0, 75, 0, 100, 800);
// 	pros::delay(800);
// 	states.setIntakeState(stateMachine::intake_state::OPEN);

// 	setMove(15, 75, 100, 80, 1200);
// 	pros::delay(800);
// 	// setMove(-18, 75, 100, 80, 800);
// 	// waitUntilSettled(20);

// 	// states.setIntakeState(stateMachine::intake_state::OPEN);
// 	setMove(0, 320, 0, 100, 800);

// 	// 2 triballs from mid
// 	pros::delay(800);
// 	setMove(20, 320, 100, 80, 1100);
// 	pros::delay(1000);
// 	states.setIntakeState(stateMachine::intake_state::CLOSED);
// 	pros::delay(100);

// 	setMove(-10, 320, 100, 80, 800);
// 	pros::delay(800);
// 	setMove(0, 92, 0, 100, 800);
// 	waitUntilSettled(20);
// 	setMove(28, 92, 100, 80, 1000);
// 	states.setWingState(stateMachine::wing_state::LEFT_OUT);
// 	pros::delay(200);
// 	states.setIntakeState(stateMachine::intake_state::OPEN);
	
// 	pros::delay(1000);
// 	setMove(-15, 92, 100, 90, 1000);
// 	// setMove(-72, 315, 105, 70, 2000);	// to opponent matchload station
// 	states.setWingState(stateMachine::wing_state::WINGS_STOWED);
// }

// void dropProgSkills() { // no shooting, dropping all triballs
// 	// Init
// 	globalPose.setPoint(25, 12, 180);
// 	states.setPuncherAngleState(stateMachine::puncher_angle_state::STEEP);
// 	states.defaultPullback = stateMachine::puncher_state::MID_PULLBACK;

// 	// Sit for 30 seconds
// 	shakeRobot();
// 	for(int i=0; i<3; i++) {
// 	pros::delay(10000);
// 	setMove(-24, 180, 100, 100, 1500);
// 	waitUntilSettled(0);
// 	setMove(24, 180, 100, 100, 1500);
// 	waitUntilSettled(0);
// 	}

// 	// Drive to other side
// 	setMove(-72, 180, 100, 100, 2000);
// 	waitUntilSettled(0);
// 	setMove(0, 0, 45, 100, 800);
// 	waitUntilSettled(0);

// 	// Push some triballs in
// 	setMove(36, 268, 105, 60, 2000);
// 	// setCurve(20, 270, 25, 100, 100, 2000);
// 	pros::delay(400);
// 	states.setWingState(stateMachine::wing_state::WINGS_OUT);
// 	waitUntilSettled(0);
// 	for(int i=0; i<3; i++) {
// 		setMove(-14, 270, 100, 80, 1500);
// 		waitUntilSettled(0);
// 		setMove(14, 270, 100, 100, 1500);
// 		waitUntilSettled(0);
// 	}

// 	// inertial.set_heading(0);
// 	globalPose.setPoint(123, 36, 0);
// 	pros::delay(40);
// 	setMove(-6, 0, 100, 80, 1000);
// 	waitUntilSettled(0);

// 	// FOUR BALL
// 	states.setWingState(stateMachine::wing_state::WINGS_STOWED);
// 	states.setIntakeState(stateMachine::intake_state::OPEN);
// 	setMoveToPoint(rightTriball5.x + 6, rightTriball5.y - 6, 0, 100, 80, 0, 1800);
// 	pros::delay(1700);
// 	states.setIntakeState(stateMachine::intake_state::CLOSED);
// 	pros::delay(100);

// 	setMove(-10, inertial.get_heading(), 100, 80, 900);
// 	pros::delay(800);

// 	setMove(0, 70, 0, 100, 800);
// 	pros::delay(800);

// 	setMove(24, 70, 100, 80, 1500);
// 	waitUntilSettled(0);
// 	// pros::delay(600);
// 	states.setIntakeState(stateMachine::intake_state::OPEN);
// 	pros::delay(100);
// 	setMove(-14, 70, 120, 100, 1200);
// 	waitUntilSettled(0);

// 	setMove(0, 330, 0, 100, 800);
// 	// setMoveToPoint(rightTriball3.x, rightTriball3.y, 0, 0, 100, 0, 800);
// 	waitUntilSettled(0);

// 	// 2 triballs from mid
// 	setMove(18, 330, 100, 80, 1300);
// 	pros::delay(1100);
// 	states.setIntakeState(stateMachine::intake_state::CLOSED);
// 	pros::delay(100);
// 	waitUntilSettled(0);

// 	setMove(-18, 330, 100, 80, 1300);
// 	waitUntilSettled(0);
// 	setMove(0, 92, 0, 100, 800);
// 	waitUntilSettled(20);
// 	setMove(30, 92, 100, 80, 1000);
// 	states.setWingState(stateMachine::wing_state::WINGS_OUT);
// 	pros::delay(200);
// 	states.setIntakeState(stateMachine::intake_state::OPEN);

// 	pros::delay(1000);
// 	setMove(-18, 80, 100, 90, 1000);
// 	// setMove(-72, 315, 105, 70, 2000);	// to opponent matchload station
// 	states.setWingState(stateMachine::wing_state::WINGS_STOWED);
// }

// void shootProgSkills() {
// 	// Init
// 	globalPose.setPoint(24, 16.5, 330);
// 	states.setPuncherAngleState(stateMachine::puncher_angle_state::STEEP);
// 	states.defaultPullback = stateMachine::puncher_state::MID_PULLBACK;

// 	// Fire 44 matchloads + 4 for error
// 	// setMove(-5, globalPose.theta, 80, 60, 800);
// 	// waitUntilSettled(20);
// 	states.setParkingBrakeState(stateMachine::parking_brake_state::BRAKE_ON);
// 	firePuncher(48, 2);
// 	pros::delay(500);

// 	// Drive to mid
// 	setMoveToPoint(48, 60, 0, 100, 100, 0, 2000);
// 	waitUntilSettled(0);
// 	setMove(0, 0, 0, 100, 800);
// 	waitUntilSettled(0);

// 	// Cross barrier
// 	setMove(-10, 0, 100, 80, 1500);
// 	waitUntilSettled(0);
// 	setMoveToPoint(84, 60, 0, 100, 100, 0, 5000);
// 	waitUntilSettled(0);

// 	// Reset against barrier
// 	setMove(-15, 0, 80, 80, 1500);
// 	waitUntilSettled(0);
// 	globalPose.setPoint(78.5, 60, 0);

// 	// Push triballs into goal
// 	states.setWingState(stateMachine::wing_state::WINGS_OUT);
// 	pros::delay(200);
// 	setMove(32, 0, 100, 80, 2000);
// 	waitUntilSettled(0);
// 	states.setWingState(stateMachine::wing_state::WINGS_STOWED);
// 	setMove(-32, 180, 100, 20, 2000);
// 	waitUntilSettled(0);
// 	setMove(0, 120, 0, 100, 1000);
// 	waitUntilSettled(0);
// 	states.setWingState(stateMachine::wing_state::WINGS_OUT);
// 	setMove(39, 100, 100, 70, 2000);
// 	waitUntilSettled(0);
// 	states.setWingState(stateMachine::wing_state::WINGS_STOWED);
// 	setMove(-39, 0, 100, 100, 2000);
// 	waitUntilSettled(0);

// }