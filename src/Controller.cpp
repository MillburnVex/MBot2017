#ifndef CONTROLLER
#define CONTROLLER
#include "../include/Controller.h"
#include "../include/Quickmaths.h"

static int JOYSTICK_VALUE_THRESHOLD = 30;

int Controller::GetButton(ButtonGroup g, int b) {
	return joystickGetDigital(1, g, b);
}

int Controller::GetJoystick(JoystickPort port) {
	int i = joystickGetAnalog(1, port);
	if(Math::Abs(i) < JOYSTICK_VALUE_THRESHOLD)
		i = 0;
	return i;
}
#endif
