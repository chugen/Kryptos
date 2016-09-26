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
//機体長さ(mm)
#define LENGTH 92.0
//機体幅(mm)
#define WIDTH 69.0
//機体重量(g)
#define MASS 105.0
//輪距(mm)
#define TREAD 65.0
//タイヤ直径(mm)
#define DIAMETER_L 21.0
#define DIAMETER_R 21.0
//ギア歯数
#define PINION 9.0
#define SPUR 35.0
//ギヤ比
#define GEAR_RATIO 3.888888888888
//エンコーダ分解能
#define ENC_RESO 4096

#endif /* PARAMETER_H_ */

/****************************************
制御パラメータ
 ****************************************/
//速度P制御
#define VELO_P 220
//速度I制御
#define VELO_I 300
//角速度P制御
#define ANG_VELO_P 0.05
//角速度I制御
#define ANG_VELO_I 0.01
