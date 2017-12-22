#ifndef DRIVE
#define DRIVE
#include "Motors.h"
#include "Drive.h"
#include "Quickmaths.h"
#include "Controller.h"

void Drive::Update() {
	int vertical = Controller::GetJoystick(JoystickPort::DRIVE_VERTICAL);
	int rotate = Controller::GetJoystick(JoystickPort::DRIVE_ROTATE);
	if(Math::Abs(vertical) > Math::Abs(rotate)) {
		if(vertical < 0) {
			Move(Drive::BACKWARDS, Math::Abs(vertical));
		} else if(vertical > 0) {
			Drive::Move(Drive::FORWARDS, vertical);
		} else {
			Drive::Stop();
		}
	} else {
		if(rotate < 0) {
			Move(ROTATE_LEFT, Math::Abs(rotate));
		} else if(rotate > 0) {
			Move(ROTATE_RIGHT, rotate);
		} else {
			Drive::Stop();
		}
	}
}

void Drive::LeftSide(int speed) {
	Motors::SetSpeed(MotorID::DRIVE_LEFT, speed);
}
void Drive::RightSide(int speed) {
	Motors::SetSpeed(MotorID::DRIVE_RIGHT, speed);
}

// Speed should always be positive because it's dependent on
// direction, thus, speed is an unsigned int
void Drive::Move(int dir, unsigned int speed) {
	if(dir == ROTATE_LEFT) {
		LeftSide(-speed);
		RightSide(speed);
	}

	if(dir == ROTATE_RIGHT) {
		LeftSide(speed);
		RightSide(-speed);
	}

	if(dir == FORWARDS) {
		RightSide(speed);
		LeftSide(speed);
	}

	if(dir == BACKWARDS) {
		RightSide(-speed);
		LeftSide(-speed);
	}
}

void Drive::Stop() {
	RightSide(0);
	LeftSide(0);
}
#endif
