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
static int startingPosition = 0;
static int stage = -1; //2+2=4-1=3
static int ticksInStage = 0;
static int badTicks = 0;
const int DISTANCE_TO_CONE_FROM_ULTRASONIC = 12; // TODO
void Autodump::Start() {
	stage = 0;
	startingPosition = Sensors::GetValue(Sensor::P_ARM);
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
		Arm::HoldAt(startingPosition + 400);
		Claw::Hold();
		Lift::Up();
		if(Sensors::GetValue(Sensor::ULTRASONIC) > 3 && Sensors::GetValue(Sensor::ULTRASONIC) < 25) {
			ticksInStage++;
		}

		if(!(Sensors::GetValue(Sensor::ULTRASONIC) > 3 && Sensors::GetValue(Sensor::ULTRASONIC) < 25)) {
			ticksInStage++;
			badTicks++;
		}
		if(ticksInStage>=6) {
			if(badTicks>3) {
				ticksInStage = 0;
				badTicks = 0;
				stage++;
			}else{
				badTicks = 0;
				ticksInStage = 0;
			}
		}
	}else if(stage==1) {
		Lift::HoldAt(Lift::GetCurrentHeight()-40);
		Arm::Up();
		ticksInStage++;
		if(ticksInStage>30) {
			ticksInStage = 0;
			stage++;
		}
	}else if(stage==2) {
		Arm::Hold();
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
		if(ticksInStage>20) {
			stage = -1;
			ticksInStage = 0;
			Arm::HoldAt(startingPosition);
			Lift::HoldAt(0);
		}
	}
	/*

	   if (ticksInStage>40) {
	        stage = -1;
	        ticksInStage = 0;
	        badTicks = 0;

	   }
	                          if (ticksSinceLastPressed == -1) {
	                          if (stage == -1) {
	                          if (Controller::GetButton(ButtonGroup::RIGHT_GROUP, JOY_LEFT)) {
	                              Start();
	                              ticksSinceLastPressed = 0;
	                          }
	                          } else if (Controller::GetButton(ButtonGroup::RIGHT_GROUP, JOY_LEFT)) {
	                          Cancel();
	                          ticksSinceLastPressed = 0;
	                          }
	                          } else {
	 ++ticksSinceLastPressed;
	                          if (ticksSinceLastPressed == TICKS_BETWEEN_PRESSES)
	                          ticksSinceLastPressed = -1;
	                          if (stage != -1) {
	 ++ticksInStage;
	                          if (stage == 0) {
	                              if (!Arm::IsHeldOut())
	                                      Arm::HoldOut();
	                              else {
	                                      stage = 1;
	                                      ticksInStage = 0;
	                                      // arm will stop automatically
	                              }
	                          }
	                          if(stage == 1) {
	                              if (IsConeInFrontOfUltrasonic())
	                                      Lift::Up();
	                              else {
	                                      stage = 2;
	                                      ticksInStage = 0;
	                              }
	                          }
	                          print("stage 1 done\n");
	                          stage = -1;
	                          return;
	                          if (stage == 2) {
	                              if (Claw::IsFullyOut()) {
	                                      // claw will stop automatically
	                                      stage = 2;
	                                      ticksInStage = 0;
	                              } else
	                                      Claw::Out();
	                          }
	                          if (stage == 3) {
	                              if (!Arm::IsFullyDown()) {
	                                      Arm::Down();
	                              } else {
	                                      stage = 4;
	                                      ticksInStage = 0;
	                              }
	                          }
	                          if(stage == 4) {
	                              if(!Lift::IsResting()) {
	                                      Lift::Down();
	                              } else {
	                                      stage = -1;
	                                      return;
	                              }
	                          }
	                          }
	                          }*/

}

#endif
