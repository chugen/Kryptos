/*
 * grobal.h
 *
 *  Created on: 2016/09/19
 *      Author: Gen
 */

#ifndef GROBAL_H_
#define GROBAL_H_

#include "my_typedef.h"

/****************************************
 グローバル変数extern宣言
 ****************************************/
//モード選択用速度取得変数
extern volatile float g_mode_velo;
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//目標速度
extern volatile floatLR_t g_target_velo;
extern volatile float g_target_gcenter_velo;

//現在速度
extern volatile floatLR_t g_current_velo;
extern volatile float g_current_gcenter_velo;
//現在偏差
extern volatile floatLR_t g_current_velo_error;
extern volatile float g_current_gcenter_velo_error;
//偏差積分
extern volatile floatLR_t g_velo_error_integral;
extern volatile float g_gcenter_velo_error_integral;
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

//フラグ
extern volatile int8_t g_flag_mode_setting;

//テスト用
extern volatile int16_t g_wait_counter;
extern volatile int16_t g_test_count;
extern volatile float g_test_array[5000];
extern volatile float g_test_array2[5000];
extern volatile int8_t g_test_flag;

#endif /* GROBAL_H_ */
