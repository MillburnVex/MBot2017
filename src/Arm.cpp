#ifndef ARM_CPP
#define ARM_CPP

#include "../include/Motors.h"
#include "../include/Controller.h"
#include "../include/Arm.h"
#include "../include/Sensors.h"
#include "../include/Quickmaths.h"

const bool PRINT = false;

static bool up = false;
static bool down = false;
static bool holdUp = false;
static bool holdDown = true;
const int ARM_SPEED = 100;
const int ARM_CORRECTION_SPEED = 50;
const int ARM_MAX_VALUE = -1800;
const int ARM_MIN_VALUE = -400;
void Arm::Up() {
	up = true;
	down = false;
	holdDown = false;
}

void Arm::Down() {
	down = true;
	up = false;
	holdUp = false;
}

bool Arm::IsFullyUp() {
	return Sensors::GetValue(Sensor::P_ARM) < ARM_MAX_VALUE;
}

bool Arm::IsFullyDown() {
	return Sensors::GetValue(Sensor::P_ARM) > ARM_MIN_VALUE;
}

void Arm::Update() {
	if (Controller::GetButton(ButtonGroup::LEFT_GROUP, JOY_UP))
		Up();
	else if (Controller::GetButton(ButtonGroup::LEFT_GROUP, JOY_DOWN))
		Down();
	if(PRINT) {
		printf("arm: %d, holding up: %d, holding down: %d\n", Sensors::GetValue(Sensor::P_ARM), holdUp, holdUp);
	}
	if (down) {
		if (IsFullyDown()) {
			down = false;
			holdDown = true;
			Motors::Stop(MotorID::ARM);
		} else
			Motors::SetSpeed(MotorID::ARM, -ARM_SPEED);
	} else if (up) {
		if (IsFullyUp()) {
			up = false;
			holdUp = true;
			Motors::Stop(MotorID::ARM);
		} else
			Motors::SetSpeed(MotorID::ARM, ARM_SPEED);
	} else if(holdUp) {
		if(!IsFullyUp()) {
			Motors::SetSpeed(MotorID::ARM, Math::Abs(ARM_MAX_VALUE - Sensors::GetValue(Sensor::P_ARM)) * 0.2);
		} else
			Motors::Stop(MotorID::ARM);
	} else if(holdDown) {
		if(Sensors::GetValue(Sensor::P_ARM) > ARM_MIN_VALUE) {
			Motors::SetSpeed(MotorID::ARM, Math::Abs(ARM_MIN_VALUE - Sensors::GetValue(Sensor::P_ARM)) * 0.2);
		} else
			Motors::Stop(MotorID::ARM);
	}
}

#endif
