/*
 * intrpt.cpp
 *
 *  Created on: 2016/05/24
 *      Author: 元太
 */
#include <stdint.h>
#include <mathf.h>
#include "iodefine.h"
#include "intrpt.h"
#include "common.h"
#include "run.h"
#include "global.h"
#include "parameter.h"
#include "sensor.h"
#include "app.h"

/****************************************
 割り込み関数0
 ****************************************/
void intrptCMT0(void) {
	g_wait_count++;
	g_log_count++;
	calcAcc();
	calcDistance();
	calcAngularAcc();
	calcAngle();
	getModeVelocity();

	g_current_velo = returnVelocityL() + returnVelocityR();
	g_current_angularvelo = returnGyroZVal() - g_gyro_reference;

	getLog(g_target_angularvelo, g_current_angularvelo);

	if (g_test_flag == 1) {
		setMotorDuty();
	}

	if (fabsf(g_target_velo-g_current_velo) > 200
			|| (fabsf(g_target_angularvelo-g_current_angularvelo) > 1000)) {

		driveMotor(OFF);
	}

}
/****************************************
 割り込み関数1
 ****************************************/
void intrptCMT1(void) {
	getSensorVal();
}
/****************************************
 割り込み関数2
 ****************************************/
void intrptCMT2(void) {
	//getSensorVal();

}
///////////////////////////////////////////////////////////////////////////////////////////////////
/****************************************
 ログ取得関数　割り込み
 ****************************************/
void getLog(float log1, float log2) {
	if (g_log_count < LOG_TIMES) {
		g_log_array[g_log_count] = log1;
		g_log_array2[g_log_count] = log2;
	}
}
/****************************************
 モード用速度取得関数　割り込み
 ****************************************/
void getModeVelocity(void) {
	if (g_flag_mode_setting == 1) {
		g_mode_velo = returnVelocityR();
	}
}
/****************************************
 Dutyセット関数　割り込み
 ****************************************/
void setMotorDuty(void) {
	setMotorDutyL(
			ctrlPropVelocity(VELO_P) + ctrlIntVelocity(VELO_I)
					- ctrlPropAngularVelocity(ANG_VELO_P)
					- ctrlIntAngularVelocity(ANG_VELO_I) - ctrlWall(WALL_P));
	setMotorDutyR(
			ctrlPropVelocity(VELO_P) + ctrlIntVelocity(VELO_I)
					+ ctrlPropAngularVelocity(ANG_VELO_P)
					+ ctrlIntAngularVelocity(ANG_VELO_I) + ctrlWall(WALL_P));
}
/****************************************
 加速　割り込み
 ****************************************/
void calcAcc(void) {
	g_target_velo += g_accele * 0.001;
}
/****************************************
 距離加算　割り込み
 ****************************************/
void calcDistance(void) {
	g_distance += g_target_velo * 0.001;
}
/****************************************
 角加速　割り込み
 ****************************************/
void calcAngularAcc(void) {
	g_target_angularvelo += g_angularaccele * 0.001;
}
/****************************************
 角度加算　割り込み
 ****************************************/
void calcAngle(void) {
	g_angle += g_target_angularvelo * 0.001;
}

/****************************************
 センサー値取得　割り込み
 ****************************************/
void getSensorVal(void) {
	int32_t i;
	uint16_t sensor_FL_on;
	uint16_t sensor_FR_on;
	uint16_t sensor_L_on;
	uint16_t sensor_R_on;
	uint16_t sensor_FL_off;
	uint16_t sensor_FR_off;
	uint16_t sensor_L_off;
	uint16_t sensor_R_off;
	static uint16_t sensor_L_before;
	static uint16_t sensor_R_before;

	sensor_L_before = g_sensor_L;
	sensor_R_before = g_sensor_R;
	driveSensorLED(FR_L);
	for (i = 0; i < 1000; i++) {
	}

	sensor_L_on = returnSenVal(SEN_L);
	sensor_FR_on = returnSenVal(SEN_FR);
	driveSensorLED(OFF);
	for (i = 0; i < 1000; i++) {
	}
	sensor_FR_off = returnSenVal(SEN_FR);
	sensor_FL_off = returnSenVal(SEN_FL);
	sensor_R_off = returnSenVal(SEN_R);
	sensor_L_off = returnSenVal(SEN_L);

	driveSensorLED(FL_R);
	for (i = 0; i < 1000; i++) {
	}
	sensor_FL_on = returnSenVal(SEN_FL);
	sensor_R_on = returnSenVal(SEN_R);
	driveSensorLED(OFF);
	g_sensor_FL = sensor_FL_on - sensor_FL_off;
	g_sensor_FR = sensor_FR_on - sensor_FR_off;
	g_sensor_L = sensor_L_on - sensor_L_off;
	g_sensor_R = sensor_R_on - sensor_R_off;

	g_sensor_L_derivative = g_sensor_L - sensor_L_before;
	g_sensor_R_derivative = g_sensor_R - sensor_R_before;
}

