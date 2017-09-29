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
volatile float g_target_omega = 0;
volatile float g_target_omega_max = 0;
//現在角速度
volatile float g_current_omega;
volatile float g_current_omega_tmp;//リファレンス補正前
//現在偏差
volatile float g_omega_error;
//偏差積分
volatile float g_omega_error_integral;
//偏差微分
volatile float g_omega_error_derivative;
//Gyro リファレンス
volatile float g_gyro_reference;
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//目標角度
volatile float g_target_angle;
volatile float g_target_angle_const;
volatile float g_count_time_angle;
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
volatile float g_target_alpha;//現在角加速度
volatile float g_alpha_max;//最高角加速度
volatile float g_turn_peaktime;//最高角速度到達時間

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//センサ
volatile int32_t g_sensor_FL;
volatile int32_t g_sensor_FR;
volatile int32_t g_sensor_L;
volatile int32_t g_sensor_R;

volatile float g_sensor_FL_average;
volatile float g_sensor_FR_average;

volatile int32_t g_sensor_L_derivative;
volatile int32_t g_sensor_R_derivative;
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//バッテリー電圧
volatile float g_battery_voltage;
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//エンコーダ差分
volatile float g_encoder_diff_L;
volatile float g_encoder_diff_R;
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
volatile float g_torque_L;
volatile float g_torque_R;
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//map
uint8_t g_orient = 1;
volatile uint8_t g_current_x = 0;
volatile uint8_t g_current_y = 0;

wall_t g_wall_info[15];
wall_t g_wall_info_tmp[15];

step_t g_step[16];

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
volatile int8_t g_flag_shortest_goal;
volatile int8_t g_flag_turn_continuous=0;
volatile int8_t g_flag_FF=0;
volatile int8_t g_flag_buzzer=0;

//テスト用
volatile float g_duty_L;
volatile float g_duty_R;

volatile int16_t g_wait_count = 0; //waitTime関数用カウンタ
volatile int16_t g_buzzer_count = 0; //ブザー関数用カウンタ
volatile int16_t g_log_count = 0;
volatile float g_log_array[LOG_TIMES];
volatile float g_log_array2[LOG_TIMES];
volatile float g_log_array3[LOG_TIMES];
volatile float g_log_array4[LOG_TIMES];
//volatile int16_t g_log_array_int[LOG_TIMES];
//volatile int16_t g_log_array2_int[LOG_TIMES];
volatile int16_t g_log_array_int[1];
volatile int16_t g_log_array2_int[1];

volatile uint16_t g_path_test[256];
volatile uint16_t g_path_test_slant[256];

