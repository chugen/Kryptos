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
float ctrlIntVelocityL(float ki);

/****************************************
 角速度P制御
 ****************************************/
float ctrlPropAngularVelocity(float kp);

/****************************************
 角速度I制御
 ****************************************/
float ctrlIntAngularVelocity(float ki);
/****************************************
 壁制御
 ****************************************/
float ctrlWall(float kp);

/****************************************
 台形加速
 ****************************************/
void runStraight(float t_acc, float t_dis, float t_max_velo, float t_end_velo);
/****************************************
 スラローム　大廻
 ****************************************/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//スラロームパラメータ				{度,alpha,M_omega,v,front,rear,dia}
extern const turn_t turn_90_L ;
extern const turn_t turn_90_R ;

extern const turn_t turn_90_wide_L ;
extern const turn_t turn_90_wide_R ;

extern const turn_t pivot;
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void turnCorner(turn_t p_turn);

#endif /* RUN_H_ */
