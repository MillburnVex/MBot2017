#ifndef MOTOR_H
#define MOTOR_H

#include "main.h"

class Motor{
  int location;
  int currentpower = 0;;
  bool reversed = false;

public:
  Motor(int loc, bool rev);

  Motor(int loc);

  void setSpeed(int speed);

  void stop();
};

#endif /* end of include guard: MOTOR_H */
