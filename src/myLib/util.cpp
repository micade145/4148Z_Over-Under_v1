#include "myLib_h/util.h"
#include <cmath>

// // Math constants (why doesn't cmath work??)
// double M_PI = 3.14159265358979323846;

// ******** Conversion Rates ******** //
double PCT_TO_VOLT = 127 / 100;
double VOLT_TO_PCT = 100 / 127;

double RAD_TO_DEG = 180 / M_PI;
double DEG_TO_RAD = M_PI / 180;

double DRIVE_INCH_TO_DEG_275 = 360 / (2.75 * M_PI);
double DRIVE_DEG_TO_INCH_275 = (2.75 * M_PI) / 360;


// ******** Util Functions ******** //

double constrainValue(double input, double max, double min) {
    if(input > max) {input = max;}
    if(input < min) {input = min;}
    return(input);
}
double constrainVoltage(int input, int max, int min) {
    if(input > max) {input = max;}
    if(input < min) {input = min;}
    return(input);
}

extern double constrainAngle180(double input) {
    while(!(input >= 0 && input < 360)) {
        if(input < 0) { input += 360; }
        if(input >= 360) { input -= 360; }
    }
    return(input);
}
extern double constrainAngle90(double input) {
    while(!(input >= -90 && input < 90)) {
        if(input < -90) { input += 180; }
        if(input >= 90) { input -= 180; }
    }
    return(input);
}

extern double getSign(double input) {
    return(std::fabs(input) / input);
}