#ifndef AUTODUMP
#define AUTODUMP

#include "../include/Controller.h"
#include "../include/Sensors.h"
#include "../include/Lift.h"
#include "../include/Arm.h"
#include "../include/Claw.h"
#include "../include/Autodump.h"

// -1: inactive
// 0: lifting up and moving arm to out position
// 1: moving arm to drop position
// 2: opening claw
// 3: moving arm back to forward position
// 4: lifting down
static int armStartingPosition = 0;
static int stage = -1; //2+2=4-1=3
static int ticksInStage = 0;
static int badTicks = 0;
const int DISTANCE_TO_CONE_FROM_ULTRASONIC = 12; // TODO

void Autodump::Start() {
	stage = 0;
	armStartingPosition = Sensors::GetValue(Sensor::P_ARM);
}

void Autodump::Cancel() {
	stage = -1;
}

bool Autodump::IsActive() {
	return stage != -1;
}

bool Autodump::IsConeInFrontOfUltrasonic() {
	return Sensors::GetValue(Sensor::ULTRASONIC) < DISTANCE_TO_CONE_FROM_ULTRASONIC;
}

void Autodump::UpdateControls() {
	if(stage == -1) {
		if (Controller::GetButton(ButtonGroup::RIGHT_GROUP, JOY_LEFT)) {
			Start();
		}
	}else if(stage != -1) {
		if (Controller::GetButton(ButtonGroup::RIGHT_GROUP, JOY_RIGHT)) {
			Cancel();
		}
	}
}

void Autodump::Update() {
	printf("%d\n", stage);
	if(stage == 0) {
		Arm::HoldAt(armStartingPosition + 400);
		Claw::Hold();
		Lift::Up();
		if(Sensors::GetValue(Sensor::ULTRASONIC) > 3 && Sensors::GetValue(Sensor::ULTRASONIC) < 25) {
			ticksInStage++;
		}

		if(!(Sensors::GetValue(Sensor::ULTRASONIC) > 3 && Sensors::GetValue(Sensor::ULTRASONIC) < 25)) {
			ticksInStage++;
			badTicks++;
		}
		if(ticksInStage>=4) {
			if(badTicks>2) {
				ticksInStage = 0;
				badTicks = 0;
				stage++;
			}else{
				badTicks = 0;
				ticksInStage = 0;
			}
		}
	}else if(stage==1) {
		Lift::Hold();
		Arm::Up();
		ticksInStage++;
		if(ticksInStage>30) {
			ticksInStage = 0;
			stage++;
		}
	}else if(stage==2) {
		Arm::Up();
		Lift::Down();
		ticksInStage++;
		if(ticksInStage>20) {
			stage++;
			ticksInStage = 0;
		}
	}else if(stage == 3) {
		Lift::Hold();
		Arm::Hold();
		Claw::Out();
		ticksInStage++;
		if(ticksInStage>10) {
			stage++;
			ticksInStage = 0;
		}
	}else if(stage == 4) {
		Lift::Up();
		Arm::Hold();
		Claw::Out();
		ticksInStage++;
		if(ticksInStage > 15) {
			stage = -1;
			ticksInStage = 0;
			Arm::HoldAt(armStartingPosition);
		}
	}
}

#endif
