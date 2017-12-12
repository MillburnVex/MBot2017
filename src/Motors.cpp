#ifndef MOTORS
#define MOTORS
#include "main.h"
#include "Motors.h"

Motor::Motor(int _id, SensorID _defaultSensorID) {
	id = _id;
	defaultSensorID = _defaultSensorID;
}

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
