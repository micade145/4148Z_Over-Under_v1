#include "robot_h/intake.h"

// bool R2 = true;
// double intVelo;
// int holdCount = 0;
// bool intConHeld = false;
// bool intClosedYet = false;
// bool closed = false;

// void intakeControl() {
//     // add current intake control
//     controller.get_digital_new_press
// }

int intakeControlTask() {
    bool R2 = true;
    double intVelo;
    int holdCount = 0;
    bool intConHeld = false;
    bool intClosedYet = false;
    bool closed = false;
    
    while(true) {
        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            R2 = true;
        }
        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
            R2 = true;
        }

        
    }
}

