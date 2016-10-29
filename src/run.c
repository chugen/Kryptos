/*
 * run.c
 *
 *  Created on: 2016/09/19
 *      Author: Gen
 */
#include <stdint.h>
#include <mathf.h>
#include "app.h"
#include "run.h"
#include "iodefine.h"
#include "init.h"
#include "intrpt.h"
#include "global.h"
#include "parameter.h"
#include "common.h"
#include "sensor.h"
#include "my_typedef.h"
/****************************************
 吸引
 ****************************************/
int8_t driveSuction(int16_t duty, int8_t on_off) {
	if (on_off == 0) {

		TPU5.TGRA = 0;
		TPU5.TGRB = 100;

		TPU5.TIOR.BIT.IOA = 0x00;	//出力禁止
		TPUA.TSTR.BIT.CST5 = 0;
	} else {
		TPU5.TIOR.BIT.IOA = 0x02;	//初期出力：H,コンペアマッチ：L
		TPU5.TGRA = 100 - duty;
		TPU5.TGRB = 100;
		TPUA.TSTR.BIT.CST5 = 1;
	}

	return 0;
}
/****************************************
 モータ駆動
 ****************************************/
int8_t driveMotor(int8_t on_off) {

	if (on_off == 1) {
		PORTC.PODR.BIT.B6 = 1; //STBY
		MTU.TSTR.BIT.CST0 = 1;
	} else {
		g_target_velo = 0;
		waitTime(500);
		PORTC.PODR.BIT.B6 = 0; //STBY
	}

	return 0;
}

/****************************************
 モータ デューティーセット
 ****************************************/
int16_t setMotorDutyL(float duty) {
	float voltage_temp;
	if (duty < 0) {
		setMotorDirL(BACKWARD);
		duty *= -1;
	} else {
		setMotorDirL(FORWARD);
	}
	if (duty >= 99) {
		duty = 99;
	}
	voltage_temp=correctVoltage();
	MTU0.TGRC = (int16_t) (250 * duty / 100 * voltage_temp);	//MOTOR_L
	return (int16_t) (250 * duty / 100 * voltage_temp);
}
int16_t setMotorDutyR(float duty) {
	float voltage_temp;
	if (duty < 0) {
		setMotorDirR(BACKWARD);
		duty *= -1;
	} else {
		setMotorDirR(FORWARD);
	}
	if (duty >= 99) {
		duty = 99;
	}
	voltage_temp=correctVoltage();
	MTU0.TGRA = (int16_t) (250 * duty / 100 *voltage_temp);	//MOTOR_R
	return (int16_t) (250 * duty / 100 *voltage_temp);
}
/****************************************
 モータ 　CW/CCW
 ****************************************/
int8_t setMotorDirL(int8_t cw_ccw) {
	if (cw_ccw == 0) {
		PORTC.PODR.BIT.B5 = 0; //モータ
		PORTC.PODR.BIT.B4 = 1;
		return cw_ccw;
	} else {
		PORTC.PODR.BIT.B5 = 1; //モータ
		PORTC.PODR.BIT.B4 = 0;
		return cw_ccw;
	}
}

int8_t setMotorDirR(int8_t cw_ccw) {
	if (cw_ccw == 0) {
		PORTC.PODR.BIT.B3 = 1; //モータ
		PORTC.PODR.BIT.B2 = 0;
		return cw_ccw;
	} else {
		PORTC.PODR.BIT.B3 = 0; //モータ
		PORTC.PODR.BIT.B2 = 1;
		return cw_ccw;
	}
}

/****************************************
 速度返す
 ****************************************/
float returnVelocityL(void) {
	return returnEncoderDiffL() * DIAMETER_L * 1000 * M_PI / (ENC_RESO * 4)
			/ GEAR_RATIO;
}

float returnVelocityR(void) {
	return returnEncoderDiffR() * DIAMETER_R * 1000 * M_PI / (ENC_RESO * 4)
			/ GEAR_RATIO;
}

/****************************************
 速度P制御
 ****************************************/
float ctrlPropVelocity(float kp) {

	g_current_velo_error = g_target_velo - g_current_velo;

	return g_current_velo_error * kp;
}

/****************************************
 速度I制御
 ****************************************/
float ctrlIntVelocity(float ki) {
	g_velo_error_integral += g_current_velo_error;
	return g_velo_error_integral * ki;
}

/****************************************
 角速度P制御
 ****************************************/
float ctrlPropAngularVelocity(float kp) {
	g_current_angularvelo_error = g_target_angularvelo - g_current_angularvelo;

	return convDegreeToRadian(g_current_angularvelo_error) * TREAD / 2.0 * kp;
}
/****************************************
 角速度I制御
 ****************************************/
float ctrlIntAngularVelocity(float ki) {
	g_angularvelo_error_integral += g_current_angularvelo_error;
	if (((g_sensor_L > SEN_THRESHOLD_L) || (g_sensor_R > SEN_THRESHOLD_R))
			&& g_flag_turn == 0) {
		g_angularvelo_error_integral = 0;
		return 0;
	} else if (g_flag_blindalley_ang == 1) {
		g_angularvelo_error_integral = 0;
		return 0;
	} else {
		return convDegreeToRadian(g_angularvelo_error_integral) * TREAD / 2.0
				* ki;
	}
}
/****************************************
 壁制御
 ****************************************/
float ctrlWall(float kp) {
	float temp;
	if (g_target_velo <= 0.4) {

		temp = 0;

	} else if ((g_flag_turn == 1) || (g_flag_diagonal == 1)
			|| (g_flag_blindalley_ang == 1)|| (g_flag_blindalley_dis == 1)) {

		temp = 0;

	} else if (((fabsf(g_sensor_L_derivative) > SEN_DERIVATIVE_L)
			|| (fabsf(g_sensor_R_derivative) > SEN_DERIVATIVE_R))
			&& (g_target_velo <= 0.5)) {

		temp = 0;

	} else if ((g_sensor_L > SEN_THRESHOLD_L)
			&& (g_sensor_R > SEN_THRESHOLD_R)) {
	//	driveRGB(GREEN,ON);
		temp = kp
				* (( SEN_REFERENCE_L - g_sensor_L)
						- ( SEN_REFERENCE_R - g_sensor_R));

	} else if ((g_sensor_L < SEN_THRESHOLD_L)
			&& (g_sensor_R < SEN_THRESHOLD_R)) {
	//	driveRGB(ORANGE,ON);
		temp = 0;

	} else if (g_sensor_L > SEN_THRESHOLD_L) {
	//	driveRGB(BLUE,ON);
		temp = 2 * kp * ( SEN_REFERENCE_L - g_sensor_L);

	} else if (g_sensor_R > SEN_REFERENCE_R) {
	//	driveRGB(RED,ON);
		temp = -2 * kp * ( SEN_REFERENCE_R - g_sensor_R);

	} else {

		temp = 0;
	}

//	if (fabsf(temp) < 0.00001) {
//		driveRGB(BLUE, ON);
//	} else {
//		driveRGB(GREEN, ON);
//	}

	return temp;
}

float ctrlWallFrontAng(float kp) {
	float temp = 0;
	if ((g_flag_blindalley_ang == 1) && (g_sensor_FL > SEN_NOWALL_FL)
			&& (g_sensor_FR > SEN_NOWALL_FR)) {
		g_angularvelo_error_integral = 0;
		temp = -kp
				* (( SEN_REFERENCE_FL - g_sensor_FL)
						- ( SEN_REFERENCE_FR - g_sensor_FR));

	} else {
		temp = 0;
	}
	return temp;
}
float ctrlWallFrontDis(float kp) {
	float temp = 0;
	if ((g_flag_blindalley_dis == 1) && (g_sensor_FL > SEN_NOWALL_FL)
			&& (g_sensor_FR > SEN_NOWALL_FR)) {

		temp = kp
				* (( SEN_REFERENCE_FL - g_sensor_FL)
						+ ( SEN_REFERENCE_FR - g_sensor_FR));

	} else {
		temp = 0;
	}
	return temp;
}
/****************************************
 袋小路
 ****************************************/
void runBlindAlley(float velo) {
	g_flag_gap = 1;
	g_flag_turn = 1;

	runStraight(5, HALF_SECTION, velo, 0);
	g_flag_blindalley_ang = 1;
	waitTime(400);
	g_flag_gap = 0;
	g_flag_blindalley_ang = 0;
	calcGyroZRef();
	g_flag_blindalley_dis = 1;
	waitTime(300);
	g_flag_blindalley_dis = 0;
	if (SEN_REFERENCE_L-g_sensor_L < -170) {
		turnCorner(pivot_90_R);
		g_flag_blindalley_ang = 1;
		waitTime(200);
		g_flag_gap = 0;
		g_flag_blindalley_ang = 0;
		g_flag_blindalley_dis = 1;
		waitTime(200);
		g_flag_blindalley_dis = 0;
		turnCorner(pivot_90_R);
		waitTime(300);
		runStraight(5, HALF_SECTION , velo, velo);
	} else if (SEN_REFERENCE_R-g_sensor_R < -170) {
		turnCorner(pivot_90_L);
		g_flag_blindalley_ang = 1;
		waitTime(200);
		g_flag_gap = 0;
		g_flag_blindalley_ang = 0;
		g_flag_blindalley_dis = 1;
		waitTime(200);
		g_flag_blindalley_dis = 0;
		turnCorner(pivot_90_L);
		waitTime(300);
		runStraight(5, HALF_SECTION , velo, velo);
	} else {
		turnCorner(pivot);
		waitTime(300);
		runStraight(5, HALF_SECTION + BLIND_ALLEY, velo, velo);
	}


	g_flag_turn = 0;

}
/****************************************
 走行初期化
 ****************************************/
void initRun(void) {
	g_flag_control = 1;
	g_log_count = 0;
	g_distance = 0;
	g_target_velo = 0;
	g_flag_failsafe=0;
}
/****************************************
 台形加速
 ****************************************/
void runStraight(float t_acc, float t_dis, float t_max_velo, float t_end_velo) {
	double section1 = 0;
	double section2 = 0;
	double section3 = 0;

	section1 = (t_max_velo * t_max_velo - g_target_velo * g_target_velo)
			/ (2 * t_acc);
	section3 = (t_max_velo * t_max_velo - t_end_velo * t_end_velo)
			/ (2 * t_acc);
	section2 = t_dis - section1 - section3;

	if (section2 <= 0) {
		if (section1 <= 0 && section3 >= 0) {
			section1 = 0;
			section2 = 0;
			section3 = t_dis;
		} else if (section1 >= 0 && section3 <= 0) {
			section1 = t_dis;
			section2 = 0;
			section3 = 0;
		} else {

			section2 = 0;

			section1 = (t_end_velo * t_end_velo - g_target_velo * g_target_velo)
					/ (4 * t_acc) + t_dis / 2;
			section3 = (g_target_velo * g_target_velo - t_end_velo * t_end_velo)
					/ (4 * t_acc) + t_dis / 2;
		}

	}
	section2 += section1;
	section3 += section2;

//section1////////////////////////////////////////////////////////////////////
	g_accele = t_acc;
	while (g_flag_failsafe!=1) {
		if (g_distance >= section1)
			break;
	}

//section2////////////////////////////////////////////////////////////////////

	g_accele = 0;
	while (g_flag_failsafe!=1) {
		if (g_distance >= section2)
			break;
	}

//section3////////////////////////////////////////////////////////////////////

	g_accele = -1.0 * t_acc;
	while (g_flag_failsafe!=1) {
		if (g_distance >= section3 || g_target_velo < 0)
			break;
	}
	g_accele = 0;
	g_target_velo = t_end_velo;
	g_distance = 0;
	g_angle = 0;
}

/****************************************
 スラローム
 ****************************************/
/*others~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//スラロームパラメータ						{degree	,alpha	,omega	,velo	,front	,rear	,sen	,dis_b	,dia}
const turn_t turn_90_L = 			{ 90	,9000	,603	,0.5	,0.018	,0.038	,15000	,0.018	,0 };
const turn_t turn_90_R = 			{-90	,9000	,603	,0.5	,0.015	,0.036	,15000	,0.015	,0 };
const turn_t pivot = 				{ 182	,6000	,500	,0		,0		,0		,10000	,0		,0 };
const turn_t pivot_90_L =			{ 93.5	,4000	,400	,0		,0		,0		,10000	,0		,0 };
const turn_t pivot_90_R =			{ -93.5	,4000	,400	,0		,0		,0		,10000	,0		,0 };
/*1000~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//スラロームパラメータ						{degree	,alpha	,omega	,velo	,front	,rear	,sen	,dis_b	,dia}
const turn_t turn_90_wide_L_1000 =	{ 90	,7000	,651	,1		,0.043	,0.06	,380	,0.02	,0 };
const turn_t turn_90_wide_R_1000 = 	{-88	,7000	,651	,1		,0.043	,0.06	,400	,0.01	,0 };

const turn_t turn_180_L_1000 = 		{ 178	,6000	,690	,1		,0.022	,0.05	,200	,0.005	,0 };
const turn_t turn_180_R_1000 =		{-178	,6000	,690	,1		,0.022	,0.07	,200	,0.005	,0 };

const turn_t turn_45_in_L_1000 = 	{ 45	,15500	,654	,1		,0.008	,0.078	,380	,0.005	,1 };
const turn_t turn_45_in_R_1000 = 	{-45	,15500	,654	,1		,0.008	,0.078	,400	,0.005	,1 };
const turn_t turn_45_out_L_1000 = 	{ 45	,15500	,634	,1		,0.095	,0.028	,10000	,0.069	,0 };
const turn_t turn_45_out_R_1000 =	{-45	,15500	,634	,1		,0.095	,0.028	,10000	,0.069	,0 };

const turn_t turn_135_in_L_1000 = 	{ 137	,10000	,1000	,1		,0.022	,0.068	,200	,0.084	,1 };
const turn_t turn_135_in_R_1000 = 	{-137	,10000	,1000	,1		,0.022	,0.068	,200	,0.084	,1 };
const turn_t turn_135_out_L_1000 = 	{ 137	,10000	,1000	,1		,0.036	,0.022	,10000	,0.022	,0 };
const turn_t turn_135_out_R_1000 = 	{-137	,10000	,1000	,1		,0.036	,0.022	,10000	,0.022	,0 };

const turn_t turn_v90_L_1000 = 		{ 90	,25000	,1256	,1		,0.04	,0.09	,10000	,0.045	,1 };
const turn_t turn_v90_R_1000 =		{-90	,25000	,1256	,1		,0.04	,0.09	,10000	,0.045	,1 };
/*1200~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//スラロームパラメータ						{degree	,alpha	,omega	,velo	,front	,rear	,sen	,dis_b	,dia}
const turn_t turn_90_wide_L_1200 =	{ 90	,8000	,696	,1.2	,0.026	,0.037	,500	,0.002	,0 };
const turn_t turn_90_wide_R_1200 = 	{-90	,8000	,696	,1.2	,0.026	,0.037	,500	,0.002	,0 };

const turn_t turn_180_L_1200 = 		{ 178	,8000	,824	,1.2	,0.022	,0.02	,500	,0.005	,0 };
const turn_t turn_180_R_1200 =		{-178	,8000	,824	,1.2	,0.022	,0.02	,500	,0.005	,0 };

const turn_t turn_45_in_L_1200 = 	{ 45	,12000	,600	,1.2	,0.014	,0.050	,10000	,0.014	,1 };
const turn_t turn_45_in_R_1200 = 	{-45	,12000	,600	,1.2	,0.014	,0.050	,10000	,0.014	,1 };
const turn_t turn_45_out_L_1200 = 	{ 45	,12000	,600	,1.2	,0.050	,0.014	,10000	,0.050	,0 };
const turn_t turn_45_out_R_1200 =	{-45	,12000	,600	,1.2	,0.050	,0.014	,10000	,0.050	,0 };

const turn_t turn_135_in_L_1200 = 	{ 135	,15500	,1200	,1.2	,0.072	,0.062	,10000	,0.072	,1 };
const turn_t turn_135_in_R_1200 = 	{-135	,15500	,1200	,1.2	,0.072	,0.062	,10000	,0.072	,1 };
const turn_t turn_135_out_L_1200 = 	{ 135	,15500	,1200	,1.2	,0.062	,0.072	,10000	,0.062	,0 };
const turn_t turn_135_out_R_1200 = 	{-135	,15500	,1200	,1.2	,0.062	,0.072	,10000	,0.062	,0 };

const turn_t turn_v90_L_1200 = 		{ 90	,22000	,1056	,1.2	,0.052	,0.052	,10000	,0.052	,1 };
const turn_t turn_v90_R_1200 =		{-90	,22000	,1056	,1.2	,0.052	,0.052	,10000	,0.052	,1 };
/*1400~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//スラロームパラメータ						{degree	,alpha	,omega	,velo	,front	,rear	,sen	,dis_b	,dia}
const turn_t turn_90_wide_L_1400 =	{ 90	,12000	,852	,1.4	,0.043	,0.04	,500	,0.002	,0 };
const turn_t turn_90_wide_R_1400 = 	{-90	,12000	,852	,1.4	,0.043	,0.04	,500	,0.002	,0 };

const turn_t turn_180_L_1400 = 		{ 178	,11500	,954	,1.4	,0.022	,0.019	,500	,0.005	,0 };
const turn_t turn_180_R_1400 =		{-178	,11500	,954	,1.4	,0.022	,0.019	,500	,0.005	,0 };

const turn_t turn_45_in_L_1400 = 	{ 45	,26000	,884	,1.4	,0.029	,0.069	,10000	,0.029	,1 };
const turn_t turn_45_in_R_1400 = 	{-45	,26000	,884	,1.4	,0.029	,0.069	,10000	,0.029	,1 };
const turn_t turn_45_out_L_1400 = 	{ 45	,26000	,884	,1.4	,0.069	,0.029	,10000	,0.069	,0 };
const turn_t turn_45_out_R_1400 =	{-45	,26000	,884	,1.4	,0.069	,0.029	,10000	,0.069	,0 };

const turn_t turn_135_in_L_1400 = 	{ 135	,17000	,1241	,1.4	,0.050	,0.039	,10000	,0.050	,1 };
const turn_t turn_135_in_R_1400 = 	{-135	,17000	,1241	,1.4	,0.050	,0.039	,10000	,0.050	,1 };
const turn_t turn_135_out_L_1400 = 	{ 135	,17000	,1241	,1.4	,0.039	,0.050	,10000	,0.039	,0 };
const turn_t turn_135_out_R_1400 = 	{-135	,17000	,1241	,1.4	,0.039	,0.050	,10000	,0.039	,0 };

const turn_t turn_v90_L_1400 = 		{ 90	,45500	,1501	,1.4	,0.050	,0.050	,10000	,0.050	,1 };
const turn_t turn_v90_R_1400 =		{-90	,45500	,1501	,1.4	,0.050	,0.050	,10000	,0.050	,1 };
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
const turn_t turn_90_wide_R_1800 = 	{-80	,20000	,1100	,1.8	,0.0	,0.15	,500	,0.002	,0 };
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void turnCorner(turn_t p) {
	double section1 = 0;
	double section2 = 0;
	double section3 = 0;

	float angacc_temp;

	if (p.angle >= 0) {
		if (g_sensor_L > 350) {

			while (g_sensor_L > p.sensor_break)
				;
			g_distance = 0;

			runStraight(5, p.dis_break, p.velocity, p.velocity);

		} else {
			runStraight(5, p.front, p.velocity, p.velocity);
		}
	} else {
		if (g_sensor_R > 400) {

			while (g_sensor_R > p.sensor_break)
				;
			g_distance = 0;

			runStraight(5, p.dis_break, p.velocity, p.velocity);

		} else {
			runStraight(5, p.front, p.velocity, p.velocity);
		}
	}

	g_flag_turn = 1; //ターンフラグ立てる
	g_flag_diagonal = p.diagonal;

	if ((p.angle) <= 0) {
		angacc_temp = -p.angular_accele;
	} else {
		angacc_temp = p.angular_accele;
	}

	g_angularaccele = angacc_temp;

	section1 = (p.max_angular_velo * p.max_angular_velo)
			/ (2 * p.angular_accele);
	section3 = (p.max_angular_velo * p.max_angular_velo)
			/ (2 * p.angular_accele);
	section2 = fabsf(p.angle) - section1 - section3;

	if (section2 <= 0) {
		if (section1 <= 0 && section3 >= 0) {
			section1 = 0;
			section2 = 0;
			section3 = fabsf(p.angle);
		} else if (section1 >= 0 && section3 <= 0) {
			section1 = fabsf(p.angle);
			section2 = 0;
			section3 = 0;
		} else {

			section2 = 0;

			section1 = (-g_current_angularvelo * g_current_angularvelo)
					/ (4 * p.angular_accele) + fabsf(p.angle) / 2;
			section3 = (g_current_angularvelo * g_current_angularvelo)
					/ (4 * p.angular_accele) + fabsf(p.angle) / 2;
		}

	}
	section2 += section1;
	section3 += section2;

//section1////////////////////////////////////////////////////////////////////

	while (g_flag_failsafe!=1) {
		if (fabsf(g_angle) >= section1)
			break;
	}

//section2////////////////////////////////////////////////////////////////////

	g_angularaccele = 0;

	if (p.angle <= 0) {
		g_target_angularvelo = -p.max_angular_velo;
	} else {
		g_target_angularvelo = p.max_angular_velo;
	}
	while (g_flag_failsafe!=1) {
		if (fabsf(g_angle) >= section2)
			break;
	}

//section3////////////////////////////////////////////////////////////////////

	g_angularaccele = angacc_temp * -1;

	while (g_flag_failsafe!=1) {
		if (fabsf(g_angle) >= section3 || fabsf(g_target_angularvelo) < 0.0001)
			break;
	}
	g_angularaccele = 0;
	g_target_angularvelo = 0;
	g_angle = 0;
	g_distance = 0;
	g_angularvelo_error_integral = 0;

	g_flag_turn = 0; //ターンフラグおろす
	runStraight(5, p.rear, p.velocity, p.velocity);
}

