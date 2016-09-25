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
 エンコーダ1ms差分取得
 ****************************************/
int32_t returnEncoderDiffL(void);
int32_t returnEncoderDiffR(void);
/****************************************
 速度返す
 ****************************************/
float returnVelocityL(void);

float returnVelocityR(void);
/****************************************
 エンコーダカウント方向
 ****************************************/
int8_t returnCountDirL(void);
int8_t returnCountDirR(void);
/****************************************
 P制御
 ****************************************/
float controlProportionL(float kp);
float controlProportionR(float kp);
/****************************************
 I制御
 ****************************************/
float controlIntegralL(float ki);
float controlIntegralR(float ki);

#endif /* RUN_H_ */
