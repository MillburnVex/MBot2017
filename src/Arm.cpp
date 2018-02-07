#ifndef ARM_CPP
#define ARM_CPP

#include "../include/Motors.h"
#include "../include/Controller.h"
#include "../include/Arm.h"
#include "../include/PID.h"
#include "../include/Sensors.h"
#include "../include/Quickmaths.h"

const bool PRINT = true;
//ur mnomo gay
const int ARM_SPEED = 100;

const int ARM_HOLD_SPEED = 10;
const int ARM_HOLD_VALUE = -500;
const int ARM_CORRECTION_THRESHOLD = 30;
const int ARM_TICKS_TO_CORRECT_FOR_MOMENTUM = 10;
const int ARM_MOMENTUM_CORRECTION_SPEED = 30;
//static int armMomentumTicks = -1;

PID pid(0.25f, 0.05f, 0.02f, 1000, -1000);
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
	//armMomentumTicks = -1;
	goal = Sensors::GetValue(Sensor::P_ARM);
}

void Arm::Down() {
	down = true;
	up = false;
	//armMomentumTicks = -1;
	goal = Sensors::GetValue(Sensor::P_ARM);
}

void Arm::Hold() {
	if(up || down) {
		up = false;
		down = false;
		//armMomentumTicks = 0;
	}
}

void Arm::HoldAt(int i) {
	up = false;
	down = false;
	//armMomentumTicks = -1;
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
		Motors::SetSpeed(MotorID::ARM, -ARM_SPEED);
	} else {
		int nval = pid.GetValue(Sensors::GetValue(Sensor::P_ARM), goal-Sensors::GetValue(Sensor::P_ARM));
		Motors::SetSpeed(MotorID::ARM, nval);
		//printf("goal: %d, current: %d, P: %d, I:%d D: %d\n", goal, 
		//	Sensors::GetValue(Sensor::P_ARM), pVal, iVal, dVal);
	}
}

#endif
