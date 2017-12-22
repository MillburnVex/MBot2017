#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "API.h"
enum ButtonGroup {
	// technically these values after 5 are uncessecary but they make it more obvious
	LEFT_TRIG = 5, RIGHT_TRIG = 6, LEFT_GROUP = 7, RIGHT_GROUP = 8
};

enum JoystickPort {
	DRIVE_VERTICAL = 3, DRIVE_ROTATE = 4,
};

namespace Controller {
int GetButton(ButtonGroup g, int dir);
int GetJoystick(JoystickPort port);
}
#endif
