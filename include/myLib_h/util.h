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

/**
 * @brief Returns constrained input as a double
*/
extern double constrainValue(double input, double max, double min);
/**
 * @brief Returns constrained input as an int
*/
extern double constrainVoltage(int input, int max, int min);

extern double constrainAngle180(double input);
extern double constrainAngle90(double input);
extern double returnSign(double input);

#endif