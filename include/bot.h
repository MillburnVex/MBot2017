#ifndef BOT_H

#define BOT_H

#include "main.h"
#include "fastmath.h"
#include "motor.h"
#include "vectors.h"
#include <map>

class Bot{
  std::map<int, Motor> motors;
};

#endif
