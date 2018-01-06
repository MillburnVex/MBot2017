#ifndef SENSORS
#define SENSORS
#include "../include/Sensors.h"
#include "../include/Quickmaths.h"
#include "../include/API.h"

const int SONIC_ECHO_PORT = 5;
const int SONIC_PING_PORT = 6;
const int RIGHT_ENCODER_TOP = 1;
const int RIGHT_ENCODER_BOTTOM = 2;
const int LEFT_ENCODER_TOP = 3;
const int LEFT_ENCODER_BOTTOM = 4;

void Sensors::Calibrate(Sensor id) {
	analogCalibrate(id);
}

int Sensors::GetValue(Sensor id) {
	if(id == ULTRASONIC) {
		return ultrasonicGet(sonic);
	} else if(id == E_LIFT_LEFT) {
		return encoderGet(liftLeft);
	} else if(id == E_LIFT_RIGHT) {
		return encoderGet(liftRight);
	}
	return analogReadCalibrated(id);
}

void Sensors::InitAll() {
	Calibrate(Sensor::P_MOBILE_GOAL);
	Calibrate(Sensor::P_ARM);
	liftRight = encoderInit(RIGHT_ENCODER_TOP, RIGHT_ENCODER_BOTTOM, false);
	liftLeft = encoderInit(LEFT_ENCODER_TOP, LEFT_ENCODER_BOTTOM, false);
	sonic = ultrasonicInit(SONIC_ECHO_PORT, SONIC_PING_PORT);
}

void Sensors::CalibrateAll() {
	Calibrate(Sensor::P_MOBILE_GOAL);
	Calibrate(Sensor::P_ARM);
	encoderReset(liftLeft);
	encoderReset(liftRight);
}

#endif
