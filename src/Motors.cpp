#ifndef MOTOR
#define MOTOR
#include "../include/API.h"
#include "../include/Motors.h"
static bool enabled = true;
void Motors::ToggleAll() {
	enabled = !enabled;
}
void Motors::SetSpeed(MotorID id, int speed) {
	if(enabled)
		motorSet(id, speed);
	else
		Stop(id);
}
void Motors::Stop(MotorID id) {
	motorStop(id);
}
#endif
