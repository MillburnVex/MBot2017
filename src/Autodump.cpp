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
static int stage = -1;
static int ticksInStage = 0;
static int ticksSinceLastPressed = -1;
const int TICKS_BETWEEN_PRESSES = 120;
const int DISTANCE_TO_CONE_FROM_ULTRASONIC = 12; // TODO
void Autodump::Start() {
    stage = 0;
}

void Autodump::Cancel() {
    stage = -1;
}

bool Autodump::IsConeInFrontOfUltrasonic() {
    return Sensors::GetValue(Sensor::ULTRASONIC) < DISTANCE_TO_CONE_FROM_ULTRASONIC;
}

void Autodump::Update() {
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
                        print("stage 1 done");
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
    }

}

#endif