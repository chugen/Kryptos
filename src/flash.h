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
void chengeFPUMode(uint16_t block,uint8_t mode) ;
/****************************************
 エラーチェック
 ****************************************/
void checkERR(uint16_t block);
/****************************************
 FRDYチェック
 ****************************************/
void checkFRDY(uint32_t us) ;
/****************************************
 ブロックをアドレスへ変換
 ****************************************/
uint32_t *convBlockToAddress(uint16_t block);
/****************************************
 対象ブロックのアドレスへ書き込み
 ****************************************/
void writeToBlock(uint16_t block,uint16_t content);

#endif /* FLASH_H_ */
