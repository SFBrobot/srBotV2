/** @file init.c
 * @brief File for initialization code
 *
 * This file should contain the user initialize() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"
#include "config.h"
#include "prosPid.h"

const unsigned int AUTON_SELECT_TIMEOUT = 8 * 1000;
const short AUTON_ROUTINE_MAX = 8;

short autonRoutine = 0;

/*
 * Runs pre-initialization code. This function will be started in kernel mode one time while the
 * VEX Cortex is starting up. As the scheduler is still paused, most API functions will fail.
 *
 * The purpose of this function is solely to set the default pin modes (pinMode()) and port
 * states (digitalWrite()) of limit switches, push buttons, and solenoids. It can also safely
 * configure a UART port (usartOpen()) but cannot set up an LCD (lcdInit()).
 */
void initializeIO() {
}

/*
 * Runs user initialization code. This function will be started in its own task with the default
 * priority and stack size once when the robot is starting up. It is possible that the VEXnet
 * communication link may not be fully established at this time, so reading from the VEX
 * Joystick may fail.
 *
 * This function should initialize most sensors (gyro, encoders, ultrasonics), LCDs, global
 * variables, and IMEs.
 *
 * This function must exit relatively promptly, or the operatorControl() and autonomous() tasks
 * will not start. An autonomous mode selection menu like the pre_auton() in other environments
 * can be implemented in this task if desired.
 */
void initialize() {
	bool autonConfirm = false;
	char str[16];
	setTeamName("4800A");
	Encs[lDriveEnc] = encoderInit(lDriveEnc_Upper, lDriveEnc_Lower, false);
	Encs[rDriveEnc] = encoderInit(rDriveEnc_Upper, rDriveEnc_Lower, false);
	lcdInit(uart1);
	lcdInit(uart2);
	lcdClear(uart1);
	lcdClear(uart2);
	lcdSetBacklight(uart1, true);
	lcdSetBacklight(uart2, true);
	if(isOnline()) {
		lcdSetText(uart1, 1, " Auton Selected ");
		int time0 = millis();
		while(millis() - time0 < AUTON_SELECT_TIMEOUT && !autonConfirm) {
			snprintf(str, 16, "         %d           ", autonRoutine);
			lcdSetText(uart1, 2, str);

			if(lcdReadButtons(uart1) == LCD_BTN_LEFT)
				autonRoutine--;
				else if(lcdReadButtons(uart1) == LCD_BTN_RIGHT)
				autonRoutine++;
				if(autonRoutine < 0)
				autonRoutine = AUTON_ROUTINE_MAX;
				else if(autonRoutine > AUTON_ROUTINE_MAX)
				autonRoutine = 0;

				if(lcdReadButtons(uart1) == LCD_BTN_CENTER)
				autonConfirm = true;
			}
			if(!autonConfirm)
			autonRoutine = 0;
			lcdSetBacklight(uart1, false);
	}
}
