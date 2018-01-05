#ifndef SENSORS_H
#define SENSORS_H
#include "../include/API.h"

enum Sensor {
	// P = potentiometer
	NONE = -1, P_MOBILE_GOAL = 1, P_LIFT_LEFT = 2, P_LIFT_RIGHT = 3, P_ARM = 4, ULTRASONIC = -2
};

namespace Sensors {

void Calibrate(Sensor id);
int GetValue(Sensor id);
bool HasProgressed(Sensor id, int lastValue, int goalValue);
static Ultrasonic sonic;
static Gyro gyro;
void InitAll();

	void CalibrateAll();
}
#endif
