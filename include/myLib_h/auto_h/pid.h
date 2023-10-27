#ifndef PID_H
#define PID_H
#include "main.h"

/** @brief PID Class */
class PID {
private: 
  double kP = 0;
  double kI = 0;
  double kD = 0;
  
  double error = 0;
  double lastError = 0;
  double integral = 0;
  double integralBound = 0;
  double integralErrorThresh = 0;
  double derivative = 0;
  double output = 0;
  
public:
  
  /**
   * @brief PID Constructor that takes in P and D gains
   * @param new_kP P term for PID object
   * @param new_kD D term for PID object
  */
  PID(double new_kP, double new_kD) {
    kP = new_kP;
    kD = new_kD;
    kI = integralErrorThresh = 0;
  }
  
  /**
   * @brief PID Constructor that takes in P, I, D gains and an integral error threshold
   * @param new_kP P term for PID object
   * @param new_kI I term for PID object
   * @param new_kD D term for PID object
   * @param new_integralErrorThresh Error threshold to start integrating
  */
  PID(double new_kP, double new_kI, double new_kD, double new_integralErrorThresh) {
    kP = new_kP;
    kI = new_kI;
    kD = new_kD;
    integralErrorThresh = new_integralErrorThresh;
  }

  /**
   * @brief Calculates PID output using an error value
   * @param new_error Error value
  */
  double calculateOutput(double new_error); // , double upperBound, double lowerBound

  /**
   * @brief Wrapper for calculateOutput that uses current and target values
   * @param new_target Target value
   * @param new_current Current value
  */
  double calculate(double new_target, double new_current);
  
  /** @brief Returns stored error in PID object */
  double getError();

  /** @brief Resets PID components to 0 */
  void reset();
};

#endif