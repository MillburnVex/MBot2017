#ifndef OPCONTROL
#define OPCONTROL
#include "main.h"
#include "Controller.h"
#include "Quickmaths.h"
#include "MobileGoal.h"
#include "Drive.h"
#include "Motors.h"
#include "Sensors.h"

const int MILLIS_PER_TICK = 20;

void Tick() {
	Drive::Update();
	MobileGoal::Update();
	// Recalibrates stuff so you don't have to power cycle
	if(Controller::GetButton(ButtonGroup::LEFT_TRIG, JOY_DOWN)) {
		Sensors::CalibrateAll();
	}
	// TODO make these have their own enum values
	printf("mobile goal: %d\n", Sensors::GetValue(Sensor::P_MOBILE_GOAL));
}

void operatorControl() {
	taskRunLoop(Tick, MILLIS_PER_TICK);
	while (1) {
		delay(20);
	}
}
#endif
