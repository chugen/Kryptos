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
#include "sensor.h"
/****************************************
 ビットシフト
 ****************************************/
void shiftBit(uint8_t *value, uint8_t shift, uint8_t shift_dir) {
	uint8_t bit;

	switch (shift_dir) {
	case LEFT:
		*value = *value << shift;
		if (*value >= 0x10) {
			*value = *value >> 4;
		}
		break;
	case RIGHT:
		bit = *value >> shift;
		if (bit == 0) {
			*value = *value << 4;
		}

		*value = *value >> shift;
		break;
	default:
		break;
	}
}
//4bit
uint8_t getBitShiftValue4bit(uint8_t *value, uint8_t shift, uint8_t shift_dir) {
	uint8_t bit;

	switch (shift_dir) {
	case LEFT:
		bit = *value << shift;
		if (bit >= 0x10) {
			bit = bit >> 4;
		}
		return bit;
		break;
	case RIGHT:
		bit = *value >> shift;
		if (bit == 0) {
			bit = *value << 4;
			bit = bit >> shift;
		}
		return bit;
		break;

	default:
		return 0;
	}
}
uint8_t getBitShiftValue8bit(uint8_t *value, uint8_t shift, uint8_t shift_dir) {
	uint8_t bit;

	switch (shift_dir) {
	case LEFT:
		bit = *value << shift;

		return bit;
		break;
	case RIGHT:
		bit = *value >> shift;

		return bit;
		break;

	default:
		return 0;
	}
}

/****************************************
 Wait関数
 ****************************************/
void waitTime(int16_t wait_ms) {
	g_wait_count = 0;
	while (1) {
		if (g_wait_count > (float) wait_ms * 0.001 / INTRPT_PERIOD)
			break;
	}
}

void waitTimeMicro(uint16_t wait_us) {
	uint32_t i;
	for (i = 0; i < (wait_us * 100); i++) {

	}
}
/****************************************
 バッテリーチェック
 ****************************************/
float checkLowVoltage(void) {

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

	if (battery < 7.8) {
		while (1) {
			driveRGB(RED, ON);
			waitTime(200);
			driveRGB(RGB_OFF, OFF);
			waitTime(200);
		}
	}
	return battery;
}

/****************************************
 センサー待ち
 ****************************************/
void waitSensor(void) {
	uint16_t count = 0;
	switchSensorLED(ON);
	while (1) {
		if ((g_sensor_L > 300) && (g_sensor_R > 300)) {
			count++;
			if (count > 200) {
				break;
			}
		} else {
			count = 0;
		}
		waitTime(1);
	}
	soundSensor();
	switchSensorLED(OFF);
}
/****************************************
 スイッチ
 ****************************************/
int16_t pushButton(void) {
	if (PORT3.PIDR.BIT.B1 != 1) {
		return 1;
	} else {
		soundButton();
		return 0;
	}

}
int16_t waitButton(void) {
	while (PORT3.PIDR.BIT.B1 != 1)
		;
	soundButton();
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

		TPU0.TIORL.BIT.IOD = 0x00;	//出力禁止
		TPU1.TIOR.BIT.IOA = 0x00;	//出力禁止
		TPU2.TIOR.BIT.IOA = 0x00;	//出力禁止

		TPU0.TCNT = 0;
		TPU1.TCNT = 0;
		TPU2.TCNT = 0;

		TPUA.TSTR.BIT.CST0 = 0;	//LED_BLUE
		TPUA.TSTR.BIT.CST1 = 0;	//LED_RED
		TPUA.TSTR.BIT.CST2 = 0;	//LED_GREEN

	} else {
		TPU0.TIORL.BIT.IOD = 0x02;	//初期出力：H,コンペアマッチ：L
		TPU1.TIOR.BIT.IOA = 0x02;	//初期出力：H,コンペアマッチ：L
		TPU2.TIOR.BIT.IOA = 0x02;	//初期出力：H,コンペアマッチ：L

		TPU0.TCNT = 0;
		TPU1.TCNT = 0;
		TPU2.TCNT = 0;

		TPU0.TGRD = 1500 - blue - 1;
		TPU0.TGRC = 1500;

		TPU1.TGRA = 1500 - red - 1;
		TPU1.TGRB = 1500;

		TPU2.TGRA = 1500 - green - 1;
		TPU2.TGRB = 1500;

		TPUA.TSTR.BIT.CST0 = 1;	//LED_BLUE
		TPUA.TSTR.BIT.CST1 = 1;	//LED_RED
		TPUA.TSTR.BIT.CST2 = 1;	//LED_GREEN

	}

	return 0;
}
/****************************************
 HSVtoRGB変換
 ****************************************/

/****************************************
 ブザー
 ****************************************/
void driveBuzzer(float freq, float wait_ms) {
	float cycle;

	if (freq == 0) {
		waitTime(wait_ms);
	} else {
		cycle = (float) 625000 / 2 / (float) freq;

		MTU2.TGRA = (int) cycle / 2;

		MTU2.TGRB = (int) cycle;

		MTU2.TIOR.BIT.IOA = 0x05;	//初期出力：H,コンペアマッチ：L
		MTU.TSTR.BIT.CST2 = 1;
		waitTime(wait_ms);
		MTU2.TIOR.BIT.IOA = 0x00;	//出力禁止
		MTU.TSTR.BIT.CST2 = 0;

	}
}

void driveBuzzerIntrpt(uint8_t left_right, uint8_t on_off) {
	float cycle;
	uint32_t time1 = 150, time2, time3;
	time2 = time1 + 30;
	time3 = time2 + 150;
	if (g_flag_buzzer == 0) {
		if (on_off == 1) {
			switch (left_right) {
			case LEFT:
				g_flag_buzzer = LEFT;
				cycle = (float) 625000 / 2 / (float) BZ_A5;
				break;
			case RIGHT:
				g_flag_buzzer = RIGHT;
				cycle = (float) 625000 / 2 / (float) BZ_G6;
				break;
			case BOTH:
				g_flag_buzzer = BOTH;
				cycle = (float) 625000 / 2 / (float) BZ_G3;
				break;
			default:
				break;
			}
			g_buzzer_count = 0;

			MTU2.TGRA = (int) cycle / 2;
			MTU2.TGRB = (int) cycle;
			MTU2.TIOR.BIT.IOA = 0x05;	//初期出力：H,コンペアマッチ：L
			MTU.TSTR.BIT.CST2 = 1;
		}
	} else if (g_flag_buzzer == LEFT) {
		if (g_buzzer_count > time1 && g_buzzer_count <= time2) {

			MTU2.TIOR.BIT.IOA = 0x00;	//出力禁止
			MTU.TSTR.BIT.CST2 = 0;

		} else if (g_buzzer_count > time2 && g_buzzer_count <= time3) {
			cycle = (float) 625000 / 2 / (float) BZ_A2;
			MTU2.TGRA = (int) cycle / 2;
			MTU2.TGRB = (int) cycle;
			MTU2.TIOR.BIT.IOA = 0x05;	//初期出力：H,コンペアマッチ：L
			MTU.TSTR.BIT.CST2 = 1;
		} else if (g_buzzer_count > time3) {
			MTU2.TIOR.BIT.IOA = 0x00;	//出力禁止
			MTU.TSTR.BIT.CST2 = 0;
			g_flag_buzzer = 0;
		}
	} else if (g_flag_buzzer == RIGHT) {
		if (g_buzzer_count > time1 && g_buzzer_count <= time2) {

			MTU2.TIOR.BIT.IOA = 0x00;	//出力禁止
			MTU.TSTR.BIT.CST2 = 0;

		} else if (g_buzzer_count > time2 && g_buzzer_count <= time3) {
			cycle = (float) 625000 / 2 / (float) BZ_G3;
			MTU2.TGRA = (int) cycle / 2;
			MTU2.TGRB = (int) cycle;
			MTU2.TIOR.BIT.IOA = 0x05;	//初期出力：H,コンペアマッチ：L
			MTU.TSTR.BIT.CST2 = 1;
		} else if (g_buzzer_count > time3) {
			MTU2.TIOR.BIT.IOA = 0x00;	//出力禁止
			MTU.TSTR.BIT.CST2 = 0;
			g_flag_buzzer = 0;
		}
	} else if (g_flag_buzzer == BOTH) {
		if (g_buzzer_count > time1 && g_buzzer_count <= time1) {

			MTU2.TIOR.BIT.IOA = 0x00;	//出力禁止
			MTU.TSTR.BIT.CST2 = 0;

		} else if (g_buzzer_count > time1 && g_buzzer_count <= time3) {
			cycle = (float) 625000 / 2 / (float) BZ_G3;
			MTU2.TGRA = (int) cycle / 2;
			MTU2.TGRB = (int) cycle;
			MTU2.TIOR.BIT.IOA = 0x05;	//初期出力：H,コンペアマッチ：L
			MTU.TSTR.BIT.CST2 = 1;
		} else if (g_buzzer_count > time3) {
			MTU2.TIOR.BIT.IOA = 0x00;	//出力禁止
			MTU.TSTR.BIT.CST2 = 0;
			g_flag_buzzer = 0;
		}
	}
}

/****************************************
 モード選択
 ****************************************/
int16_t selectMode(int16_t max_mode) {
	int16_t mode = 0;
	g_flag_mode_setting = 1;

	while (pushButton()) {
		driveLED(mode);
		if (g_mode_velo < -0.25) {

			mode--;
			if (mode < 0) {
				mode = max_mode;
			}
			if (mode > max_mode) {
				mode = 0;
			}
			driveLED(mode);
			soundCount(mode);
		} else if (g_mode_velo > 0.25) {

			mode++;
			if (mode < 0) {
				mode = max_mode;
			}
			if (mode > max_mode) {
				mode = 0;
			}
			driveLED(mode);
			soundCount(mode);
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
		myprintf("%d\t%f\t%f\n", i, *(g_log_array + i), *(g_log_array2 + i));
	}
	soundPrint();
}
void printLog4(void) {
	int32_t i;
	for (i = 0; i < LOG_TIMES; i++) {
		myprintf("%d\t%f\t%f\t%f\t%f\n", i, *(g_log_array + i), *(g_log_array2 + i),
				*(g_log_array3 + i), *(g_log_array4 + i));
	}
	soundPrint();
}
void printLogInt(void) {
	int32_t i;
	for (i = 0; i < LOG_TIMES; i++) {
		myprintf("%d	%d	%d\n", i, *(g_log_array_int + i),
				*(g_log_array2_int + i));
	}
	soundPrint();
}
/****************************************
 ゴール音
 ****************************************/
void soundGoal(void) {
	driveBuzzer(BZ_A4, 240);
	driveBuzzer(0, 50);
	driveBuzzer(BZ_F4, 240);
	driveBuzzer(0, 50);
	driveBuzzer(BZ_C4, 360);
	driveBuzzer(0, 50);
	driveBuzzer(BZ_AS4, 60);
	driveBuzzer(0, 50);
	driveBuzzer(BZ_AS4, 60);
	driveBuzzer(0, 50);
	driveBuzzer(BZ_G4, 60);
	driveBuzzer(0, 50);
	driveBuzzer(BZ_G4, 60);
	driveBuzzer(0, 50);
	driveBuzzer(BZ_AS4, 60);
	driveBuzzer(0, 50);
	driveBuzzer(BZ_A4, 360);
}
/****************************************
 エラー音
 ****************************************/
void soundError(void) {
	driveBuzzer(BZ_C2, 100);
	driveBuzzer(0, 50);
	driveBuzzer(BZ_CS2, 100);
	driveBuzzer(0, 50);
	driveBuzzer(BZ_D2, 100);
	driveBuzzer(0, 50);
	driveBuzzer(BZ_CS2, 100);
	driveBuzzer(0, 50);
	driveBuzzer(BZ_C2, 100);
	driveBuzzer(0, 50);
	driveBuzzer(BZ_CS2, 100);
	driveBuzzer(0, 50);
	driveBuzzer(BZ_D2, 100);
	driveBuzzer(0, 50);
	driveBuzzer(BZ_CS2, 100);
	driveBuzzer(0, 50);
	driveBuzzer(BZ_C2, 300);
}
/****************************************
 スタート音
 ****************************************/
void soundStartSearch(void) {
	driveBuzzer(BZ_A2, 50);
	waitTime(30);
	driveBuzzer(BZ_B2, 50);
	driveBuzzer(BZ_A3, 50);
	waitTime(30);
	driveBuzzer(BZ_B3, 50);
	driveBuzzer(BZ_A4, 50);
	waitTime(30);
	driveBuzzer(BZ_B4, 50);
	driveBuzzer(BZ_A5, 50);
	waitTime(30);
	driveBuzzer(BZ_B5, 50);
}
void soundStartRun(void) {
//	driveBuzzer(BZ_A2, 600);
//	waitTime(150);
//
//	driveBuzzer(BZ_A2, 600);
//	waitTime(150);
//
//	driveBuzzer(BZ_A2, 600);
//	waitTime(150);
//
//	driveBuzzer(BZ_A3, 750);
	driveBuzzer(BZ_C0, 80);
	driveBuzzer(BZ_C1, 80);
	driveBuzzer(BZ_C2, 80);
	driveBuzzer(BZ_C3, 80);
	driveBuzzer(BZ_C4, 80);
	driveBuzzer(BZ_C5, 80);
	driveBuzzer(BZ_C6, 80);
	driveBuzzer(BZ_C0, 80);
	driveBuzzer(BZ_C1, 80);
	driveBuzzer(BZ_C2, 80);
	driveBuzzer(BZ_C3, 80);
	driveBuzzer(BZ_C4, 80);
	driveBuzzer(BZ_C5, 80);
	driveBuzzer(BZ_C6, 80);

}
/****************************************
 通知音
 ****************************************/
void soundSensor(void) {
	driveBuzzer(BZ_A4, 50);
	waitTime(30);
	driveBuzzer(BZ_A5, 50);
	waitTime(30);
	driveBuzzer(BZ_B5, 30);
}
void soundButton(void) {
	driveBuzzer(BZ_A4, 50);
	waitTime(30);
	driveBuzzer(BZ_B4, 50);
	driveBuzzer(BZ_A4, 50);
	waitTime(30);
	driveBuzzer(BZ_B4, 50);
}
void soundPrint(void) {
	driveBuzzer(BZ_A3, 50);
	waitTime(30);
	driveBuzzer(BZ_B4, 50);
	driveBuzzer(BZ_A5, 50);
	waitTime(30);
	driveBuzzer(BZ_B3, 50);
}
/****************************************
 カウント音
 ****************************************/
void soundCount(int16_t mode) {
	switch (mode) {
	case 0:
		driveBuzzer(BZ_A3, 200);
		break;
	case 1:
		driveBuzzer(BZ_B3, 200);
		break;
	case 2:
		driveBuzzer(BZ_C3, 200);
		break;
	case 3:
		driveBuzzer(BZ_D3, 200);
		break;
	case 4:
		driveBuzzer(BZ_E3, 200);
		break;
	case 5:
		driveBuzzer(BZ_F3, 200);
		break;
	case 6:
		driveBuzzer(BZ_G3, 200);
		break;
	case 7:
		driveBuzzer(BZ_A4, 200);
		break;
	case 8:
		driveBuzzer(BZ_B4, 200);
		break;
	case 9:
		driveBuzzer(BZ_C4, 200);
		break;
	case 10:
		driveBuzzer(BZ_D4, 200);
		break;
	case 11:
		driveBuzzer(BZ_E4, 200);
		break;
	case 12:
		driveBuzzer(BZ_F4, 200);
		break;
	case 13:
		driveBuzzer(BZ_G4, 200);
		break;
	case 14:
		driveBuzzer(BZ_A5, 200);
		break;
	case 15:
		driveBuzzer(BZ_B5, 200);
		break;
	default:
		break;
	}
}
/****************************************
 動作モード起動通知
 ****************************************/
void notificateStartUp(void) {
	driveBuzzer(BZ_A5, 30);
	waitTime(20);
	driveBuzzer(BZ_A4, 30);
	waitTime(20);
	driveBuzzer(BZ_A3, 30);
	waitTime(20);
	driveBuzzer(BZ_A2, 30);
	driveLED(1);
	waitTime(50);
	driveLED(2);
	waitTime(50);
	driveLED(4);
	waitTime(50);
	driveLED(8);
	waitTime(50);
	driveLED(4);
	waitTime(50);
	driveLED(2);
	waitTime(50);
	driveLED(1);
	waitTime(50);
	driveLED(0);
}
