/*
 * flash.h
 *
 *  Created on: 2016/10/18
 *      Author: Gen
 */

#ifndef FLASH_H_
#define FLASH_H_

/****************************************
 FPUモード変更
 ****************************************/
void changeFCUMode(uint16_t block, uint16_t byte, uint8_t mode);
/****************************************
 エラーチェック
 ****************************************/
void checkERR(uint16_t block, uint16_t byte);
/****************************************
 FRDYチェック
 ****************************************/
void checkFRDY(uint32_t us);
/****************************************
 ブロックをアドレスへ変換
 ****************************************/
uint32_t *convBlockToAddress(uint16_t block, uint16_t byte);
/****************************************
 対象ブロックのアドレスへ書き込み
 ****************************************/
void writeToBlock(uint16_t block, uint16_t byte, uint8_t mode, volatile uint16_t content);
uint16_t readFCUValue(uint16_t block, uint16_t byte);
/****************************************
 FCU RAM へのファームウェア転送
 ****************************************/
void trancefarFirmwareToRam(void);
/****************************************
 クロック通知
 ****************************************/
void notificateClock(uint16_t block, uint16_t byte);
/****************************************
 Program/Erase
 ****************************************/
void programFCU(uint16_t block, uint16_t byte, uint16_t content);
void eraseFCU(uint16_t block, uint16_t byte);

#endif /* FLASH_H_ */
