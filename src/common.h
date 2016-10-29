/*
 * common.hpp
 *
 *  Created on: 2016/06/26
 *      Author: 元太
 */

#ifndef COMMON_HPP_
#define COMMON_HPP_
/****************************************
 定数定義
 ****************************************/
#define LEFT 0
#define RIGHT 1

#define OFF 0
#define ON 1

#define READ 1
#define WRITE 0

#define FORWARD 0
#define BACKWARD 1

#define LOG_TIMES 1500

#define SECTION 0.18
#define HALF_SECTION 0.09

#define M_PI 3.141592653589793
#define M_SQRT2 1.41421356237
/****************************************
 map関連
 ****************************************/
#define NORTH 0x01
#define WEST 0x02
#define SOUTH 0x04
#define EAST 0x08

#define START_X 0
#define START_Y 0
#define GOAL_X  7
#define GOAL_Y 7
/****************************************
 path
 ****************************************/
//一次path
#define STRAIGHT 0x01
#define L_CURVE 0x02
#define R_CURVE 0x04
#define ERROR 0x08
//2次path
#define S_L_CURVE 31
#define S_BIG_L_CURVE 32
#define S_R_CURVE 33
#define S_BIG_R_CURVE 34
#define S_U_L_CURVE 35
#define S_U_R_CURVE 36
//斜め系
#define L_45_I 37
#define L_45_O 38
#define R_45_I 39
#define R_45_O 40
#define L_135_I 41
#define L_135_O 42
#define R_135_I 43
#define R_135_O 44
#define L_V90 45
#define R_V90 46
#define DIAGONAL 47
/****************************************
 色定義
 ****************************************/
#define RED 100,0,0
#define GREEN 0,100,0
#define BLUE 0,0,100
#define YELLOW 100,100,0
#define CYAN 0,100,100
#define MAGENTA 100,0,100
#define WHITE 100,100,100
#define WATER 0,30,100
#define ORANGE 100,50,0
#define LBLUE 30,30,100
#define LRED 100,30,30
#define RGB_OFF 0,0,0
/****************************************
 Gyro(MPU-6000)レジスタ定義
 ****************************************/
#define WHO_AM_I 0x75
#define USER_CTRL 0x6A
#define SIGNAL_PATH_RESET 0x68
#define GYRO_CONFIG 0x1B
#define ACCEL_CONFIG 0x1C
#define GYRO_ZOUT_L 0x48
#define GYRO_ZOUT_H 0x47
#define ACCEL_XOUT_L 0x3B
#define ACCEL_XOUT_H 0x3C
#define ACCEL_YOUT_L 0x3E
#define ACCEL_YOUT_H 0x3D
#define PWR_MGMT_1 0x6B
#define PWR_MGMT_2 0x6C
/****************************************
 Flash関連
 ****************************************/
#define TE16K 100000
#define P_E 0

#define PROGRAM_S1 0xE8
#define PROGRAM_S2 0x01
#define PROGRAM_END 0xD0

#define ERASE_S1 0x20
#define ERASE_S2 0xD0

#define STATUS_CLEAR 0x50

#define BLANK_CHECK_S1 0x71
#define BLANK_CHECK_S2 0xD0

/****************************************
 センサー
 ****************************************/
#define SEN_L 3
#define SEN_FL 2
#define SEN_FR 1
#define SEN_R 0

#define FR_L 1
#define FL_R 2

/****************************************
 周波数定義
 ****************************************/
#define BZ_C0 	16.35
#define BZ_CS0  17.32
#define BZ_D0 	18.35
#define BZ_DS0  19.45
#define BZ_E0 	20.6
#define BZ_F0 	21.83
#define BZ_FS0  23.12
#define BZ_G0 	24.5
#define BZ_GS0  25.96
#define BZ_A0 	27.5
#define BZ_AS0  29.14
#define BZ_B0 	30.87
#define BZ_C1 	32.7
#define BZ_CS1  34.65
#define BZ_D1 	36.71
#define BZ_DS1  38.89
#define BZ_E1 	41.2
#define BZ_F1 	43.65
#define BZ_FS1  46.25
#define BZ_G1 	49
#define BZ_GS1  51.91
#define BZ_A1 	55
#define BZ_AS1  58.27
#define BZ_B1 	61.74
#define BZ_C2 	65.41
#define BZ_CS2  69.3
#define BZ_D2 	73.42
#define BZ_DS2  77.78
#define BZ_E2 	82.41
#define BZ_F2 	87.31
#define BZ_FS2  92.5
#define BZ_G2 	98
#define BZ_GS2  103.83
#define BZ_A2 	110
#define BZ_AS2  116.54
#define BZ_B2 	123.47
#define BZ_C3 	130.81
#define BZ_CS3  138.59
#define BZ_D3 	146.83
#define BZ_DS3  155.56
#define BZ_E3 	164.81
#define BZ_F3 	174.61
#define BZ_FS3  185
#define BZ_G3 	196
#define BZ_GS3  207.65
#define BZ_A3 	220
#define BZ_AS3  233.08
#define BZ_B3 	246.94
#define BZ_C4 	261.63
#define BZ_CS4  277.18
#define BZ_D4 	293.66
#define BZ_DS4  311.13
#define BZ_E4 	329.63
#define BZ_F4 	349.23
#define BZ_FS4  369.99
#define BZ_G4 	392
#define BZ_GS4  415.3
#define BZ_A4 	440
#define BZ_AS4  466.16
#define BZ_B4 	493.88
#define BZ_C5 	523.25
#define BZ_CS5  554.37
#define BZ_D5 	587.33
#define BZ_DS5  622.25
#define BZ_E5 	659.26
#define BZ_F5 	698.46
#define BZ_FS5  739.99
#define BZ_G5   783.99
#define BZ_GS5  830.61
#define BZ_A5   880
#define BZ_AS5  932.33
#define BZ_B5   987.77
#define BZ_C6   1046.5
#define BZ_CS6  1108.73
#define BZ_D6   1174.66
#define BZ_DS6  1244.51
#define BZ_E6   1318.51
#define BZ_F6   1396.91
#define BZ_FS6  1479.98
#define BZ_G6   1567.98
#define BZ_GS6  1661.22
#define BZ_A6   1760
#define BZ_AS6  1864.66
#define BZ_B6   1975.53
#define BZ_C7   2093
#define BZ_CS7  2217.46
#define BZ_D7   2349.32
#define BZ_DS7  2489.02
#define BZ_E7   2637.02
#define BZ_F7   2793.83
#define BZ_FS7  2959.96
#define BZ_G7   3135.96
#define BZ_GS7  3322.44
#define BZ_A7   3520
#define BZ_AS7  3729.31
#define BZ_B7   3951.07
#define BZ_C8   4186.01
#define BZ_CS8  4434.92
#define BZ_D8   4698.64
#define BZ_DS8  4978.03
#define BZ_E8   5274.04
#define BZ_F8   5587.65
#define BZ_FS8  5919.91
#define BZ_G8   6271.93
#define BZ_GS8  6644.88
#define BZ_A8   7040
#define BZ_AS8  7458.62
#define BZ_B8   7902.13
#define BZ_C9   8372.02
#define BZ_CS9  8869.84
#define BZ_D9   9397.27
#define BZ_DS9  9956.06
#define BZ_E9   10548.08
#define BZ_F9   11175.3
#define BZ_FS9  11839.82
#define BZ_G9   12543.85
#define BZ_GS9  13289.75
#define BZ_A9   14080
#define BZ_AS9  14917.24
#define BZ_B9   15804.27
#define BZ_C10  16744.04

#endif /* COMMON_HPP_ */
