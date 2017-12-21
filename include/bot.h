#ifndef BOT_H
#define BOT_H

#include "API.h"
#include "Motors.h"
#include "MotorAction.h"
#include "MotorActionQueue.h"

// Namespace and static to avoid singletons, versus singletons? I like the namespace better
// https://stackoverflow.com/questions/5793334/c-static-vs-namespace-vs-singleton
namespace Bot {

// Pointer b/c init as null
static Motor* motors[12];
static int* tickCount;
// The queue of currently running actions to be evaluated, if necessary
static MotorActionQueue actionQueue;
Motor* GetMotor(int id);
void SetMotor(int id, int speed);
void AddMotor(Motor* motor);
void ExecuteAction(MotorAction& action, bool over = false);
void Tick();
void CancelAction(int index);
}
#endif
