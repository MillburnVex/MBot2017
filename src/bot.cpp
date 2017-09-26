#include "bot.h";

Bot::Bot(){

}

Motor Bot::getMotor(char* name){
  for(int i = 0; i < 12; i++){
    if(motors[i].name == name){
      return motors[i];
    }
  }
  return 0;
}

Motor Bot::getMotor(int loc){
  return motors[loc];
}

void Bot::addMotor(Motor motor){
  motors[motor.location] = motor;
}

Bot bot;

Bot getBot(){
  return bot;
}
