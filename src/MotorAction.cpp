#ifndef MOTORACTION
#define MOTORACTION
#include "MotorAction.h"

MotorAction::MotorAction(int _goalValue, MotorID _motorID, int _cancelThreshold) {
        goalValue = _goalValue;
        motorID = _motorID;
        cancelThreshold = _cancelThreshold;
}

#endif
