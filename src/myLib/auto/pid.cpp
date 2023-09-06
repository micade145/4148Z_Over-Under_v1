#include "myLib_h/auto_h/pid.h"

double PID::calculateOutput(double new_error) {
    // Calculate error
    error = new_error;
    // Calculate derivative
    derivative = (error - lastError);
    // Output 
    output = (error * kP) + (derivative * kD);
    // Last error
    lastError = error;

    return output;
}

double PID::calculate(double new_target, double new_current) {
    return calculateOutput(new_target - new_current);
}

double PID::getError() {
    return error;
}

void PID::reset() {
    error = 0;
    lastError = 0;
    derivative = 0;
    output = 0;
}