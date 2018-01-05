#ifndef ARM_CPP
#define ARM_CPP

#include "../include/Motors.h"
#include "../include/Controller.h"
#include "../include/Arm.h"
#include "../include/Sensors.h"

static bool up = false;
static bool down = false;
const int ARM_SPEED = 100;
const int ARM_MAX_VALUE = 0;
const int ARM_MIN_VALUE = 0;

void Arm::Up() {
    up = true;
    down = false;
}

void Arm::Down() {
    down = true;
    up = false;
}

bool Arm::IsFullyUp() {
    return Sensors::GetValue(Sensor::P_ARM) < ARM_MIN_VALUE;
}

bool Arm::IsFullyDown() {
    return Sensors::GetValue(Sensor::P_ARM) > ARM_MAX_VALUE;
}

void Arm::Update() {
    if (Controller::GetButton(ButtonGroup::LEFT_GROUP, JOY_UP))
        Up();
    else if (Controller::GetButton(ButtonGroup::LEFT_GROUP, JOY_DOWN))
        Down();
    if (down) {
        if (Sensors::GetValue(Sensor::P_ARM) > ARM_MAX_VALUE) {
            down = false;
            Motors::Stop(MotorID::ARM);
        } else
            Motors::SetSpeed(MotorID::ARM, -ARM_SPEED);
    } else if (up) {
        if (Sensors::GetValue(Sensor::P_ARM) < ARM_MIN_VALUE) {
            up = false;
            Motors::Stop(MotorID::ARM);
        } else
            Motors::SetSpeed(MotorID::ARM, ARM_SPEED);
    }
}

#endif