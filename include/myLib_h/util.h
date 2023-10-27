#ifndef UTIL_H
#define UTIL_H
#include "main.h"

// ******** Constants ******** //
// extern double PI;


// ******** Conversion Rates ******** //

/** @brief 127 volt / 100 pct */
extern double PCT_TO_VOLT;

/** @brief 100 pct / 127 volt */
extern double VOLT_TO_PCT;

/** @brief 180 / M_PI */
extern double RAD_TO_DEG;

/** @brief M_PI / 180*/
extern double DEG_TO_RAD;

/** @brief For 2.75" wheels: 360 / (2.75 * M_PI) */
extern double DRIVE_INCH_TO_DEG_275;

/** @brief For 2.75" wheels: (2.75 * M_PI) / 360 */
extern double DRIVE_DEG_TO_INCH_275;


// ******** Util Functions ******** //
/** 
 * @brief Constrains input as a DOUBLE
 * @return DOUBLE
*/
extern double constrainValue(double input, double max, double min);

/** 
 * @brief Constrains input as an INT
 * @return INTEGER
*/
extern double constrainVoltage(int input, int max, int min);

/** @brief Constrains angle between 0 and 360. */
extern double constrainAngle360(double input);

/** @brief Constrains angle from -180 to 180. 
 *  Useful for taking the shortest turn to a target
*/
extern double constrainAngle180(double input);

/** @brief Constrains angle from -90 to 90. 
 *  Useful for finding angle when reversing movement
*/
extern double constrainAngle90(double input);

/** @brief Returns either 1 or -1 as the sign of the input */
extern double getSign(double input);

#endif