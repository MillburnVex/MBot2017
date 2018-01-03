/*
 #ifndef CLAW
 #define CLAW
 #include "Motors.h"
   const int TICKS_TO_FULLY_IN = 160;
   const int CLAW_SPEED = 100;
   // how many ticks this has been going in for
   static int ticksIn = 0;
   static bool in = false;
   static bool out = false;
   namespace Claw {
   void Out() {
        in = false;
        out = true;
   }
   void In() {
        in = true;
        out = false;
   }
   void Update() {
        if(out) {
                Motors::SetSpeed(MotorID::CLAW, CLAW_SPEED);
        } else if(in) {
                if(ticksIn == TICKS_TO_FULLY_IN) {
                        in = false;
                        ticksIn = 0;
                } else {
 ++ticksIn;
                        Motors::SetSpeed(MotorID::CLAW, CLAW_SPEED);
                }
        }
   }
   }
 #endif
 */
