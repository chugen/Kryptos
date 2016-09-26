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
#include "grobal.h"

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

	if (diff < INT16_MAX) {
		return -diff * returnCountDirL();
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
	int16_t temp;

	temp = (((int16_t) (commSPI(GYRO_ZOUT_H, 0x00, READ))) << 8);
	temp |= ((int16_t) (commSPI(GYRO_ZOUT_H, 0x00, READ)));

	return (float) (temp * 2000.0 / INT16_MAX);
}
/****************************************
 GYRO_Zのリファレンス値を算出
 ****************************************/
int8_t calcGyroZRef(void){
	int i=0;
	float temp;
	g_gyro_reference=0;
	for(i=0;i<150;i++){
		temp+=returnGyroZVal();
		waitTime(1);
	}
	g_gyro_reference=temp/150.0;
	return 0;
}
