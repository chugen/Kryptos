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
 割り込み関数CMT0
 ****************************************/
void intrptCMT0(void) {
	static uint8_t log_count = 0;
	log_count++;
	g_wait_count++;
	g_buzzer_count++;

	calcAcc();
	calcDistance();
	calcAngularAcc();
	calcAngle();

	getModeVelocity();

	g_current_omega_tmp = returnGyroZVal();
	g_current_velo = returnVelocityL() + returnVelocityR();
	g_current_omega = g_current_omega_tmp - g_gyro_reference;

	if (log_count % 1 == 0) {
		/*Log=====================================================*/
		//getLog(g_sensor_L, g_sensor_R);
		//getLog(g_sensor_FL,g_sensor_FR);
		//getLog(g_sensor_L,g_flag_pillar_edge_L);
		//getLog(g_sensor_R,g_flag_pillar_edge_R);
		//getLog(g_target_velo, g_current_velo);
		//getLog(g_current_velo, g_accele);
		//getLog(g_target_omega, g_current_omega);
		//getLog(fabsf(g_encoder_diff_L) * INTRPT_FREQENCY / (ENC_RESO * 4) * 60,fabsf(g_encoder_diff_R) * INTRPT_FREQENCY / (ENC_RESO * 4) * 60);
		//getLog(ctrlFeedForwardL(g_accele,g_target_alpha),ctrlFeedForwardR(g_accele,g_target_alpha));
		//getLog(g_target_angle, g_current_angle);
		//getLog(g_duty_L, g_duty_R);
		//getLogInt(commSPI(GYRO_ZOUT_H, 0x0f, READ),commSPI(GYRO_ZOUT_L, 0x0f, READ));
		//getLog(g_sensor_R, g_target_omega);
//		getLog4(g_target_velo, g_current_velo, g_target_omega, g_current_omega);
		getLog4(g_battery_voltage, g_current_velo, g_target_omega, g_current_omega);
		//getLog4(g_target_velo, g_current_velo, g_distance,g_accele );
		//getLog4(g_sensor_L, g_sensor_R, g_flag_pillar_edge_L, g_flag_pillar_edge_R);
		//getLog4(g_torque_L,g_torque_R,g_target_omega,g_current_omega);
		//getLog4(g_sensor_FL, g_sensor_FR, g_sensor_FL_average,
		//		g_sensor_FR_average);
		//getLog4(g_current_x, g_current_y, (getWallData(WALL_RIGHT) == 0),	checkStep(WALL_RIGHT));
		/*========================================================*/
		log_count = 0;
	}

	getBatteryVoltage();
	setMotorDuty();
	checkFailsafe(2, 1500, 2600);

}
/****************************************
 割り込み関数CMT1
 ****************************************/
void intrptCMT1(void) {
	getSensorVal();
	checkPillarEdgeL();
	checkPillarEdgeR();

	if (g_flag_run_mode == SEARCH && g_flag_turn != 1) {
		if (g_flag_pillar_edge_L == 1 && g_flag_pillar_edge_R == 1 && g_target_velo >= 0.7) {
			driveRGB(GREEN, ON);
			driveBuzzerIntrpt(BOTH, ON);
		} else if (g_flag_pillar_edge_R == 1 && g_target_velo >= 0.7) {
			driveRGB(RED, ON);
			driveBuzzerIntrpt(RIGHT, ON);

		} else if (g_flag_pillar_edge_L == 1 && g_target_velo >= 0.7) {
			driveRGB(BLUE, ON);
			driveBuzzerIntrpt(LEFT, ON);

		} else {
			driveRGB(BLUE, OFF);
			driveBuzzerIntrpt(0, OFF);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/****************************************
 ログ取得関数 割り込み
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

void getLog4(float log1, float log2, float log3, float log4) {

	if (g_log_count < LOG_TIMES) {
		g_log_array[g_log_count] = log1;
		g_log_array2[g_log_count] = log2;
		g_log_array3[g_log_count] = log3;
		g_log_array4[g_log_count] = log4;
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
 モード用速度取得関数 割り込み
 ****************************************/
void getModeVelocity(void) {
	if (g_flag_mode_setting == 1) {
		g_mode_velo = returnVelocityR();
	}
}
/****************************************
 Dutyセット関数 割り込み
 ****************************************/
void setMotorDuty(void) {
	if (g_flag_control == 1) {
		setMotorDutyL(ctrlPropVelocity(VELO_P) + ctrlIntVelocity(VELO_I) - ctrlPropOmega(changeOmegaCtrlConst(ANG_VELO_P)) - ctrlIntOmega(changeOmegaCtrlConst(ANG_VELO_I)) - ctrlDeriOmega(changeOmegaCtrlConst(ANG_VELO_D)) - ctrlPropAngle(ANG_P) - ctrlIntAngle(ANG_I) - ctrlWall(WALL_P) - ctrlWallFrontAng(WALL_FRONT_ANG) + ctrlWallFrontDis(WALL_FRONT_DIS) + ctrlFeedForwardL(g_accele, g_target_alpha));

		setMotorDutyR(ctrlPropVelocity(VELO_P) + ctrlIntVelocity(VELO_I) + ctrlPropOmega(changeOmegaCtrlConst(ANG_VELO_P)) + ctrlIntOmega(changeOmegaCtrlConst(ANG_VELO_I)) + ctrlDeriOmega(changeOmegaCtrlConst(ANG_VELO_D)) + ctrlPropAngle(ANG_P) + ctrlIntAngle(ANG_I) + ctrlWall(WALL_P) + ctrlWallFrontAng(WALL_FRONT_ANG) + ctrlWallFrontDis(WALL_FRONT_DIS) + ctrlFeedForwardR(g_accele, g_target_alpha));
	}
}
/****************************************
 加速 割り込み
 ****************************************/
void calcAcc(void) {
	g_target_velo += g_accele * INTRPT_PERIOD;
}
/****************************************
 距離加算 割り込み
 ****************************************/
void calcDistance(void) {
	g_distance += g_target_velo * INTRPT_PERIOD;
}
/****************************************
 角加速 割り込み
 ****************************************/
void calcAngularAcc(void) {
	if (g_flag_turn_continuous == 1) {
		g_count_time_angle++;
		if (1 - powf((g_count_time_angle * INTRPT_PERIOD - g_turn_peaktime) / g_turn_peaktime, 2) > 0) {
			g_target_alpha = -2 * g_alpha_max * (g_count_time_angle * INTRPT_PERIOD - g_turn_peaktime) / g_turn_peaktime * sqrtf(1 - powf((g_count_time_angle * INTRPT_PERIOD - g_turn_peaktime) / g_turn_peaktime, 2));
		} else {
			g_target_alpha = 0;
		}
		g_target_omega += g_target_alpha * INTRPT_PERIOD;
	} else {
		g_target_omega += g_target_alpha * INTRPT_PERIOD;
	}

}
/****************************************
 角度加算 割り込み
 ****************************************/
void calcAngle(void) {
	g_target_angle += g_target_omega * INTRPT_PERIOD;

	g_current_angle += g_current_omega * INTRPT_PERIOD;
}

/****************************************
 バッテリー電圧取得
 ****************************************/
float getBatteryVoltage(void) {
	float battery, tmp;
	S12AD.ADCSR.BIT.ADST = 0x00; 	//AD変換停止
	S12AD.ADANS0.WORD = 0x40;
	S12AD.ADCSR.BIT.ADST = 0x01; 	//AD変換スタート
	while (S12AD.ADCSR.BIT.ADST == 1)
		;
	tmp = S12AD.ADDR6;
	battery = (float) (tmp / 4096.0 * 3.3 * 3.0) + 0.06;

	g_battery_voltage = battery;

	return battery;
}
/****************************************
 センサー値取得 割り込み
 ****************************************/
void getSensorVal(void) {
	int32_t i, wait_clock = 500;
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
	static float sensor_FL_before[10] = { 0 };
	static float sensor_FR_before[10] = { 0 };

	//battery_correct = MAX_VOLTAGE / g_battery_voltage;
	battery_correct = 1;

	sensor_L_before = g_sensor_L;
	sensor_R_before = g_sensor_R;
	driveSensorLED(FR_L);
	for (i = 0; i < wait_clock; i++) {
	}

	sensor_L_on = returnSenVal(SEN_L);
	sensor_FR_on = returnSenVal(SEN_FR);
	driveSensorLED(OFF);
	for (i = 0; i < wait_clock; i++) {
	}
	sensor_FR_off = returnSenVal(SEN_FR);
	sensor_FL_off = returnSenVal(SEN_FL);
	sensor_R_off = returnSenVal(SEN_R);
	sensor_L_off = returnSenVal(SEN_L);

	driveSensorLED(FL_R);
	for (i = 0; i < wait_clock; i++) {
	}
	sensor_FL_on = returnSenVal(SEN_FL);
	sensor_R_on = returnSenVal(SEN_R);
	driveSensorLED(OFF);
	g_sensor_FL = (sensor_FL_on - sensor_FL_off) * battery_correct;
	//g_sensor_FR = (sensor_FR_on - sensor_FR_off) * battery_correct;
	g_sensor_FR = (int32_t) (2.55 * (sensor_FR_on - sensor_FR_off) * battery_correct);
	g_sensor_L = (sensor_L_on - sensor_L_off) * battery_correct;
	g_sensor_R = (sensor_R_on - sensor_R_off) * battery_correct;

	g_sensor_L_derivative = g_sensor_L - sensor_L_before;
	g_sensor_R_derivative = g_sensor_R - sensor_R_before;

	g_sensor_FL_average = (sensor_FL_before[0] + sensor_FL_before[1] + sensor_FL_before[2] + sensor_FL_before[3] + sensor_FL_before[4] + sensor_FL_before[5] + sensor_FL_before[6] + sensor_FL_before[7] + sensor_FL_before[8] + sensor_FL_before[9]) / 10.0;
	g_sensor_FR_average = (sensor_FR_before[0] + sensor_FR_before[1] + sensor_FR_before[2] + sensor_FR_before[3] + sensor_FR_before[4] + sensor_FR_before[5] + sensor_FR_before[6] + sensor_FR_before[7] + sensor_FR_before[8] + sensor_FR_before[9]) / 10.0;
	for (i = 8; i >= 0; i--) {
		sensor_FL_before[i + 1] = sensor_FL_before[i];
		sensor_FR_before[i + 1] = sensor_FR_before[i];
	}
	sensor_FL_before[0] = g_sensor_FL;
	sensor_FR_before[0] = g_sensor_FR;

}

/****************************************
 壁切れ判定
 ****************************************/
uint8_t checkPillarEdgeL() {
	int16_t i, diff;
	static float sensor_L_before[8] = { 0 };

	static float sensor_L_pillar = 0;

	for (i = 6; i >= 0; i--) {
		sensor_L_before[i + 1] = sensor_L_before[i];
	}
	sensor_L_before[0] = g_sensor_L;

	sensor_L_pillar = ((sensor_L_before[0] + sensor_L_before[1] + sensor_L_before[2]) - (sensor_L_before[5] + sensor_L_before[6] + sensor_L_before[7])) / 3;
	if (g_flag_run_mode == RUN) {
		diff = SEN_PILLAR_EDGE_L;
	} else {
		diff = SEN_PILLAR_EDGE_SEARCH_L;
	}

	if (sensor_L_pillar < diff) {
		g_flag_pillar_edge_L = 1;
	} else {
		g_flag_pillar_edge_L = 0;
	}

	return 0;
}
uint8_t checkPillarEdgeR() {
	int16_t i, diff;
	static float sensor_R_before[8] = { 0 };

	static float sensor_R_pillar = 0;

	for (i = 6; i >= 0; i--) {
		sensor_R_before[i + 1] = sensor_R_before[i];
	}
	sensor_R_before[0] = g_sensor_R;

	sensor_R_pillar = ((sensor_R_before[0] + sensor_R_before[1] + sensor_R_before[2]) - (sensor_R_before[5] + sensor_R_before[6] + sensor_R_before[7])) / 3;
	if (g_flag_run_mode == RUN) {
		diff = SEN_PILLAR_EDGE_R;
	} else {
		diff = SEN_PILLAR_EDGE_SEARCH_R;
	}
	if (sensor_R_pillar < diff) {
		g_flag_pillar_edge_R = 1;
	} else {
		g_flag_pillar_edge_R = 0;
	}

	return 0;
}
/****************************************
 フェイルセーフ 割り込み
 ****************************************/
void checkFailsafe(float velo, float angularvelo, float sensor) {
	if (fabsf(g_target_velo-g_current_velo) > velo || (fabsf(g_target_omega-g_current_omega) > angularvelo) || ((g_sensor_FL + g_sensor_FR >= sensor) && (g_flag_run_mode == RUN))) {
		g_flag_failsafe = 1;
		g_target_velo = 0;
		driveSuction(70, OFF);
		PORTC.PODR.BIT.B6 = 0; //STBY
		driveRGB(RED, ON);
	}
}
