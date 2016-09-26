/*
 * run.c
 *
 *  Created on: 2016/09/19
 *      Author: Gen
 */
#include <stdint.h>
#include "app.h"
#include "run.h"
#include "iodefine.h"
#include "intrpt.h"
#include "grobal.h"
#include "parameter.h"
#include "common.h"
#include "sensor.h"
/****************************************
 吸引
 ****************************************/
int8_t driveSuction(int16_t duty, int8_t on_off) {
	if (on_off == 0) {
		TPUA.TSTR.BIT.CST5 = 0;
	} else {
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
		PORTC.PODR.BIT.B6 = 0; //STBY
	}

	return 0;
}

/****************************************
 モータ デューティーセット
 ****************************************/
int16_t setMotorDutyL(float duty) {
	if (duty < 0) {
		setMotorDirL(BACKWARD);
		duty *= -1;
	} else {
		setMotorDirL(FORWARD);
	}
	if (duty >= 80) {
		duty = 80;
	}
	MTU0.TGRC = (int16_t) (250 * duty / 100);	//MOTOR_L
	return (int16_t) (250 * duty / 100);
}
int16_t setMotorDutyR(float duty) {
	if (duty < 0) {
		setMotorDirR(BACKWARD);
		duty *= -1;
	} else {
		setMotorDirR(FORWARD);
	}
	if (duty >= 80) {
		duty = 80;
	}
	MTU0.TGRA = (int16_t) (250 * duty / 100);	//MOTOR_R
	return (int16_t) (250 * duty / 100);
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
	return returnEncoderDiffL() * DIAMETER_L * M_PI / (ENC_RESO * 2)
			/ GEAR_RATIO;
}

float returnVelocityR(void) {
	return returnEncoderDiffR() * DIAMETER_R * M_PI / (ENC_RESO * 2)
			/ GEAR_RATIO;
}

/****************************************
 速度P制御
 ****************************************/
float ctrlPropVelocity(float kp) {

	g_current_gcenter_velo_error = g_target_gcenter_velo
			- g_current_gcenter_velo;

	return g_current_gcenter_velo_error * kp;
}

/****************************************
 速度I制御
 ****************************************/
float ctrlIntVelocity(float ki) {
	g_gcenter_velo_error_integral += g_current_gcenter_velo_error;
	return g_gcenter_velo_error_integral * ki;
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
	return convDegreeToRadian(g_angularvelo_error_integral) * TREAD / 2.0 * ki;
}

