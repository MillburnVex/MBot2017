#ifndef SENSORS_H
#define SENSORS_H
#include "API.h"

enum SensorID {
	// Potentiometers
	NONE = -1, LIFT_LEFT, LIFT_RIGHT,
	// Ultrasonic sensors
	CLAW,
	// Gyroscopic sensors
	GRYO
};

namespace Sensors {
int GetValue(SensorID id);
bool HasProgressed(SensorID id, int lastValue, int goalValue);
static Ultrasonic sonic;
static Gyro gyro;
}
#endif
