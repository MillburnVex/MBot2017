#ifndef MOTOR
#define MOTOR
#include "API.h"
#include "Motors.h"
void Motors::SetSpeed(MotorID id, int speed) {
	motorSet(id, speed);
}
void Motors::Stop(MotorID id) {
	motorStop(id);
}
#endif
