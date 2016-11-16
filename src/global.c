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
volatile float g_velo_error;
//偏差積分
volatile float g_velo_error_integral;
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//目標角速度
volatile float g_target_angularvelo = 0;
//現在角速度
volatile float g_current_angularvelo;

//現在偏差
volatile float g_angularvelo_error;
//偏差積分
volatile float g_angularvelo_error_integral;
//Gyro　リファレンス
volatile float g_gyro_reference;
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//目標角度
volatile float g_target_angle;
//現在角度
volatile float g_current_angle;
//現在偏差
volatile float g_angle_error;
//偏差積分
volatile float g_angle_error_integral;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//距離
volatile float g_distance;
//加速度
volatile float g_accele;

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
//map
volatile uint8_t g_orient = 1;
volatile uint8_t g_current_x = 0;
volatile uint8_t g_current_y = 0;
volatile uint8_t g_wall_data_temp[16][16];
volatile uint8_t g_wall_data[16][16];

volatile int16_t g_target_x = 1;
volatile int16_t g_target_y = 0;
volatile uint8_t g_step_map[16][16];
volatile uint16_t g_path[1024];
volatile uint16_t g_path_2[1024];
volatile uint16_t g_path_3[256];

volatile uint8_t g_flag_step_goal;
volatile uint8_t g_flag_step_goal_2;
volatile uint8_t g_flag_step_goal_3;
volatile uint8_t g_flag_curve = 0;
volatile uint8_t g_flag_gap = 0;
volatile uint8_t g_flag_adachi_goal = 0;
volatile uint8_t g_flag_path_run_goal = 0;
volatile uint8_t g_flag_diagonal = 0;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//フラグ
volatile int8_t g_flag_mode_setting = 0;
volatile int8_t g_flag_control = 0;
volatile int8_t g_flag_turn;
volatile int8_t g_flag_failsafe = 0;
volatile int8_t g_flag_blindalley = 0;
volatile int8_t g_flag_circuit = 0;
volatile int8_t g_flag_run_mode=0; //0:デフォルト,1:探索,2:最短
volatile int8_t g_flag_pillar_edge_L=0;
volatile int8_t g_flag_pillar_edge_R=0;

//テスト用
volatile float g_duty_L;
volatile float g_duty_R;

volatile int16_t g_wait_count = 0; //waitTime関数用カウンタ
volatile int16_t g_log_count = 0;
volatile float g_log_array[LOG_TIMES];
volatile float g_log_array2[LOG_TIMES];
volatile int16_t g_log_array_int[LOG_TIMES];
volatile int16_t g_log_array2_int[LOG_TIMES];

volatile uint16_t g_path_test[256];
volatile uint16_t g_path_test_slant[256];

