#include "myLib_h/auto_h/pid.h"

double PID::calculateOutput(double m_error) {
    // Calculate error
    error = m_error;
    // Calculate derivative
    derivative = (error - lastError);
    // Output 
    output = (error * kP) + (derivative * kD);
    // Last error
    lastError = error;

    return output;
}

double PID::calculate(double pidTarget, double pidCurrent) {
    return calculateOutput(pidTarget - pidCurrent);
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