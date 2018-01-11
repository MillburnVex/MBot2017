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
#ifndef AUTO
#define AUTO
#include "../include/main.h"
#include "../include/Motors.h"

/*
 * Runs the user autonomous code. This function will be started in its own task with the default
 * priority and stack size whenever the robot is enabled via the Field Management System or the
 * VEX Competition Switch in the autonomous mode. If the robot is disabled or communications is
 * lost,  the autonomous task will be stopped by the kernel. Re-enabling the robot will restart
 * the task, not re-start it from where it left off.
 *
 * Code running in the autonomous task cannot access information from the VEX Joystick. However,
 * the autonomous function can be invoked from another task if a VEX Competition Switch is not
 * available, and it can access joystick information if called in this way.
 *
 * The autonomous task may exit, unlike operatorControl() which should never exit. If it does
 * so, the robot will await a switch to another mode or disable/enable cycle.
 */

/*
 * Runs the user autonomous code. This function will be started in its own task with the default
 * priority and stack size whenever the robot is enabled via the Field Management System or the
 * VEX Competition Switch in the autonomous mode. If the robot is disabled or communications is
 * lost,  the autonomous task will be stopped by the kernel. Re-enabling the robot will restart
 * the task, not re-start it from where it left off.
 *
 * Code running in the autonomous task cannot access information from the VEX Joystick. However,
 * the autonomous function can be invoked from another task if a VEX Competition Switch is not
 * available, and it can access joystick information if called in this way.
 *
 * The autonomous task may exit, unlike operatorControl() which should never exit. If it does
 * so, the robot will await a switch to another mode or disable/enable cycle.
 */
void runDrive(int jx, int jy){
	motorSet(MotorID::DRIVE_LEFT, jx-jy);
	motorSet(MotorID::DRIVE_RIGHT, jx+jy);
}

void autonomous() {
	Ultrasonic sonic = ultrasonicInit(2,1);

	motorSet(MotorID::CLAW, 20);
	runDrive(-100,0);
	motorSet(MotorID::ARM, 100);
	delay(200);
	runDrive(100,0);
	motorSet(1, 100);
	delay(1000);
	motorSet(MotorID::ARM, 20);
	delay(2000);
	motorSet(1, -100);
	runDrive(0,0);
	delay(1500);
	motorSet(1,0);
	motorSet(MotorID::CLAW, -100);
	delay(500);
	motorSet(MotorID::CLAW,0);
	runDrive(-100,0);
	delay(2500);
	runDrive(0,100);
	delay(2000);
	runDrive(100,0);
	motorSet(1,127);
	delay(1000);
	runDrive(0,0);
	delay(500);
	runDrive(-100,0);
	delay(500);
	motorSet(1,0);
	runDrive(0,0);
}

#endif
