/*
 * contest.c
 *
 *  Created on: 2016/10/17
 *      Author: Gen
 */
#include <stdint.h>
#include "common.h"
#include "parameter.h"
#include "global.h"
#include "run.h"
#include "serial.h"
#include "app.h"

/****************************************
 サーキット関数
 ****************************************/
void runCircuit(uint8_t x, uint8_t y, uint8_t times, float velocity,
		float accelaration, float turn_velo) {
	int i;
	driveMotor(ON);
	switchSensorLED(ON);
	driveSuction(70, ON);
	waitTime(1000);
	runStraight(accelaration, INIT_DIS + HALF_SECTION, velocity, turn_velo);
	for (i = 0; i < times; i++) {
		runStraight(accelaration, SECTION * (y - 3), velocity, turn_velo);
		turnCorner(turn_90_wide_R_1000);
		runStraight(accelaration, SECTION * (x - 3), velocity, turn_velo);
		turnCorner(turn_90_wide_R_1000);
		runStraight(accelaration, SECTION * (y - 3), velocity, turn_velo);
		turnCorner(turn_90_wide_R_1000);
		runStraight(accelaration, SECTION * (x - 3), velocity, turn_velo);
		turnCorner(turn_90_wide_R_1000);
	}
	runStraight(accelaration, SECTION * 2, velocity, 0);
	waitTime(500);
	driveMotor(OFF);
	switchSensorLED(OFF);
}
/****************************************
 探索 1
 ****************************************/
void search1(void) {
	setCurrentCoord(START_X, START_Y);
	setTargetCoord(GOAL_X, GOAL_Y);
	setOrient(NORTH);

	switchSensorLED(ON);
	soundStart();
	searchAdachi();
}
/****************************************
 探索 2
 ****************************************/
void search2(void) {
	setCurrentCoord(START_X, START_Y);
	setTargetCoord(GOAL_X, GOAL_Y);
	setOrient(NORTH);

	countStepQueue();
	switchSensorLED(ON);
	soundStart();
	searchAdachi();
	driveMotor(ON);
	switchSensorLED(ON);
	checkOrient(180);
	setTargetCoord(START_X, START_Y);
	countStepQueue();
	searchAdachi();

}
/****************************************
 探索 3
 ****************************************/
void search3(void) {
	setCurrentCoord(START_X, START_Y);
	setTargetCoord(GOAL_X, GOAL_Y);
	setOrient(NORTH);

	countStepQueue();

	switchSensorLED(ON);
	soundStart();
	searchAdachi();
	//
	driveMotor(ON);
	switchSensorLED(ON);

	checkOrient(180);
	setTargetCoord(START_X, START_Y + 1);

	countStepQueue();
	searchAdachi();
	//
	driveMotor(ON);
	switchSensorLED(ON);

	checkOrient(180);
	setTargetCoord(GOAL_X, GOAL_Y);

	countStepQueue();
	searchAdachi();

}
/****************************************
 探索 古川
 ****************************************/
void runFurukawa(void) {
	setCurrentCoord(START_X, START_Y);
	setTargetCoord(GOAL_X, GOAL_Y);
	setOrient(NORTH);

	switchSensorLED(ON);
	soundStart();
	searchFurukawa();

}
/****************************************
 探索 古川足立
 ****************************************/
void runFurukawaAdachi(void) {
	setCurrentCoord(START_X, START_Y);
	setTargetCoord(GOAL_X, GOAL_Y);
	setOrient(NORTH);

	countStepQueue();
	switchSensorLED(ON);
	soundStart();
	searchFurukawa();
	driveMotor(ON);
	switchSensorLED(ON);
	turnCorner(pivot);
	checkOrient(180);
	setTargetCoord(START_X, START_Y);

	countStepQueue();
	searchAdachi();
	turnCorner(pivot);
	driveMotor(OFF);
	waitTime(500);

}
/****************************************
 探索選択
 ****************************************/
void selectSearch(void) {
	waitTime(500);
	switch (selectMode(4)) {
	case 0:
		runFurukawaAdachi();
		break;
	case 1:
		runFurukawa();
		break;
	case 2:
		search1();
		break;
	case 3:
		search2();

		break;

	default:
		break;
	}
}

/****************************************
 走行選択
 ****************************************/
void selectRun(void) {
	waitTime(500);
	switch (selectMode(5)) {
	case 0:
		setTargetCoord(GOAL_X, GOAL_Y);

		countStepShortest();
		setCurrentCoord(START_X, START_Y);

		setOrient(NORTH);
		makePath();
		makePath2();

		switchSensorLED(ON);
		soundStart();
		setCurrentCoord(START_X, START_Y);

		runPath();

		switchSensorLED(OFF);
		break;
	case 1:
		setTargetCoord(GOAL_X, GOAL_Y);

		countStepShortest();
		setCurrentCoord(START_X, START_Y);

		setOrient(NORTH);
		makePath();
		makePath2();

		switchSensorLED(ON);
		soundStart();
		setCurrentCoord(START_X, START_Y);

		runPath();

		switchSensorLED(OFF);
		break;
	case 2:
		setTargetCoord(GOAL_X, GOAL_Y);

		countStepShortest();
		setCurrentCoord(START_X, START_Y);

		setOrient(NORTH);
		makePath();
		makePath2();

		switchSensorLED(ON);
		soundStart();
		setCurrentCoord(START_X, START_Y);

		runPath();

		switchSensorLED(OFF);
		break;
	case 3:
		setTargetCoord(GOAL_X, GOAL_Y);

		countStepShortest();
		setCurrentCoord(START_X, START_Y);

		setOrient(NORTH);
		makePath();
		makePath2();

		switchSensorLED(ON);
		soundStart();
		setCurrentCoord(START_X, START_Y);

		runPath();

		switchSensorLED(OFF);
		break;
	case 4:
		setTargetCoord(GOAL_X, GOAL_Y);

		countStepShortest();
		setCurrentCoord(START_X, START_Y);

		setOrient(NORTH);
		makePath();
		makePath3();

		switchSensorLED(ON);
		soundStart();
		setCurrentCoord(START_X, START_Y);

		runPathDiagonal();

		switchSensorLED(OFF);
		break;
	case 5:

		break;
	default:
		break;
	}
}

/****************************************
 大会用関数
 ****************************************/
void selectContest(void) {
	while (1) {
		driveRGB(CYAN, ON);
		waitTime(500);
		switch (selectMode(4)) {

		case 0:
			driveRGB(GREEN, ON);
			selectSearch();
			break;
		case 1:
			driveRGB(BLUE, ON);
			selectRun();
			break;
		case 2:
			waitButton();
			countStepShortest();
			waitTime(200);
			printMap();
			makePath();
			makePath2();
			makePath3();
			printPath2();
			printPath3();
			printPathTest();
			printPathTestDiagonal();
			break;

		case 3:

			break;
		case 4:

			break;
		default:
			break;

		}
	}
}
