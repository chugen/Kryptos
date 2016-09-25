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
#include "grobal.h"
#include "intrpt.h"

/****************************************
 Wait関数
 ****************************************/
void waitTime(int16_t wait_ms) {
	g_wait_counter = 0;
	while (1) {
		if (g_wait_counter > wait_ms)
			break;
	}
}

/****************************************
 バッテリーチェック
 ****************************************/
float checkBatt(void) {

	int16_t tmp;
	float battery;
	waitTime(100);
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
 センサー値返す
 ****************************************/
int16_t returnSenVal(uint8_t mode) {
	switch (mode) {
	S12AD.ADCSR.BIT.ADST = 0x01; 	//AD変換スタート
	while (S12AD.ADCSR.BIT.ADST == 1)
		;
case 0:
	return S12AD.ADDR1;
	break;
case 1:
	return S12AD.ADDR2;
	break;
case 2:
	return S12AD.ADDR3;
	break;
case 3:
	return S12AD.ADDR4;
	break;
default:
	return 0;
	break;
	}
	S12AD.ADCSR.BIT.ADST = 0x00; 	//AD変換ストップ
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
		TPU0.TGRD = 1500 - blue;
		TPU0.TGRC = 1500;

		TPU1.TGRA = 1500 - red;
		TPU1.TGRB = 1500;

		TPU2.TGRA = 1500 - green;
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
uint16_t selectMode(int16_t max_mode) {
	int16_t mode = 0;
	g_flag_mode_setting = 1;
	driveRGB(20, 0, 0, 1);
	while (pushButton()) {
		driveLED(mode);
		if (g_mode_velo < -0.6) {

			mode--;
			if (mode < 0) {
				mode = max_mode;
			}
			if (mode > max_mode) {
				mode = 0;
			}
			driveLED(mode);
			waitTime(300);
		} else if (g_mode_velo > 0.6) {

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
float convDegRad(float degree) {
	double radian;
	radian = degree * M_PI / 180;
	return radian;
}
