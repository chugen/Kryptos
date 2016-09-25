/*
 * sensor.c
 *
 *  Created on: 2016/09/19
 *      Author: Gen
 */
#include <stdint.h>
#include "iodefine.h"
#include "sensor.h"

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
