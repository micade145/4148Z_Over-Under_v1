#ifndef PID_H
#define PID_H
#include "main.h"

class PID {
private: 
  double kP = 0;
  double kD = 0;
  
  double error = 0;
  double lastError = 0;
  double derivative = 0;
  double output = 0;
  
public:
  PID(double new_kP, double new_kD) {
    kP = new_kP;
    kD = new_kD;
  }
  double calculateOutput(double new_error);
  double calculate(double new_target, double new_current);
  double getError();
  void reset();
};

#endif