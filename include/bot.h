#ifndef BOT_H

#define BOT_H

#include "main.h"
#include "fastmath.h"
#include "motor.h"
#include "vectors.h"

class Bot{
public:
  Motor motors[12];
  MotorGroup groups[6];
  int lgroup = 0;
  //12 digital
  //8 analog

  Bot();

  Motor getMotor(char* name);

  Motor getMotor(int loc);

  void setMotor(char* name, int speed);

  void addMotor(Motor motor);

  MotorGroup getGroup(char* name);

  void setGroup(char* name, int speed);

  void addGroup(MotorGroup group);
};

Bot getBot();

#endif
