#ifndef LIFT
#define LIFT

#include "../include/Controller.h"
#include "../include/Motors.h"
#include "../include/Sensors.h"
#include "../include/Quickmaths.h"
#include "../include/Lift.h"
#include "../include/Arm.h"
#include "../include/PID.h"

const bool PRINT = false;
const bool T = false;

const int LIFT_MAX_VALUE = 106;
const int LIFT_MIN_VALUE = 1;

// how different from each other the sides have to be when moving to be corrected
const int LIFT_CORRECTION_THRESHOLD = 1;
// speed for up/down normally
const int LIFT_SPEED = 100;
const int LIFT_REST_SPEED = 30;

const int LIFT_TICKS_TO_CORRECT_FOR_MOMENTUM = 10;
const int LIFT_MOMENTUM_CORRECTION_SPEED = 50;
static int liftMomentumTicks = -1;

static int goal = LIFT_MIN_VALUE;
// if the lift is on its lowest position (we can then count on the supports to hold it)
static bool resting = true;
static bool lifting = false;
static bool dropping = false;

static int leftSpeed = 0;
static int rightSpeed = 0;

PID pid1(3.0f, 0.2f, 4.0f, 1000, -1000);
PID pid2(3.0f, 0.2f, 4.0f, 1000, -1000);

const int LIFT_HOLD_SPEED = 20;

void Lift::MakePID(){
	pid1 = PID(3.0f, 0.1f, 2.0f, 1000, -1000);
	pid2 = PID(3.0f, 0.1f, 2.0f, 1000, -1000);
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
		// if this is resting, momentum should only carry it down
		liftMomentumTicks = 0;
		goal = GetCurrentHeight();
	}
}

void Lift::HoldAt(int pos){
	if(dropping || lifting) {
		dropping = false;
		lifting = false;
		// if this is resting, momentum should only carry it down
		liftMomentumTicks = 0;
		goal = pos;
	}
}

void Lift::Down() {
	goal = LIFT_MIN_VALUE - 1 - LIFT_CORRECTION_THRESHOLD;
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
	int right = Sensors::GetValue(Sensor::E_LIFT_LEFT);
	int left = Sensors::GetValue(Sensor::E_LIFT_RIGHT);
	bool rightBelow = right < LIFT_MIN_VALUE;
	bool leftBelow = left < LIFT_MIN_VALUE;
	bool rightAbove = right > LIFT_MAX_VALUE;
	bool leftAbove = left > LIFT_MAX_VALUE;
	
	if(leftBelow && rightBelow) {
		resting = true;
		liftMomentumTicks = -1;
	}
	if(resting && !lifting) {
		//print("cancel: resting and not lifting\n");
		resting = true;
		LeftSide(-LIFT_REST_SPEED);
		RightSide(-LIFT_REST_SPEED);
		dropping = false;
		return;
	}
	if(lifting && rightAbove && leftAbove) {
		//print("cancel: both sides above and lifting\n");
		LeftSide(0);
		RightSide(0);
		Hold();
		return;
	}
	if(dropping && resting) {
		//print("cancel: trying to drop while resting\n");
		LeftSide(-LIFT_REST_SPEED);
		RightSide(-LIFT_REST_SPEED);
		Hold();
		return;
	}
	
		RightSide(pid1.GetValue(right, goal-right));
		LeftSide(pid2.GetValue(left, goal-left));/*
		//printf("goal: %d - ", goal);
		if(Math::Abs(goal - right) > LIFT_CORRECTION_THRESHOLD) {
			//printf("right side needs correction: %d, %d, ", sign, GetMultiplier(right));
			RightSide((goal - right) * P);
		} else {
			//print("right side passive, ");
			RightSide(LIFT_HOLD_SPEED);
		}
		if(Math::Abs(goal - left) > LIFT_CORRECTION_THRESHOLD) {
			//printf("left side needs correction: %d ,%d\n", sign, GetMultiplier(left));
			LeftSide((goal - left) * P);
		} else {
			//print("left side passive\n");
			LeftSide(LIFT_HOLD_SPEED);
		}*/
	
}



#endif