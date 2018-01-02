#ifndef LIFT
#define LIFT
#include "Controller.h"
#include "Motors.h"
#include "Sensors.h"
#include "Quickmaths.h"
#include "Lift.h"

// Rest: 44400 and above, Highest: 11400 and lower

const int MAX_LIFT_VALUE = -33000;
const int MIN_LIFT_VALUE = -100;

// how different from each other the sides have to be when moving to be corrected
const int LIFT_CORRECTION_THRESHOLD = 500;
// speed for up/down normally
const int LIFT_SPEED = 100;
// the speed the side is higher is set to to allow the other side to catch up (could be 0 but it would be jerky)
const int LIFT_CORRECTING_SPEED = 50;

// how different from each other the sides have to be when holding to be corrected
const int LIFT_HOLD_CORRECTION_THRESHOLD = 500;
// moving it to the hold position (correcting)
const int LIFT_HOLD_ACTIVE_POWER = 80;
// holding it without moving
const int LIFT_HOLD_PASSIVE_POWER = 30;

static int hold = MIN_LIFT_VALUE;
static bool lifting = false;
static bool dropping = false;

void Lift::LeftSide(int speed) {
	printf("Left: %d", speed);
	Motors::SetSpeed(MotorID::LIFT_LEFT_1, speed);
	Motors::SetSpeed(MotorID::LIFT_LEFT_2, speed);
}

void Lift::RightSide(int speed) {
	printf("Right: %d\n", speed);
	Motors::SetSpeed(MotorID::LIFT_RIGHT_1, speed);
	Motors::SetSpeed(MotorID::LIFT_RIGHT_2, speed);
}

void Lift::Up() {
	lifting = true;
	dropping = false;
}

void Lift::Hold() {
	if(dropping || lifting) {
		hold = GetCurrentAverageHeight();
		dropping = false;
		lifting = false;
	}
}

void Lift::Down() {
	dropping = true;
	lifting = false;
}

bool Lift::SideOutOfBounds(int value) {
	return value < MAX_LIFT_VALUE || value > MIN_LIFT_VALUE;
}

int Lift::GetCurrentAverageHeight() {
	return (Sensors::GetValue(Sensor::P_LIFT_LEFT) + Sensors::GetValue(Sensor::P_LIFT_RIGHT)) / 2;
}

void Lift::Update() {
	// if we are lifting
	//   find which sides are above bounds
	//   if both are above, stop lifting, set the hold value to the max value
	//   if one is above, stop it and set the other
	//   else (both must be in bounds and going up),
	//	   if one is above the other by a value higher than the threshold, stop it and set the other
	//		 else set both
	// else if we are dropping
	//	find which sides are below bounds
	//	if both are below, stop dropping, set the hold value the min value
	//	if one is above, stop it and set the other
	//	else
	//		if one is below the other by a value higher than the threshold, stop it and set the other
	//		else set both
	// else (we are holding)
	//	if either side is away from the hold value by more than the threshold, set it in the appropriate direction
	int left = Sensors::GetValue(Sensor::P_LIFT_LEFT);
	int right = Sensors::GetValue(Sensor::P_LIFT_RIGHT);
	if(lifting) {
		bool leftAbove = left < MAX_LIFT_VALUE;
		bool rightAbove = right < MAX_LIFT_VALUE;
		if(leftAbove && rightAbove) {
			lifting = false;
			Hold();
		} else if(left - right > LIFT_CORRECTION_THRESHOLD) { // left is higher
			LeftSide(0);
			RightSide(LIFT_SPEED);
		} else if(right - left > LIFT_CORRECTION_THRESHOLD) { // right is higher

		}
	}
}
#endif
