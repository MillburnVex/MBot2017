#ifndef BOT_H

#define BOT_H

#include "main.h"
#include "fastmath.h"
#include "motor.h"
#include "vectors.h"

int const llift = 2;
int const rlift = 9;
int const arm = 5;
int const brdrive = 8;
int const bldrive = 4;
int const frdrive = 7;
int const fldrive = 3;
int const claw = 6;
int const goallift = 10;
int const armpotentiometer = 4;
int const lliftpotentiometer = 2;
int const rliftpotentiometer = 1;
int const gliftpotentiometer = 3;

class Bot{
public:
  static Ultrasonic sonic;
  static Gyro gyro;
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
