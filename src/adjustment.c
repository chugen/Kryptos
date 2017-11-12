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
#include "parameter.h"
#include "sensor.h"

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

	g_flag_shortest_goal = 1;
}
/****************************************
 調整用初期化2
 ****************************************/
void initAdjustment2(void) {
	waitSensor();

	driveRGB(GREEN, ON);
	waitTime(1000);
	calcGyroZRef();

	initRun();
	driveMotor(ON);
	switchSensorLED(OFF);
}
/****************************************
 調整用関数1
 ****************************************/
void selectAdjustment1(uint8_t velo) {
	int16_t mode;
	float velocity;
	driveRGB(MAGENTA, ON);
	waitTime(500);
	g_flag_FF = 1;
	mode = selectMode(13);
	switch (velo) {
	case T10:
		velocity = 1.0;
		break;
	case T12:
		velocity = 1.2;
		break;
	case T14:
		velocity = 1.4;
		break;
	case T16:
		velocity = 1.6;
		break;
	case T18:
		velocity = 1.8;
		break;
	}
	switch (mode) {
	case 0:
		initAdjustment();
		runStraight(15, SECTION, velocity, velocity);

		turnShortest(tc_para[velo][mode]);
		switchSensorLED(OFF);
		runStraight(15, SECTION, velocity, 0);

		break;
	case 1:
		initAdjustment();
		runStraight(15, SECTION, velocity, velocity);

		turnShortest(tc_para[velo][mode]);
		switchSensorLED(OFF);
		runStraight(15, SECTION, velocity, 0);

		break;
	case 2:
		initAdjustment();
		runStraight(15, SECTION, velocity, velocity);

		turnShortest(tc_para[velo][mode]);
		switchSensorLED(OFF);
		runStraight(15, SECTION, velocity, 0);

		break;

	case 3:
		initAdjustment();
		runStraight(15, SECTION, velocity, velocity);

		turnShortest(tc_para[velo][mode]);
		switchSensorLED(OFF);
		runStraight(15, SECTION, velocity, 0);

		break;
	case 4:
		initAdjustment();
		runStraight(15, SECTION, velocity, velocity);
		turnShortest(tc_para[velo][mode]);
		switchSensorLED(OFF);
		runStraight(15, SECTION * M_SQRT2, velocity, 0);

		break;
	case 5:
		initAdjustment();
		runStraight(15, SECTION, velocity, velocity);
		turnShortest(tc_para[velo][mode]);
		switchSensorLED(OFF);
		runStraight(15, SECTION * M_SQRT2, velocity, 0);

		break;
	case 6:
		initAdjustment();
		runStraight(15, SECTION * M_SQRT2, velocity, velocity);
		turnShortest(tc_para[velo][mode]);
		switchSensorLED(OFF);
		runStraight(15, SECTION, velocity, 0);

		break;
	case 7:
		initAdjustment();
		runStraight(15, SECTION * M_SQRT2, velocity, velocity);
		turnShortest(tc_para[velo][mode]);
		switchSensorLED(OFF);
		runStraight(15, SECTION, velocity, 0);

		break;
	case 8:
		initAdjustment();
		runStraight(15, SECTION, velocity, velocity);
		turnShortest(tc_para[velo][mode]);
		switchSensorLED(OFF);
		runStraight(15, SECTION * M_SQRT2, velocity, 0);

		break;
	case 9:
		initAdjustment();
		runStraight(15, SECTION, velocity, velocity);
		turnShortest(tc_para[velo][mode]);
		switchSensorLED(OFF);
		runStraight(15, SECTION * M_SQRT2, velocity, 0);

		break;
	case 10:
		initAdjustment();
		runStraight(15, SECTION * M_SQRT2, velocity, velocity);
		turnShortest(tc_para[velo][mode]);
		switchSensorLED(OFF);
		runStraight(15, SECTION, velocity, 0);

		break;
	case 11:
		initAdjustment();
		runStraight(15, SECTION * M_SQRT2, velocity, velocity);
		turnShortest(tc_para[velo][mode]);
		switchSensorLED(OFF);
		runStraight(15, SECTION, velocity, 0);

		break;
	case 12:
		initAdjustment();
		runStraight(15, SECTION * M_SQRT2, velocity, velocity);
		turnShortest(tc_para[velo][mode]);
		switchSensorLED(OFF);
		runStraight(15, SECTION * M_SQRT2, velocity, 0);

		break;
	case 13:
		initAdjustment();
		runStraight(15, SECTION * M_SQRT2, velocity, velocity);
		turnShortest(tc_para[velo][mode]);
		switchSensorLED(OFF);
		runStraight(15, SECTION * M_SQRT2, velocity, 0);

		break;

	default:
		break;

	}
	driveMotor(OFF);
	driveSuction(70, OFF);
	waitButton();
	printLog4();
}
/****************************************
 調整用関数2
 ****************************************/
void selectAdjustment2(void) {
	uint8_t i;
	uint8_t mode;
	float velo = 0.7;
	g_flag_FF = 1;
	driveRGB(YELLOW, ON);
	waitTime(500);

	mode = selectMode(13);

	switch (mode) {

	case 0:
		initAdjustment2();
		switchSensorLED(ON);
		runStraight(5, SECTION * 4, velo, 0);
		break;
	case 1:
		initAdjustment2();
//		g_flag_diagonal = 1;
//		runStraight(5, SECTION * 4, velo, 0);
		g_flag_run_mode = SEARCH;
		switchSensorLED(ON);
		runStraightSearch(5,SECTION*2,velo);
		runStraight(5, HALF_SECTION, velo, 0);
		break;
	case 2:
		initAdjustment2();
		switchSensorLED(ON);
		runStraight(5, SECTION, velo, velo);
		//runStraightSearch(5, SECTION, 0.7);
		turnSearch(&tc_90_L_07);
		runStraight(5, SECTION, velo, 0);
		break;

	case 3:
		initAdjustment2();
		switchSensorLED(ON);
		runStraight(5, SECTION, velo, velo);
		//runStraightSearch(5, SECTION, 0.7);
		turnSearch(&tc_90_R_07);
		runStraight(5, SECTION, velo, 0);
		break;
	case 4:
		initAdjustment2();
		for (i = 0; i < 16; i++) {
			turnShortest(&tc_pivot_90_L);
			waitTime(200);
		}
		break;
	case 5:
		initAdjustment2();
		for (i = 0; i < 16; i++) {
			turnShortest(&tc_pivot_90_R);
			waitTime(200);
		}
		break;
	case 6:
		initAdjustment2();
		for (i = 0; i < 10; i++) {
			turnShortest(&tc_pivot);
			waitTime(200);
		}
		break;
	case 7:
		initAdjustment2();
		runStraight(5, SECTION, velo, velo);
		switchSensorLED(ON);
		runBlindAlley(velo);
		runStraight(5, SECTION, velo, 0);
		break;
	case 8:

		break;
	case 9:

		break;
	case 10:

		break;
	case 11:

		break;
	case 12:
		initAdjustment2();
		runStraight(5, HALF_SECTION, velo, velo);

		for (i = 0; i < 16; i++) {
			runStraight(5, SECTION, velo, velo);
			turnSearch(&tc_90_L_07);
		}
		runStraight(5, SECTION, velo, 0);
		break;
	case 13:
		initAdjustment2();
		runStraight(5, HALF_SECTION, velo, velo);

		for (i = 0; i < 16; i++) {
			runStraight(5, SECTION, velo, velo);
			turnSearch(&tc_90_R_07);
		}
		runStraight(5, SECTION, velo, 0);
		break;

	default:
		break;

	}
	waitTime(300);
	driveMotor(OFF);
	driveSuction(70, OFF);
	waitButton();
	printLog4();
}
