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
static bool holdOut = false;
const int ARM_SPEED = 100;
const int ARM_HOLD_SPEED = 10;
const int ARM_MAX_VALUE = -1800;
const int ARM_MIN_VALUE = 20;
const int ARM_HOLD_VALUE = -500;
const int ARM_CORRECTION_THRESHOLD = 100;
const int ARM_TICKS_TO_CORRECT_FOR_MOMENTUM = 10;
const int ARM_MOMENTUM_CORRECTION_SPEED = 30;
static int armMomentumTicks = -1;
static int goal = ARM_MIN_VALUE;

void Arm::Up() {
	up = true;
	down = false;
	holdOut = false;
	armMomentumTicks = -1;
	goal = ARM_MAX_VALUE;
}

void Arm::Down() {
	down = true;
	up = false;
	holdOut = false;
	armMomentumTicks = -1;
	goal = ARM_MIN_VALUE;
}

void Arm::Hold() {
	if(up || down) {
		up = false;
		down = false;
		armMomentumTicks = 0;
		goal = Sensors::GetValue(Sensor::P_ARM);
	}
}

bool Arm::IsHeldOut() {
	return Math::Abs(Sensors::GetValue(Sensor::P_ARM) - ARM_HOLD_VALUE) < ARM_CORRECTION_THRESHOLD;
}

void Arm::HoldAt(int i) {
	up = false;
	down = false;
	armMomentumTicks = -1;
	goal = i;
}

bool Arm::IsFullyUp() {
	return Sensors::GetValue(Sensor::P_ARM) < ARM_MAX_VALUE;
}

bool Arm::IsFullyDown() {
	return Sensors::GetValue(Sensor::P_ARM) > ARM_MIN_VALUE;
}

void Arm::Update() {
	if (Controller::GetButton(ButtonGroup::RIGHT_GROUP, JOY_UP))
		Up();
	else if (Controller::GetButton(ButtonGroup::RIGHT_GROUP, JOY_DOWN))
		Down();
	else
		Hold();

	if(up && IsFullyUp()) {
		Hold();
		Motors::SetSpeed(MotorID::ARM, ARM_HOLD_SPEED);
		return;
	}
	int val = Sensors::GetValue(Sensor::P_ARM);
	if(PRINT) {
		printf("up: %d, down: %d, goal: %d\n, val: %d", up, down, goal, val);
	}
	if(armMomentumTicks != -1) {
		if(armMomentumTicks == ARM_TICKS_TO_CORRECT_FOR_MOMENTUM) {
			armMomentumTicks = -1;
			goal = val;
			Motors::SetSpeed(MotorID::ARM, ARM_HOLD_SPEED);
		} else {
			++armMomentumTicks;
			Motors::SetSpeed(MotorID::ARM, ARM_MOMENTUM_CORRECTION_SPEED);
		}
	} else if(Math::Abs(goal - val) > ARM_CORRECTION_THRESHOLD) {
		int sign = -Math::Sign(goal - val);
		Motors::SetSpeed(MotorID::ARM, sign * Math::Abs(goal - val) * 0.7);
	} else {
		Motors::SetSpeed(MotorID::ARM, ARM_HOLD_SPEED);
	}

}

#endif
