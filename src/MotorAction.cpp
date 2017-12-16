#ifndef MOTORACTION
#define MOTORACTION
#include "MotorAction.h"

MotorAction::MotorAction(Motor& _motor, int _speed, int _goalValue, SensorID _sensor,
                         int _timeLimit, int _cancelThreshold) :
	motor(_motor) {
	speed = _speed;
	goalValue = _goalValue;
	sensor = _sensor;
	cancelThreshold = _cancelThreshold;
}

MotorAction::MotorAction(Motor& _motor, int _speed, int _goalValue,
                         int _timeLimit, int _cancelThreshold) :
	motor(_motor) {
	speed = _speed;
	goalValue = _goalValue;
	cancelThreshold = _cancelThreshold;
}

bool MotorAction::operator==(const MotorAction& other) const {
	return this->motor == other.motor && this->currentTicks == other.currentTicks && this->currentValue == other.currentValue;
}

MotorAction& MotorAction::operator=(const MotorAction &other) {
	this->motor = other.motor;
	return *this;
}
#endif
