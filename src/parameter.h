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
#define DIAMETER_L 0.0219//0.0218
#define DIAMETER_R 0.0219//0.0218
//ギア歯数
#define PINION 9.0
#define SPUR 35.0
//ギヤ比
#define GEAR_RATIO 3.888888888888
//エンコーダ分解能
#define ENC_RESO 4096
//最高電圧
#define MAX_VOLTAGE 8.4
//初期距離
#define INIT_DIS 0.054
//袋小路脱出距離
#define BLIND_ALLEY 0.024
/****************************************
 制御パラメータ
 ****************************************/
//リファレンス
#define SEN_REFERENCE_L 510//535//430//400//430//470//525//500
#define SEN_REFERENCE_R 580//520//480//550//520//520
#define SEN_REFERENCE_FL 1000//980//1000//1030//1030
#define SEN_REFERENCE_FR 392//410//395//400//410
/*==========*/
#define SEN_DIAGONAL_FL 70
#define SEN_DIAGONAL_FR 70
//変化量
#define SEN_DERIVATIVE_L 5//13
#define SEN_DERIVATIVE_R 5//13
//制御閾値
#define SEN_THRESHOLD_L 400
#define SEN_THRESHOLD_R 410
//壁有無判定基準値
#define SEN_NOWALL_L 170
#define SEN_NOWALL_R 200
#define SEN_NOWALL_FL 75//160
#define SEN_NOWALL_FR 65
//死亡判定
#define SEN_DEATH 1600
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//速度P制御
#define VELO_P 220
//速度I制御
#define VELO_I 10
//角速度P制御
#define ANG_VELO_P 200//160
//角速度I制御
#define ANG_VELO_I 5//1
//角度P制御
#define ANG_P 0.01
//角度I制御
#define ANG_I 0.1//0.02

//壁制御
#define WALL_P 0.3
#define WALL_HIGH_SPEED 0.08
#define WALL_FRONT_ANG 0.07
#define WALL_FRONT_DIS 0.1



#endif /* PARAMETER_H_ */

