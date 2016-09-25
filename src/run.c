/*
 * run.c
 *
 *  Created on: 2016/09/19
 *      Author: Gen
 */
#include <stdint.h>
#include "run.h"
#include "iodefine.h"
#include "intrpt.h"
#include "app.h"
#include "grobal.h"
#include "parameter.h"
#include "common.h"
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
		setMotorDirL(1);
		duty*=-1;
	}else{
		setMotorDirL(0);
	}
	if (duty >= 80) {
		duty = 80;
	}
	MTU0.TGRC = (int16_t) (250 * duty / 100);	//MOTOR_L
	return 0;
}
int16_t setMotorDutyR(float duty) {
	if (duty < 0) {
			setMotorDirR(1);
			duty*=-1;
		}else{
			setMotorDirR(0);
		}
	if (duty >= 80) {
		duty = 80;
	}
	MTU0.TGRA = (int16_t) (250 * duty / 100);	//MOTOR_R
	return 0;
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
 エンコーダ1ms差分取得
 ****************************************/
int32_t returnEncoderDiffL(void) {
	int32_t diff = 0;

	diff = TPU4.TCNT;

	TPU4.TCNT = 0;

	if (diff < INT16_MAX) {
		return diff * returnCountDirL();
	} else {
		return -(UINT16_MAX - diff) * returnCountDirL();
	}
}

int32_t returnEncoderDiffR(void) {
	int32_t diff = 0;

	diff = MTU1.TCNT;

	MTU1.TCNT = 0;

	if (diff < INT16_MAX) {
		return diff * returnCountDirR();
	} else {
		return (UINT16_MAX - diff) * returnCountDirR();
	}
}

/****************************************
 速度返す
 ****************************************/
float returnVelocityL(void) {
	return returnEncoderDiffL() * DIAMETER_L * M_PI / (ENC_RESO * 2) * PINION
			/ SPUR*returnCountDirL();
}

float returnVelocityR(void) {
	return returnEncoderDiffR() * DIAMETER_R * M_PI / (ENC_RESO * 2) * PINION
			/ SPUR;
}

/****************************************
 エンコーダカウント方向
 ****************************************/
int8_t returnCountDirL(void) {
	int8_t temp;
	if (TPU4.TSR.BIT.TCFD == 0) {
		temp = -1;
	} else if (TPU4.TSR.BIT.TCFD == 1) {
		temp = 1;
	}
	return temp;
}
int8_t returnCountDirR(void) {
	int8_t temp;
	if (MTU1.TSR.BIT.TCFD == 0) {
		temp = 1;
	} else if (MTU1.TSR.BIT.TCFD == 1) {
		temp = -1;
	}
	return temp;
}

/****************************************
 P制御
 ****************************************/
float controlProportionL(float kp) {

	g_current_error.L = g_target_velo.L - g_current_velo.L;

	return g_current_error.L * kp;
}
float controlProportionR(float kp) {

	g_current_error.R = g_target_velo.R - g_current_velo.R;

	return g_current_error.R * kp;
}
/****************************************
 I制御
 ****************************************/
float controlIntegralL(float ki) {

	return g_error_integral.L*ki;
}

float controlIntegralR(float ki) {

	return g_error_integral.R*ki;

}







