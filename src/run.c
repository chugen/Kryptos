/*
 * run.c
 *
 *  Created on: 2016/09/19
 *      Author: Gen
 */
#include <stdint.h>
#include <mathf.h>
#include "app.h"
#include "run.h"
#include "iodefine.h"
#include "init.h"
#include "intrpt.h"
#include "global.h"
#include "parameter.h"
#include "common.h"
#include "sensor.h"
#include "my_typedef.h"
/****************************************
 吸引
 ****************************************/
int8_t driveSuction(int16_t duty, int8_t on_off) {
	if (on_off == 0) {

		TPU5.TGRA = 0;
		TPU5.TGRB = 100;

		TPU5.TIOR.BIT.IOA = 0x00;	//出力禁止
		TPUA.TSTR.BIT.CST5 = 0;
	} else {
		TPU5.TIOR.BIT.IOA = 0x02;	//初期出力：H,コンペアマッチ：L
		TPU5.TGRA = 100 - duty;
		TPU5.TGRB = 100;
		TPUA.TSTR.BIT.CST5 = 1;
	}

	return 0;
}
/****************************************
 モータ駆動
 ****************************************/
int8_t driveMotor(int8_t on_off) {

	if (on_off == 1) {
		PORTC.PODR.BIT.B6 = 1; //STBY
		MTU.TSTR.BIT.CST0 = 1;
	} else {
		g_target_velo = 0;
		waitTime(500);
		PORTC.PODR.BIT.B6 = 0; //STBY
	}

	return 0;
}

/****************************************
 モータ デューティーセット
 ****************************************/
int16_t setMotorDutyL(float duty) {
	float voltage_temp;
	if (duty < 0) {
		setMotorDirL(BACKWARD);
		duty *= -1;
	} else {
		setMotorDirL(FORWARD);
	}
	if (duty >= 99) {
		duty = 99;
	}

	g_duty_L = duty;

	voltage_temp = MAX_VOLTAGE / g_battery_voltage;
	MTU0.TGRC = (int16_t) (250 * duty / 100 * voltage_temp);	//MOTOR_L
	return (int16_t) (250 * duty / 100 * voltage_temp);
}
int16_t setMotorDutyR(float duty) {
	float voltage_temp;
	if (duty < 0) {
		setMotorDirR(BACKWARD);
		duty *= -1;
	} else {
		setMotorDirR(FORWARD);
	}
	if (duty >= 99) {
		duty = 99;
	}

	g_duty_R = duty;

	voltage_temp = MAX_VOLTAGE / g_battery_voltage;
	MTU0.TGRA = (int16_t) (250 * duty / 100 * voltage_temp);	//MOTOR_R
	return (int16_t) (250 * duty / 100 * voltage_temp);
}
/****************************************
 モータ CW/CCW
 ****************************************/
int8_t setMotorDirL(int8_t cw_ccw) {
	if (cw_ccw == 0) {
		PORTC.PODR.BIT.B5 = 0; //モータ
		PORTC.PODR.BIT.B4 = 1;
		return cw_ccw;
	} else {
		PORTC.PODR.BIT.B5 = 1; //モータ
		PORTC.PODR.BIT.B4 = 0;
		return cw_ccw;
	}
}

int8_t setMotorDirR(int8_t cw_ccw) {
	if (cw_ccw == 0) {
		PORTC.PODR.BIT.B3 = 1; //モータ
		PORTC.PODR.BIT.B2 = 0;
		return cw_ccw;
	} else {
		PORTC.PODR.BIT.B3 = 0; //モータ
		PORTC.PODR.BIT.B2 = 1;
		return cw_ccw;
	}
}

/****************************************
 速度返す
 ****************************************/
float returnVelocityL(void) {
	return returnEncoderDiffL() * DIAMETER_L * INTRPT_FREQENCY * M_PI / (ENC_RESO * 4) / GEAR_RATIO;
}

float returnVelocityR(void) {
	return returnEncoderDiffR() * DIAMETER_R * INTRPT_FREQENCY * M_PI / (ENC_RESO * 4) / GEAR_RATIO;
}

/****************************************
 速度P制御
 ****************************************/
float ctrlPropVelocity(float kp) {
	g_velo_error = g_target_velo - g_current_velo;
	return g_velo_error * kp;
}

/****************************************
 速度I制御
 ****************************************/
float ctrlIntVelocity(float ki) {
	g_velo_error_integral += g_velo_error;
	if (g_flag_blindalley == 1 || g_flag_blindalley == 2) {
		g_velo_error_integral = 0;
	}
	return g_velo_error_integral * ki;
}
/****************************************
 角速度比例定数変更
 ****************************************/
float changeOmegaCtrlConst(float value) {
	if (value == ANG_VELO_P) {
		if ((g_flag_run_mode == RUN) && (fabsf(g_target_alpha) != 0)) {
			return ANG_FASTVELO_P;
		} else {
			return ANG_VELO_P;
		}
	} else if (value == ANG_VELO_I) {
		if ((g_flag_run_mode == RUN) && (fabsf(g_target_alpha) != 0)) {
			return ANG_FASTVELO_I;
		} else {

			return ANG_VELO_I;
		}
	} else if (value == ANG_VELO_D) {
		if ((g_flag_run_mode == RUN) && (fabsf(g_target_alpha) != 0)) {
			return ANG_FASTVELO_D;
		} else {
			return ANG_VELO_D;
		}
	} else {
		return 0;
	}
}
/****************************************
 角速度P制御
 ****************************************/
float ctrlPropOmega(float kp) {
	g_omega_error = g_target_omega - g_current_omega;

	return convDegreeToRadian(g_omega_error) * TREAD / 2.0 * kp;
}
/****************************************
 角速度I制御
 ****************************************/
float ctrlIntOmega(float ki) {
	g_omega_error_integral += g_omega_error;
	if (((g_sensor_L > SEN_THRESHOLD_L) || (g_sensor_R > SEN_THRESHOLD_R)) && g_flag_turn == 0) {
		g_omega_error_integral = 0;
		return 0;
	} else if (g_flag_blindalley == 1 || g_flag_blindalley == 2) {
		g_omega_error_integral = 0;
		return 0;
	} else {
		return convDegreeToRadian(g_omega_error_integral) * TREAD / 2.0 * ki;
	}
}
/****************************************
 角速度D制御
 ****************************************/
float ctrlDeriOmega(float kd) {
	static float omega_error_before = 0;
	g_omega_error_derivative = g_omega_error - omega_error_before;
	omega_error_before = g_omega_error;
	return convDegreeToRadian(g_omega_error_derivative) * TREAD / 2.0 * kd;
}
/****************************************
 角度P制御
 ****************************************/
float ctrlPropAngle(float kp) {
	g_angle_error = g_target_angle - g_current_angle;

	return convDegreeToRadian(g_angle_error) * TREAD / 2.0 * kp;
}
/****************************************
 角度I制御
 ****************************************/
float ctrlIntAngle(float ki) {
	g_angle_error_integral += g_angle_error;
	if (((g_sensor_L > SEN_THRESHOLD_L) || (g_sensor_R > SEN_THRESHOLD_R)) && g_flag_turn == 0) {
		g_angle_error_integral = 0;
		return 0;
	} else if (g_flag_blindalley == 1 || g_flag_blindalley == 2) {
		g_angle_error_integral = 0;
		return 0;
	} else {
		return convDegreeToRadian(g_angle_error_integral) * TREAD / 2.0 * ki;
	}
}
/****************************************
 壁制御
 ****************************************/
//float ctrlWall(float kp) {
//	float tmp;
//	if (g_target_velo <= 0.4) {
////低速域
//
//		tmp = 0;
//
//	} else if ((g_flag_turn == 1) || (g_flag_blindalley == 1) || (g_flag_blindalley == 2)) {
//// ターン中　袋小路中
//		tmp = 0;
//
//	} else if (g_flag_diagonal == 1) {
////斜め中
//		if (SEN_DIAGONAL_FL > g_sensor_FL) {
//			tmp = ( SEN_DIAGONAL_FL - g_sensor_FL) * 0.8;
//		}
//		if (SEN_DIAGONAL_FR > g_sensor_FR) {
//			tmp = -( SEN_DIAGONAL_FR - g_sensor_FR) * 0.8;
//		}
//		tmp += 0.07 * (( SEN_REFERENCE_L - g_sensor_L) - ( SEN_REFERENCE_R - g_sensor_R));
//
//	} else if (g_flag_circuit == 1) {
////サーキット
//		tmp = 2 * ( SEN_REFERENCE_L - g_sensor_L);
//	} else if (((fabsf(g_sensor_L_derivative) > SEN_DERIVATIVE_L) || (fabsf(g_sensor_R_derivative) > SEN_DERIVATIVE_R)) && (g_target_velo <= 0.5)) {
////探索速度で変化量が一定以上
//		tmp = 0;
//
//	} else if ((g_sensor_L > SEN_THRESHOLD_L) && (g_sensor_R > SEN_THRESHOLD_R)) {
////壁が両方ある
//		tmp = (( SEN_REFERENCE_L - g_sensor_L) - ( SEN_REFERENCE_R - g_sensor_R));
//
//	} else if ((g_sensor_L < SEN_THRESHOLD_L) && (g_sensor_R < SEN_THRESHOLD_R)) {
////壁が両方ない
//		tmp = 0;
//
//	} else if (g_sensor_L > SEN_THRESHOLD_L) {
////左壁のみ
//		tmp = 2 * ( SEN_REFERENCE_L - g_sensor_L);
//
//	} else if (g_sensor_R > SEN_REFERENCE_R) {
////右壁のみ
//		tmp = -2 * ( SEN_REFERENCE_R - g_sensor_R);
//
//	} else {
//
//		tmp = 0;
//	}
//
//
//	if (g_target_velo < 0.5) {
//		return tmp * kp;
//	} else if (g_target_velo < 1.5) {
//		return tmp * 0.1;
//	} else {
//		return tmp * WALL_HIGH_SPEED;
//	}
//
//}
float ctrlWall(float kp) {
	float tmp;
	if (g_target_velo <= 0.4) { //低速域

		tmp = 0;

	} else if ((g_flag_turn == 1) || (g_flag_blindalley == 1) || (g_flag_blindalley == 2)) {

		tmp = 0;

	} else if (g_flag_diagonal == 1) {

		if (SEN_DIAGONAL_FL > g_sensor_FL) {
			tmp = ( SEN_DIAGONAL_FL - g_sensor_FL) * 0.8;
		}
		if (SEN_DIAGONAL_FR > g_sensor_FR) {
			tmp = -( SEN_DIAGONAL_FR - g_sensor_FR) * 0.8;
		}
		tmp += 0.07 * (( SEN_REFERENCE_L - g_sensor_L) - ( SEN_REFERENCE_R - g_sensor_R));

	} else if (g_flag_circuit == 1) {
		tmp = 2 * ( SEN_REFERENCE_L - g_sensor_L);
	} else if (((fabsf(g_sensor_L_derivative) > SEN_DERIVATIVE_L)

	|| (fabsf(g_sensor_R_derivative) > SEN_DERIVATIVE_R)) && (g_target_velo <= 0.5)) {

		tmp = 0;

	} else if ((g_sensor_L > SEN_THRESHOLD_L) && (g_sensor_R > SEN_THRESHOLD_R)) {
		//	driveRGB(GREEN,ON);
		tmp = (( SEN_REFERENCE_L - g_sensor_L) - ( SEN_REFERENCE_R - g_sensor_R));

	} else if ((g_sensor_L < SEN_THRESHOLD_L) && (g_sensor_R < SEN_THRESHOLD_R)) {
		//	driveRGB(ORANGE,ON);
		tmp = 0;

	} else if (g_sensor_L > SEN_THRESHOLD_L) {
		//	driveRGB(BLUE,ON);
		tmp = 2 * ( SEN_REFERENCE_L - g_sensor_L);

	} else if (g_sensor_R > SEN_REFERENCE_R) {
		//	driveRGB(RED,ON);
		tmp = -2 * ( SEN_REFERENCE_R - g_sensor_R);

	} else {

		tmp = 0;
	}

//	if (fabsf(temp) < 0.00001) {
//		driveRGB(BLUE, ON);
//	} else {
//		driveRGB(GREEN, ON);
//	}

	if (g_target_velo < 0.5) {
		return tmp * kp;
	} else if (g_target_velo < 1.5) {
		return tmp * 0.1;
	} else {
		return tmp * WALL_HIGH_SPEED;
	}

}
float ctrlWallFrontAng(float kp) {
	float tmp = 0;
	if ((g_flag_blindalley == 1) && (g_sensor_FL_average > SEN_NOWALL_FL) && (g_sensor_FR_average > SEN_NOWALL_FR)) {

		g_omega_error_integral = 0;
		tmp = -kp * (( SEN_REFERENCE_FL - g_sensor_FL_average) - ( SEN_REFERENCE_FR - g_sensor_FR_average));

	} else if ((g_flag_blindalley == 2) && (g_sensor_FL_average > SEN_NOWALL_FL) && (g_sensor_FR_average > SEN_NOWALL_FR)) {

		g_omega_error_integral = 0;
		tmp = -kp * ((SEN_REFERENCE_FL_S - g_sensor_FL_average) - (SEN_REFERENCE_FR_S - g_sensor_FR_average));

	} else {
		tmp = 0;
	}
	return tmp;
}
float ctrlWallFrontDis(float kp) {
	float tmp = 0;
	if ((g_flag_blindalley == 1) && (g_sensor_FL_average > SEN_NOWALL_FL) && (g_sensor_FR_average > SEN_NOWALL_FR)) {

		tmp = kp * (( SEN_REFERENCE_FL - g_sensor_FL_average) + ( SEN_REFERENCE_FR - g_sensor_FR_average));

	} else if ((g_flag_blindalley == 2) && (g_sensor_FL_average > SEN_NOWALL_FL) && (g_sensor_FR_average > SEN_NOWALL_FR)) {

		tmp = kp * ((SEN_REFERENCE_FL_S - g_sensor_FL_average) + (SEN_REFERENCE_FR_S - g_sensor_FR_average));

	} else {
		tmp = 0;
	}
	return tmp;
}
/****************************************
 フィードフォワード制御
 ****************************************/
float ctrlFeedForwardL(float accele, float alpha) {
	float accele_torque, alpha_torque, const_torque, torque, rpm;

	rpm = fabsf(g_encoder_diff_L) * INTRPT_FREQENCY / (ENC_RESO * 4) * 60;
//加速トルク
	accele_torque = (MASS * accele / 2) * DIAMETER_L / 2 / GEAR_RATIO;
//角加速トルク
	alpha_torque = (INERTIA * convDegreeToRadian(alpha) / TREAD) * DIAMETER_L / 2 / GEAR_RATIO;
//等速時トルク
	if (g_accele == 0 && g_target_alpha == 0 && g_target_omega != 0) {
		const_torque = 0.000572 * g_target_velo + 0.000304;
		if (g_target_omega > 0) {
			const_torque += (0.00001492 * g_target_omega - 0.001341) * 0;
		} else {
			const_torque += (0.000002314 * g_target_omega + 0.0002122) * 0;
		}

	} else {
		const_torque = 0;
	}

//トルク合計
	torque = accele_torque - alpha_torque + const_torque;
//実際のトルク
	g_torque_L =
	MOTOR_TORQUE * (g_battery_voltage * g_duty_L / 100 - MOTOR_BACK_EMF * rpm) / MOTOR_RESISTANCE;
	if (g_flag_FF == 1) {
		return 100 * (MOTOR_RESISTANCE * torque / MOTOR_TORQUE + MOTOR_BACK_EMF * rpm) / g_battery_voltage;
	} else {
		return 0;
	}
}

float ctrlFeedForwardR(float accele, float alpha) {
	float accele_torque, alpha_torque, const_torque, torque, rpm;

	rpm = fabsf(g_encoder_diff_R) * INTRPT_FREQENCY / (ENC_RESO * 4) * 60;
//加速トルク
	accele_torque = (MASS * accele / 2) * DIAMETER_R / 2 / GEAR_RATIO;
//角加速トルク
	alpha_torque = (INERTIA * convDegreeToRadian(alpha) / TREAD) * DIAMETER_R / 2 / GEAR_RATIO;
//等速時トルク
	if (g_accele == 0 && g_target_alpha == 0 && g_target_omega != 0) {
		const_torque = 0.000572 * g_target_velo + 0.000304;
		if (g_target_omega > 0) {
			const_torque += (0.000002314 * g_target_omega + 0.0002122) * 0;
		} else {
			const_torque += (0.00001492 * g_target_omega - 0.001341) * 0;
		}

	} else {
		const_torque = 0;
	}

//トルク合計
	torque = accele_torque + alpha_torque + const_torque;
//実際のトルク
	g_torque_R =
	MOTOR_TORQUE * (g_battery_voltage * g_duty_R / 100 - MOTOR_BACK_EMF * rpm) / MOTOR_RESISTANCE;
	if (g_flag_FF == 1) {
		return 100 * (MOTOR_RESISTANCE * torque / MOTOR_TORQUE + MOTOR_BACK_EMF * rpm) / g_battery_voltage;
	} else {
		return 0;
	}
}
/****************************************
 袋小路
 ****************************************/
void runBlindAlley(float velo) {
	static uint16_t times_count = 0;

	g_flag_turn = 1;
	times_count++;
	if (times_count > 5) {
		times_count = 0;
	}

	runStraight(5, HALF_SECTION, velo, 0);
	if ((g_sensor_FL + g_sensor_FR) > (SEN_NOWALL_FL + SEN_NOWALL_FR)) {
		g_flag_blindalley = 1;

		waitTime(300);
	}

	if (times_count == 0) {
		calcGyroZRef();
	}

	g_flag_blindalley = 0;

	initRun();
	if (SEN_REFERENCE_L - g_sensor_L < -170) {
		turnCorner(&pivot_90_R);
		g_flag_blindalley = 2;

		waitTime(300);
		g_flag_blindalley = 0;

		initRun();
		turnCorner(&pivot_90_R);
		waitTime(300);
		g_distance = 0;

		//runStraight(5, HALF_SECTION + 0.01, velo, velo);
		runStraight(5, -0.045, 0.5, 0);
		runStraightSearch(5, HALF_SECTION + 0.045, velo);
	} else if (SEN_REFERENCE_R - g_sensor_R < -170) {
		turnCorner(&pivot_90_L);
		g_flag_blindalley = 2;

		waitTime(300);
		g_flag_blindalley = 0;

		initRun();
		turnCorner(&pivot_90_L);
		waitTime(300);
		g_distance = 0;
		//runStraight(5, HALF_SECTION + 0.01, velo, velo);
		runStraight(5, -0.045, 0.5, 0);
		runStraightSearch(5, HALF_SECTION + 0.045, velo);
	} else {
		g_target_angle = 0;
		turnCorner(&pivot);
		waitTime(300);
		g_distance = 0;
		//runStraight(5, HALF_SECTION + BLIND_ALLEY, velo, velo);
		runStraight(5, -0.035, 0.5, 0);
		runStraightSearch(5, HALF_SECTION + 0.035, velo);
	}

	g_flag_turn = 0;

}
/****************************************
 走行初期化
 ****************************************/
void initRun(void) {
	g_flag_control = 1;
	g_log_count = 0;
	g_flag_failsafe = 0;
	g_flag_shortest_goal = 0;

	g_distance = 0;

	g_target_velo = 0;

	g_target_angle = 0;
	g_current_angle = 0;

	g_velo_error = 0;
	g_velo_error_integral = 0;

	g_omega_error = 0;
	g_omega_error_integral = 0;
	g_omega_error_derivative = 0;

	g_angle_error = 0;
	g_angle_error_integral = 0;

}
/****************************************
 台形加速
 ****************************************/
void runStraight(float t_acc, float t_dis, float t_max_velo, float t_end_velo) {
	double section1 = 0;
	double section2 = 0;
	double section3 = 0;
	float acc_temp;
	int8_t sign;

	section1 = (t_max_velo * t_max_velo - g_target_velo * g_target_velo) / (2 * t_acc);
	section3 = (t_max_velo * t_max_velo - t_end_velo * t_end_velo) / (2 * t_acc);
	section2 = fabsf(t_dis) - section1 - section3;

	if (section2 <= 0) {
		if (section1 <= 0 && section3 >= 0) {
			section1 = 0;
			section2 = 0;
			section3 = fabsf(t_dis);
		} else if (section1 >= 0 && section3 <= 0) {
			section1 = fabsf(t_dis);
			section2 = 0;
			section3 = 0;
		} else {

			section2 = 0;

			section1 = (t_end_velo * t_end_velo - g_target_velo * g_target_velo) / (4 * t_acc) + fabsf(t_dis) / 2;
			section3 = (g_target_velo * g_target_velo - t_end_velo * t_end_velo) / (4 * t_acc) + fabsf(t_dis) / 2;
		}

	}
	section2 += section1;
	section3 += section2;

	if ((t_dis) <= 0) {
		acc_temp = -t_acc;
		sign = -1;
	} else {
		acc_temp = t_acc;
		sign = 1;
	}

//section1////////////////////////////////////////////////////////////////////
	g_accele = acc_temp;
	while (g_flag_failsafe != 1) {
		if (fabsf(g_distance) >= section1)
			break;
	}

//section2////////////////////////////////////////////////////////////////////

	g_accele = 0;
	while (g_flag_failsafe != 1) {
		if (fabsf(g_distance) >= section2)
			break;
	}

//section3////////////////////////////////////////////////////////////////////

	g_accele = -1.0 * acc_temp;
	while (g_flag_failsafe != 1) {
		if (fabsf(g_distance) >= section3 || ((g_target_velo * sign) < 0))
			break;
	}
	g_accele = 0;
	g_target_velo = t_end_velo;
	g_distance = 0;
	g_target_angle = 0;
}
/****************************************
 直線走行(探索)
 ****************************************/
void runStraightSearch(float acceleration, float distance, float velocity) {
	double section1 = 0;
	double section2 = 0;
	g_accele = 0;

	if (acceleration != 0) {
		section1 = (velocity * velocity - g_target_velo * g_target_velo) / (2 * acceleration);
	} else {
		section1 = 0;
	}
	section2 = distance;

//section1////////////////////////////////////////////////////////////////////
	g_accele = acceleration;
	while (g_flag_failsafe != 1) {
		if (fabsf(g_distance) >= section1 || ((g_flag_pillar_edge_L == 1 || g_flag_pillar_edge_R == 1) && g_distance > distance / 2))
			break;
	}
	g_accele = 0;
	g_target_velo = velocity;

	while (g_flag_failsafe != 1) {
		if (fabsf(g_distance) >= section2 || ((g_flag_pillar_edge_L == 1 || g_flag_pillar_edge_R == 1) && g_distance > distance / 2))
			break;
	}
	g_distance = 0;
	if (g_flag_pillar_edge_L == 1) {
		while (g_flag_failsafe != 1) {

			if (fabsf(g_distance) >= 0.075) //0.09
				break;
		}
	} else if (g_flag_pillar_edge_R == 1) {
		while (g_flag_failsafe != 1) {

			if (fabsf(g_distance) >= 0.07) //0.075
				break;
		}
	}

	g_accele = 0;
	g_target_velo = velocity;
	g_distance = 0;
	g_target_angle = 0;
}
/****************************************
 直線走行(オフセット)
 ****************************************/
void runStraightOffset(float dis, float velo) {
	uint32_t sensor_value_FL, sensor_value_FR;

	g_accele = 0;
	g_target_velo = velo;

	if ((g_sensor_FL + g_sensor_FR > SEN_NOWALL_FL + SEN_NOWALL_FR) && g_sensor_FL > SEN_NOWALL_FL && g_sensor_FR > SEN_NOWALL_FR) {
		sensor_value_FL = 222.82 * expf(13.64 * dis);
		sensor_value_FR = 216.23 * expf(14.11 * dis);

		while (g_flag_failsafe != 1) {
			if ((g_sensor_FL_average > sensor_value_FL && g_sensor_FR_average > sensor_value_FR))
				break;
		}
	} else {
		while (g_flag_failsafe != 1) {
			if (fabsf(g_distance) >= dis)
				break;
		}
	}

	g_accele = 0;
	g_target_velo = velo;
	g_distance = 0;
	g_target_angle = 0;
}
/****************************************
 ターン 非連続
 ****************************************/
void turnCorner(turn_t *p) {
	double section1 = 0;
	double section2 = 0;
	double section3 = 0;
	int8_t left_right = 0;
	float angacc_tmp;

	if (p->mode == 0 || p->mode == 1) { //壁切れ
		if (p->angle >= 0) {

			while (g_flag_failsafe != 1) {
				if (g_flag_pillar_edge_L == 1)
					break;

			}
			g_distance = 0;
			runStraight(5, p->front, p->velocity, p->velocity);

		} else {

			while (g_flag_failsafe != 1) {
				if (g_flag_pillar_edge_R == 1)
					break;

			}
			g_distance = 0;
			runStraight(5, p->front, p->velocity, p->velocity);

		}
	} else if (p->mode == -1) { //壁切れなし
		runStraight(5, p->front, p->velocity, p->velocity);
	} else {

	}

	g_flag_turn = 1; //ターンフラグ立てる
	g_flag_diagonal = p->dia;

	if ((p->angle) <= 0) {
		left_right = -1;
		angacc_tmp = -p->alpha;
	} else {
		left_right = 1;
		angacc_tmp = p->alpha;
	}

	g_target_alpha = angacc_tmp;

	section1 = (p->omega * p->omega) / (2 * p->alpha);
	section3 = (p->omega * p->omega) / (2 * p->alpha);
	section2 = fabsf(p->angle) - section1 - section3;

	if (section2 <= 0) {
		if (section1 <= 0 && section3 >= 0) {
			section1 = 0;
			section2 = 0;
			section3 = fabsf(p->angle);
		} else if (section1 >= 0 && section3 <= 0) {
			section1 = fabsf(p->angle);
			section2 = 0;
			section3 = 0;
		} else {

			section2 = 0;

			section1 = (-g_current_omega * g_current_omega) / (4 * p->alpha) + fabsf(p->angle) / 2;
			section3 = (g_current_omega * g_current_omega) / (4 * p->alpha) + fabsf(p->angle) / 2;
		}

	}
	section2 += section1;
	section3 += section2;

//section1////////////////////////////////////////////////////////////////////

	while (g_flag_failsafe != 1) {
		if (fabsf(g_target_angle) >= section1)
			break;
	}

//section2////////////////////////////////////////////////////////////////////

	g_target_alpha = 0;

	if (p->angle <= 0) {
		g_target_omega = -p->omega;
	} else {
		g_target_omega = p->omega;
	}
	while (g_flag_failsafe != 1) {
		if (fabsf(g_target_angle) >= section2)
			break;
	}

//section3////////////////////////////////////////////////////////////////////

	g_target_alpha = angacc_tmp * -1;

	while (g_flag_failsafe != 1) {
		if (fabsf(g_target_angle) >= section3) {
			break;
		}

		if (left_right == 1) {
			if (g_target_omega < 0)
				break;
		} else if (left_right == -1) {
			if (g_target_omega > 0)
				break;
		}
	}
	g_target_alpha = 0;
	g_target_omega = 0;

	g_target_angle = 0;
	g_distance = 0;

	g_current_angle = 0;

//	g_angle_error = 0;
//	g_angle_error_integral = 0;

//	g_angularvelo_error = 0;
//	g_angularvelo_error_integral = 0;

	g_flag_turn = 0; //ターンフラグおろす
	if ((g_flag_shortest_goal == 1) || (g_flag_run_mode == SEARCH)) {
		runStraight(5, p->rear, p->velocity, p->velocity);
	}

}

/****************************************
 スラローム 連続
 ****************************************/
void turnCornerContinuous(float degree, float omega) {
//パラメータ計算
	g_target_angle_const = degree;
	g_target_omega_max = omega;
	g_alpha_max = 9.0 * M_PI / 16 * powf(omega, 2) / degree;
	g_turn_peaktime = 3 * g_target_omega_max / fabsf(g_alpha_max) / 2;

//フラグ立てる
	g_flag_turn_continuous = 1; //連続角速度ターンフラグ
	g_flag_turn = 1; //ターンフラグ

//初期化
	g_count_time_angle = 0;
	g_target_omega = 0;
	g_current_angle = 0;
	g_target_alpha = 0;

	while (g_count_time_angle * INTRPT_PERIOD < g_turn_peaktime * 2) {
		if (g_target_omega > 2000) {
			g_target_omega = 0;
			break;
		}
	}

//初期化
	g_distance = 0;
	g_target_alpha = 0;
	g_alpha_max = 0;
	g_target_omega = 0;

	g_accele = 0;

	g_target_angle = 0;
	g_current_angle = 0;

//フラグ降ろす
	g_flag_turn_continuous = 0;
	g_flag_turn = 0;
}
/****************************************
 ターン連続_探索
 ****************************************/
void turnSearch(turn2_t *p) {

	//runStraight(5, p->front, p->velocity, p->velocity);
	runStraightOffset(p->front, p->velocity);
	turnCornerContinuous(p->angle, p->omega);
	runStraight(5, p->rear, p->velocity, p->velocity);

}
/****************************************
 ターン連続_最短走行
 ****************************************/
void turnShortest(turn2_t *p) {
//壁切れ
	if (p->angle >= 0) {
		while (g_flag_failsafe != 1) {
			if (g_flag_pillar_edge_L == 1)
				break;
		}
		g_distance = 0;
		runStraight(5, p->front, p->velocity, p->velocity);
	} else {
		while (g_flag_failsafe != 1) {
			if (g_flag_pillar_edge_R == 1)
				break;
		}
		g_distance = 0;
		runStraight(5, p->front, p->velocity, p->velocity);
	}
//ターン
	turnCornerContinuous(p->angle, p->omega);
//ターン後オフセット
	g_flag_diagonal = p->dia; //斜めフラグ
	if ((g_flag_shortest_goal == 1)) {
		runStraight(5, p->rear, p->velocity, p->velocity);
	}
}
