#ifndef ACTION
#define ACTION
#include "SensorID.h"
class Action {
  public:
    int goalValue;
    int cancelThreshold;
    SensorID sensor;

    Action(int gV, SensorID s, int cThreshold = 20) {
      goalValue = gV;
      sensor = s;
      cancelThreshold = cThreshold;
    }
};
typedef struct {int ID; SensorID sensorID;} MotorID;
class MotorAction : public Action {
  public:
    MotorID motorID;
    MotorAction(int gV, MotorID mID, int cThreshold = 20) : Action(gV, mID.sensorID, cThreshold) {
      motorID = mID;
    }
};
#endif
