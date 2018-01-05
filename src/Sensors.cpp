#ifndef SENSORS
#define SENSORS
#include "../include/Sensors.h"
#include "../include/Quickmaths.h"
#include "../include/API.h"

const int SONIC_ECHO_PORT = -1;
const int SONIC_PING_PORT = -1;

void Sensors::Calibrate(Sensor id) {
	analogCalibrate(id);
}

int Sensors::GetValue(Sensor id) {
    if(id == ULTRASONIC) {
        return ultrasonicGet(sonic);
    }
	return analogReadCalibrated(id);
}


void Sensors::InitAll() {
	Calibrate(Sensor::P_MOBILE_GOAL);
	Calibrate(Sensor::P_LIFT_LEFT);
	Calibrate(Sensor::P_LIFT_RIGHT);
    sonic = ultrasonicInit(SONIC_ECHO_PORT, SONIC_PING_PORT);
}

void Sensors::CalibrateAll() {
    Calibrate(Sensor::P_MOBILE_GOAL);
    Calibrate(Sensor::P_LIFT_LEFT);
    Calibrate(Sensor::P_LIFT_RIGHT);
}

#endif
