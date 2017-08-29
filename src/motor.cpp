#include "main.h"
#include "motor.h"

  Motor::Motor(int loc, bool rev){
    location = loc;
    reversed = rev;
  }

  Motor::Motor(int loc){
    location = loc;
  }

  void Motor::setSpeed(int speed){
    currentpower = speed;
    motorSet(location, currentpower);
  }

  void Motor::stop(){
    currentpower = 0;
    motorStop(location);
  }
