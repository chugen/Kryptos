/*
 * grobal.c
 *
 *  Created on: 2016/09/19
 *      Author: Gen
 */
#include <stdint.h>
#include "my_typedef.h"
#include "grobal.h"


/****************************************
 グローバル変数定義
 ****************************************/
//モード選択用速度取得変数
volatile float g_mode_velo;

//目標速度
volatile floatLR_t g_target_velo;

//現在速度
volatile floatLR_t g_current_velo;

//現在偏差
volatile floatLR_t g_current_error;

//偏差積分
volatile floatLR_t g_error_integral;

//フラグ
volatile int8_t g_flag_mode_setting = 0;
//テスト用
volatile int16_t g_wait_counter = 0; //waitTime関数用カウンタ
volatile int16_t g_test_count = 0;
volatile float g_test_array[5000];
volatile float g_test_array2[5000];

volatile int8_t g_test_flag = 0;
