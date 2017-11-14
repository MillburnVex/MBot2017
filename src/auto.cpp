/** @file auto.c
 * @brief File for autonomous code
 *
 * This file should contain the user autonomous() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"
#include "util.h"
#include "bot.h"

/*
 * Runs the user autonomous code. This function will be started in its own task with the default
 * priority and stack size whenever the robot is enabled via the Field Management System or the
 * VEX Competition Switch in the autonomous mode. If the robot is disabled or communications is
 * lost, the autonomous task will be stopped by the kernel. Re-enabling the robot will restart
 * the task, not re-start it from where it left off.
 *
 * Code running in the autonomous task cannot access information from the VEX Joystick. However,
 * the autonomous function can be invoked from another task if a VEX Competition Switch is not
 * available, and it can access joystick information if called in this way.
 *
 * The autonomous task may exit, unlike operatorControl() which should never exit. If it does
 * so, the robot will await a switch to another mode or disable/enable cycle.
 */
void autonomous() {
	
	int start = gyroGet(Bot::gyro);
	motorSet(arm,100);
	runDrive(-100,0);
	delay(300);

	runDrive(0,0);
	motorSet(claw, 20);
	delay(1500);

	motorSet(claw, -40);
	delay(800);

	runDrive(90,0);
	delay(300);

	runDrive(0,0);
	motorSet(claw,30);
	delay(300);

	motorSet(arm, -25);

	runDrive(-60,0);
	motorSet(claw,20);
	delay(800);
	runDrive(0,0);
	
	bool done = false;
	int autoticks = 0;
	while(!done){
		delay(20);
		int armpot = analogRead(armpotentiometer);
		if(armpot > 1600){
			motorSet(claw, 20);
			motorSet(arm, -1.0f * (armpot - 1100));
		}else{
			autoticks++;
			motorSet(arm, -0.1f * (armpot - 1100));
			if(autoticks > 20){
				motorSet(claw, -40);
				autoticks++;
				if (autoticks > 50){
					autoticks = 0;
					done = true;
				}
			}
		}
	}
	motorSet(arm, 100);
	delay(200);

	motorSet(claw, 50);

}