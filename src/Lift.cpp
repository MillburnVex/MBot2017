#ifndef LIFT
#define LIFT

#include "../include/Controller.h"
#include "../include/Motors.h"
#include "../include/Sensors.h"
#include "../include/Quickmaths.h"
#include "../include/Lift.h"
#include "../include/Arm.h"

const bool PRINT = false;
const bool T = false;

const int LIFT_MAX_VALUE = 64;
const int LIFT_MIN_VALUE = 5;

// how different from each other the sides have to be when moving to be corrected
const int LIFT_CORRECTION_THRESHOLD = 1;
// speed for up/down normally
const int LIFT_SPEED = 100;

static int goal = LIFT_MIN_VALUE;
// if the lift is on its lowest position (we can then count on the supports to hold it)
static bool resting = true;
static bool lifting = false;
static bool dropping = false;

static int leftSpeed = 0;
static int rightSpeed = 0;

const int LIFT_HOLD_SPEED = 20;

void Lift::LeftSide(int speed) {
    leftSpeed = speed;
    Motors::SetSpeed(MotorID::LIFT_LEFT_1, speed);
    Motors::SetSpeed(MotorID::LIFT_LEFT_2, speed);
}

void Lift::RightSide(int speed) {
    rightSpeed = speed;
    Motors::SetSpeed(MotorID::LIFT_RIGHT_1, speed);
    Motors::SetSpeed(MotorID::LIFT_RIGHT_2, speed);
}

void Lift::Up() {
    goal = LIFT_MAX_VALUE;
    resting = false;
    dropping = false;
    lifting = true;
}

void Lift::Hold() {
    if(dropping || lifting) {
        dropping = false;
        lifting = false;
        goal = GetCurrentHeight();
    }
}

void Lift::Down() {
    goal = LIFT_MIN_VALUE;
    dropping = true;
    lifting = false;
}

int Lift::GetCurrentHeight() {
    return Math::Max(Sensors::GetValue(Sensor::E_LIFT_LEFT), Sensors::GetValue(Sensor::E_LIFT_RIGHT));
}

bool Lift::IsResting() {
    return resting;
}

void Lift::Update() {
    if (Controller::GetButton(ButtonGroup::LEFT_GROUP, JOY_DOWN))
        Down();
    else if (Controller::GetButton(ButtonGroup::LEFT_GROUP, JOY_UP))
        Up();
    else
        Hold();
    int right = Sensors::GetValue(Sensor::E_LIFT_LEFT);
    int left = Sensors::GetValue(Sensor::E_LIFT_RIGHT);
    bool rightBelow = right < LIFT_MIN_VALUE;
    bool leftBelow = left < LIFT_MIN_VALUE;
    bool rightAbove = right > LIFT_MAX_VALUE;
    bool leftAbove = left > LIFT_MAX_VALUE;
    if(leftBelow && rightBelow && !lifting) {
        resting = true;
        LeftSide(0);
        RightSide(0);
        Hold();
        return;
    }
    if(lifting && rightAbove && leftAbove) {
        LeftSide(0);
        RightSide(0);
        Hold();
        return;
    }
    if(dropping && resting) {
        Hold();
        return;
    }
    if(Math::Abs(goal - right) > LIFT_CORRECTION_THRESHOLD) {
        int sign = Math::Sign(goal - right);
        RightSide(sign * LIFT_SPEED);
    } else {
        RightSide(LIFT_HOLD_SPEED);
    }
    if(Math::Abs(goal - left) > LIFT_CORRECTION_THRESHOLD) {
        int sign = Math::Sign(goal - left);
        LeftSide(sign * LIFT_SPEED);
    } else {
        LeftSide(LIFT_HOLD_SPEED);
    }
}

#endif
