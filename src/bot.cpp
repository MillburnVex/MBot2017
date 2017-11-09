#include "bot.h";

Ultrasonic Bot::sonic;

Bot::Bot(){

}

Motor Bot::getMotor(char* name){
  for(int i = 0; i < 12; i++){
    if(strcmp(motors[i].name, name)){
      printf("%s\n", motors[i].name);
      printf("%d\n", motors[i].location);
      return motors[i];
    }
  }
}

Motor Bot::getMotor(int loc){
  return motors[loc];
}

void Bot::setMotor(char* name, int speed){
  getMotor(name).setSpeed(speed);
}

void Bot::addMotor(Motor motor){
  motors[motor.location] = motor;
}

MotorGroup Bot::getGroup(char *name){
  for(int i = 0; i < 6; i++){
    if(groups[i].getName() == name){
      return groups[i];
    }
  }
}

void Bot::setGroup(char *name, int speed){
  getGroup(name).setPower(speed);
}

void Bot::addGroup(MotorGroup group){
  groups[lgroup] = group;
  lgroup++;
}

Bot bot;

Bot getBot(){
  return bot;
}
