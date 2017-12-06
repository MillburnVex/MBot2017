#ifndef MOTORACTION_H
#define MOTORACTION_H

#include "Sensors.h"
#include "Motors.h"

class MotorAction {
public:
// Where this should be progressing to. Progression is judged simply on a numeric basis,
// so if the current value is getting smaller and the goal value is negative that's good (or vice versa).
// Otherwise, we wait <cancelThreshold> update cycles and then cancel it
int goalValue;
// The number of ticks this action will wait with no progress before cancelling
int cancelThreshold;
// The number of ticks to run this for. -1 means forever
int timeLimit;
// The sensor to update progress against. SensorID::NONE means don't update progress
SensorID sensor;
// The motor to run this on
Motor& motor;

MotorAction(Motor& _motor, int _goalValue, SensorID _sensor, int _timeLimit = -1, int _cancelThreshold = 20);
MotorAction(Motor& _motor, int _goalValue, int _timeLimit = -1, int _cancelThreshold = 20);
};

#endif
