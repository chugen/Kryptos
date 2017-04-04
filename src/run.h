/*
 * run.h
 *
 *  Created on: 2016/09/19
 *      Author: Gen
 */

#ifndef RUN_H_
#define RUN_H_

#include "my_typedef.h"
/****************************************
 吸引
 ****************************************/
int8_t driveSuction(int16_t duty, int8_t on_off);
/****************************************
 モータ駆動
 ****************************************/
int8_t driveMotor(int8_t on_off);
/****************************************
 モータ デューティーセット
 ****************************************/
int16_t setMotorDutyL(float duty);
int16_t setMotorDutyR(float duty);
/****************************************
 モータ 　CW/CCW
 ****************************************/
int8_t setMotorDirL(int8_t cw_ccw);
int8_t setMotorDirR(int8_t cw_ccw);

/****************************************
 速度返す
 ****************************************/
float returnVelocityL(void);

float returnVelocityR(void);

/****************************************
 速度P制御
 ****************************************/
float ctrlPropVelocity(float kp);

/****************************************
 速度I制御
 ****************************************/
float ctrlIntVelocity(float ki);

/****************************************
 角速度P制御
 ****************************************/
float ctrlPropOmega(float kp);

/****************************************
 角速度I制御
 ****************************************/
float ctrlIntOmega(float ki);
/****************************************
 角速度D制御
 ****************************************/
float ctrlDeriOmega(float kd);
/****************************************
 角速度比例定数変更
 ****************************************/
float changeOmegaCtrlConst(float value);
/****************************************
 角度P制御
 ****************************************/
float ctrlPropAngle(float kp);
/****************************************
 角度I制御
 ****************************************/
float ctrlIntAngle(float ki);
/****************************************
 壁制御
 ****************************************/
float ctrlWall(float kp);
float ctrlWallFrontAng(float kp);
float ctrlWallFrontDis(float kp);
/****************************************
フィードフォワード制御
 ****************************************/
float ctrlFeedForwardL(float accele,float alpha);
float ctrlFeedForwardR(float accele,float alpha);
/****************************************
 走行初期化
 ****************************************/
void initRun(void);
/****************************************
 台形加速
 ****************************************/
void runStraight(float t_acc, float t_dis, float t_max_velo, float t_end_velo);
/****************************************
 台形加速(探索)
 ****************************************/
void runStraightSearch(float dis, float velo);
/****************************************
袋小路
 ****************************************/
void runBlindAlley(float velo);
/****************************************
 スラローム　大廻
 ****************************************/

void turnCorner(turn_t *p);
/****************************************
 スラローム　連続
 ****************************************/
void turnCornerContinuous(float degree, float omega);
#endif /* RUN_H_ */
