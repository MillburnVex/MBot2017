#ifndef MOTOR_H
#define MOTOR_H

#include "main.h"

class Motor{
public:
  int location = -1;
  int currentpower = 0;
  char* name = "";
  bool reversed = false;

  Motor();

  Motor(int loc, char* mname, bool rev);

  Motor(int loc);

  void setSpeed(int speed);

  void stop();
};

class MotorGroup{
private:
  char* name;
  int currentpower;
  int motorcount;
  Motor* motors;

public:
  MotorGroup();

  MotorGroup(Motor usedmotors[], int motoramount);

  bool isUsed();

  int getPower();

  void setPower(int npower);

  char* getName();

  Motor* getMotors();
};

#endif /* end of include guard: MOTOR_H */
