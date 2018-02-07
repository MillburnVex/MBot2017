#ifndef CLAW_CPP
#define CLAW_CPP
// ^ we use cpp here because otherwise it conflicts with MotorID::CLAW
#include "../include/Claw.h"
#include "../include/Motors.h"
#include "../include/Controller.h"

const int TICKS_TO_FULLY_IN = 20;
const int TICKS_TO_FULLY_OUT = -20;
const int CLAW_SPEED = 60;
const int CLAW_HOLD_SPEED = 20;
int ticks = 0;
bool fullyIn = false;
bool fullyOut = false;
bool in = false;
bool hold = false;
bool out = false;

void Claw::Out() {
	in = false;
	out = true;
}

void Claw::In() {
	in = true;
	out = false;
	fullyIn = false;
}

void Claw::Stop() {
	in = false;
	hold = false;
	out = false;
}

void Claw::Hold() {
	hold = true;
	in = false;
	out = false;
}

bool Claw::IsFullyIn() {
	return fullyIn;
}

bool Claw::IsFullyOut() {
	return fullyOut;
}

void Claw::UpdateControls() {
	if (Controller::GetButton(ButtonGroup::LEFT_TRIG, JOY_DOWN)) {
		Out();
	} else if (Controller::GetButton(ButtonGroup::LEFT_TRIG, JOY_UP)) {
		In();
	} else {
		Hold();
	}
}

void Claw::Update() {
	if(out) {
		Motors::SetSpeed(MotorID::CLAW, CLAW_SPEED);
	} else if(in) {
		Motors::SetSpeed(MotorID::CLAW, -CLAW_SPEED);
	} else if(hold) {
		Motors::SetSpeed(MotorID::CLAW, -CLAW_HOLD_SPEED);
	}
}

#endif
