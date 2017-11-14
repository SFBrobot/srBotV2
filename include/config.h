#ifndef CONFIG_FUNCS

#define CONFIG_FUNCS

#include "main.h"

#define roller 1
#define lLift 2
#define rLift 3
#define frDrive 4
#define brDrive 5
#define lDriveY 6
#define mrDrive 7
#define mlDrive 8
#define lGoal 9
#define rGoal 10

#define liftPot 1
#define goalPot 2
#define lDriveEnc_Lower 9
#define lDriveEnc_Upper 10
#define lDriveEnc 0
#define rDriveEnc_Lower 11
#define rDriveEnc_Upper 12
#define rDriveEnc 1

Encoder Encs[2];

char setDriveL(char pwr) {
	motorSet(lDriveY, pwr);
	motorSet(mlDrive, -pwr);
	return pwr;
}

char setDriveR(char pwr) {
	motorSet(frDrive, -pwr);
	motorSet(mrDrive, pwr);
	motorSet(brDrive, -pwr);
	return pwr;
}

char setLift(char pwr) {
	motorSet(lLift, -pwr);
	motorSet(rLift, pwr);
	return pwr;
}

char setGoal(char pwr) {
	motorSet(lGoal, -pwr);
	motorSet(rGoal, pwr);
	return pwr;
}

char setIntake(char pwr) {
	motorSet(roller, pwr);
	return pwr;
}

#endif
