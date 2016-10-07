/*
 * parameter.h
 *
 *  Created on: 2016/09/17
 *      Author: Gen
 */

#include "my_typedef.h"

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
//最高電圧
#define MAX_VOLTAGE 8.4

/****************************************
 制御パラメータ
 ****************************************/
//リファレンス
#define SEN_REFERENCE_L 500
#define SEN_REFERENCE_R 520
//変化量
#define SEN_DERIVATIVE_L 5
#define SEN_DERIVATIVE_R 5
//制御閾値
#define SEN_THRESHOLD_L 400
#define SEN_THRESHOLD_R 400
//壁有無判定基準値
#define SEN_NOWALL_L 260
#define SEN_NOWALL_R 260
#define SEN_NOWALL_FL 100
#define SEN_NOWALL_FR 80
//死亡判定
#define SEN_DEATH 1750
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//速度P制御
#define VELO_P 220
//速度I制御
#define VELO_I 1000
//角速度P制御
#define ANG_VELO_P 160
//角速度I制御
#define ANG_VELO_I 1
//壁制御
#define WALL_P 0.05




#endif /* PARAMETER_H_ */

