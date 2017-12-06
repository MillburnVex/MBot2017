#ifndef BOT_H

#define BOT_H

#include "API.h"
#include "Motors.h"
#include "MotorAction.h"
#include <vector>

// Namespace and static to avoid singletons, versus singletons? I like the namespace better
// https://stackoverflow.com/questions/5793334/c-static-vs-namespace-vs-singleton
namespace Bot {
// TODO are these necessary to have here? I.E. what function do they serve
static Ultrasonic sonic;
static Gyro gryo;

// Array and not vec because memory limits
// Pointer b/c init as null
static Motor* motors[12];

// The 'queue' of currently running actions to be evaluated, if necessary
static std::vector<MotorAction> actionQueue;
static Motor* GetMotor(char* name);
static Motor* GetMotor(int id);
static void SetMotor(int id, int speed);
static void AddMotor(Motor* motor);
static void ExecuteAction(MotorAction& action);
static void Tick();
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
