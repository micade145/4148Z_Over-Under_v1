#include "myLib_h/auto_h/pid.h"

double PID::calculateOutput(double new_error) { //, double upperBound, double lowerBound
    error = new_error;

    // Calculate derivative
    derivative = (error - lastError);

    // Calculate integral only if kI exists
    if(kI > 0) {
        if(std::fabs(error) < integralErrorThresh) { // Start integrating when close to target
            integral += error;
        }
        if(getSign(error) != getSign(lastError)) {   // Set integral to 0 if we cross target
            integral = 0;
        }
    }

    // Calculate output 
    output = (error * kP) + (integral * kI) + (derivative * kD);

    // Constrain output to upper and lower power bounds
    // if(output > upperBound) {output = upperBound;}
    // if(output < lowerBound) {output = lowerBound;}

    // Update last error
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
    integral = 0;
    derivative = 0;
    output = 0;
}