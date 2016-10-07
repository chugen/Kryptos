/*
 * app.cpp
 *
 *  Created on: 2016/06/28
 *      Author: 元太
 */

#include <stdint.h>
#include "app.h"
#include "iodefine.h"
#include "common.h"
#include "run.h"
#include "global.h"
#include "intrpt.h"
#include "serial.h"
#include "parameter.h"

/****************************************
 Wait関数
 ****************************************/
void waitTime(int16_t wait_ms) {
	g_wait_count = 0;
	while (1) {
		if (g_wait_count > wait_ms)
			break;
	}
}

/****************************************
 バッテリーチェック/補正
 ****************************************/
float checkBatt(void) {

	int16_t tmp;
	float battery;
	waitTime(100);
	S12AD.ADCSR.BIT.ADST = 0x00; 	//AD変換停止
	S12AD.ADANS0.WORD = 0x40;
	S12AD.ADCSR.BIT.ADST = 0x01; 	//AD変換スタート
	while (S12AD.ADCSR.BIT.ADST == 1)
		;
	tmp = S12AD.ADDR6;
	battery = (float) (tmp / 4096.0 * 3.3 * 3.0) + 0.06;

	if (battery < 7.4) {
		while (1) {
			driveRGB(100, 0, 0, 1);
			waitTime(200);
			driveRGB(0, 0, 0, 0);
			waitTime(200);
		}
	}
	return battery;
}

float correctVoltage(void) {
	float temp,battery,tmp;
	S12AD.ADCSR.BIT.ADST = 0x00; 	//AD変換停止
	S12AD.ADANS0.WORD = 0x40;
	S12AD.ADCSR.BIT.ADST = 0x01; 	//AD変換スタート
	while (S12AD.ADCSR.BIT.ADST == 1)
		;
	tmp = S12AD.ADDR6;
	battery = (float) (tmp / 4096.0 * 3.3 * 3.0) + 0.06;

	temp=MAX_VOLTAGE/battery;

	return temp;
}
/****************************************
 スイッチ
 ****************************************/
int16_t pushButton(void) {
	return PORT3.PIDR.BIT.B1 != 1;
}
int16_t waitButton(void) {
	while (PORT3.PIDR.BIT.B1 != 1)
		;
	return 0;
}

/****************************************
 モード選択LED
 ****************************************/
int16_t driveLED(int16_t mode) {
	switch (mode) {
	case 0:
		PORTA.PODR.BIT.B1 = 0;
		PORTA.PODR.BIT.B0 = 0;
		PORTE.PODR.BIT.B5 = 0;
		PORTE.PODR.BIT.B4 = 0;
		break;
	case 1:
		PORTA.PODR.BIT.B1 = 1;
		PORTA.PODR.BIT.B0 = 0;
		PORTE.PODR.BIT.B5 = 0;
		PORTE.PODR.BIT.B4 = 0;
		break;
	case 2:
		PORTA.PODR.BIT.B1 = 0;
		PORTA.PODR.BIT.B0 = 1;
		PORTE.PODR.BIT.B5 = 0;
		PORTE.PODR.BIT.B4 = 0;
		break;
	case 3:
		PORTA.PODR.BIT.B1 = 1;
		PORTA.PODR.BIT.B0 = 1;
		PORTE.PODR.BIT.B5 = 0;
		PORTE.PODR.BIT.B4 = 0;
		break;
	case 4:
		PORTA.PODR.BIT.B1 = 0;
		PORTA.PODR.BIT.B0 = 0;
		PORTE.PODR.BIT.B5 = 1;
		PORTE.PODR.BIT.B4 = 0;
		break;
	case 5:
		PORTA.PODR.BIT.B1 = 1;
		PORTA.PODR.BIT.B0 = 0;
		PORTE.PODR.BIT.B5 = 1;
		PORTE.PODR.BIT.B4 = 0;
		break;
	case 6:
		PORTA.PODR.BIT.B1 = 0;
		PORTA.PODR.BIT.B0 = 1;
		PORTE.PODR.BIT.B5 = 1;
		PORTE.PODR.BIT.B4 = 0;
		break;
	case 7:
		PORTA.PODR.BIT.B1 = 1;
		PORTA.PODR.BIT.B0 = 1;
		PORTE.PODR.BIT.B5 = 1;
		PORTE.PODR.BIT.B4 = 0;
		break;
	case 8:
		PORTA.PODR.BIT.B1 = 0;
		PORTA.PODR.BIT.B0 = 0;
		PORTE.PODR.BIT.B5 = 0;
		PORTE.PODR.BIT.B4 = 1;
		break;
	case 9:
		PORTA.PODR.BIT.B1 = 1;
		PORTA.PODR.BIT.B0 = 0;
		PORTE.PODR.BIT.B5 = 0;
		PORTE.PODR.BIT.B4 = 1;
		break;
	case 10:
		PORTA.PODR.BIT.B1 = 0;
		PORTA.PODR.BIT.B0 = 1;
		PORTE.PODR.BIT.B5 = 0;
		PORTE.PODR.BIT.B4 = 1;
		break;
	case 11:
		PORTA.PODR.BIT.B1 = 1;
		PORTA.PODR.BIT.B0 = 1;
		PORTE.PODR.BIT.B5 = 0;
		PORTE.PODR.BIT.B4 = 1;
		break;
	case 12:
		PORTA.PODR.BIT.B1 = 0;
		PORTA.PODR.BIT.B0 = 0;
		PORTE.PODR.BIT.B5 = 1;
		PORTE.PODR.BIT.B4 = 1;
		break;
	case 13:
		PORTA.PODR.BIT.B1 = 1;
		PORTA.PODR.BIT.B0 = 0;
		PORTE.PODR.BIT.B5 = 1;
		PORTE.PODR.BIT.B4 = 1;
		break;
	case 14:
		PORTA.PODR.BIT.B1 = 0;
		PORTA.PODR.BIT.B0 = 1;
		PORTE.PODR.BIT.B5 = 1;
		PORTE.PODR.BIT.B4 = 1;
		break;
	case 15:
		PORTA.PODR.BIT.B1 = 1;
		PORTA.PODR.BIT.B0 = 1;
		PORTE.PODR.BIT.B5 = 1;
		PORTE.PODR.BIT.B4 = 1;
		break;
	default:
		return 0;

	}
	return 0;
}
/****************************************
 フルカラーLED
 ****************************************/
int16_t driveRGB(int16_t red, int16_t green, int16_t blue, int8_t on_off) {
	if (on_off == 0) {
		TPU0.TGRD = 1500;
		TPU0.TGRC = 1500;

		TPU1.TGRA = 1500;
		TPU1.TGRB = 1500;

		TPU2.TGRA = 1500;
		TPU2.TGRB = 1500;

		TPU0.TCNT = 0;
		TPU1.TCNT = 0;
		TPU2.TCNT = 0;

		TPUA.TSTR.BIT.CST0 = 0;	//LED_BLUE
		TPUA.TSTR.BIT.CST1 = 0;	//LED_RED
		TPUA.TSTR.BIT.CST2 = 0;	//LED_GREEN

	} else {
		TPU0.TGRD = 1500 - blue;
		TPU0.TGRC = 1500;

		TPU1.TGRA = 1500 - red;
		TPU1.TGRB = 1500;

		TPU2.TGRA = 1500 - green;
		TPU2.TGRB = 1500;

		TPUA.TSTR.BIT.CST0 = 1;	//LED_BLUE
		TPUA.TSTR.BIT.CST1 = 1;	//LED_RED
		TPUA.TSTR.BIT.CST2 = 1;	//LED_GREEN

	}

	return 0;
}

/****************************************
 モード選択
 ****************************************/
int16_t selectMode(int16_t max_mode) {
	int16_t mode = 0;
	g_flag_mode_setting = 1;
	driveRGB(20, 20, 20, 1);
	while (pushButton()) {
		driveLED(mode);
		if (g_mode_velo < -0.3) {

			mode--;
			if (mode < 0) {
				mode = max_mode;
			}
			if (mode > max_mode) {
				mode = 0;
			}
			driveLED(mode);
			waitTime(300);
		} else if (g_mode_velo > 0.3) {

			mode++;
			if (mode < 0) {
				mode = max_mode;
			}
			if (mode > max_mode) {
				mode = 0;
			}
			driveLED(mode);
			waitTime(300);
		}
	}
	g_flag_mode_setting = 0;
	return mode;
}
/****************************************
 deg-rad変換
 ****************************************/
float convDegreeToRadian(float degree) {
	float temp;
	temp = degree * M_PI / 180.0;
	return temp;
}
/****************************************
 ログ書き出し関数
 ****************************************/
void printLog(void) {
	int32_t i;
	for (i = 0; i < LOG_TIMES; i++) {
		myprintf("%d	%f	%f\n", i, *(g_log_array + i), *(g_log_array2 + i));
	}
}
