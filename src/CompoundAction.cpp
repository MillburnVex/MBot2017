#ifndef COMPOUNDACTION
#define COMPOUNDACTION
#include <vector>
#include "MotorAction.h"
class CompoundAction {
virtual std::vector<MotorAction>& create() = 0;
};

namespace Actions {
class DriveVertical : CompoundAction {
int amount;
DriveVertical(int _amount) : CompoundAction() {
	this->amount = _amount;
}
std::vector<MotorAction>& create() {
}
};
// tick, predicate, onFinish, timelimit
}
#endif
