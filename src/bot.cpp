#ifndef BOT
#define BOT

#include "Bot.h"

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

void Bot::AddMotor(Motor* motor){
        motors[motor->id] = motor;
}

// Runs an action. If there is a motor that is currently running an action already
// this will be cancelled
// TODO should I combine values so we can resolve conflicting commands?
static void Bot::ExecuteAction(MotorAction& action) {
        for(MotorAction& a : actionQueue) {
                if(a.motor == action.motor) {
                        return;
                }
        }
        actionQueue.push_back(action);
}

#endif
