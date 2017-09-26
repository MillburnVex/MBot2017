#ifndef MOTOR_H
#define MOTOR_H

#include "main.h"

class Motor{
public:
  int location;
  int currentpower = 0;
  char* name = "";
  bool reversed = false;

  Motor();

  Motor(int loc, char* mname, bool rev);

  Motor(int loc);

  void setSpeed(int speed);

  void stop();
};

#endif /* end of include guard: MOTOR_H */
