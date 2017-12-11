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
static Ultrasonic sonic;
static Gyro gyro;
static int GetValue(SensorID id);
static bool HasProgressed(SensorID id, int lastValue, int goalValue);
}
#endif
