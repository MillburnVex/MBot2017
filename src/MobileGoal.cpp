#ifndef MOBILE_GOAL
#define MOBILE_GOAL

#include "../include/Motors.h"
#include "../include/MobileGoal.h"
#include "../include/Sensors.h"
#include "../include/Controller.h"

static int GOAL_LIFT_SPEED = 127;
static int GOAL_DROP_SPEED = 100;
static int GOAL_LIFT_HOLD_POSITION = 0;
static int GOAL_LIFT_OUT_POSITION = 1800;
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

void MobileGoal::UpdateControls() {
	if (Controller::GetButton(ButtonGroup::RIGHT_TRIG, JOY_UP))
		MobileGoal::Lift();
	else if (Controller::GetButton(ButtonGroup::RIGHT_TRIG, JOY_DOWN))
		MobileGoal::Drop();
	else{
		dropping = false;
		lifting = false;
	}
}

void MobileGoal::Update() {
	if (dropping) {
		Motors::SetSpeed(MotorID::MOBILE_GOAL_LIFT, -GOAL_DROP_SPEED);
	} else if (lifting) {
		Motors::SetSpeed(MotorID::MOBILE_GOAL_LIFT, GOAL_LIFT_SPEED);
	}else{
		Motors::SetSpeed(MotorID::MOBILE_GOAL_LIFT, 0);
	}
}

#endif
