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
	calcAcc();
	calcDistance();
	calcAngularAcc();
	calcAngle();

	getModeVelocity();

	g_current_velo = returnVelocityL() + returnVelocityR();
	g_current_angularvelo = returnGyroZVal() - g_gyro_reference;

	/*Log=====================================================*/
	//getLog(g_sensor_L, g_sensor_R);
	//getLog(g_sensor_FL,g_sensor_FR);
	//getLog(g_sensor_L,g_flag_pillar_edge_L);

	//getLog(g_target_velo, g_current_velo);
	//getLog(g_target_angularvelo, g_current_angularvelo);
	getLog(g_target_angle, g_current_angle);

	//getLog(g_duty_L, g_duty_R);
	/*========================================================*/


	setMotorDuty();

	checkFailsafe(2, 1500, 2600);

}
/****************************************
 割り込み関数1
 ****************************************/
void intrptCMT1(void) {
	getSensorVal();
	checkPillarEdgeL();
	checkPillarEdgeR();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/****************************************
 ログ取得関数　割り込み
 ****************************************/
void getLog(float log1, float log2) {

	if (g_log_count < LOG_TIMES) {
		g_log_array[g_log_count] = log1;
		g_log_array2[g_log_count] = log2;
		g_log_count++;
	} else {
		g_log_count = LOG_TIMES;
	}
}
void getLogInt(int16_t log1, int16_t log2) {

	if (g_log_count < LOG_TIMES) {
		g_log_array_int[g_log_count] = log1;
		g_log_array2_int[g_log_count] = log2;
		g_log_count++;
	} else {
		g_log_count = LOG_TIMES;
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
	if (g_flag_control == 1) {
		setMotorDutyL(
				ctrlPropVelocity(VELO_P) + ctrlIntVelocity(VELO_I)
						- ctrlPropAngularVelocity(ANG_VELO_P)
						- ctrlIntAngularVelocity(ANG_VELO_I)
						- ctrlPropAngle(ANG_P) - ctrlIntAngle(ANG_I)
						- ctrlWall(WALL_P) - ctrlWallFrontAng(WALL_FRONT_ANG)
						+ ctrlWallFrontDis(WALL_FRONT_DIS));
		setMotorDutyR(
				ctrlPropVelocity(VELO_P) + ctrlIntVelocity(VELO_I)
						+ ctrlPropAngularVelocity(ANG_VELO_P)
						+ ctrlIntAngularVelocity(ANG_VELO_I)
						+ ctrlPropAngle(ANG_P) + ctrlIntAngle(ANG_I)
						+ ctrlWall(WALL_P) + ctrlWallFrontAng(WALL_FRONT_ANG)
						+ ctrlWallFrontDis(WALL_FRONT_DIS));
	}
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
	g_target_angle += g_target_angularvelo * 0.001;
	g_current_angle += g_current_angularvelo * 0.001;
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
	float battery_correct;
	static uint16_t sensor_L_before;
	static uint16_t sensor_R_before;

	battery_correct = correctVoltage();

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
	g_sensor_FL = (sensor_FL_on - sensor_FL_off) * battery_correct;
	g_sensor_FR = (sensor_FR_on - sensor_FR_off) * battery_correct;
	g_sensor_L = (sensor_L_on - sensor_L_off) * battery_correct;
	g_sensor_R = (sensor_R_on - sensor_R_off) * battery_correct;

	g_sensor_L_derivative = g_sensor_L - sensor_L_before;
	g_sensor_R_derivative = g_sensor_R - sensor_R_before;
}

/****************************************
 壁切れ判定
 ****************************************/
uint8_t checkPillarEdgeL() {
	int16_t i;
	static float sensor_L_before[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

	static float sensor_L_pillar = 0;

	for (i = 6; i >= 0; i--) {
		sensor_L_before[i + 1] = sensor_L_before[i];
	}
	sensor_L_before[0] = g_sensor_L;

	sensor_L_pillar = ((sensor_L_before[0] + sensor_L_before[1] + sensor_L_before[2])
					- (sensor_L_before[5] + sensor_L_before[6] + sensor_L_before[7]))/3;

	if (sensor_L_pillar < -100) {
		g_flag_pillar_edge_L = 1;
	} else {
		g_flag_pillar_edge_L = 0;
	}

	return 0;
}
uint8_t checkPillarEdgeR() {
	int16_t i;
		static float sensor_R_before[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

		static float sensor_R_pillar = 0;

		for (i = 6; i >= 0; i--) {
			sensor_R_before[i + 1] = sensor_R_before[i];
		}
		sensor_R_before[0] = g_sensor_R;

		sensor_R_pillar = ((sensor_R_before[0] + sensor_R_before[1] + sensor_R_before[2])
						- (sensor_R_before[5] + sensor_R_before[6] + sensor_R_before[7]))/3;

		if (sensor_R_pillar < -100) {
			g_flag_pillar_edge_R = 1;
		} else {
			g_flag_pillar_edge_R = 0;
		}

		return 0;
}
/****************************************
 フェイルセーフ　割り込み
 ****************************************/
void checkFailsafe(float velo, float angularvelo, float sensor) {
	if (fabsf(g_target_velo-g_current_velo) > velo
			|| (fabsf(g_target_angularvelo-g_current_angularvelo) > angularvelo)
			|| ((g_sensor_FL + g_sensor_FR >= sensor)
					&& (g_flag_run_mode == RUN))) {
		g_flag_failsafe = 1;
		g_target_velo = 0;
		driveSuction(70, OFF);
		PORTC.PODR.BIT.B6 = 0; //STBY
		driveRGB(RED, ON);
	}
}
