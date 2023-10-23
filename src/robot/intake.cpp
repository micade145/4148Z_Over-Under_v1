#include "robot_h/intake.h"

// ******** Intake Constants ******** //
int INTAKE_CLOSE_THRESHOLD = 20;
int INTAKE_OPEN_THRESHOLD = 20;

// ******** Intake Variables ******** //
int openCount = 0;
int closeCount = 0;


// ******** Intake Helper Functions ******** //
void spinIntake(int intakeVolt) {
    leftIntake.move(intakeVolt);
    rightIntake.move(intakeVolt);
}
void stopIntake(pros::motor_brake_mode_e_t newIntakeBrakeMode) {
    leftIntake.set_brake_mode(newIntakeBrakeMode);
    rightIntake.set_brake_mode(newIntakeBrakeMode);
    leftIntake.brake();
    rightIntake.brake();
}


// ******** Intake Opcontrol function ******** //
bool R2 = true;
bool intakeClosed = false;
void intakeOpControl() {
    // add current intake control
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {R2 = true;}
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {R2 = false;}

    if(R2) {
        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            states.setIntakeState(stateMachine::intake_state::INTAKING);
        }
        else {states.setIntakeState(stateMachine::intake_state::OPEN);}
    }
    else {
        if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
            intakeClosed = !intakeClosed;
        }

        if(intakeClosed) {
            states.setIntakeState(stateMachine::intake_state::CLOSED); 
            // pros::screen::print(TEXT_MEDIUM_CENTER, 6, "SHOULD BE CLOSE");
        }
        else {
            states.setIntakeState(stateMachine::intake_state::OPEN);
            // pros::screen::print(TEXT_MEDIUM_CENTER, 6, "SHOULD BE OPEN");
        }
    }
}


