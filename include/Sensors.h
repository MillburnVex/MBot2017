#ifndef SENSORS_H
#define SENSORS_H

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
bool hasProgressed(SensorID id, int lastValue);
}
#endif
