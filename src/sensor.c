/*
 * sensor.c
 *
 *  Created on: 2016/09/19
 *      Author: Gen
 */
#include <stdint.h>
#include "iodefine.h"
#include "sensor.h"
#include "common.h"
#include "global.h"
#include <mathf.h>

/****************************************
 SPI送受信
 ****************************************/
uint8_t commSPI(uint8_t address, uint8_t write, uint8_t mode) {

	uint8_t temp;
	volatile uint16_t i;

	RSPI1.SPCR.BIT.SPE = 1; //RSPI機能有効
	RSPI1.SPSR.BYTE = 0xA0; //ステータスクリア
	for (i = 0; i < 1000; i++)
		;

	RSPI1.SPDR.WORD.H = (address | (mode << 7));

	while (RSPI1.SPSR.BIT.SPRF == 0)
		;
	temp = RSPI1.SPDR.WORD.H;

	RSPI1.SPDR.WORD.H = write;

	while (RSPI1.SPSR.BIT.SPRF == 0)
		;
	temp = RSPI1.SPDR.WORD.H;

	RSPI1.SPCR.BIT.SPE = 0; //RSPI機能無効

	return temp;
}

/****************************************
 エンコーダ1ms差分取得
 ****************************************/
int32_t returnEncoderDiffL(void) {
	int32_t diff = 0;

	diff = TPU4.TCNT;

	TPU4.TCNT = 0;

	if (diff <= INT16_MAX) {
		return -diff * returnCountDirL();
	} else {
		return -(UINT16_MAX - diff) * returnCountDirL();
	}
}

int32_t returnEncoderDiffR(void) {
	int32_t diff = 0;

	diff = MTU1.TCNT;

	MTU1.TCNT = 0;

	if (diff <= INT16_MAX) {
		return diff * returnCountDirR();
	} else {
		return (UINT16_MAX - diff) * returnCountDirR();
	}
}

/****************************************
 エンコーダカウント方向
 ****************************************/
int8_t returnCountDirL(void) {
	int8_t temp;
	if (TPU4.TSR.BIT.TCFD == 0) {
		temp = 1;
	} else if (TPU4.TSR.BIT.TCFD == 1) {
		temp = -1;
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
 GYRO_Zの値を返す
 ****************************************/
float returnGyroZVal(void) {
	int16_t temp = 0;
	float value;
	static int16_t currentL;
	static int16_t pastL;
	static int16_t currentH;

	pastL = currentL;
	currentL = (int16_t) commSPI(GYRO_ZOUT_L, 0x0f, READ);
	if (fabsf(pastL-currentL) > 240 || fabsf(currentL) > 240) {
		currentL = 0x00;
	}

	currentH = (int16_t) commSPI(GYRO_ZOUT_H, 0x0f, READ);

	if (currentH == 129) {
		currentH = 0x00;
	}
	temp |= currentL;
	temp |= (currentH << 8);

	if (temp <= -250 && temp >= -256) {
		temp = 0;
	}

	value = (float) (temp * 2000.0 / INT16_MAX);

	if (value < 0) {
		value *= 90.0 / 90.67;
	} else {
		value *= 90.0 / 87.9;
	}

	return value;
}
/****************************************
 GYRO_Zのリファレンス値を算出
 ****************************************/
int8_t calcGyroZRef(void) {
	int i = 0;
	float temp;
	g_gyro_reference = 0;
	for (i = 0; i < 1000; i++) {

		temp += returnGyroZVal();
		waitTime(1);
	}
	g_gyro_reference = temp / 1000.0;
	return 0;
}
/****************************************
 受光センサー値返す
 ****************************************/
uint16_t returnSenVal(uint8_t mode) {
	switch (mode) {
	S12AD.ADCSR.BIT.ADST = 0x00; 	//AD変換停止
case 0:
	S12AD.ADANS0.WORD = 0x02;
	S12AD.ADCSR.BIT.ADST = 0x01; 	//AD変換スタート
	while (S12AD.ADCSR.BIT.ADST == 1)
		;
	return S12AD.ADDR1;
	break;
case 1:
	S12AD.ADANS0.WORD = 0x04;
	S12AD.ADCSR.BIT.ADST = 0x01; 	//AD変換スタート
	while (S12AD.ADCSR.BIT.ADST == 1)
		;
	return S12AD.ADDR2;
	break;
case 2:
	S12AD.ADANS0.WORD = 0x08;
	S12AD.ADCSR.BIT.ADST = 0x01; 	//AD変換スタート
	while (S12AD.ADCSR.BIT.ADST == 1)
		;
	return S12AD.ADDR3;
	break;
case 3:
	S12AD.ADANS0.WORD = 0x10;
	S12AD.ADCSR.BIT.ADST = 0x01; 	//AD変換スタート
	while (S12AD.ADCSR.BIT.ADST == 1)
		;
	return S12AD.ADDR4;
	break;
default:
	return 0;
	break;
	}
	S12AD.ADCSR.BIT.ADST = 0x00; 	//AD変換ストップ
}

/****************************************
 光センサー
 ****************************************/
static uint8_t switch_sensorLED;
void driveSensorLED(uint8_t mode) {
	if (switch_sensorLED == OFF) {
		mode = OFF;
	}
	switch (mode) {
	case OFF:
		PORT5.PODR.BIT.B4 = 0;
		PORT5.PODR.BIT.B5 = 0;
		break;
	case FR_L:
		PORT5.PODR.BIT.B4 = 1;
		PORT5.PODR.BIT.B5 = 0;
		break;
	case FL_R:
		PORT5.PODR.BIT.B4 = 0;
		PORT5.PODR.BIT.B5 = 1;
		break;
	default:
		PORT5.PODR.BIT.B4 = 0;
		PORT5.PODR.BIT.B5 = 0;
		break;
	}
}

void switchSensorLED(uint8_t on_off) {
	if (on_off == 1) {
		switch_sensorLED = 1;
	} else {
		switch_sensorLED = 0;
	}

}
