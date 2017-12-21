#ifndef JOYSTICK
#define JOYSTICK
#include "API.h"
#include "Quickmaths.h"

int JOYSTICK_VALUE_THRESHOLD = 30;

enum JoystickPort {
	DRIVE_VERTICAL = 3, DRIVE_ROTATE = 4
};

namespace Joystick {

int GetValue(JoystickPort port) {
	int i = joystickGetAnalog(1, port);
	if(Math::Abs(i) < JOYSTICK_VALUE_THRESHOLD)
		i = 0;
	return i;
}

}
#endif
