#include "main.h"
#include "motor.h"

  Motor::Motor(){
    location = -1;
  }

  Motor::Motor(int loc, char* mname, bool rev){
    location = loc;
    reversed = rev;
    name = mname;
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
