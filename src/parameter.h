/*
 * parameter.h
 *
 *  Created on: 2016/09/17
 *      Author: Gen
 */

#ifndef PARAMETER_H_
#define PARAMETER_H_

/****************************************
機体パラメータ
 ****************************************/
//機体長さ(m)
#define LENGTH 0.092
//機体幅(m)
#define WIDTH 0.069
//機体重量(kg)
#define MASS 0.105
//輪距(m)
#define TREAD 0.065
//タイヤ直径(m)
#define DIAMETER_L 0.0208
#define DIAMETER_R 0.0208
//ギア歯数
#define PINION 9.0
#define SPUR 35.0
//ギヤ比
#define GEAR_RATIO 3.888888888888
//エンコーダ分解能
#define ENC_RESO 4096
/****************************************
制御パラメータ
 ****************************************/
//速度P制御
#define VELO_P 220
//速度I制御
#define VELO_I 1000
//角速度P制御
#define ANG_VELO_P 5
//角速度I制御
#define ANG_VELO_I 2

#endif /* PARAMETER_H_ */