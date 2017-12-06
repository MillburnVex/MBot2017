#ifndef MOTORS
#define MOTORS
#include "main.h"
#include "Motors.h"
void Motor::SetSpeed(int speed){
	currentPower = speed;
	motorSet(id, currentPower);
}

void Motor::Stop(){
	currentPower = 0;
	motorStop(id);
}

bool Motor::operator==(Motor other) {
	return other.id == id;
}
#endif
