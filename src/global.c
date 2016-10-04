/*
 * global.c
 *
 *  Created on: 2016/10/02
 *      Author: Gen
 */

#include <stdint.h>
#include "my_typedef.h"
#include "global.h"
#include "common.h"

/****************************************
 グローバル変数定義
 ****************************************/
//モード選択用速度取得変数
volatile float g_mode_velo;
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//目標速度
volatile float g_target_velo = 0;
//現在速度
volatile float g_current_velo;
//現在偏差
volatile float g_current_velo_error;
//偏差積分
volatile float g_velo_error_integral;
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//目標角速度
volatile float g_target_angularvelo = 0;
//現在角速度
volatile float g_current_angularvelo;
//現在偏差
volatile float g_current_angularvelo_error;
//偏差積分
volatile float g_angularvelo_error_integral;
//Gyro　リファレンス
volatile float g_gyro_reference;
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//距離
volatile float g_distance;
//加速度
volatile float g_accele;
//角度
volatile float g_angle;
//角加速度
volatile float g_angularaccele;
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//センサ
volatile int32_t g_sensor_FL;
volatile int32_t g_sensor_FR;
volatile int32_t g_sensor_L;
volatile int32_t g_sensor_R;

volatile int32_t g_sensor_L_derivative;
volatile int32_t g_sensor_R_derivative;
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//フラグ
volatile int8_t g_flag_mode_setting = 0;
volatile int8_t g_test_flag = 0;
//テスト用
volatile int16_t g_wait_count = 0; //waitTime関数用カウンタ
volatile int16_t g_log_count = 0;
volatile float g_log_array[LOG_TIMES];
volatile float g_log_array2[LOG_TIMES];


