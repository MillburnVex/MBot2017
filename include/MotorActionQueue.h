#ifndef MOTOR_ACTION_QUEUE_H
#define MOTOR_ACTION_QUEUE_H
#include "MotorAction.h"

const int MAX_ACTIONS_IN_QUEUE = 20;

class MotorActionQueue {
public:
MotorAction* actions[MAX_ACTIONS_IN_QUEUE];
int maxIndex = 0;
// Returns the index. Save this if you want to remove it later.
// When I have time I'll add a remove feature that takes in
// a MotorAction instead
int Add(MotorAction& action, bool over);
void Remove(int index);
void ShiftLeft(int startIndex);
void Update();
};

#endif
