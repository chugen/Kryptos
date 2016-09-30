/*
 * run.h
 *
 *  Created on: 2016/09/19
 *      Author: Gen
 */

#ifndef RUN_H_
#define RUN_H_

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
 台形加速
 ****************************************/
void accTrape(float t_acc, float t_dis, float t_max_velo, float t_end_velo);
/****************************************
 スラローム　大廻
 ****************************************/
void turn90Wide(float s_angacc, float s_angle, float s_max_angvelo,
		float c_velo);
#endif /* RUN_H_ */
