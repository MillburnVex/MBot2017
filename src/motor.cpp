#ifndef MOTOR
#define MOTOR
#include "main.h"
#include "Motor.h"

Motor::Motor(){
        location = -1;
}

Motor::Motor(int loc, char* mname, bool rev){
        location = loc;
        reversed = rev;
        name = mname;
}

Motor::Motor(int loc){
        location = loc;
}

void Motor::setSpeed(int speed){
        currentpower = speed;
        printf("hit the quan\n");
        printf("%d\n", location);
        if(reversed) currentpower = -currentpower;
        motorSet(location, currentpower);
}

void Motor::stop(){
        currentpower = 0;
        motorStop(location);
}

MotorGroup::MotorGroup(){
}

MotorGroup::MotorGroup(Motor usedmotors[], int motoramount){
        motors = usedmotors;
        motorcount = motoramount;
}

bool MotorGroup::isUsed(){
        return currentpower == 0;
}

int MotorGroup::getPower(){
        return currentpower;
}

void MotorGroup::setPower(int npower){
        currentpower = npower;

        for(int i = 0; i < motorcount; i++) {
                motors[i].setSpeed(npower);
        }
}
#endif
