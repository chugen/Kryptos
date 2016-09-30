/*
 * intrpt.cpp
 *
 *  Created on: 2016/05/24
 *      Author: 元太
 */
#include <stdint.h>
#include "iodefine.h"
#include "intrpt.h"
#include "common.h"
#include "run.h"
#include "grobal.h"
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

	getLog(g_target_velo, g_current_velo);

	if (g_test_flag == 1) {
		setMotorDuty();
	}
}
/****************************************
 割り込み関数1
 ****************************************/
void intrptCMT1(void) {

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
					- ctrlIntAngularVelocity(ANG_VELO_I));
	setMotorDutyR(
			ctrlPropVelocity(VELO_P) + ctrlIntVelocity(VELO_I)
					+ ctrlPropAngularVelocity(ANG_VELO_P)
					+ ctrlIntAngularVelocity(ANG_VELO_I));
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
	g_distance += g_current_velo * 0.001;
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
	g_angle+= g_target_angularvelo * 0.001;
}
