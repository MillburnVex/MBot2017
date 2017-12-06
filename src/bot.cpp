#ifndef BOT
#define BOT

#include "Bot.h"
#include <algorithm>

// The
static const int PROGRESS_THRESHOLD = 2;

static Motor* Bot::GetMotor(char* name){
	for(int i = 0; i < 12; i++) {
		if(strcmp(motors[i]->name, name)) {
			return motors[i];
		}
	}
	return nullptr;
}

static Motor* Bot::GetMotor(int id){
	return motors[id];
}

static void Bot::SetMotor(int id, int speed){
	GetMotor(id)->SetSpeed(speed);
}

static void Bot::AddMotor(Motor* motor){
	motors[motor->id] = motor;
}

// Runs an action. If there is a motor that is currently running an action already
// this will be combined, see below for combination results
static void Bot::ExecuteAction(MotorAction& action) {
	for(MotorAction& a : actionQueue) {
		if(a.motor == action.motor) {
			// Combine them. Logic is as follows:
			// Max the goal value
			// Min the cancel threshold
			// Max the time limit
			// Keep current progress of old one
			// TODO what do i do if they have different sensors?
			a.goalValue = std::max(a.goalValue, action.goalValue);
			a.cancelThreshold = std::min(a.cancelThreshold, action.cancelThreshold);
			a.timeLimit = std::max(a.timeLimit, action.timeLimit);
			return;
		}
	}
	actionQueue.push_back(action);
}

static void Bot::Tick() {
	for(MotorAction& a : actionQueue) {
		if(a.sensor != SensorID::NONE) {
			int newValue = Sensors::GetValue(a.sensor);
			// Progress!
			if(std::abs(newValue) - std::abs(a.currentValue) > 0) {

				// No progress
			} else {
				a.
			}
		}
	}
}

#endif
