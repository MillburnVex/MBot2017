#ifndef MOBILE_GOAL
#define MOBILE_GOAL
#include "Motors.h"
#include "MobileGoal.h"
#include "Sensors.h"
#include "Controller.h"
static int GOAL_LIFT_SPEED = 100;
static int GOAL_DROP_SPEED = 100;
static int GOAL_LIFT_HOLD_POSITION = 300;
static int GOAL_LIFT_OUT_POSITION = 26900;
static bool dropping = false;
static bool lifting = false;

void MobileGoal::Lift() {
	lifting = true;
	dropping = false;
}

void MobileGoal::Drop() {
	dropping = true;
	lifting = false;
}

void MobileGoal::Update() {
	if(Controller::GetButton(ButtonGroup::RIGHT_TRIG, JOY_UP) == 1)
		MobileGoal::Lift();
	if(Controller::GetButton(ButtonGroup::RIGHT_TRIG, JOY_DOWN) == 1)
		MobileGoal::Drop();
	if(dropping) {
		if(Sensors::GetValue(Sensor::P_MOBILE_GOAL) > GOAL_LIFT_OUT_POSITION) {
			dropping = false;
			Motors::Stop(MotorID::MOBILE_GOAL_LIFT);
		} else {
			Motors::SetSpeed(MotorID::MOBILE_GOAL_LIFT, -GOAL_DROP_SPEED);
		}
	} else if(lifting) {
		if(Sensors::GetValue(Sensor::P_MOBILE_GOAL) < GOAL_LIFT_HOLD_POSITION) {
			lifting = false;
			Motors::Stop(MotorID::MOBILE_GOAL_LIFT);
		} else {
			Motors::SetSpeed(MotorID::MOBILE_GOAL_LIFT, GOAL_LIFT_SPEED);
		}
	}
}
#endif
