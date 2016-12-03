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
#include "map.h"
#include "sensor.h"

/****************************************
 サーキット関数
 ****************************************/

void runCircuit(uint8_t x, uint8_t y, uint8_t times, float velocity,
		float accelaration, float t_velo) {
	int i;
	g_flag_circuit = 1;
	waitSensor();
	waitTime(500);
	calcGyroZRef();
	driveMotor(ON);
	switchSensorLED(ON);
	initRun();
	driveSuction(70, ON);
	waitTime(1000);
	runStraight(accelaration, INIT_DIS + SECTION, velocity, t_velo);
	for (i = 0; i < times; i++) {
		runStraight(accelaration, SECTION * (y - 3), velocity, t_velo);
		turnCorner(&t_w90_R_10);
		runStraight(accelaration, SECTION * (x - 3), velocity, t_velo);
		turnCorner(&t_w90_R_10);
		runStraight(accelaration, SECTION * (y - 3), velocity, t_velo);
		turnCorner(&t_w90_R_10);
		runStraight(accelaration, SECTION * (x - 3), velocity, t_velo);
		turnCorner(&t_w90_R_10);
	}
	runStraight(accelaration, SECTION * 2, velocity, 0);
	driveSuction(70, OFF);
	waitTime(500);
	driveMotor(OFF);
	switchSensorLED(OFF);
	g_flag_circuit = 0;
}
/****************************************
 探索 足立
 ****************************************/
void runAdachi(void) {
	setCurrentCoord(START_X, START_Y);
	setTargetCoord(GOAL_X, GOAL_Y);
	setOrient(NORTH);
	countStepQueue();

	waitSensor();

	switchSensorLED(ON);
	driveMotor(ON);
	waitTime(1000);
	soundStartSearch();
	calcGyroZRef();
	initRun();

	searchAdachi();
}
/****************************************
 探索 足立足立
 ****************************************/
void runAdachiAdachi(void) {
	setCurrentCoord(START_X, START_Y);
	setTargetCoord(GOAL_X, GOAL_Y);
	setOrient(NORTH);

	countStepQueue();

	waitSensor();

	switchSensorLED(ON);
	driveMotor(ON);
	waitTime(1000);
	soundStartSearch();
	calcGyroZRef();
	initRun();

	searchAdachi();

	driveMotor(ON);
	switchSensorLED(ON);
	turnCorner(&pivot);
	checkOrient(180);

	setTargetCoord(START_X, START_Y);
	countStepQueue();

	switchSensorLED(ON);
	driveMotor(ON);
	initRun();

	searchAdachi();

}

/****************************************
 探索 古川
 ****************************************/
void runFurukawa(void) {
	setCurrentCoord(START_X, START_Y);
	setTargetCoord(GOAL_X, GOAL_Y);
	setOrient(NORTH);
	countStepQueue();

	waitSensor();

	switchSensorLED(ON);
	driveMotor(ON);
	waitTime(1000);
	soundStartSearch();
	calcGyroZRef();
	initRun();

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

	waitSensor();

	switchSensorLED(ON);
	driveMotor(ON);
	waitTime(1000);
	soundStartSearch();
	calcGyroZRef();
	initRun();

	searchFurukawa();

	driveMotor(ON);
	switchSensorLED(ON);
	turnCorner(&pivot);
	checkOrient(180);
	setTargetCoord(START_X, START_Y);

	countStepQueue();

	switchSensorLED(ON);
	driveMotor(ON);
	initRun();

	searchAdachi();
	turnCorner(&pivot);
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
		runAdachi();
		break;
	case 3:
		runAdachiAdachi();

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
	switch (selectMode(6)) {
	case 0:
		setTargetCoord(GOAL_X, GOAL_Y);

		countStepShortest();
		setCurrentCoord(START_X, START_Y);

		setOrient(NORTH);
		makePath();
		makePath3();

		waitSensor();

		waitTime(1000);
		calcGyroZRef();
		soundStartRun();
		driveSuction(100, ON);
		waitTime(1000);
		initRun();
		driveMotor(ON);
		switchSensorLED(ON);
		runPathDiagonal(T14,2, 10, 2, 10);
		switchSensorLED(OFF);
		driveMotor(OFF);
		driveSuction(100, OFF);
		break;
	case 1:
		setTargetCoord(GOAL_X, GOAL_Y);

		countStepShortest();
		setCurrentCoord(START_X, START_Y);

		setOrient(NORTH);
		makePath();
		makePath3();

		waitSensor();

		waitTime(1000);
		calcGyroZRef();
		soundStartRun();
		driveSuction(100, ON);
		waitTime(1000);
		initRun();
		driveMotor(ON);
		switchSensorLED(ON);
		runPathDiagonal(T14,3, 15, 3, 10);
		switchSensorLED(OFF);
		driveMotor(OFF);
		driveSuction(100, OFF);
		break;
	case 2:
		setTargetCoord(GOAL_X, GOAL_Y);

		countStepShortest();
		setCurrentCoord(START_X, START_Y);

		setOrient(NORTH);
		makePath();
		makePath3();

		waitSensor();

		waitTime(1000);
		calcGyroZRef();
		soundStartRun();
		driveSuction(100, ON);
		waitTime(1000);
		initRun();
		driveMotor(ON);
		switchSensorLED(ON);
		runPathDiagonal(T14,4, 15, 3, 15);
		switchSensorLED(OFF);
		driveMotor(OFF);
		driveSuction(100, OFF);
		break;
	case 3:
		setTargetCoord(GOAL_X, GOAL_Y);

		countStepShortest();
		setCurrentCoord(START_X, START_Y);

		setOrient(NORTH);
		makePath();
		makePath3();

		waitSensor();

		waitTime(1000);
		calcGyroZRef();
		soundStartRun();
		driveSuction(100, ON);
		waitTime(1000);
		initRun();
		driveMotor(ON);
		switchSensorLED(ON);
		runPathDiagonal(T14,4, 20, 3, 20);
		switchSensorLED(OFF);
		driveMotor(OFF);
		driveSuction(100, OFF);
		break;
	case 4:
		setTargetCoord(GOAL_X, GOAL_Y);

		countStepShortest();
		setCurrentCoord(START_X, START_Y);

		setOrient(NORTH);
		makePath();
		makePath3();

		waitSensor();

		waitTime(1000);
		calcGyroZRef();
		soundStartRun();
		driveSuction(100, ON);
		waitTime(1000);
		initRun();
		driveMotor(ON);
		switchSensorLED(ON);
		runPathDiagonal(T14,4, 20, 4, 20);
		switchSensorLED(OFF);
		driveMotor(OFF);
		driveSuction(100, OFF);
		break;
	case 5:
		setTargetCoord(GOAL_X, GOAL_Y);

		countStepShortest();
		setCurrentCoord(START_X, START_Y);

		setOrient(NORTH);
		makePath();
		makePath3();

		waitSensor();

		waitTime(1000);
		calcGyroZRef();
		soundStartRun();
		driveSuction(100, ON);
		waitTime(1000);
		initRun();
		driveMotor(ON);
		switchSensorLED(ON);
		runPathDiagonal(T14,4, 30, 4, 20);
		switchSensorLED(OFF);
		driveMotor(OFF);
		driveSuction(100, OFF);
		break;
	case 6:

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
			//runCircuit(16, 16, 2, 4, 20, 1);
			setTargetCoord(GOAL_X, GOAL_Y);

			countStepShortest();
			setCurrentCoord(START_X, START_Y);

			setOrient(NORTH);
			makePath();
			makePath3();

			printMap();
			printSearch();
			printPath3();
			break;
		case 4:
			//runCircuit(16, 16, 2, 4.5, 25, 1);
			waitButton();
			printLog();
			break;
		default:
			break;

		}
	}
}
