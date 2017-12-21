#ifndef BOT
#define BOT

#include "Bot.h"

Motor* Bot::GetMotor(int id){
	return motors[id];
}

void Bot::SetMotor(int id, int speed){
	GetMotor(id)->SetSpeed(speed);
}

void Bot::AddMotor(Motor* motor){
	motors[motor->id] = motor;
}

// Runs an action. If there is a motor that is currently running an action already
// this will be combined, see below for combination results
void Bot::ExecuteAction(MotorAction& action, bool over) {
	actionQueue.Add(action, over);
}

// Pray to the lord above that this works.
void Bot::Tick() {
	actionQueue.Update();
}

// I'll add a function that does this from just a reference when we need it
void Bot::CancelAction(int index) {
	actionQueue.Remove(index);
}

#endif
