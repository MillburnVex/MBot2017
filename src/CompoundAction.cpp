#ifndef COMPOUNDACTION
#define COMPOUNDACTION
#include "MotorAction.h"
#include "Bot.h"

class CompoundAction {
virtual void Run() = 0;
};

namespace CompoundActions {

class DriveVertical : CompoundAction {
int speed;
DriveVertical(int _speed) {
	this->speed = _speed;
}
// MotorAction(Motor& _motor, int _speed, int _goalValue, SensorID _sensor, int _timeLimit = -1, int _cancelThreshold = -1);
void Run() {
	auto bl = MotorAction(Motors::DRIVE_BOTTOM_LEFT, speed, 0, SensorID::NONE, 1);
	auto br = MotorAction(Motors::DRIVE_BOTTOM_RIGHT, speed, 0, SensorID::NONE, 1);
	auto tl = MotorAction(Motors::DRIVE_TOP_LEFT, speed, 0, SensorID::NONE, 1);
	auto tr = MotorAction(Motors::DRIVE_TOP_RIGHT, speed, 0, SensorID::NONE, 1);
	Bot::ExecuteAction(bl);
	Bot::ExecuteAction(br);
	Bot::ExecuteAction(tl);
	Bot::ExecuteAction(tr);
}
};
class DriveRotate : CompoundAction {
int speed;
int dir;
// dir 1 = right, dir -1 = left
DriveRotate(int _speed, int _dir) {
	this->speed = _speed;
	this->dir = _dir;
}
void Run() {
	if(dir == 1) {
		auto bl = MotorAction(Motors::DRIVE_BOTTOM_LEFT, speed, 0, SensorID::NONE, 1);
		auto br = MotorAction(Motors::DRIVE_BOTTOM_RIGHT, speed, 0, SensorID::NONE, 1);
	}

	auto tl = MotorAction(Motors::DRIVE_TOP_LEFT, speed, 0, SensorID::NONE, 1);
	auto tr = MotorAction(Motors::DRIVE_TOP_RIGHT, speed, 0, SensorID::NONE, 1);
	Bot::ExecuteAction(bl);
	Bot::ExecuteAction(br);
	Bot::ExecuteAction(tl);
	Bot::ExecuteAction(tr);
}
};
// tick, predicate, onFinish, timelimit
}
#endif
