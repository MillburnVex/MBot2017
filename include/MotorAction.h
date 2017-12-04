#ifndef MOTORACTION_H
#define MOTORACTION_H

#include "SensorID.h"

struct MotorID {int ID; SensorID sensorID;};

class MotorAction {
public:
int goalValue;
int cancelThreshold;
MotorID motorID;

MotorAction(int _goalValue, MotorID _motorID, int cThreshold = 20);
};

#endif
