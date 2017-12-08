#ifndef BOT
#define BOT

#include "Bot.h"
#include <algorithm>

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

// Pray to the lord above that this works. I've never used a vector iterator in cpp b4
static void Bot::Tick() {
	std::vector<MotorAction>::iterator it = actionQueue.begin();
	while(it != actionQueue.end()) {
		MotorAction& a = (*it);
		if(a.sensor != SensorID::NONE) {
			// Progress!
			if(Sensors::HasProgressed(a.sensor, a.currentValue, a.goalValue)) {
				a.currentTicks++;
			} else {
				a.ticksWithoutProgress++;
				if(a.ticksWithoutProgress >= a.cancelThreshold) {
					it = actionQueue.erase(it);
				}
			}
		}
		++it;
	}
}

#endif
