#include "myLib_h/util.h"
#include <cmath>

// // Math constants (why doesn't cmath work??)
// double M_PI = 3.14159265358979323846;

// Conversion rates
double PCT_TO_VOLT = 12.7 / 100;
double VOLT_TO_PCT = 100 / 12.7;

double RAD_TO_DEG = 180 / M_PI;
double DEG_TO_RAD = M_PI / 180;

// useful functions
double constrainValue(double input, double max, double min) {
    if(input > max) {input = max;}
    if(input < min) {input = min;}
    return(input);
}

extern double constrainAngle180(double input) {
    while(!(input >= 0 && input < 360)) {
        if( input < 0 ) { input += 360; }
        if(input >= 360) { input -= 360; }
    }
    return(input);
}

extern double constrainAngle90(double input) {
    while(!(input >= -90 && input < 90)) {
        if( input < -90 ) { input += 180; }
        if(input >= 90) { input -= 180; }
    }
    return(input);
}

extern double returnSign(double input) {
    return(std::fabs(input) / input);
}