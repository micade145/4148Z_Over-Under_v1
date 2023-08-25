#ifndef UTIL_H
#define UTIL_H
#include "main.h"

extern double constrainValue(double input, double max, double min);
extern double constrainAngle180(double input);
extern double constrainAngle90(double input);
extern double returnSign(double input);

#endif