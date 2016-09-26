/*
 * sensor.h
 *
 *  Created on: 2016/09/19
 *      Author: Gen
 */

#ifndef SENSOR_H_
#define SENSOR_H_

/****************************************
 SPI送受信
 ****************************************/
uint8_t commSPI(uint8_t address, uint8_t trancemit, uint8_t rw);
/****************************************
 エンコーダ1ms差分取得
 ****************************************/
int32_t returnEncoderDiffL(void);
int32_t returnEncoderDiffR(void);
/****************************************
 エンコーダカウント方向
 ****************************************/
int8_t returnCountDirL(void);
int8_t returnCountDirR(void);
/****************************************
 GYRO_Zの値を返す
 ****************************************/
float returnGyroZVal(void);
/****************************************
 GYRO_Zのリファレンス値を算出
 ****************************************/
int8_t calcGyroZRef(void);
#endif /* SENSOR_H_ */
