#ifndef COMPOUND_ACTION_H
#define COMPOUND_ACTION_H
#include "MotorAction.h"
#include "Bot.h"

class CompoundAction {
public:
virtual void Run() = 0;
};

class DriveLeft : CompoundAction {
public:
int speed;
DriveLeft(int _speed);
void Run();
};

class DriveRight : CompoundAction {
public:
int speed;
DriveRight(int _speed);
void Run();
};

class DriveRotate : CompoundAction {
public:
int speed;
int dir;
// dir 1 = right, dir -1 = left
DriveRotate(int _speed, int _dir);
void Run();
};

class DriveVertical : CompoundAction {
public:
int speed;
DriveVertical(int _speed);
void Run();
};

#endif
