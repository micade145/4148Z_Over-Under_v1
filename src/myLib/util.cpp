#include "myLib_h/util.h"

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