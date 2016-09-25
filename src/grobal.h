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

//目標速度

extern volatile floatLR_t g_target_velo;

//現在速度
extern volatile floatLR_t g_current_velo;

//現在偏差
extern volatile floatLR_t g_current_error;

//偏差積分
extern volatile floatLR_t g_error_integral;

//フラグ
extern volatile int8_t g_flag_mode_setting;

//テスト用
extern volatile int16_t g_wait_counter;
extern volatile int16_t g_test_count;
extern volatile float g_test_array[5000];
extern volatile float g_test_array2[5000];
extern volatile int8_t g_test_flag;


#endif /* GROBAL_H_ */
