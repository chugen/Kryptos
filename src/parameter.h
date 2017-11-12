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
//慣性モーメント(kg・m^2)
#define INERTIA 0.00030//0.00043//0.00011571875
//タイヤ直径(m)
#define DIAMETER_L 0.02175//0.02160//0.0219//0.0218
#define DIAMETER_R 0.02220//0.02230//0.0219//0.0218
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
/*モータ特性-------------------*/
//端子間抵抗(Ω)
#define MOTOR_RESISTANCE 1.07
//逆起電圧定数(V/rpm)
#define MOTOR_BACK_EMF 0.000207
//トルク定数(Nm/A)
#define MOTOR_TORQUE 0.00198
//定数(Nm/rpm)
#define MOTOR_CONST_TORQUE 0.00000094
/****************************************
 制御パラメータ
 ****************************************/
//ローパスフィルタ定数
#define SEN_LOWPASS 0.8

//リファレンス
#define SEN_REFERENCE_L 456//
#define SEN_REFERENCE_R 464//
//前壁制御
#define SEN_REFERENCE_FL 975//
#define SEN_REFERENCE_FR 913//

#define SEN_REFERENCE_FL_L 971//
#define SEN_REFERENCE_FR_L 904//

#define SEN_REFERENCE_FL_R 967//
#define SEN_REFERENCE_FR_R 780//
/*==========*/
#define SEN_DIAGONAL_FL 70
#define SEN_DIAGONAL_FR 70
//変化量
#define SEN_DERIVATIVE_L 3//5//13
#define SEN_DERIVATIVE_R 3//5//13
//制御閾値
#define SEN_THRESHOLD_L 400
#define SEN_THRESHOLD_R 410
//壁有無判定基準値
#define SEN_NOWALL_L 240//170
#define SEN_NOWALL_R 240
#define SEN_NOWALL_FL 130//75//160
#define SEN_NOWALL_FR 120//65
//死亡判定
#define SEN_DEATH 1600
//壁切れ判定変化量
#define SEN_PILLAR_EDGE_L -45//-50//-100
#define SEN_PILLAR_EDGE_R -50//-50//-100

#define SEN_PILLAR_EDGE_SEARCH_L -20//-40
#define SEN_PILLAR_EDGE_SEARCH_R -22//-40
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//速度P制御
#define VELO_P 220
//速度I制御
#define VELO_I 10

//角速度P制御
#define ANG_VELO_P 200//250.0
//角速度I制御
#define ANG_VELO_I 6.0
//角速度D制御
#define ANG_VELO_D 30//20//5.0
//角速度P制御
#define ANG_FASTVELO_P 300.0
//角速度I制御
#define ANG_FASTVELO_I 13.0
//角速度D制御
#define ANG_FASTVELO_D 70.0

//角度P制御
#define ANG_P 0//1//0.01
//角度I制御
#define ANG_I 0//10//0.7//0.02

//壁制御
#define WALL_P 0.3//0.7//0.3
#define WALL_HIGH_SPEED 0.08
#define WALL_FRONT_ANG 0.02//0.05//0.07
#define WALL_FRONT_DIS 0.05//0.01//0.08//0.1
/*Interrupt*/
#define INTRPT_PERIOD 0.0005
#define INTRPT_MS 0.001/INTRPT_PERIOD
#define INTRPT_FREQENCY 2000
/****************************************
 ターンパラメータ
 ****************************************/
/*others~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
extern turn_t pivot;
extern turn_t pivot_90_L;
extern turn_t pivot_90_R;

extern turn_t t_test;
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
extern turn_t t_90_L_05;
extern turn_t t_90_R_05;
/*1000~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
extern turn_t t_w90_L_10;
extern turn_t t_w90_R_10;
extern turn_t t_180_L_10;
extern turn_t t_180_R_10;
extern turn_t t_i45_L_10;
extern turn_t t_i45_R_10;
extern turn_t t_o45_L_10;
extern turn_t t_o45_R_10;
extern turn_t t_i135_L_10;
extern turn_t t_i135_R_10;
extern turn_t t_o135_L_10;
extern turn_t t_o135_R_10;
extern turn_t t_v90_L_10;
extern turn_t t_v90_R_10;
/*1200~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
extern turn_t t_w90_L_12;
extern turn_t t_w90_R_12;
extern turn_t t_180_L_12;
extern turn_t t_180_R_12;
extern turn_t t_i45_L_12;
extern turn_t t_i45_R_12;
extern turn_t t_o45_L_12;
extern turn_t t_o45_R_12;
extern turn_t t_i135_L_12;
extern turn_t t_i135_R_12;
extern turn_t t_o135_L_12;
extern turn_t t_o135_R_12;
extern turn_t t_v90_L_12;
extern turn_t t_v90_R_12;
/*1400~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
extern turn_t t_w90_L_14;
extern turn_t t_w90_R_14;
extern turn_t t_180_L_14;
extern turn_t t_180_R_14;
extern turn_t t_i45_L_14;
extern turn_t t_i45_R_14;
extern turn_t t_o45_L_14;
extern turn_t t_o45_R_14;
extern turn_t t_i135_L_14;
extern turn_t t_i135_R_14;
extern turn_t t_o135_L_14;
extern turn_t t_o135_R_14;
extern turn_t t_v90_L_14;
extern turn_t t_v90_R_14;
/*1600~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
extern turn_t t_w90_L_16;
extern turn_t t_w90_R_16;
extern turn_t t_180_L_16;
extern turn_t t_180_R_16;
extern turn_t t_i45_L_16;
extern turn_t t_i45_R_16;
extern turn_t t_o45_L_16;
extern turn_t t_o45_R_16;
extern turn_t t_i135_L_16;
extern turn_t t_i135_R_16;
extern turn_t t_o135_L_16;
extern turn_t t_o135_R_16;
extern turn_t t_v90_L_16;
extern turn_t t_v90_R_16;
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
extern turn_t t_w90_R_1500;
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/****************************************
 ターンパラメータ
 ****************************************/
/*others~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
extern turn2_t tc_pivot;
extern turn2_t tc_pivot_90_L;
extern turn2_t tc_pivot_90_R;

extern turn2_t tc_test;
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
extern turn2_t tc_90_L_07;
extern turn2_t tc_90_R_07;
/*1000~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
extern turn2_t tc_w90_L_10;
extern turn2_t tc_w90_R_10;
extern turn2_t tc_180_L_10;
extern turn2_t tc_180_R_10;
extern turn2_t tc_i45_L_10;
extern turn2_t tc_i45_R_10;
extern turn2_t tc_o45_L_10;
extern turn2_t tc_o45_R_10;
extern turn2_t tc_i135_L_10;
extern turn2_t tc_i135_R_10;
extern turn2_t tc_o135_L_10;
extern turn2_t tc_o135_R_10;
extern turn2_t tc_v90_L_10;
extern turn2_t tc_v90_R_10;
/*1200~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
extern turn2_t tc_w90_L_12;
extern turn2_t tc_w90_R_12;
extern turn2_t tc_180_L_12;
extern turn2_t tc_180_R_12;
extern turn2_t tc_i45_L_12;
extern turn2_t tc_i45_R_12;
extern turn2_t tc_o45_L_12;
extern turn2_t tc_o45_R_12;
extern turn2_t tc_i135_L_12;
extern turn2_t tc_i135_R_12;
extern turn2_t tc_o135_L_12;
extern turn2_t tc_o135_R_12;
extern turn2_t tc_v90_L_12;
extern turn2_t tc_v90_R_12;
/*1400~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
extern turn2_t tc_w90_L_14;
extern turn2_t tc_w90_R_14;
extern turn2_t tc_180_L_14;
extern turn2_t tc_180_R_14;
extern turn2_t tc_i45_L_14;
extern turn2_t tc_i45_R_14;
extern turn2_t tc_o45_L_14;
extern turn2_t tc_o45_R_14;
extern turn2_t tc_i135_L_14;
extern turn2_t tc_i135_R_14;
extern turn2_t tc_o135_L_14;
extern turn2_t tc_o135_R_14;
extern turn2_t tc_v90_L_14;
extern turn2_t tc_v90_R_14;
/*1600~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
extern turn2_t tc_w90_L_16;
extern turn2_t tc_w90_R_16;
extern turn2_t tc_180_L_16;
extern turn2_t tc_180_R_16;
extern turn2_t tc_i45_L_16;
extern turn2_t tc_i45_R_16;
extern turn2_t tc_o45_L_16;
extern turn2_t tc_o45_R_16;
extern turn2_t tc_i135_L_16;
extern turn2_t tc_i135_R_16;
extern turn2_t tc_o135_L_16;
extern turn2_t tc_o135_R_16;
extern turn2_t tc_v90_L_16;
extern turn2_t tc_v90_R_16;
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
extern turn2_t tc_w90_R_1500;
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/****************************************
 ターン種類保存配列
 ****************************************/
extern turn_t * t10[];
extern turn_t * t12[];
extern turn_t * t14[];
extern turn_t * t16[];
extern turn_t * t18[];
//continuous
extern turn2_t * tc10[];
extern turn2_t * tc12[];
extern turn2_t * tc14[];
extern turn2_t * tc16[];
extern turn2_t * tc18[];
/****************************************
 ターン速度保存配列
 ****************************************/
extern turn_t ** t_para[];
extern turn2_t ** tc_para[];

enum TURN_VELO {
	T10, T12, T14, T16, T18
};

enum TURN_TYPE {
	W90L,
	W90R,
	T180L,
	T180R,
	I45L,
	I45R,
	O45L,
	O45R,
	I135L,
	I135R,
	O135L,
	O135R,
	V90L,
	V90R
};

#endif /* PARAMETER_H_ */

