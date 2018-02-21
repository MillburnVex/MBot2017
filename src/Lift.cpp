#ifndef LIFT
#define LIFT

#include "../include/Controller.h"
#include "../include/Motors.h"
#include "../include/Sensors.h"
#include "../include/Quickmaths.h"
#include "../include/Lift.h"
#include "../include/Arm.h"
#include "../include/PID.h"

const int LIFT_MAX_VALUE = 130;
const int LIFT_MIN_VALUE = 1;

// how different from each other the sides have to be when moving to be corrected
const int LIFT_CORRECTION_THRESHOLD = 1;
// speed for up/down normally

const int LIFT_TICKS_TO_CORRECT_FOR_MOMENTUM = 10;
const int LIFT_MOMENTUM_CORRECTION_SPEED = 50;

static int goal = LIFT_MIN_VALUE;
// if the lift is on its lowest position (we can then count on the supports to hold it)
static bool resting = true;
static bool lifting = false;
static bool dropping = false;

static int leftSpeed = 0;
static int rightSpeed = 0;

PID pidRight(0, 0, 0, 0, 0);
PID pidLeft(0, 0, 0, 0, 0);

const int LIFT_HOLD_SPEED = 20;

void Lift::MakePID(){
	pidRight = PID(3.0f, 0.00f, 20.0f, 1000, -1000);
	pidLeft = PID(3.0f, 0.00f, 20.0f, 1000, -1000);
}

void Lift::LeftSide(int speed) {
	leftSpeed = speed;
	Motors::SetSpeed(MotorID::LIFT_LEFT_1, speed);
	Motors::SetSpeed(MotorID::LIFT_LEFT_2, speed);
}

void Lift::RightSide(int speed) {
	rightSpeed = speed;
	Motors::SetSpeed(MotorID::LIFT_RIGHT_1, -speed);
	Motors::SetSpeed(MotorID::LIFT_RIGHT_2, -speed);
}

void Lift::Up() {
	goal = LIFT_MAX_VALUE;
	resting = false;
	dropping = false;
	lifting = true;
}

void Lift::Hold() {
	if(dropping || lifting) {
		dropping = false;
		lifting = false;
		goal = GetCurrentHeight();
	}
}

void Lift::HoldAt(int pos){
	if(dropping || lifting) {
		dropping = false;
		lifting = false;
		goal = pos;
	}
}

void Lift::Down() {
	// the minus two is here so that it always will try to go down, even if on lowest value.
	// this is because the lift sometimes does not go all the way down, usually due to rubber bands
	goal = LIFT_MIN_VALUE - 2;
	dropping = true;
	lifting = false;
}

int Lift::GetCurrentHeight() {
	return Math::Max(Sensors::GetValue(Sensor::E_LIFT_LEFT), Sensors::GetValue(Sensor::E_LIFT_RIGHT));
}

bool Lift::IsResting() {
	return resting;
}

void Lift::UpdateControls() {
	if (Controller::GetButton(ButtonGroup::LEFT_GROUP, JOY_DOWN))
		Down();
	else if (Controller::GetButton(ButtonGroup::LEFT_GROUP, JOY_UP))
		Up();
	else
		Hold();
}

void Lift::Update() {
	if(lifting) {
		LeftSide(100);
	} else if(dropping) {
		LeftSide(-100);
	} else {
		LeftSide(0);
	}
	/*
	   int right = Sensors::GetValue(Sensor::E_LIFT_LEFT);
	   int left = Sensors::GetValue(Sensor::E_LIFT_RIGHT);
	   printf("l: %d, r: %d\n", left, right);
	   RightSide(pidRight.GetValue(right, goal));
	   LeftSide(pidLeft.GetValue(left, goal));
	 */
}

#endif
