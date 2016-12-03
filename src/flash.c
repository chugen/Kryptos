/*
 * flash.c
 *
 *  Created on: 2016/10/18
 *      Author: Gen
 */
#include "iodefine.h"
#include <stdint.h>
#include "common.h"
#include "flash.h"
#include "app.h"

/****************************************
 FPUモード変更
 ****************************************/
void changeFCUMode(uint16_t block, uint16_t byte, uint8_t mode) {
	switch (mode) {
	case P_E: //　P/Eモードにする
		FLASH.FENTRYR.WORD = 0xAA80;
		FLASH.FWEPROR.BYTE = 0x01;
		break;
	case READ: //　リードモードにする
		checkFRDY(TE16K);
		checkERR(block, byte);
		do {
			FLASH.FENTRYR.WORD = 0xAA00;
		} while (FLASH.FENTRYR.WORD == 0x0000);

		FLASH.FWEPROR.BYTE = 0x02;
		break;

	default:
		break;
	}

}
/****************************************
 エラーチェック
 ****************************************/
void checkERR(uint16_t block, uint16_t byte) {

	if ((FLASH.FSTATR0.BIT.ILGLERR == 1) || (FLASH.FSTATR0.BIT.ERSERR == 1)
			|| (FLASH.FSTATR0.BIT.PRGERR == 1)) {
		if (FLASH.FSTATR0.BIT.ILGLERR == 1) {
			if (FLASH.FASTAT.BYTE != 0x10) {
				FLASH.FASTAT.BYTE = 0x10;
			}
		}
		writeToBlock(block, byte, BYTE_MODE, STATUS_CLEAR); //ステータスクリアコマンド発行
	}
}
/****************************************
 FRDYチェック
 ****************************************/
void checkFRDY(uint32_t us) {
	if (FLASH.FSTATR0.BIT.FRDY == 0) {
		waitTimeMicro(us);
		if (FLASH.FSTATR0.BIT.FRDY == 0) {
			//FCUリセット
			FLASH.FRESETR.BIT.FRESET = 1;
			waitTimeMicro(100);
			FLASH.FRESETR.BIT.FRESET = 0;
		}
	}
}
/****************************************
 ブロックをアドレスへ変換
 ****************************************/
uint32_t *convBlockToAddress(uint16_t block, uint16_t byte) {
	uint32_t *address;

	address =(uint32_t *) (block * 32 + 0x00100000 + byte);

	return address;
}
/****************************************
 対象ブロックのアドレスへ書き込み
 ****************************************/
void writeToBlock(uint16_t block, uint16_t byte, uint8_t mode,volatile uint16_t content) {
	uint16_t *address_word;
	uint8_t *address_byte;


	if (mode == BYTE_MODE) {
		address_byte = (uint8_t *) convBlockToAddress(block, byte);
		*address_byte = content;
	} else {
		address_word = (uint16_t *) convBlockToAddress(block, byte);
		*address_word = content;
	}

}

uint16_t readFCUValue(uint16_t block, uint16_t byte){

	FLASH.DFLRE0.WORD=0x2BFF;
	return *(volatile uint16_t *)convBlockToAddress(block, byte);
	FLASH.DFLRE0.WORD=0x2B00;

}
/****************************************
 FCU RAM へのファームウェア転送
 ****************************************/
void trancefarFirmwareToRam(void) {

	SYSTEM.PRCR.WORD = 0xA502;	//プロテクト解除

	FLASH.FCURAME.WORD = 0xC401; //FCU RAMアクセス許可
	//
	DMAC0.DMCNT.BIT.DTE = 0;	//DMA転送禁止
	DMAC0.DMAMD.BIT.DM = 2;		//転送先アドレス更新モード：インクリメント
	DMAC0.DMAMD.BIT.SM = 2;		//転送元アドレス更新モード：インクリメント
	DMAC0.DMTMD.BIT.DTS = 2; 	//ﾘﾋﾟｰﾄ領域選択しない

	DMAC0.DMSAR = (long *) 0xFEFFE000; //DMA転送元ｱﾄﾞﾚｽSET!
	DMAC0.DMDAR = (long *) 0x007F8000; //DMA転送先ｱﾄﾞﾚｽSET!

	DMAC0.DMCRA = 0x000;	//ブロックサイズ　1024
	DMAC0.DMCRB = 0x08;	//32回転送

	DMAC0.DMREQ.BIT.CLRS = 0; //ｿﾌﾄ起動後SWREQをｸﾘｱ

	DMAC.DMAST.BIT.DMST = 1; //DMAC起動を許可
	DMAC0.DMCNT.BIT.DTE = 1; //DMA転送を許可

	SYSTEM.PRCR.WORD = 0xA500;

	if (FLASH.FENTRYR.WORD != 0x0000) {
		FLASH.FENTRYR.BIT.FENTRY0 = 0;
		FLASH.FENTRYR.BIT.FENTRY1 = 0;
		FLASH.FENTRYR.BIT.FENTRY2 = 0;
		FLASH.FENTRYR.BIT.FENTRY3 = 0;
	}
	FLASH.FCURAME.WORD = 0xC401;
	while (DMAC0.DMREQ.BIT.SWREQ) {
	}
	DMAC0.DMREQ.BIT.SWREQ = 1;
	while (DMAC0.DMREQ.BIT.SWREQ) {
	}
	DMAC0.DMREQ.BIT.SWREQ = 1;

}

/****************************************
 クロック通知
 ****************************************/
void notificateClock(uint16_t block, uint16_t byte) {
	FLASH.PCKAR.BIT.PCKA = 0x32;
	writeToBlock(block, byte, BYTE_MODE, CLOCK_S1);
	writeToBlock(block, byte, BYTE_MODE, CLOCK_S2);
	writeToBlock(block, byte, WORD_MODE, CLOCK_S3);
	writeToBlock(block, byte, WORD_MODE, CLOCK_S3);
	writeToBlock(block, byte, WORD_MODE, CLOCK_S3);
	writeToBlock(block, byte, BYTE_MODE, END);
	checkFRDY(200);
}
/****************************************
 Program/Erase
 ****************************************/
void programFCU(uint16_t block, uint16_t byte, uint16_t content) {
	writeToBlock(block, byte, BYTE_MODE, PROGRAM_S1);
	writeToBlock(block, byte, BYTE_MODE, PROGRAM_S2);
	writeToBlock(block, byte, WORD_MODE, content);
	writeToBlock(block, byte, BYTE_MODE, END);
	//while(FLASH.FSTATR0.BIT.FRDY == 0);
	checkFRDY(50);
}

void eraseFCU(uint16_t block, uint16_t byte){
	writeToBlock(block, byte, BYTE_MODE, ERASE_S1);
	writeToBlock(block, byte, BYTE_MODE, END);
}
