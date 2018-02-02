#ifndef SENSORS_H
#define SENSORS_H
#include "../include/API.h"

enum Sensor {
	// P = potentiometer, E = encoder
	NONE = -1, P_MOBILE_GOAL = 1, E_LIFT_LEFT = -3, E_LIFT_RIGHT = -4, P_ARM = 2, ULTRASONIC = -2
};

namespace Sensors {

void Calibrate(Sensor id);
int GetValue(Sensor id);
bool HasProgressed(Sensor id, int lastValue, int goalValue);
static Ultrasonic sonic;
static Gyro gyro;
static Encoder liftLeft;
static Encoder liftRight;
void InitAll();

void CalibrateAll();
}
#endif
