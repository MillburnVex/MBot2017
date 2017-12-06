#ifndef JOYSTICK
#define JOYSTICK
#include "API.h"
enum JoystickPort {
	DRIVE_VERTICAL = 3, DRIVE_ROTATE = 4
};

namespace Joystick {
int getValue(JoystickPort port) {
	return joystickGetAnalog(1, port);
}
}
#endif
