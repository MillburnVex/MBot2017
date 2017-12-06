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
#include "Bot.h"
#include "Joystick.h"
#include "Quickmaths.h"

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

static const double JOYSTICK_SENSITIVITY = 0.8;

void operatorControl() {
	while(1) {
		int vertical = Joystick::getValue(JoystickPort::DRIVE_VERTICAL);
	}
	return;
	/*
	   oops
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
	        int lx = joystickGetAnalog(1, 1)*0.8;

	        if(abs(lx) < 20) lx = 0; ;

	        // Left lift potentiometerg
	        int lliftpot = analogReadCalibrated(2);
	        // Right lift potentiometer
	        int rliftpot = analogReadCalibrated(1);
	        // Goal lift potentiometer
	        int gliftpot = analogReadCalibrated(3);
	        int armpot = analogRead(4);
	        if(armpot < 259) armpot = 4095;
	        int dif = rliftpot-lliftpot;
	        dif *= -0.1f;
	        if(lliftpot > 1000 && rliftpot > 1000) dif = 0;

	        if(abs(jx) > 30 || abs(jy) > 30) {
	                runDrive(jx,jy);
	        }else{
	                runDrive(0,0);
	        }

	        //bot.setMotor("rf", jx+jy);
	        //bot.setMotor("rb", jx+jy);
	        //bot.setMotor("lf", jx-jy);
	        //bot.setMotor("lb", jx-jy);

	        if(!autodumping) {
	                if(joystickGetDigital(1, 8, JOY_DOWN)) {
	                        motorSet(arm, 100); //arm back
	                        hold = armpot;
	                }else if(joystickGetDigital(1, 8, JOY_UP)) {
	                        motorSet(arm, -100); //arm forward
	                        hold = armpot;
	                }else{
	                        motorSet(arm, -0.15 * (armpot-hold));
	                }
	                if(abs(lx) > 10);

	                if(joystickGetDigital(1, 7, JOY_UP)) {
	                        motorSet(llift, 127 - dif+lx); //left lift up
	                        motorSet(rlift, -127 + dif+lx); //right lift up
	                }else if(joystickGetDigital(1, 7, JOY_DOWN)) {
	                        motorSet(llift, -127 + dif+lx); //left lift down
	                        motorSet(rlift, 127 - dif+lx); //right lift down
	                }else{
	                        motorSet(llift, lx); //left lift stop
	                        motorSet(rlift, lx); //right lift stop
	                }



	                if(joystickGetDigital(1, 6, JOY_DOWN)) {
	                        motorSet(claw, -50); //claw open
	                        lastopen = true;
	                }else if(joystickGetDigital(1, 6, JOY_UP)) {
	                        motorSet(claw, 50); //claw close
	                        lastopen = false;
	                }else{
	                        motorSet(claw, lastopen ? -4 : 15); //claw stop
	                }
	        }

	        if(joystickGetDigital(1, 5, JOY_UP)) {
	                setMobileLift(127); //goal lift up
	        }else if(joystickGetDigital(1, 5, JOY_DOWN)) {
	                setMobileLift(-60); //goal lift down
	        }else{
	                setMobileLift(0);
	        }
	        printf("%d\n", armpot);
	        if(joystickGetDigital(1, 8, JOY_LEFT) || autodumping) {
	                autodumping = true;
	                if(ultrasonicGet(Bot::sonic) < 50 && ultrasonicGet(Bot::sonic) > 5  && !donelifting) {
	                        motorSet(llift, 127 - dif); //left lift up
	                        motorSet(rlift, -127 + dif); //right lift up
	                        motorSet(claw, 15);
	                        motorSet(arm, 0);

	                        if(autoticks > 10) {
	                                autoticks = 0;
	                                badticks = 0;
	                        }
	                }else if(!(ultrasonicGet(Bot::sonic) < 50 && ultrasonicGet(Bot::sonic) > 5) && !donelifting) {
	                        autoticks++;
	                        badticks++;

	                        if(((float)badticks/(float)autoticks) > 0.5f && badticks > 3) {
	                                donelifting = true;
	                                autoticks = 0;
	                        }
	                        if(autoticks > 10) {
	                                autoticks = 0;
	                                badticks = 0;
	                        }
	                }else{

	                        motorSet(llift, lx); //left lift up
	                        motorSet(rlift, lx); //right lift up
	                        if(armpot > 1500) {
	                                motorSet(claw, 15);
	                                motorSet(arm, -0.8f * (armpot - 900));
	                        }else{
	                                autoticks++;
	                                motorSet(arm, -0.1f * (armpot - 900));
	                                if(autoticks > 20) {
	                                        autoticks++;
	                                        if(autoticks < 50) {
	                                                motorSet(claw, -40);
	                                                motorSet(arm, 80);
	                                        }

	                                        if(autoticks > 50) {
	                                                motorSet(claw, 40);
	                                                motorSet(arm, 80);
	                                        }

	                                        if (autoticks > 80) {
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

	        if(joystickGetDigital(1, 7, JOY_RIGHT)) {
	                autoticks = 0;
	                badticks = 0;
	                autodumping = false;
	                confirmeddone = 0;
	                donelifting = false;
	                lastopen = true;
	        }

	        if(joystickGetDigital(1, 7, JOY_LEFT) && joystickGetDigital(1, 8, JOY_RIGHT)) {
	                analogCalibrate(1);
	                analogCalibrate(2);
	                analogCalibrate(3);
	                analogCalibrate(4);
	        }

	        delay(20);
	   }
	 */
}
