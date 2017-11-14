#ifndef ACTION
#define ACTION
class Action {
  public:
    int goalValue;
    int cancelThreshold;
    Action(int gV, int cThreshold = 20) {
      goalValue = gV;
      cancelThreshold = cThreshold;
    };
};
typedef int ID;
class MotorAction : public Action {
  public:
    ID motorID;
    MotorAction(int gV, ID mID, int cThreshold = 20) : Action(gV, cThreshold) {
      motorID = mID;
    };
};
#endif
