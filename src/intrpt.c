/*
 * intrpt.cpp
 *
 *  Created on: 2016/05/24
 *      Author: 元太
 */
#include <stdint.h>
#include "iodefine.h"
#include "intrpt.h"
#include "common.h"
#include "run.h"
#include "grobal.h"
#include "parameter.h"
#include "sensor.h"
#include "app.h"

/****************************************
 割り込み関数0
 ****************************************/
void intrptCMT0(void) {
	g_wait_counter++;
	g_test_count++;
	if (g_flag_mode_setting == 1) {
		g_mode_velo = returnVelocityR();
	}

	if (g_test_count < 5000) {
		g_test_array[g_test_count] = 1;
		g_test_array2[g_test_count] = -1;
	}

	if (g_test_flag == 1) {
		g_current_gcenter_velo = returnVelocityL() + returnVelocityR();
		g_current_angularvelo = returnGyroZVal() - g_gyro_reference;

		setMotorDutyL(
				ctrlPropVelocity(VELO_P) + ctrlIntVelocity(VELO_I)
						- ctrlPropAngularVelocity(ANG_VELO_P)
						- ctrlIntAngularVelocity(ANG_VELO_I));
		setMotorDutyR(
				ctrlPropVelocity(VELO_P) + ctrlIntVelocity(VELO_I)
						+ ctrlPropAngularVelocity(ANG_VELO_P)
						+ ctrlIntAngularVelocity(ANG_VELO_I));

	}
}
/****************************************
 割り込み関数1
 ****************************************/

