/*
 * global.h
 *
 *  Created on: 2016/10/02
 *      Author: Gen
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include "my_typedef.h"

/****************************************
 グローバル変数extern宣言
 ****************************************/
//モード選択用速度取得変数
extern volatile float g_mode_velo;
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//目標速度
extern volatile float g_target_velo;
//現在速度
extern volatile float g_current_velo;
//現在偏差
extern volatile float g_current_velo_error;
//偏差積分
extern volatile float g_velo_error_integral;
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//目標角速度
extern volatile float g_target_angularvelo;

//現在角速度
extern volatile float g_current_angularvelo;

//現在偏差
extern volatile float g_current_angularvelo_error;

//偏差積分
extern volatile float g_angularvelo_error_integral;

//Gyro　リファレンス
extern volatile float g_gyro_reference;
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//距離
extern volatile float g_distance;
//加速度
extern volatile float g_accele;
//角度
extern volatile float g_angle;
//各加速度
extern volatile float g_angularaccele;
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//センサ
extern volatile int32_t g_sensor_FL;
extern volatile int32_t g_sensor_FR;
extern volatile int32_t g_sensor_L;
extern volatile int32_t g_sensor_R;

extern volatile int32_t g_sensor_L_derivative;
extern volatile int32_t g_sensor_R_derivative;
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//フラグ
extern volatile int8_t g_flag_mode_setting;

//テスト用
extern volatile int16_t g_wait_count;
extern volatile int16_t g_log_count;
extern volatile float g_log_array[];
extern volatile float g_log_array2[];
extern volatile int8_t g_test_flag;

#endif /* GLOBAL_H_ */
