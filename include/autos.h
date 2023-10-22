#ifndef AUTOS_H
#define AUTOS_H
#include "main.h"

extern int autoToRun;

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
// enum progSkills_mode{LEFT, RIGHT};

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

/** @brief Setup: Under Hang Bar of Offensive Zone, facing goal, ~45 deg --
 * 
 * Shoot preload, (turn) intake hangBarTriball, shoot to goal; Knock out Matchload triball & push into goal; Score 1 from mid and 2 from auto line
*/
extern void sixBall();

/** @brief Setup: In front of matchload station, back to goal, 200 deg --
 * 
 * Push preload into goal; Score 1 from mid and 2 from auto line
*/
extern void fourBall();

/** @brief Setup: Right side of Matchload Station, 45 deg --
 * 
 * Shoot preloads (44 + 4 [error margin]); move across to other zone; push triballs into goal
*/
extern void progSkills();

extern void defense3Ball();

extern void shootDropProgSkills();
extern void dropProgSkills();
extern void shootProgSkills();

// ************* Deprecated autos !! ************* //

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