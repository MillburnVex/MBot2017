#ifndef MOTOR_H
#define MOTOR_H

class Motor {
public:
int location = -1;
int currentPower;
char* name = "";

Motor();

Motor(int _location, char* _name);

Motor(int _location);

void SetSpeed(int speed);

void Stop();
};

#endif
