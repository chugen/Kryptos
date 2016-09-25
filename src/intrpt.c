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

/****************************************
 割り込み関数0
 ****************************************/
void intrptCMT0(void) {
	g_wait_counter++;
	g_test_count++;
	if (g_flag_mode_setting == 1) {
		g_mode_velo = returnVelocityR();
	}

	if (g_test_flag == 1) {
		g_current_velo.L = returnVelocityL();
		g_current_velo.R = returnVelocityR();

		setMotorDutyL(controlProportionL(400)+controlIntegralL(150));
		setMotorDutyR(controlProportionR(400)+controlIntegralR(150));

		g_error_integral.L+=g_current_error.L;
		g_error_integral.R+=g_current_error.R;

	}
}
/****************************************
 割り込み関数1
 ****************************************/

