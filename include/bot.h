#ifndef BOT_H

#define BOT_H

#include "API.h"
#include "Motor.h"

namespace Bot {
Ultrasonic sonic;
Gyro gryo;
Motor motors[12];
Motor* GetMotor(char* name);
Motor* GetMotor(int loc);
void SetMotor(char* name, int speed);
void AddMotor(Motor motor);
}

/*

   int const llift = 2;
   int const rlift = 9;
   int const arm = 5;
   int const brdrive = 8;
   int const bldrive = 4;
   int const frdrive = 7;
   int const fldrive = 3;
   int const claw = 6;
   int const goallift = 10;
   int const armpotentiometer = 4;
   int const lliftpotentiometer = 2;
   int const rliftpotentiometer = 1;
   int const gliftpotentiometer = 3;

 */


/*

   class Bot {
   public:
        static Ultrasonic sonic;
        static Gyro gyro;
        Motor motors[12];
        MotorGroup groups[6];
        int lgroup;
   //12 digital
   //8 analog

 */
#endif
