#ifndef LIFT
#define LIFT

#include "../include/../include/Controller.h"
#include "../include/../include/Motors.h"
#include "../include/../include/Sensors.h"
#include "../include/../include/Quickmaths.h"
#include "../include/../include/Lift.h"

const bool PRINT = true;
const bool T = false;

const int LIFT_MAX_VALUE = -64;
const int LIFT_MIN_VALUE = -5;

// how different from each other the sides have to be when moving to be corrected
const int LIFT_CORRECTION_THRESHOLD = 2;
// speed for up/down normally
const int LIFT_SPEED = 100;
// the speed the side that is further to completion is set to to allow the other side to catch up (could be 0 but it would be jerky)
const int LIFT_CORRECTING_SPEED = 50;

// moving it to the hold position (correcting)
const int LIFT_HOLD_CORRECTION_SPEED_UP = 100;
const int LIFT_HOLD_CORRECTION_SPEED_DOWN = 10;
// holding it without moving
const int LIFT_HOLD_PASSIVE_POWER = 20;

static int hold = LIFT_MIN_VALUE;
// if the lift is on its lowest position (we can then count on the supports to hold it)
static bool resting = true;
static bool lifting = false;
static bool dropping = false;

static int leftSpeed = 0;
static int rightSpeed = 0;

void Lift::LeftSide(int speed) {
	leftSpeed = speed;
	Motors::SetSpeed(MotorID::LIFT_LEFT_1, speed);
	Motors::SetSpeed(MotorID::LIFT_LEFT_2, speed);
}

void Lift::RightSide(int speed) {
	rightSpeed = speed;
	Motors::SetSpeed(MotorID::LIFT_RIGHT_1, speed);
	Motors::SetSpeed(MotorID::LIFT_RIGHT_2, speed);
}

void Lift::Up() {
	lifting = true;
	dropping = false;
}

void Lift::Hold() {
	if (dropping || lifting) {
		hold = GetCurrentAverageHeight();
		dropping = false;
		lifting = false;
	}
}

void Lift::Down() {
	dropping = true;
	lifting = false;
}

int Lift::GetCurrentAverageHeight() {
	return Math::Min(Sensors::GetValue(Sensor::E_LIFT_LEFT), Sensors::GetValue(Sensor::E_LIFT_RIGHT));
}

bool Lift::IsResting() {
	return resting;
}

void Lift::Update() {
	if (Controller::GetButton(ButtonGroup::RIGHT_GROUP, JOY_DOWN))
		Down();
	else if (Controller::GetButton(ButtonGroup::RIGHT_GROUP, JOY_UP))
		Up();
	else
		Hold();
	int left = Sensors::GetValue(Sensor::E_LIFT_LEFT);
	int right = Sensors::GetValue(Sensor::E_LIFT_RIGHT);
	if (PRINT) { printf("l: %d, r: %d ", left, right); }
	if (lifting) {
		resting = false;
		bool leftAbove = left < LIFT_MAX_VALUE;
		bool rightAbove = right < LIFT_MAX_VALUE;
		if (leftAbove && rightAbove) {
			// done lifting
			Hold();
			if (PRINT) {
				print("done lifting");
			}
		} else if (leftAbove) {
			// 1 side done
			LeftSide(0);
			RightSide(LIFT_SPEED);
			if (PRINT) {
				print("1 side done");
			}
		} else if (rightAbove) {
			// 1 side done
			RightSide(0);
			LeftSide(LIFT_SPEED);
			if (PRINT) {
				print("1 side done");
			}
		} else {
			// no sides done
			// correction
			if (Math::Abs(left - right) > LIFT_CORRECTION_THRESHOLD) {
				if (left < right) { // left is higher
					if (PRINT) {
						print("correcting, left is too high");
					}
					LeftSide(LIFT_CORRECTING_SPEED);
					RightSide(LIFT_SPEED);
				} else if (right < left) { // right is higher
					if (PRINT) {
						print("correcting, right is too high");
					}
					RightSide(LIFT_CORRECTING_SPEED);
					LeftSide(LIFT_SPEED);
				}
			} else { // no correction needed
				if (PRINT) {
					print("both sides going up");
				}
				LeftSide(LIFT_SPEED);
				RightSide(LIFT_SPEED);
			}
		}
	} else if (dropping) {
		if (resting) {
			// if this is already resting, don't do anything
			Hold();
			if (PRINT) {
				print("resting");
			}
		} else {
			bool leftBelow = left > LIFT_MIN_VALUE;
			bool rightBelow = right > LIFT_MIN_VALUE;
			if (leftBelow && rightBelow) {
				// done dropping
				resting = true;
				LeftSide(0);
				RightSide(0);
				Hold();
				if (PRINT) {
					print("done dropping");
				}
			} else if (leftBelow) {
				// 1 side done
				LeftSide(0);
				RightSide(-LIFT_SPEED);
				if (PRINT) {
					print("1 side done");
				}
			} else if (rightBelow) {
				// 1 side done
				RightSide(0);
				LeftSide(-LIFT_SPEED);
				if (PRINT) {
					print("1 side done");
				}
			} else {
				// no sides done
				// correction
				if (Math::Abs(left - right) > LIFT_CORRECTION_THRESHOLD) {
					if (left < right) { // left is higher
						if (PRINT) {
							print("correcting, left is too low");
						}
						LeftSide(-LIFT_CORRECTING_SPEED);
						RightSide(-LIFT_SPEED);
					} else if (right > left) { // right is higher
						if (PRINT) {
							print("correcting, right is too low");
						}
						RightSide(-LIFT_CORRECTING_SPEED);
						LeftSide(-LIFT_SPEED);
					}
				} else { // no correction needed
					if (PRINT) {
						print("both sides going down");
					}
					LeftSide(-LIFT_SPEED);
					RightSide(-LIFT_SPEED);
				}
			}
		}
	} else { // holding
		if (!resting) {
			if (PRINT) {
				printf("holding at %d: ", hold);
			}
			if(Math::Abs(hold - left) > LIFT_CORRECTION_THRESHOLD) { // too far away
				if(hold < left) { // too low
					if(PRINT) {
						print("left too low, ");
					}
					LeftSide(LIFT_HOLD_CORRECTION_SPEED_UP);
				} else if(hold > left) { // too high
					if(PRINT) {
						print("left too high, ");
					}
					LeftSide(-LIFT_HOLD_CORRECTION_SPEED_DOWN);
				} else {
					print("right passive");
					LeftSide(LIFT_HOLD_PASSIVE_POWER);
				}
			}
			if(Math::Abs(hold - right) > LIFT_CORRECTION_THRESHOLD) { // too far away
				if(hold < right) { // too low
					if(PRINT) {
						print("right too low");
					}
					RightSide(LIFT_HOLD_CORRECTION_SPEED_UP);
				} else if(hold > right) { // too high
					if(PRINT) {
						print("right too high");
					}
					RightSide(-LIFT_HOLD_CORRECTION_SPEED_DOWN);
				} else {
					print("right passive");
					RightSide(LIFT_HOLD_PASSIVE_POWER);
				}
			}
		}
	}
	if (PRINT) { print("\n"); }
	if (T) { printf(" ls: %d, rs: %d\n", leftSpeed, rightSpeed); }
}

#endif
