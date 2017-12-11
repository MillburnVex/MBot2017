#ifndef MOTORACTION
#define MOTORACTION
#include "MotorAction.h"

MotorAction::MotorAction(Motor& _motor, int _goalValue, SensorID _sensor,
                         int _timeLimit, int _cancelThreshold) :
	motor(_motor) {
	goalValue = _goalValue;
	sensor = _sensor;
	cancelThreshold = _cancelThreshold;
}

MotorAction::MotorAction(Motor& _motor, int _goalValue,
                         int _timeLimit, int _cancelThreshold) :
	motor(_motor) {
	goalValue = _goalValue;
	cancelThreshold = _cancelThreshold;
}

bool MotorAction::operator==(MotorAction& other) {
	return this->motor == other.motor && this->currentTicks == other.currentTicks && this->currentValue == other.currentValue;
}

MotorAction& MotorAction::operator=(MotorAction &other) {
	this->motor = other.motor;
	return *this;
}
#endif
