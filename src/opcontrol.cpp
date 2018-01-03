#ifndef OPCONTROL
#define OPCONTROL
#include "main.h"
#include "Controller.h"
#include "MobileGoal.h"
#include "Drive.h"
#include "Lift.h"
#include "Sensors.h"
#include "Motors.h"

const int MILLIS_PER_TICK = 20;
const int TICKS_PER_COMMAND = 120;
static int ticksUntilCommand = 0;

void Tick() {
	//Drive::Update();
	//MobileGoal::Update();
	Lift::Update();
	// The stuff below doesn't really fit into any specific update so it goes here
	// Recalibrates stuff so you don't have to power cycle
	if(ticksUntilCommand == 0) {
		if(Controller::GetButton(ButtonGroup::LEFT_TRIG, JOY_DOWN)) {
			if(Controller::GetButton(ButtonGroup::LEFT_TRIG, JOY_UP)) {
				Motors::ToggleAll();
			} else {
				Sensors::CalibrateAll();
			}
			ticksUntilCommand = TICKS_PER_COMMAND;
		}
	} else {
		--ticksUntilCommand;
	}
	// TODO make buttons have their own enum values (goddamnit if this were kotlin...)
}

void operatorControl() {
	taskRunLoop(Tick, MILLIS_PER_TICK);
	while (1) {
		delay(20);
	}
}
#endif
