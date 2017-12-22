#ifndef SENSORS_H
#define SENSORS_H
#include "API.h"

enum Sensor {
	// P = potentiometer
	NONE = -1, P_MOBILE_GOAL = 1
};

namespace Sensors {

void Calibrate(Sensor id);
int GetValue(Sensor id);
bool HasProgressed(Sensor id, int lastValue, int goalValue);
static Ultrasonic sonic;
static Gyro gyro;
void CalibrateAll();

}
#endif
