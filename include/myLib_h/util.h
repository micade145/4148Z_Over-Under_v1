#ifndef UTIL_H
#define UTIL_H
#include "main.h"

// // Math constants
// extern double PI;

// Conversion rates
extern double PCT_TO_VOLT;
extern double VOLT_TO_PCT;

extern double RAD_TO_DEG;
extern double DEG_TO_RAD;

// useful functions
extern double constrainValue(double input, double max, double min);
extern double constrainAngle180(double input);
extern double constrainAngle90(double input);
extern double returnSign(double input);

#endif