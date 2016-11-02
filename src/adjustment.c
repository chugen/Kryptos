/*
 * adjustment.c
 *
 *  Created on: 2016/10/29
 *      Author: Gen
 */
#include <stdint.h>
#include "my_typedef.h"
#include "iodefine.h"
#include "app.h"
#include "run.h"
#include "global.h"
#include "common.h"
/****************************************
 調整用初期化
 ****************************************/
void initAdjustment(void) {
	waitSensor();

	driveRGB(GREEN, ON);
	waitTime(1000);
	calcGyroZRef();
	driveSuction(70, ON);
	waitTime(1000);
	initRun();
	driveMotor(ON);
	switchSensorLED(ON);
}

/****************************************
 調整用関数1
 ****************************************/
void selectAdjustment(void) {

	driveRGB(MAGENTA, ON);
	waitTime(500);

	switch (selectMode(13)) {

	case 0:
		initAdjustment();
		runStraight(15, SECTION, 1, 1);

		turnCorner(turn_90_wide_L_1000);
		switchSensorLED(OFF);
		runStraight(15, SECTION, 1, 0);

		break;
	case 1:
		initAdjustment();
		runStraight(15, SECTION, 1, 1);

		turnCorner(turn_90_wide_R_1000);
		switchSensorLED(OFF);
		runStraight(15, SECTION, 1, 0);

		break;
	case 2:
		initAdjustment();
		runStraight(15, SECTION, 1, 1);

		turnCorner(turn_180_L_1000);
		switchSensorLED(OFF);
		runStraight(15, SECTION, 1, 0);

		break;

	case 3:
		initAdjustment();
		runStraight(15, SECTION, 1, 1);

		turnCorner(turn_180_R_1000);
		switchSensorLED(OFF);
		runStraight(15, SECTION, 1, 0);

		break;
	case 4:
		initAdjustment();
		runStraight(15, SECTION , 1, 1);
		turnCorner(turn_45_in_L_1000);
		switchSensorLED(OFF);
		runStraight(15, SECTION * M_SQRT2, 1, 0);

		break;
	case 5:
		initAdjustment();
		runStraight(15, SECTION, 1, 1);
		turnCorner(turn_45_in_R_1000);
		switchSensorLED(OFF);
		runStraight(15, SECTION * M_SQRT2, 1, 0);

		break;
	case 6:
		initAdjustment();
		runStraight(15, SECTION * M_SQRT2, 1, 1);
		turnCorner(turn_45_out_L_1000);
		switchSensorLED(OFF);
		runStraight(15, SECTION , 1, 0);

		break;
	case 7:
		initAdjustment();
		runStraight(15, SECTION * M_SQRT2, 1, 1);
		turnCorner(turn_45_out_R_1000);
		switchSensorLED(OFF);
		runStraight(15, SECTION , 1, 0);

		break;
	case 8:
		initAdjustment();
		runStraight(15, SECTION , 1, 1);
		turnCorner(turn_135_in_L_1000);
		switchSensorLED(OFF);
		runStraight(15, SECTION * M_SQRT2, 1, 0);

		break;
	case 9:
		initAdjustment();
		runStraight(15, SECTION , 1, 1);
		turnCorner(turn_135_in_R_1000);
		switchSensorLED(OFF);
		runStraight(15, SECTION * M_SQRT2, 1, 0);

		break;
	case 10:
		initAdjustment();
		runStraight(15, SECTION * M_SQRT2, 1, 1);
		turnCorner(turn_135_out_L_1000);
		switchSensorLED(OFF);
		runStraight(15, SECTION , 1, 0);

		break;
	case 11:
		initAdjustment();
		runStraight(15, SECTION * M_SQRT2, 1, 1);
		turnCorner(turn_135_out_R_1000);
		switchSensorLED(OFF);
		runStraight(15, SECTION , 1, 0);

		break;
	case 12:
		initAdjustment();
		runStraight(15, SECTION * M_SQRT2, 1, 1);
		turnCorner(turn_v90_L_1000);
		switchSensorLED(OFF);
		runStraight(15, SECTION * M_SQRT2, 1, 0);

		break;
	case 13:
		initAdjustment();
		runStraight(15, SECTION * M_SQRT2, 1, 1);
		turnCorner(turn_v90_R_1000);
		switchSensorLED(OFF);
		runStraight(15, SECTION * M_SQRT2, 1, 0);

		break;

	default:
		break;

	}
	driveMotor(OFF);
	driveSuction(70, OFF);
	waitButton();
	printLog();
}
