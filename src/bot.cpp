#ifndef BOT
#define BOT

#include "Bot.h"
#include <algorithm>
#include <string.h>

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
static void Bot::ExecuteAction(const MotorAction& action, bool over) {
	for(MotorAction& a : actionQueue) {
		if(a.motor == action.motor) {
			if(over) {
				CancelAction(a);
				actionQueue.push_back(action);
				return;
			}
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

// Pray to the lord above that this works. I've never used a vector iterator in cpp b4
static void Bot::Tick() {
	std::vector<MotorAction>::iterator it = actionQueue.begin();
	while(it != actionQueue.end()) {
		bool hasRemoved = false;
		MotorAction& a = (*it);
		a.currentTicks++;
		if(a.sensor != SensorID::NONE) {
			// Progress!
			if(!Sensors::HasProgressed(a.sensor, a.currentValue, a.goalValue)) {
				a.ticksWithoutProgress++;
				if(a.ticksWithoutProgress >= a.cancelThreshold) {
					it = actionQueue.erase(it);
					hasRemoved = true;
				}
			}
			a.currentValue = Sensors::GetValue(a.sensor);
		}
		if(a.currentTicks >= a.timeLimit) {
			it = actionQueue.erase(it);
			hasRemoved = true;
		}
		if(!hasRemoved) {
			++it;
		} else {
			hasRemoved = false;
		}
	}
}

static void Bot::CancelAction(const MotorAction& a) {
	std::vector<MotorAction>::iterator it = actionQueue.begin();
	while(it != actionQueue.end()) {
		MotorAction& o = (*it);
		if(a == o) {
			actionQueue.erase(it);
			return;
		}
	}
}

#endif
