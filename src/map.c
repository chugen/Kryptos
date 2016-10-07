/*
 * map.c
 *
 *  Created on: 2016/10/06
 *      Author: Gen
 */

#include "iodefine.h"
#include <stdint.h>
#include "global.h"
#include "map.h"
#include "app.h"
#include "common.h"
#include "parameter.h"
#include "run.h"
/****************************************
 方位管理
 ****************************************/
void checkOrient(int ori_deg) {
	if (ori_deg == 90) {
		g_orient = g_orient << 1;
		if (g_orient >= 0x10) {
			g_orient = 0x01;
		}
	} else if (ori_deg == -90) {
		g_orient = g_orient >> 1;
		if (g_orient == 0x00) {
			g_orient = 0x08;
		}
	} else {
		if (g_orient == 0x01) {
			g_orient = 0x04;
		} else if (g_orient == 0x02) {
			g_orient = 0x08;
		} else if (g_orient == 0x04) {
			g_orient = 0x01;
		} else if (g_orient == 0x08) {
			g_orient = 0x02;
		}
	}
}

/****************************************
 座標管理
 ****************************************/
void countCoord(void) {
	if (g_orient == NORTH) {
		g_current_x += 0;
		g_current_y += 1;
	} else if (g_orient == EAST) {
		g_current_x += 1;
		g_current_y += 0;
	} else if (g_orient == SOUTH) {
		g_current_x += 0;
		g_current_y += -1;
	} else if (g_orient == WEST) {
		g_current_x += -1;
		g_current_y += 0;
	}
	g_wall_data_temp[g_current_x][g_current_y] |= 0xf0;
}
/****************************************
 map表示
 ****************************************/
void printMap(void) {
	int i_x;
	int i_y;

	waitTime(500);
	myprintf("\x1b[31m\x1b[1m");

	for (i_y = 15; i_y >= 0; i_y--) {
		myprintf("+");
		for (i_x = 0; i_x < 16; i_x++) {
			if (((g_wall_data[i_x][i_y] & 1) == 1)) {
				myprintf("---+");
			} else {
				myprintf("   +");
			}
		}
		myprintf("\n\r");
		myprintf("|");
		for (i_x = 0; i_x < 16; i_x++) {
			if (((g_wall_data[i_x][i_y] & 0x08) == 0x08) || i_x == 15) {
				myprintf("\x1b[39m\x1b[0m");
				if ((g_wall_data[i_x][i_y] & 0xf0) == 0xf0) {
					myprintf("\x1b[44m");
				}
				myprintf("%3d", g_step_map[i_x][i_y]);
				myprintf("\x1b[40m");
				myprintf("\x1b[31m\x1b[1m");
				myprintf("|");
			} else {
				myprintf("\x1b[39m\x1b[0m");
				if ((g_wall_data[i_x][i_y] & 0xf0) == 0xf0) {
					myprintf("\x1b[44m");
				}
				myprintf("%3d", g_step_map[i_x][i_y]);
				myprintf("\x1b[40m");
				myprintf("\x1b[31m\x1b[1m");
				myprintf(" ");
			}
		}
		myprintf("\n\r");
	}

	myprintf("+");
	for (i_x = 0; i_x < 16; i_x++) {
		myprintf("---+");
	}
	myprintf("\n\r");

}

/****************************************
 初期壁セット
 ****************************************/
void setInitWall(void) {
	int i;
	for (i = 0; i < 16; i++) {
		g_wall_data_temp[0][i] |= 0x02;
		g_wall_data_temp[15][i] |= 0x08;
		g_wall_data_temp[i][0] |= 0x04;
		g_wall_data_temp[i][15] |= 0x01;
		g_wall_data_temp[0][i] |= 0x20;
		g_wall_data_temp[15][i] |= 0x80;
		g_wall_data_temp[i][0] |= 0x40;
		g_wall_data_temp[i][15] |= 0x10;
	}
	g_wall_data_temp[0][0] |= 0x08;
	g_wall_data_temp[0][0] |= 0xf0;

	for (i = 0; i < 16; i++) {
		g_wall_data[0][i] |= 0x02;
		g_wall_data[15][i] |= 0x08;
		g_wall_data[i][0] |= 0x04;
		g_wall_data[i][15] |= 0x01;
		g_wall_data[0][i] |= 0x20;
		g_wall_data[15][i] |= 0x80;
		g_wall_data[i][0] |= 0x40;
		g_wall_data[i][15] |= 0x10;
	}
	g_wall_data[0][0] |= 0x08;
	g_wall_data[0][0] |= 0xf0;
}
/****************************************
 壁情報一致
 ****************************************/
void matchWall(void) {
	int i_x, i_y;
	for (i_x = 0; i_x < 16; i_x++) {
		for (i_y = 0; i_y < 15; i_y++) {
			if ((g_wall_data_temp[i_x][i_y + 1] & 0x04) == 0x04) { //南壁があれば下のマスの北壁もある
				g_wall_data_temp[i_x][i_y] |= 0x01;
			}
			if ((g_wall_data_temp[i_x][i_y + 1] & 0x40) == 0x40) { //南壁が既知であれば下のマスの北壁も既知である
				g_wall_data_temp[i_x][i_y] |= 0x10;
			}
		}
	}
	for (i_x = 0; i_x < 15; i_x++) {
		for (i_y = 0; i_y < 16; i_y++) {
			if ((g_wall_data_temp[i_x + 1][i_y] & 0x02) == 0x02) { //西壁があれば左隣のマスの東壁もある
				g_wall_data_temp[i_x][i_y] |= 0x08;

			}
			if ((g_wall_data_temp[i_x + 1][i_y] & 0x20) == 0x20) { //西壁が既知であれば左隣のマスの東壁も既知である
				g_wall_data_temp[i_x][i_y] |= 0x80;

			}
		}
	}

	for (i_x = 0; i_x < 16; i_x++) {
		for (i_y = 1; i_y < 16; i_y++) {
			if ((g_wall_data_temp[i_x][i_y - 1] & 0x01) == 0x01) { //北壁があれば上のマスの南壁もある
				g_wall_data_temp[i_x][i_y] |= 0x04;

			}
			if ((g_wall_data_temp[i_x][i_y - 1] & 0x10) == 0x10) { //北壁が既知であれば上のマスの南壁も既知である
				g_wall_data_temp[i_x][i_y] |= 0x40;

			}
		}
	}
	for (i_x = 1; i_x < 16; i_x++) {
		for (i_y = 0; i_y < 16; i_y++) {
			if ((g_wall_data_temp[i_x - 1][i_y] & 0x08) == 0x08) { //東壁が既知であれば右隣のマスの西壁もある
				g_wall_data_temp[i_x][i_y] |= 0x02;

			}
			if ((g_wall_data_temp[i_x - 1][i_y] & 0x80) == 0x80) { //東壁が既知であれば右隣のマスの西壁も既知である
				g_wall_data_temp[i_x][i_y] |= 0x20;

			}
		}
	}
}
/****************************************
 壁情報決定版
 ****************************************/
void matchWallGoal(void) {
	int i_x, i_y;
	for (i_x = 0; i_x < 16; i_x++) {
		for (i_y = 0; i_y < 16; i_y++) {
			g_wall_data[i_x][i_y] = g_wall_data_temp[i_x][i_y];
		}
	}
}

/****************************************
 壁情報読み込み
 ****************************************/
void checkWall(void) {

	g_wall_data_temp[g_current_x][g_current_y] |= 0xf0;

	if (g_sensor_L > SEN_NOWALL_L) {
		if (g_orient == 0x01) {
			g_wall_data_temp[g_current_x][g_current_y] |= 0x02;
		} else if (g_orient == 0x02) {
			g_wall_data_temp[g_current_x][g_current_y] |= 0x04;
		} else if (g_orient == 0x04) {
			g_wall_data_temp[g_current_x][g_current_y] |= 0x08;
		} else if (g_orient == 0x08) {
			g_wall_data_temp[g_current_x][g_current_y] |= 0x01;
		}
	}
	if (g_sensor_R > SEN_NOWALL_R) {
		if (g_orient == 0x01) {
			g_wall_data_temp[g_current_x][g_current_y] |= 0x08;
		} else if (g_orient == 0x02) {
			g_wall_data_temp[g_current_x][g_current_y] |= 0x01;
		} else if (g_orient == 0x04) {
			g_wall_data_temp[g_current_x][g_current_y] |= 0x02;
		} else if (g_orient == 0x08) {
			g_wall_data_temp[g_current_x][g_current_y] |= 0x04;
		}
	}
	if (g_sensor_FL + g_sensor_FR > SEN_NOWALL_FL + SEN_NOWALL_FR) {
		if (g_orient == 0x01) {
			g_wall_data_temp[g_current_x][g_current_y] |= 0x01;
		} else if (g_orient == 0x02) {
			g_wall_data_temp[g_current_x][g_current_y] |= 0x02;
		} else if (g_orient == 0x04) {
			g_wall_data_temp[g_current_x][g_current_y] |= 0x04;
		} else if (g_orient == 0x08) {
			g_wall_data_temp[g_current_x][g_current_y] |= 0x08;
		}
	}
	//comb_breaker();
}

/****************************************
 queuemap
 ****************************************/
void countStepQueue(void) {
	int i, j;
	unsigned char x, y;
	short head = 0, tail = 1;
	unsigned char queue[257];
	setInitWall();
	matchWall();

	for (i = 0; i < 16; i++) {
		for (j = 0; j < 16; j++) {
			g_step_map[i][j] = 255;
		}
	}

	g_step_map[g_target_x][g_target_y] = 0;

	queue[0] = (g_target_x + g_target_y * 16);

	while (head != tail) {
		y = queue[head] >> 4;
		x = queue[head] & 0x0f;
		head++;
		if (y < 16) {
			if ((g_wall_data_temp[x][y] & 0x01) == 0) {
				if (g_step_map[x][y + 1] == 255) {
					g_step_map[x][y + 1] = g_step_map[x][y] + 1;
					queue[tail] = (x + (y + 1) * 16);
					tail++;
				}
			}
		}
		if (x > 0) {
			if ((g_wall_data_temp[x][y] & 0x02) == 0) {
				if (g_step_map[x - 1][y] == 255) {
					g_step_map[x - 1][y] = g_step_map[x][y] + 1;
					queue[tail] = (x - 1 + y * 16);
					tail++;
				}
			}
		}
		if (y > 0) {
			if ((g_wall_data_temp[x][y] & 0x04) == 0) {
				if (g_step_map[x][y - 1] == 255) {
					g_step_map[x][y - 1] = g_step_map[x][y] + 1;
					queue[tail] = (x + (y - 1) * 16);
					tail++;
				}
			}
		}
		if (x < 16) {
			if ((g_wall_data_temp[x][y] & 0x08) == 0) {
				if (g_step_map[x + 1][y] == 255) {
					g_step_map[x + 1][y] = g_step_map[x][y] + 1;
					queue[tail] = (x + 1 + y * 16);
					tail++;
				}
			}
		}

	}
}
/****************************************
 足立法
 ****************************************/
void searchAdachi(void) {
	runStraight(5, HALF_SECTION, 0.5, 0.5);
	driveRGB(YELLOW, ON);
	countCoord();
	checkWall();
	countStepQueue();
	driveRGB(WHITE, ON);
	while (1) {
		//////////////////////////////////////////////////////////////////////////
		g_flag_adachi_goal = 0;
		if (g_current_x == g_target_x && g_current_y == g_target_y) {
			g_flag_adachi_goal = 1;
			break;
		}
		if (g_step_map[g_current_x][g_current_y] == 255) {
			driveRGB(RED, ON);
			driveMotor(OFF);

			break;
		}
		if (g_sensor_FL + g_sensor_FR >= SEN_DEATH) {
			driveRGB(BLUE, ON);
			driveMotor(OFF);
			break;
		}
		if (pushButton() == 0) {
			driveRGB(MAGENTA, ON);
			driveMotor(OFF);
			break;
		}

		//////////////////////////////////////////////////////////////////////////
		checkWall();
		g_flag_gap = 1;
		g_distance = 0;
		g_current_velo = 500;
		countStepQueue();

		if (g_orient == 0x01) {
			if ((g_wall_data_temp[g_current_x][g_current_y] & 0x01) == 0
					&& g_step_map[g_current_x][g_current_y + 1]
							- g_step_map[g_current_x][g_current_y] == -1) {


				runStraight(5, SECTION, 0.5, 0.5);

				countCoord();

			} else if ((g_wall_data_temp[g_current_x][g_current_y] & 0x02) == 0
					&& (g_step_map[g_current_x - 1][g_current_y]
							- g_step_map[g_current_x][g_current_y]) == -1) {

				turnCorner(turn_90_L);

				checkOrient(90);
				countCoord();

			} else if ((g_wall_data_temp[g_current_x][g_current_y] & 0x08) == 0
					&& (g_step_map[g_current_x + 1][g_current_y]
							- g_step_map[g_current_x][g_current_y]) == -1) {

				turnCorner(turn_90_R);

				checkOrient(-90);
				countCoord();

			} else {
				g_flag_gap = 1;
				runStraight(5, HALF_SECTION, 0.5, 0);

				waitTime(100);
				g_flag_gap = 0;

				turnCorner(pivot);

				waitTime(100);

				runStraight(5, HALF_SECTION, 0.5, 0.5);

				checkOrient(180);
				countCoord();
			}
		} else if (g_orient == 0x02) {
			if ((g_wall_data_temp[g_current_x][g_current_y] & 0x02) == 0
					&& g_step_map[g_current_x - 1][g_current_y]
							- g_step_map[g_current_x][g_current_y] == -1) {

				runStraight(5, SECTION, 0.5, 0.5);

				countCoord();

			} else if ((g_wall_data_temp[g_current_x][g_current_y] & 0x04) == 0
					&& g_step_map[g_current_x][g_current_y - 1]
							- g_step_map[g_current_x][g_current_y] == -1) {

				turnCorner(turn_90_L);

				checkOrient(90);
				countCoord();

			} else if ((g_wall_data_temp[g_current_x][g_current_y] & 0x01) == 0
					&& g_step_map[g_current_x][g_current_y + 1]
							- g_step_map[g_current_x][g_current_y] == -1) {

				turnCorner(turn_90_R);

				checkOrient(-90);
				countCoord();

			} else {

				g_flag_gap = 1;
				runStraight(5, HALF_SECTION, 0.5, 0);

				waitTime(100);
				g_flag_gap = 0;

				turnCorner(pivot);

				waitTime(100);

				runStraight(5, HALF_SECTION, 0.5, 0.5);

				checkOrient(180);
				countCoord();

			}
		} else if (g_orient == 0x04) {
			if ((g_wall_data_temp[g_current_x][g_current_y] & 0x04) == 0
					&& g_step_map[g_current_x][g_current_y - 1]
							- g_step_map[g_current_x][g_current_y] == -1) {

				runStraight(5, SECTION, 0.5, 0.5);

				countCoord();

			} else if ((g_wall_data_temp[g_current_x][g_current_y] & 0x08) == 0
					&& g_step_map[g_current_x + 1][g_current_y]
							- g_step_map[g_current_x][g_current_y] == -1) {

				turnCorner(turn_90_L);

				checkOrient(90);
				countCoord();

			} else if ((g_wall_data_temp[g_current_x][g_current_y] & 0x02) == 0
					&& g_step_map[g_current_x - 1][g_current_y]
							- g_step_map[g_current_x][g_current_y] == -1) {

				turnCorner(turn_90_R);

				checkOrient(-90);
				countCoord();

			} else {

				g_flag_gap = 1;
				runStraight(5, HALF_SECTION, 0.5, 0);

				waitTime(100);
				g_flag_gap = 0;

				turnCorner(pivot);

				waitTime(100);

				runStraight(5, HALF_SECTION, 0.5, 0.5);

				checkOrient(180);
				countCoord();

			}
		} else if (g_orient == 0x08) {
			if ((g_wall_data_temp[g_current_x][g_current_y] & 0x08) == 0
					&& g_step_map[g_current_x + 1][g_current_y]
							- g_step_map[g_current_x][g_current_y] == -1) {

				runStraight(5, SECTION, 0.5, 0.5);

				countCoord();

			} else if ((g_wall_data_temp[g_current_x][g_current_y] & 0x01) == 0
					&& g_step_map[g_current_x][g_current_y + 1]
							- g_step_map[g_current_x][g_current_y] == -1) {

				turnCorner(turn_90_L);

				checkOrient(90);
				countCoord();

			} else if ((g_wall_data_temp[g_current_x][g_current_y] & 0x04) == 0
					&& g_step_map[g_current_x][g_current_y - 1]
							- g_step_map[g_current_x][g_current_y] == -1) {

				turnCorner(turn_90_R);

				checkOrient(-90);
				countCoord();

			} else {

				g_flag_gap = 1;
				runStraight(5, HALF_SECTION, 0.5, 0);

				waitTime(100);
				g_flag_gap = 0;

				turnCorner(pivot);

				waitTime(100);

				runStraight(5, HALF_SECTION, 0.5, 0.5);

				checkOrient(180);
				countCoord();

			}
		}
	}
	g_flag_gap = 0;
	if (g_flag_adachi_goal == 1) {

		runStraight(5, HALF_SECTION, 0.5, 0);
		switchSensorLED(OFF);
		driveMotor(OFF);
		matchWallGoal();
	} else {
		switchSensorLED(OFF);

	}
}
