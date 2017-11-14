#ifndef POTENTIOMETER
#define POTENTIOMETER
#include "bot.h"
#include "SensorID.h"
class Sensor {
public:
  int getValue(SensorID id) {
    return analogReadCalibrated(id);
  }
};
#endif
