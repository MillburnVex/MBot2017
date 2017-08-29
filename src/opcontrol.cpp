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
	int i = 0;
	while (1) {
		i++;
		int rotate = joystickGetAnalog(1, 3);
		int strafe = joystickGetAnalog(1, 4);
		int power = joystickGetAnalog(1, 1);
		float r = fasthypot(power,strafe);
		float angle = fastatan2(strafe,power) - PI / 4;

		// if(r * cos(angle) + rotate > 15){
		// 	motorSet(6, r * cos(angle) + rotate); //FL
		// }
		// else{
		// 	motorSet(6, 0);
		// }
		// if(r * sin(angle) + rotate > 15){
		// 	motorSet(7, r * sin(angle) + rotate); //BL
		// }
		// else{
		// 	motorSet(7, 0);
		// }
		// if(r * cos(angle) - rotate > 15){
		// 	motorSet(8, r * cos(angle) - rotate); //BR
		// }
		// else{
		// 	motorSet(8, 0);
		// }
		// if(r * sin(angle) - rotate > 15){
		// 	motorSet(9, r * sin(angle) - rotate); //FR
		// }
		// else{
		// 	motorSet(9, 0);
		// }



		if(power + strafe + rotate > 15 || power + strafe + rotate < -15){
			motorSet(6, power + strafe + rotate); //FL
		}
		else{
			motorSet(6, 0);
		}
		if(power - strafe + rotate > 15 || power - strafe + rotate < -15){
			motorSet(7, power - strafe + rotate); //BL
		}
		else{
			motorSet(7, 0);
		}
		if(power - strafe - rotate > 15 || power - strafe - rotate < -15){
			motorSet(8, power - strafe - rotate); //BR
		}
		else{
			motorSet(8, 0);
		}
		if(power + strafe - rotate > 15 || power + strafe - rotate < -15){
			motorSet(9, power + strafe - rotate); //FR
		}
		else{
			motorSet(9, 0);
		}

		delay(20);
	}
}
