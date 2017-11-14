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
#include "config.h"

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
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */

const short int STICK_THRESH = 11,
	LEFT_DRIVE = 0,
	RIGHT_DRIVE = 1,
	LIFT = 2,
	MOBILE_GOAL = 3,
	INTAKE = 4;


void operatorControl() {
	int sticks[4] = { 0, 0, 0, 0 };
	unsigned int btns[4] = { 0, 0, 0, 0 },
		btnsLast[4] =  { 0, 0, 0, 0 };
	int mtrPwr[5] = { 0, 0, 0, 0, 0 },
		mtrPwrLast[5] = { 0, 0, 0, 0, 0};

	while (true) {
		for(int i = 0; i < 4; i++)
			sticks[i] = (abs(joystickGetAnalog(0, i)) >= STICK_THRESH)
				? joystickGetAnalog(0, i)
				: 0;
		for(int group = 0; group < 4; group++) {
			btns[group] = 0;
			if(joystickGetDigital(0, group, JOY_DOWN))
				btns[group] += JOY_DOWN;
			if((group == 7 || group == 8)
				&& joystickGetDigital(0, group, JOY_LEFT))
				btns[group] += JOY_LEFT;
			if(joystickGetDigital(0, group, JOY_UP))
				btns[group] += JOY_UP;
			if((group == 7 || group == 8)
				&& joystickGetDigital(0, group, JOY_RIGHT))
				btns[group] += JOY_RIGHT;
		}

		mtrPwr[LEFT_DRIVE] = sticks[2] + sticks[3];
		mtrPwr[RIGHT_DRIVE] = sticks[2] - sticks[3];
		mtrPwr[LIFT] = (btns[0] & JOY_UP) ^ (btns[0] & JOY_DOWN)
			? (btns[0] & JOY_UP)
				? 127
				: -127
			: 0;
		mtrPwr[MOBILE_GOAL] = (btns[1] & JOY_UP) ^ (btns[1] & JOY_DOWN)
				? (btns[1] & JOY_UP)
				? 127
				: -127
			: 0;
		mtrPwr[INTAKE] = (btns[2] & JOY_UP) ^ (btns[2] & JOY_DOWN)
			? (btns[2] & JOY_UP)
				? 127
				: -127
			: 0;


		setDriveL(mtrPwr[LEFT_DRIVE]);
		setDriveR(mtrPwr[RIGHT_DRIVE]);
		setLift(mtrPwr[LIFT]);
		setGoal(mtrPwr[MOBILE_GOAL]);
		setIntake(mtrPwr[INTAKE]);

		for(unsigned int i = 0; i < sizeof(mtrPwr) / sizeof(int); i++)
			mtrPwrLast[i] = mtrPwr[i];

		for(unsigned int i = 0; i < sizeof(btns) / sizeof(int); i++)
			btnsLast[i] = btns[i];

		delay(20);
	}
}
