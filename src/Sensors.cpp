#ifndef SENSORS
#define SENSORS
#include "Sensors.h"
#include "Quickmaths.h"
#include <algorithm>

// The amount of progress we need to make before we actually consider it real progress
// This accounts for shakes and such
// TODO create sensor classes and use different thresholds for each class
const int PROGRESS_THRESHOLD = 2;

int Sensors::GetValue(SensorID id) {
	// read value logic TODO check if its none!
	if(id == SensorID::GRYO) {
		return gyroGet(gyro);
	} else if(id == SensorID::CLAW) {
		return ultrasonicGet(sonic);
	} else {
		// potentiometer TODO
	}
}

// Checks if a sensor has moved towards
bool Sensors::HasProgressed(SensorID id, int lastValue, int goalValue) {
	int currentValue = Sensors::GetValue(id);
	int difference = currentValue - lastValue;
	return (Math::Abs(difference) > PROGRESS_THRESHOLD && Math::Sign(currentValue - lastValue) == Math::Sign(goalValue));
}

#endif
