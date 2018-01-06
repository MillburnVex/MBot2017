#ifndef CLAW_CPP
#define CLAW_CPP
// ^ we use cpp here because otherwise it conflicts with MotorID::CLAW
#include "../include/Claw.h"
#include "../include/Motors.h"
#include "../include/Controller.h"

const int TICKS_TO_FULLY_IN = 20;
const int TICKS_TO_FULLY_OUT = -20;
const int CLAW_SPEED = 60;
static int ticks = 0;
static bool fullyIn = false;
static bool fullyOut = false;
static bool in = false;
static bool hold = false;
static bool out = false;

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

bool Claw::IsFullyIn() {
    return fullyIn;
}

bool Claw::IsFullyOut() {
    return fullyOut;
}

void Claw::Update() {
    if (Controller::GetButton(ButtonGroup::LEFT_TRIG, JOY_DOWN)) {
        Out();
    } else if (Controller::GetButton(ButtonGroup::LEFT_TRIG, JOY_UP)) {
        In();
    }

    if (out) {
        if (ticks == TICKS_TO_FULLY_OUT) {
            out = false;
            ticks = 0;
            fullyOut = true;
            Motors::Stop(MotorID::CLAW);
        } else {
            fullyIn = false;
            Motors::SetSpeed(MotorID::CLAW, -CLAW_SPEED);
            --ticks;
        }
    } else if(hold) {
        Motors::SetSpeed(MotorID::CLAW, 10);
    } else if (in && !fullyIn) {
        if (ticks == TICKS_TO_FULLY_IN) {
            in = false;
            fullyIn = true;
            ticks = 0;
            hold = true;
            Motors::Stop(MotorID::CLAW);
        } else {
            fullyOut = false;
            Motors::SetSpeed(MotorID::CLAW, CLAW_SPEED);
            ++ticks;
        }

    }
}

#endif
