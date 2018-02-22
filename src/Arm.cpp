#ifndef ARM_CPP
#define ARM_CPP

#include "../include/Motors.h"
#include "../include/Controller.h"
#include "../include/Arm.h"
#include "../include/PID.h"
#include "../include/Sensors.h"
#include "../include/Quickmaths.h"

const int ARM_SPEED = 127;

const int ARM_HOLD_SPEED = 10;
const int ARM_HOLD_VALUE = -500;

PID pid(0, 0, 0, 0, 0);
int goal = 0;
bool up = false;
bool down = false;
bool holdOut = false;

void Arm::MakePID(){
	pid = PID(0.25f, 0.02f, 0.5f, 1000, -1000);
}

void Arm::Up() {
	up = true;
	down = false;
	goal = Sensors::GetValue(Sensor::P_ARM);
}

void Arm::Down() {
	down = true;
	up = false;
	goal = Sensors::GetValue(Sensor::P_ARM);
}

void Arm::Hold() {
	if(up || down) {
		up = false;
		down = false;
	}
}

void Arm::HoldAt(int i) {
	up = false;
	down = false;
	goal = i;
}

void Arm::UpdateControls() {
	if (Controller::GetButton(ButtonGroup::RIGHT_GROUP, JOY_UP))
		Up();
	else if (Controller::GetButton(ButtonGroup::RIGHT_GROUP, JOY_DOWN))
		Down();
	else
		Hold();
}

void Arm::Update() {
	if(up) {
		Motors::SetSpeed(MotorID::ARM, ARM_SPEED);
	}else if(down) {
		Motors::SetSpeed(MotorID::ARM, -ARM_SPEED*0.5f);
	} else {
		int nval = pid.GetValue(Sensors::GetValue(Sensor::P_ARM), goal);
		Motors::SetSpeed(MotorID::ARM, 12);
	}
}

#endif
