#ifndef CONTROLLER
#define CONTROLLER
#include "Controller.h"
#include "Quickmaths.h"

static int VALUE_THRESHOLD = 30;

int Controller::GetButton(ButtonGroup g, int b) {
	return joystickGetDigital(1, g, b);
}

int Controller::GetJoystick(JoystickPort port) {
	int i = joystickGetAnalog(1, port);
	if(Math::Abs(i) < VALUE_THRESHOLD)
		i = 0;
	return i;
}
#endif
