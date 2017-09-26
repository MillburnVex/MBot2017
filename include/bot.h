#ifndef BOT_H

#define BOT_H

#include "main.h"
#include "fastmath.h"
#include "motor.h"
#include "vectors.h"

class Bot{
public:
  Motor motors[12];
  //12 digital
  //8 analog

  Bot();

  Motor getMotor(char* name);

  Motor getMotor(int loc);

  void addMotor(Motor motor);
};

Bot getBot();

#endif
