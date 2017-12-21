#ifndef COMPOUND_ACTION
#define COMPOUND_ACTION
#include "MotorAction.h"
#include "Bot.h"
#include "CompoundAction.h"

// MotorAction(Motor& _motor, int _speed, int _goalValue, SensorID _sensor, int _timeLimit = -1, int _cancelThreshold = -1);

DriveLeft::DriveLeft(int _speed) {
	speed = _speed;
}

void DriveLeft::Run() {
	auto bl = MotorAction(Motors::DRIVE_BOTTOM_LEFT, speed, 0, SensorID::NONE, 1);
	auto tl = MotorAction(Motors::DRIVE_TOP_LEFT, speed, 0, SensorID::NONE, 1);
	Bot::ExecuteAction(bl);
	Bot::ExecuteAction(tl);
}

DriveRight::DriveRight(int _speed) {
	this->speed = _speed;
}

void DriveRight::Run() {
	auto br = MotorAction(Motors::DRIVE_BOTTOM_RIGHT, speed, 0, SensorID::NONE, 1);
	auto tr = MotorAction(Motors::DRIVE_TOP_RIGHT, speed, 0, SensorID::NONE, 1);
	Bot::ExecuteAction(br);
	Bot::ExecuteAction(tr);
}

DriveRotate::DriveRotate(int _speed, int _dir){
	this->speed = _speed;
	this->dir = _dir;
}

void DriveRotate::Run() {
	if(dir == 1) {
		DriveLeft(-speed).Run();
		DriveRight(speed).Run();
	} else {
		DriveRight(-speed).Run();
		DriveLeft(speed).Run();
	}
}

DriveVertical::DriveVertical(int _speed) {
	this->speed = _speed;
}

void DriveVertical::Run() {
	DriveLeft(speed).Run();
	DriveRight(speed).Run();
	printf("tick count: %d\n", Bot::tickCount);
}


// tick, predicate, onFinish, timelimit

#endif
