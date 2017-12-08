#ifndef COMPOUNDACTION
#define COMPOUNDACTION
#include <vector>
#include "MotorAction.h"
class CompoundAction {
virtual const* MotorAction create() = 0;
};

namespace Actions {

}
#endif
