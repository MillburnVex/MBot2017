/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"
#include "bot.h"
#include "fastmath.h"
//#include <stdio.h>

/*
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (inc luding system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */
void operatorControl() {
	//Bot bot = getBot();
	bool lastopen = false;
	bool autohold = true;
	bool autodumping = false;
	bool confirmeddone = false;
	bool donelifting = false;
	int autoticks = 0;
	int badticks = 0;
	int hold = analogRead(4);
	while (1) {
		int jx = joystickGetAnalog(1, 3)*0.8;
		int jy = joystickGetAnalog(1, 4)*0.8;

		int lliftpot = analogReadCalibrated(2);
		int rliftpot = analogReadCalibrated(1);
		int gliftpot = analogReadCalibrated(3);
		int armpot = analogRead(4);

		int dif = rliftpot-lliftpot;
		dif *= -0.1f;
		if(lliftpot > 1000 && rliftpot > 1000) dif = 0;

		if(abs(jx) > 30 || abs(jy) > 30){
			motorSet(frdrive, -jx-jy);  //right drive front
			motorSet(brdrive, -jx-jy);  //right drive back
			motorSet(bldrive, -jx+jy);  //left drive back
			motorSet(fldrive, -jx+jy);  //left drive front
		}else{
			motorSet(frdrive, 0);
			motorSet(brdrive, 0);

			motorSet(bldrive, 0);
			motorSet(fldrive, 0);
		}

		//bot.setMotor("rf", jx+jy);
		//bot.setMotor("rb", jx+jy);
		//bot.setMotor("lf", jx-jy);
		//bot.setMotor("lb", jx-jy);
		if(!autodumping){
			if(joystickGetDigital(1, 8, JOY_DOWN)){
				motorSet(arm, 100);  //arm back
				hold = armpot;
			}else if(joystickGetDigital(1, 8, JOY_UP)){
				motorSet(arm, -100);  //arm forward
				hold = armpot;
			}else{
				motorSet(arm, -0.15 * (armpot-hold)); 
			}

			if(joystickGetDigital(1, 7, JOY_UP)){
				motorSet(llift, 127 - dif);  //left lift up
				motorSet(rlift, -127 + dif);  //right lift up
			}else if(joystickGetDigital(1, 7, JOY_DOWN)){
				motorSet(llift, -127 + dif);  //left lift down
				motorSet(rlift, 127 - dif);  //right lift down
			}else{
				motorSet(llift, 0);  //left lift stop
				motorSet(rlift, 0);  //right lift stop
			}

			if(joystickGetDigital(1, 6, JOY_DOWN)){
				motorSet(claw, -50);  //claw open
				lastopen = true;
			}else if(joystickGetDigital(1, 6, JOY_UP)){
				motorSet(claw, 50);  //claw close
				lastopen = false;
			}else{
				motorSet(claw, lastopen?-4:15);  //claw stop
			}
		}

		

		if(joystickGetDigital(1, 5, JOY_UP)){
			motorSet(goallift, -127);  //goal lift up
		}else if(joystickGetDigital(1, 5, JOY_DOWN)){
			motorSet(goallift, 60);  //goal lift down
		}else{
			if(gliftpot > 350){
				motorSet(goallift, -30);  //claw stop
			}else{
				motorSet(goallift,0);
			}
		}
		printf("%d   %d   %f\n", autoticks, badticks, (float)badticks/(float)autoticks);
		if(joystickGetDigital(1, 8, JOY_LEFT) || autodumping){
			autodumping = true;
			if(ultrasonicGet(Bot::sonic) < 30 && ultrasonicGet(Bot::sonic) > 5  && !donelifting){
				motorSet(llift, 127 - dif);  //left lift up
				motorSet(rlift, -127 + dif);  //right lift up
				motorSet(claw, 15);
				autoticks++;
			}else if(!(ultrasonicGet(Bot::sonic) < 30 && ultrasonicGet(Bot::sonic) > 5) && !donelifting){
				autoticks++;
				badticks++;

				if(((float)badticks/(float)autoticks) < 0.5f){
					donelifting = true;
					autoticks = 0;
				}
				if(autoticks > 20){
					autoticks = 0;
					badticks = 0;
				}
			}else{
				motorSet(llift, 0);
				motorSet(rlift, 0);
				if(armpot > 1700){
					motorSet(claw, 15);
					motorSet(arm, -0.8f * (armpot - 1200));
				}else{
					autoticks++;
					motorSet(arm, -0.1f * (armpot - 1200));
					if(autoticks > 20){
						motorSet(claw, -40);
						autoticks++;
						if (autoticks > 50){
							autoticks = 0;
							badticks = 0;
							autodumping = false;
							confirmeddone = 0;
							donelifting = false;
							lastopen = true;
						}
					}
				}
			}
		}
		printf("%d\n", ultrasonicGet(Bot::sonic));
		if(joystickGetDigital(1, 7, JOY_RIGHT)){
			autoticks = 0;
			badticks = 0;
			autodumping = false;
			confirmeddone = 0;
			donelifting = false;
			lastopen = true;
		}

		if(joystickGetDigital(1, 7, JOY_LEFT) && joystickGetDigital(1, 8, JOY_RIGHT)){
			analogCalibrate(1);
  			analogCalibrate(2);
  			analogCalibrate(3);
  			analogCalibrate(4);
		}

		delay(20);
	}
}
