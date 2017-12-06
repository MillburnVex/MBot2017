#ifndef SENSORS
#define SENSORS
#include "Sensors.h"
int Sensors::GetValue(SensorID id) {
	// read value logic TODO
	// gyros
	if(id == SensorID::GRYO) {
		// ultrasonic
	} else if(id == SensorID::CLAW) {
		// potentiometer
	} else {

	}
}
bool Sensors::HasProgressed(SensorID id, int lastValue)
#endif
