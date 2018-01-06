#ifndef ARM_CPP
#define ARM_CPP

#include "../include/Motors.h"
#include "../include/Controller.h"
#include "../include/Arm.h"
#include "../include/Sensors.h"
#include "../include/Quickmaths.h"

const bool PRINT = false;

static bool up = false;
static bool down = false;
static bool holdUp = false;
static bool holdOut = true;
const int ARM_SPEED = 60;
const int ARM_CORRECTION_SPEED = 50;
const int ARM_HOLD_SPEED = 10;
const int ARM_MAX_VALUE = -1800;
const int ARM_MIN_VALUE = -300;
const int ARM_HOLD_VALUE = -500;
const int ARM_CORRECTION_THRESHOLD = 80;

void Arm::Up() {
	up = true;
	down = false;
	holdOut = false;
}

void Arm::Down() {
    holdOut = false;
	down = true;
	up = false;
	holdUp = false;
}

void Arm::Hold() {
    up = false;
    down = false;
}

void Arm::HoldOut() {
    holdOut = true;
}

bool Arm::IsFullyUp() {
	return Sensors::GetValue(Sensor::P_ARM) < ARM_MAX_VALUE;
}

bool Arm::IsFullyDown() {
	return Sensors::GetValue(Sensor::P_ARM) > ARM_MIN_VALUE;
}

void Arm::Update() {
    if (Controller::GetButton(ButtonGroup::LEFT_GROUP, JOY_UP))
        Up();
    else if (Controller::GetButton(ButtonGroup::LEFT_GROUP, JOY_DOWN))
        Down();
    else
        Hold();
    if (PRINT) {
        printf("arm: %d, holding up: %d, holding down: %d\n", Sensors::GetValue(Sensor::P_ARM), holdUp, holdUp);
    }
    if(up) {
        Motors::SetSpeed(MotorID::ARM, ARM_SPEED);
    } else if(down) {
        Motors::SetSpeed(MotorID::ARM, -ARM_SPEED);
    } else {
        Motors::SetSpeed(MotorID::ARM, ARM_HOLD_SPEED);
    }
    /*
     int val = Sensors::GetValue(Sensor::P_ARM);
    if (down) {
        if (IsFullyDown()) {
            down = false;
            holdOut = true;
            Motors::Stop(MotorID::ARM);
        } else
            Motors::SetSpeed(MotorID::ARM, -ARM_SPEED);
    } else if (up) {
        if (IsFullyUp()) {
            up = false;
            holdUp = true;
            Motors::Stop(MotorID::ARM);
        } else
            Motors::SetSpeed(MotorID::ARM, ARM_SPEED);
    } else if (holdUp) {
        if (!IsFullyUp()) {
            Motors::SetSpeed(MotorID::ARM, ARM_CORRECTION_SPEED);
        } else {
            Motors::SetSpeed(MotorID::ARM, ARM_HOLD_SPEED);
        }
    } else if(holdOut) {
        if(Math::Abs(val - ARM_HOLD_VALUE) > ARM_CORRECTION_THRESHOLD) {
            if(val > ARM_HOLD_VALUE) {
                Motors::SetSpeed(MotorID::ARM, -ARM_CORRECTION_SPEED);
            } else {
                Motors::SetSpeed(MotorID::ARM, ARM_CORRECTION_SPEED);
            }
        } else {
            Motors::SetSpeed(MotorID::ARM, ARM_HOLD_SPEED);
        }
    }
     */

}

#endif
