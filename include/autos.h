#ifndef AUTOS_H
#define AUTOS_H
#include "main.h"

/** @brief Shakes robot to help engage PTO */
extern void shakeRobot();

// ******* Test Autos *******//
// Odom tests
extern void odomBoxTest();
extern void odomTriangleTest();

// Squiggles
extern void squigglesTest();
extern void chainedMoveToPoint();

// Curves
extern void oldCurveTest();
extern void curveTuning();

/** @brief Parameter for defenseAuto */
enum defense_auto_mode{SOLO, ELIMS};
enum offense_auto_mode{SAFE, RISKY};

// ******* Match Autos *******//
/** @brief Setup: Right side of Matchload Station, 45 deg -- Shoot preload; Score 2 from auto line;
 * 
 * (SOLO) Knock out matchload triball; Touch Hang Bar -- OR -- (ELIMS)  Drive back to Matchload Station
*/
extern void defenseAuto(defense_auto_mode s);

/** @brief Setup: In front of Matchload station, facing goal, 0 deg -- Push preload into goal; Score 1 from mid;
 * 
 *  (SAFE) Drive to Hang Bar and intake triball -- OR -- (RISKY) Score 2 from auto line
*/
extern void offenseAuto(offense_auto_mode s);

/** @brief Setup: Under Hang Bar of Offensive Zone, facing Triball, 270 deg --
 * 
 * Shoot preload, intake Triball, shoot to goal; Knock out Matchload triball & push into goal; Score 1 from mid and 2 from auto line
*/
extern void sixBall();


// ************* Deprecated autos :( ************* //

/** @brief Setup: Right side of Matchload Station, 45 deg --
 * 
 * 
*/
extern void defenseElims();

/** @brief Setup: In front of Matchload station, facing goal, 0 deg --
 * 
 * Push preload into goal; Score 1 from mid; 
*/
extern void offenseSafe();

#endif