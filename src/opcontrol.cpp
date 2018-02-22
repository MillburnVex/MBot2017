#ifndef OPCONTROL
#define OPCONTROL
#include "../include/main.h"
#include "../include/Controller.h"
#include "../include/MobileGoal.h"
#include "../include/Drive.h"
#include "../include/Lift.h"
#include "../include/Sensors.h"
#include "../include/Motors.h"
#include "../include/Claw.h"
#include "../include/Arm.h"
#include "../include/Autodump.h"

const int MILLIS_PER_TICK = 20;
const int TICKS_PER_COMMAND = 120;
static int ticksUntilCommand = 0;
static bool pressedDebugModeButton = false;

static bool debugMode = false;

void Tick() {
	printf("sonice: %d\n", Sensors::GetValue(Sensor::ULTRASONIC));
	if(!debugMode) {
		Autodump::UpdateControls();
		Autodump::Update();
		Drive::UpdateControls();
		Drive::Update();

		if(!Autodump::IsActive()) {
			MobileGoal::UpdateControls();
			Claw::UpdateControls();
			Lift::UpdateControls();
			Arm::UpdateControls();
		}

		MobileGoal::Update();
		Claw::Update();
		Lift::Update();
		Arm::Update();
	} else {
		if(ticksUntilCommand == 0) {
			if(Controller::GetButton(ButtonGroup::LEFT_TRIG, JOY_DOWN)) {
				Sensors::CalibrateAll();
				print("calibrated all sensors\n");
				ticksUntilCommand = TICKS_PER_COMMAND;
				return;
			}
			if(Controller::GetButton(ButtonGroup::LEFT_TRIG, JOY_UP)) {
				Motors::ToggleAll();
				print("toggled all motors\n");
				ticksUntilCommand = TICKS_PER_COMMAND;
				return;
			}
		} else {
			--ticksUntilCommand;
		}
	}
	if(Controller::GetButton(ButtonGroup::LEFT_GROUP, JOY_LEFT) && Controller::GetButton(ButtonGroup::LEFT_GROUP, JOY_RIGHT)) {
		if(!pressedDebugModeButton) {
			debugMode = !debugMode;
			ticksUntilCommand = 0;
			printf("debug mode: %d\n", debugMode);
		}
		pressedDebugModeButton = true;
	} else {
		pressedDebugModeButton = false;
	}
}

void operatorControl() {
	taskRunLoop(Tick, MILLIS_PER_TICK);
	while (1) {}
}
#endif
