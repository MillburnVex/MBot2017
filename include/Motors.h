#ifndef MOTORSENSOR_H
#define MOTORSENSOR_H

#include "Sensors.h"

class Motor {
public:
// ID is used in physical access to IO ports for controlling motor
int id;
// The current power amount being fed into the motor
int currentPower;
// The default sensor to check progress against. SensorID::NONE for no sensor,
// you can use a different sensor when creating a MotorAction if you want it to
// temporarily use some other measure
SensorID defaultSensorID;

Motor(int id, SensorID _defaultSensorID);

// Adjusts physical power being fed into corresponding port along with updating
// currentPower appropriately
void SetSpeed(int speed);

// Set speed to 0
void Stop();

bool operator==(Motor other);
};
namespace Motors {
// The IDs should be the port nums
static Motor DRIVE_TOP_RIGHT = Motor(0, SensorID::NONE);
static Motor DRIVE_TOP_LEFT = Motor(1, SensorID::NONE);
static Motor DRIVE_BOTTOM_RIGHT = Motor(2, SensorID::NONE);
static Motor DRIVE_BOTTOM_LEFT = Motor(3, SensorID::NONE);
}

#endif
