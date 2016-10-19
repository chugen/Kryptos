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

/****************************************
 FPUモード変更
 ****************************************/
void chengeFPUMode(uint16_t block, uint8_t mode) {
	switch (mode) {
	case P_E: //　P/Eモードにする
		FLASH.FENTRYR.WORD = 0xAA80;
		FLASH.FWEPROR.BYTE = 0x01;
		break;
	case READ: //　リードモードにする
		checkFRDY(TE16K);
		checkERR(block);
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
void checkERR(uint16_t block) {

	if ((FLASH.FSTATR0.BIT.ILGLERR == 1) || (FLASH.FSTATR0.BIT.ERSERR == 1)
			|| (FLASH.FSTATR0.BIT.PRGERR == 1)) {
		if (FLASH.FSTATR0.BIT.ILGLERR == 1) {
			if (FLASH.FASTAT.BYTE != 0x10) {
				FLASH.FASTAT.BYTE = 0x10;
			}
		}
		writeToBlock(block, STATUS_CLEAR); //ステータスクリアコマンド発行
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
uint32_t *convBlockToAddress(uint16_t block) {
	uint32_t address;
	address = block * 32 + 0x00100000;
	return (uint32_t *) address;
}
/****************************************
 対象ブロックのアドレスへ書き込み
 ****************************************/
void writeToBlock(uint16_t block, uint16_t content) {
	uint32_t *address;
	address = convBlockToAddress(block);
	*address = content;
}
/****************************************
 FCU RAM へのファームウェア転送
 ****************************************/
void trancefarFirmwareToRam(void) {
	if (FLASH.FENTRYR.WORD |= 0x0000) {
		FLASH.FENTRYR.BIT.FENTRY0 = 0;
		FLASH.FENTRYR.BIT.FENTRY1 = 0;
		FLASH.FENTRYR.BIT.FENTRY2 = 0;
		FLASH.FENTRYR.BIT.FENTRY3 = 0;
	}
	FLASH.FCURAME.WORD = 0xC401; //FCU RAMアクセス許可
	//
	DMAC0.DMCNT.BIT.DTE = 0;	//DMA転送禁止
	DMAC0.DMAMD.BIT.DM = 2;		//転送先アドレス更新モード：インクリメント
	DMAC0.DMAMD.BIT.SM = 2;		//転送元アドレス更新モード：インクリメント
	DMAC0.DMTMD.BIT.DTS = 2; 	//ﾘﾋﾟｰﾄ領域選択しない

}

/****************************************
 Program/Erase
 ****************************************/

