#ifndef MOTOR_ACTION_QUEUE
#define MOTOR_ACTION_QUEUE

#include "Quickmaths.h"
#include "MotorActionQueue.h"

// Returns the index. Save this if you want to remove it later.
// When I have time I'll add a remove feature that takes in
// a MotorAction instead
int MotorActionQueue::Add(MotorAction& action, bool over) {
	if(maxIndex == MAX_ACTIONS_IN_QUEUE) {
		print("Adding too many actions to queue !");
		return -1;
	}
	// Combine
	for(int index = 0; index < MAX_ACTIONS_IN_QUEUE; ++index) {
		MotorAction* p = actions[index];
		if(p != nullptr) {
			MotorAction& a = *p;
			if(a == action) {
				if(over) {
					// Don't stop the motor because they have the same motors so
					// it will be going anyways
					actions[index] = &action;
					return index;
				}
				// Combine them. Logic is as follows:
				// Max the goal value
				// Min the cancel threshold
				// Max the time limit
				// Keep current progress of old one
				// TODO what do i do if they have different sensors?
				a.goalValue = Math::Max(a.goalValue, action.goalValue);
				a.cancelThreshold = Math::Min(a.cancelThreshold, action.cancelThreshold);
				a.timeLimit = Math::Max(a.timeLimit, action.timeLimit);
				a.speed = Math::Max(a.speed, action.speed);
				return index;
			}
		}
	}
	// Assume there are no other actions who need combining with
	action.motor.SetSpeed(action.speed);
	actions[maxIndex + 1] = &action;
	return ++maxIndex;
}

// Simply removes the element at this index and shifts the
// rest of the queue
void MotorActionQueue::Remove(int index) {
	if(actions[index] == nullptr) {
		print("Removing a nonexistent action !");
		return;
	}
	actions[index]->motor.Stop();
	ShiftLeft(index);
}
// Inclusively shifts the array to the left
void MotorActionQueue::ShiftLeft(int startIndex) {
	for(int i = MAX_ACTIONS_IN_QUEUE - 1; i >= startIndex; --i) {
		actions[i] = actions[i + 1];
	}
	actions[MAX_ACTIONS_IN_QUEUE] = nullptr;
}

void MotorActionQueue::Update() {
	for(int index = 0; index < MAX_ACTIONS_IN_QUEUE; ++index) {
		MotorAction* m = actions[index];
		if(m != nullptr) {
			MotorAction& a = *m;
			bool hasRemoved = false;
			a.currentTicks++;
			if(a.sensor != SensorID::NONE) {
				// Progress!
				if(!Sensors::HasProgressed(a.sensor, a.currentValue, a.goalValue)) {
					a.ticksWithoutProgress++;
					if(a.ticksWithoutProgress >= a.cancelThreshold) {
						Remove(index);
						hasRemoved = true;
					}
				}
				a.currentValue = Sensors::GetValue(a.sensor);
			}
			if(a.currentTicks >= a.timeLimit) {
				Remove(index);
				hasRemoved = true;
			}
			if(!hasRemoved) {
				a.motor.SetSpeed(a.speed);
				++index;
			} else {
				hasRemoved = false;
			}
		}
	}
}
#endif
