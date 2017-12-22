#ifndef SENSORS
#define SENSORS
#include "Sensors.h"
#include "Quickmaths.h"
#include <algorithm>
#include "API.h"

// The amount of progress we need to make before we actually consider it real progress
// This accounts for shakes and such
// TODO create sensor classes and use different thresholds for each class
const int PROGRESS_THRESHOLD = 2;

void Sensors::Calibrate(Sensor id) {
	analogCalibrate(id);
}

int Sensors::GetValue(Sensor id) {
	return analogReadCalibratedHR(id);
}

// Checks if a sensor has moved towards
bool Sensors::HasProgressed(Sensor id, int lastValue, int goalValue) {
	int currentValue = GetValue(id);
	int difference = currentValue - lastValue;
	return (Math::Abs(difference) > PROGRESS_THRESHOLD && Math::Sign(currentValue - lastValue) == Math::Sign(goalValue));
}

void Sensors::CalibrateAll() {
	Calibrate(Sensor::P_MOBILE_GOAL);
}

#endif
