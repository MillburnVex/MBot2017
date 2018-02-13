#ifndef DRIVE
#define DRIVE
#include "../include/Motors.h"
#include "../include/Drive.h"
#include "../include/Quickmaths.h"
#include "../include/Controller.h"

const float SPEED_MULTIPLIER = 1.0f;
const int deadzone = 20;
static int vertical = 0;
static int rotate = 0;

void Drive::UpdateControls() {
	vertical = Controller::GetJoystick(JoystickPort::DRIVE_VERTICAL) * SPEED_MULTIPLIER;
	rotate = Controller::GetJoystick(JoystickPort::DRIVE_ROTATE) * SPEED_MULTIPLIER;
}

void Drive::Update() {
	if(abs(vertical) > deadzone || abs(rotate) > deadzone) {
		Move(vertical,rotate);
	} else {
		Stop();
	}
}

void Drive::LeftSide(int speed) {
	Motors::SetSpeed(MotorID::DRIVE_LEFT, speed);
}
void Drive::RightSide(int speed) {
	Motors::SetSpeed(MotorID::DRIVE_RIGHT, -speed);
}

void Drive::Move(int x, int z) {
	LeftSide(x+z);
	RightSide(x-z);
}

void Drive::Stop() {
	RightSide(0);
	LeftSide(0);
}
#endif
