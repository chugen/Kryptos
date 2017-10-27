/*
 * map.c
 *
 *  Created on: 2016/10/06
 *      Author: Gen
 */

#include "iodefine.h"
#include <stdint.h>
#include <mathf.h>
#include "global.h"
#include "map.h"
#include "app.h"
#include "common.h"
#include "parameter.h"
#include "run.h"
#include "mathf.h"
#include "serial.h"
#include "sensor.h"
#include "my_typedef.h"

/****************************************
 方位管理
 ****************************************/
void checkOrient(int ori_deg) {
	if (ori_deg == 90) {
		shiftBit(&g_orient, 1, LEFT);

	} else if (ori_deg == -90) {
		shiftBit(&g_orient, 1, RIGHT);

	} else {
		shiftBit(&g_orient, 2, LEFT);

	}
}
/****************************************
 方位セット
 ****************************************/
void setOrient(uint8_t orient) {
	g_orient = orient;
}
/****************************************
 方向方位変換
 ****************************************/
uint8_t convDirToOrient(uint8_t dir) {
	uint8_t orient;

	orient = g_orient;
	switch (dir) {
	case WALL_FRONT:
		break;
	case WALL_LEFT:
		shiftBit(&orient, 1, LEFT);
		break;
	case WALL_RIGHT:
		shiftBit(&orient, 1, RIGHT);
		break;
	case WALL_BEHIND:
		shiftBit(&orient, 2, LEFT);
		break;
	default:
		break;
	}

	return orient;
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

	setWallDataKnown(g_wall_info_tmp, g_current_x, g_current_y);
}
void countCoord2(int8_t *x, int8_t *y) {
	if (g_orient == NORTH) {
		*x += 0;
		*y += 1;
	} else if (g_orient == EAST) {
		*x += 1;
		*y += 0;
	} else if (g_orient == SOUTH) {
		*x += 0;
		*y += -1;
	} else if (g_orient == WEST) {
		*x += -1;
		*y += 0;
	}
}
/****************************************
 現在座標セット
 ****************************************/
void setCurrentCoord(uint16_t x, uint16_t y) {
	g_current_x = x;
	g_current_y = y;
}
/****************************************
 目標座標セット
 ****************************************/
void setTargetCoord(uint16_t x, uint16_t y) {
	g_target_x = x;
	g_target_y = y;
}

/****************************************
 map表示
 ****************************************/
void printMap(void) {
	int i_x;
	int i_y;

	waitTime(500);
	myprintf("\x1b[2");
	myprintf("\x1b[31m");
	myprintf("\n\r");
	myprintf(" ");
	for (i_x = 0; i_x < 16; i_x++) {
		if (i_x == 10) {
			myprintf(" ");
		}
		myprintf("%4d", i_x);

	}
	myprintf("\n\r");

	for (i_y = 15; i_y >= 0; i_y--) {

		myprintf("  +");

		for (i_x = 0; i_x < 16; i_x++) {
			if (getWallData(g_wall_info_tmp, i_x, i_y, NORTH)) {
				myprintf("---");
			} else {
				myprintf("   ");
			}
			myprintf("+");
		}
		myprintf("\n\r");
		myprintf("%2d|", i_y);
		for (i_x = 0; i_x < 16; i_x++) {

			myprintf("\x1b[0m");
			if (isUnknownSection(i_x, i_y) != 1) {
				myprintf("\x1b[33m\x1b[49m\x1b[7m");
			}
			myprintf("%3d", g_step_map[i_x][i_y]);
			myprintf("\x1b[0m");
			myprintf("\x1b[31m");
			if (getWallData(g_wall_info_tmp, i_x, i_y, EAST)) {
				myprintf("|");
			} else {
				myprintf(" ");
			}
		}
		myprintf("%2d\n", i_y);
	}

	myprintf("  +");
	for (i_x = 0; i_x < 16; i_x++) {
		myprintf("---+");
	}

	myprintf("\n\r");
	myprintf(" ");
	for (i_x = 0; i_x < 16; i_x++) {
		if (i_x == 10) {
			myprintf(" ");
		}
		myprintf("%4d", i_x);

	}
	myprintf("\n\r");
	myprintf("\x1b[0m");

}

void printMapNew(void) {
	uint8_t i_x;
	int8_t i_y;

	waitTime(500);
	myprintf(ES_CLEAR);
	myprintf(ES_CURSOR_RESET);
	myprintf(ES_F_RED);
	myprintf("\n\r");
	myprintf(" ");
	for (i_x = 0; i_x < 16; i_x++) {
		if (i_x == 10) {
			myprintf(" ");
		}
		myprintf("%4d", i_x);
	}
	myprintf("\n\r");

	for (i_y = 15; i_y >= 0; i_y--) {

		myprintf("  +");

		for (i_x = 0; i_x < 16; i_x++) {
			if (getWallData(g_wall_info_tmp, i_x, i_y, NORTH)) {
				myprintf("---");
			} else {
				myprintf(ES_F_WHITE);
				myprintf("%3d", g_step[i_x].row[i_y]);
				myprintf(ES_F_RED);
			}
			myprintf("+");
		}
		myprintf("\n\r");
		myprintf("%2d| ", i_y);
		for (i_x = 0; i_x < 16; i_x++) {

			myprintf(ES_DEFAULT);
			if (isUnknownSection(i_x, i_y) != 1) {
				myprintf(ES_F_YELLOW);
				myprintf(ES_B_DEFAULT);
				myprintf(ES_FLIP);
			}

			myprintf(ES_DEFAULT);
			myprintf(ES_F_RED);
			if (getWallData(g_wall_info_tmp, i_x, i_y, EAST)) {
				myprintf("  | ");
			} else {
				myprintf(ES_F_WHITE);
				myprintf(" %3d", g_step[i_x].column[i_y]);
				myprintf(ES_F_RED);
			}
		}
		myprintf("%2d\n", i_y);
	}

	myprintf("  +");
	for (i_x = 0; i_x < 16; i_x++) {
		myprintf("---+");
	}

	myprintf("\n\r");
	myprintf(" ");
	for (i_x = 0; i_x < 16; i_x++) {
		if (i_x == 10) {
			myprintf(" ");
		}
		myprintf("%4d", i_x);

	}
	myprintf("\n\r");
	myprintf(ES_DEFAULT);

}
/****************************************
 壁情報セット
 ****************************************/
void setWallData(wall_t *wall_info, uint16_t x, uint16_t y, uint8_t orient,
		uint16_t wall) {
	switch (orient) {
	case NORTH:
		if (y < 15) {
			wall_info[y].row |= wall << x;
		}
		break;
	case WEST:
		if (x > 0) {
			wall_info[x - 1].column |= wall << y;
		}
		break;
	case SOUTH:
		if (y > 0) {
			wall_info[y - 1].row |= wall << x;
		}
		break;
	case EAST:
		if (x < 15) {
			wall_info[x].column |= wall << y;
		}
		break;
	default:
		break;
	}
}
void setWallDataKnown(wall_t *wall_info, uint16_t x, uint16_t y) {
	if (y < 15) {
		wall_info[y].row_known |= 1 << x;
	}
	if (y > 0) {
		wall_info[y - 1].row_known |= 1 << x;
	}
	if (x > 0) {
		wall_info[x - 1].column_known |= 1 << y;
	}
	if (x < 15) {
		wall_info[x].column_known |= 1 << y;
	}

}

/****************************************
 壁情報ゲット
 ****************************************/
uint8_t getWallData(wall_t *wall_info, uint16_t x, uint16_t y, uint8_t orient) {
	uint8_t tmp;
	wall_t *wall;
	wall = wall_info;
	switch (orient) {
	case NORTH:
		if (y < 15) {
			tmp = (wall[y].row >> x) & 0x01;
		} else {
			tmp = 0x01;
		}
		break;
	case WEST:
		if (x > 0) {
			tmp = (wall[x - 1].column >> y) & 0x01;
		} else {
			tmp = 0x01;
		}
		break;
	case SOUTH:
		if (y > 0) {
			tmp = (wall[y - 1].row >> x) & 0x01;
		} else {
			tmp = 0x01;
		}
		break;
	case EAST:
		if (x < 15) {
			tmp = (wall[x].column >> y) & 0x01;
		} else {
			tmp = 0x01;
		}
		break;
	default:
		break;
	}

	return tmp;

}
uint8_t getWallDataKnown(wall_t *wall_info, uint16_t x, uint16_t y,
		uint8_t orient) {
	uint8_t tmp;
	wall_t *wall;
	wall = wall_info;
	switch (orient) {
	case NORTH:
		if (y < 15) {
			tmp = (wall[y].row_known >> x) & 0x01;
		} else {
			tmp = 0x01;
		}
		break;
	case WEST:
		if (x > 0) {
			tmp = (wall[x - 1].column_known >> y) & 0x01;
		} else {
			tmp = 0x01;
		}
		break;
	case SOUTH:
		if (y > 0) {
			tmp = (wall[y - 1].row_known >> x) & 0x01;
		} else {
			tmp = 0x01;
		}
		break;
	case EAST:
		if (y < 15) {
			tmp = (wall[x].column_known >> y) & 0x01;
		} else {
			tmp = 0x01;
		}
		break;
	default:
		break;
	}
	return tmp;
}
/****************************************
 初期壁セット
 ****************************************/
void setInitWall(void) {

	setWallData(g_wall_info_tmp, 0, 0, EAST, 1);
	setWallDataKnown(g_wall_info_tmp, 0, 0);
}

/****************************************
 壁情報決定版
 ****************************************/
void matchWallGoal(void) {
	int i;
	for (i = 0; i < 15; i++) {
		//g_wall_data[i_x][i_y] = g_wall_data_tmp[i_x][i_y];
		g_wall_info[i] = g_wall_info_tmp[i];
	}
}

/****************************************
 壁情報読み込み
 ****************************************/
void checkWall(void) {

	setWallDataKnown(g_wall_info_tmp, g_current_x, g_current_y);

	if (g_sensor_L > SEN_NOWALL_L) {

		setWallData(g_wall_info_tmp, g_current_x, g_current_y,
				convDirToOrient(WALL_LEFT), 1);
	}
	if (g_sensor_R > SEN_NOWALL_R) {

		setWallData(g_wall_info_tmp, g_current_x, g_current_y,
				convDirToOrient(WALL_RIGHT), 1);
	}
	if ((g_sensor_FL + g_sensor_FR > SEN_NOWALL_FL + SEN_NOWALL_FR)
			&& g_sensor_FL > SEN_NOWALL_FL && g_sensor_FR > SEN_NOWALL_FR) {

		setWallData(g_wall_info_tmp, g_current_x, g_current_y,
				convDirToOrient(WALL_FRONT), 1);
	}
	//comb_breaker();
}
/****************************************
 壁データ有無判定
 ****************************************/
uint8_t isNoWall(wall_t *wall_info, uint8_t dir) {

	return getWallData(wall_info, g_current_x, g_current_y,
			convDirToOrient(dir)) != 1;
}
uint8_t isNoWall2(wall_t *wall_info, uint8_t x, uint8_t y, uint8_t dir) {

	return getWallData(wall_info, x, y, convDirToOrient(dir)) != 1;
}
/****************************************
 壁既知データ有無判定
 ****************************************/
uint8_t isUnknownWall(wall_t *wall_info, uint8_t dir) {

	return getWallDataKnown(wall_info, g_current_x, g_current_y,
			convDirToOrient(dir)) != 1;
}
/****************************************
 進行方向の歩数確認
 ****************************************/
uint8_t isSmallerSteps(uint8_t dir) {
	uint8_t bit = 0;
	int8_t x, y;

	bit = g_orient;
	if (dir == WALL_FRONT) {

	} else if (dir == WALL_LEFT) {
		shiftBit(&bit, 1, LEFT);
	} else if (dir == WALL_RIGHT) {
		shiftBit(&bit, 1, RIGHT);
	} else {

	}
	switch (bit) {
	case NORTH:
		x = 0;
		y = 1;
		break;
	case WEST:
		x = -1;
		y = 0;
		break;
	case SOUTH:
		x = 0;
		y = -1;
		break;
	case EAST:
		x = 1;
		y = 0;
		break;

	default:
		break;
	}
	return (g_step_map[g_current_x + x][g_current_y + y]
			- g_step_map[g_current_x][g_current_y]) < 0;

}
uint8_t isSmallerSteps2(uint8_t coord_x, uint8_t coord_y, uint8_t dir) {
	uint8_t bit = 0;
	int8_t x, y;

	bit = g_orient;
	if (dir == WALL_FRONT) {

	} else if (dir == WALL_LEFT) {
		shiftBit(&bit, 1, LEFT);
	} else if (dir == WALL_RIGHT) {
		shiftBit(&bit, 1, RIGHT);
	} else {

	}
	switch (bit) {
	case NORTH:
		x = 0;
		y = 1;
		break;
	case WEST:
		x = -1;
		y = 0;
		break;
	case SOUTH:
		x = 0;
		y = -1;
		break;
	case EAST:
		x = 1;
		y = 0;
		break;

	default:
		break;
	}
	return (g_step_map[coord_x + x][coord_y + y] - g_step_map[coord_x][coord_y])
			< 0;

}
/****************************************
 進行方向が未知か確認
 ****************************************/
uint8_t isUnknownSection(uint16_t x, uint16_t y) {
	uint8_t tmp;
	tmp = (getWallDataKnown(g_wall_info, x, y, NORTH)
			& getWallDataKnown(g_wall_info, x, y, EAST)
			& getWallDataKnown(g_wall_info, x, y, WEST)
			& getWallDataKnown(g_wall_info, x, y, SOUTH)) != 1;
	return tmp;
}
uint8_t isUnknownSection2(uint16_t x, uint16_t y) {
	uint8_t tmp;
	tmp = (getWallDataKnown(g_wall_info_tmp, x, y, NORTH)
			& getWallDataKnown(g_wall_info_tmp, x, y, EAST)
			& getWallDataKnown(g_wall_info_tmp, x, y, WEST)
			& getWallDataKnown(g_wall_info_tmp, x, y, SOUTH)) != 1;
	return tmp;
}
uint8_t isUnknownNextSection(uint8_t dir) {
	uint8_t tmp, bit = 0;
	int8_t x, y;

	bit = g_orient;
	if (dir == WALL_FRONT) {

	} else if (dir == WALL_LEFT) {
		shiftBit(&bit, 1, LEFT);
	} else if (dir == WALL_RIGHT) {
		shiftBit(&bit, 1, RIGHT);
	} else {

	}
	switch (bit) {
	case NORTH:
		x = 0;
		y = 1;
		break;
	case WEST:
		x = -1;
		y = 0;
		break;
	case SOUTH:
		x = 0;
		y = -1;
		break;
	case EAST:
		x = 1;
		y = 0;
		break;

	default:
		break;
	}

	tmp = (getWallDataKnown(g_wall_info_tmp, g_current_x + x, g_current_y + y,
	NORTH)
			& getWallDataKnown(g_wall_info_tmp, g_current_x + x,
					g_current_y + y, EAST)
			& getWallDataKnown(g_wall_info_tmp, g_current_x + x,
					g_current_y + y, WEST)
			& getWallDataKnown(g_wall_info_tmp, g_current_x + x,
					g_current_y + y, SOUTH)) != 1;
	return tmp;
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
			if (getWallData(g_wall_info_tmp, x, y, NORTH) == 0) {
				if (g_step_map[x][y + 1] == 255) {
					g_step_map[x][y + 1] = g_step_map[x][y] + 1;
					queue[tail] = (x + (y + 1) * 16);
					tail++;
				}
			}
		}
		if (x > 0) {
			if (getWallData(g_wall_info_tmp, x, y, WEST) == 0) {
				if (g_step_map[x - 1][y] == 255) {
					g_step_map[x - 1][y] = g_step_map[x][y] + 1;
					queue[tail] = (x - 1 + y * 16);
					tail++;
				}
			}
		}
		if (y > 0) {
			if (getWallData(g_wall_info_tmp, x, y, SOUTH) == 0) {
				if (g_step_map[x][y - 1] == 255) {
					g_step_map[x][y - 1] = g_step_map[x][y] + 1;
					queue[tail] = (x + (y - 1) * 16);
					tail++;
				}
			}
		}
		if (x < 16) {
			if (getWallData(g_wall_info_tmp, x, y, EAST) == 0) {
				if (g_step_map[x + 1][y] == 255) {
					g_step_map[x + 1][y] = g_step_map[x][y] + 1;
					queue[tail] = (x + 1 + y * 16);
					tail++;
				}
			}
		}

	}
}
void countStepQueueNew(void) {
	uint16_t i, j, NorE = 0;
	uint16_t const max = 200;
	uint8_t x, y, orient2;
	uint8_t plus_straight = 10, plus_diagonal = 7;
	short head = 0, tail = 1;
	uint16_t queue[200];

	setInitWall();

	for (i = 0; i < 16; i++) {
		for (j = 0; j < 16; j++) {
			g_step[i].row[j] = 999;
			g_step[i].column[j] = 999;
		}
	}

	g_step[g_target_x].row[g_target_y] = 0;
	g_step[g_target_x].column[g_target_y] = 0;
	queue[0] = (g_target_x + g_target_y * 16 + NorE * 256);

	NorE = 1;
	queue[tail] = (g_target_x + g_target_y * 16 + NorE * 256);
	tail++;

	while (head != tail) {
		orient2 = (queue[head] >> 8) & 0x0f;
		y = (queue[head] >> 4) & 0x0f;
		x = queue[head] & 0x0f;
		if (head + 1 == max) {
			head = 0;
		} else {
			head++;
		}
		//myprintf("head %d,tail %d \n", head, tail);

		if (orient2 == 0 && getWallData(g_wall_info_tmp, x, y, NORTH) == 0) {
			if (getWallData(g_wall_info_tmp, x, y, WEST) == 0) {
				if (g_step[x - 1].column[y]
						> g_step[x].row[y] + plus_diagonal) {
					g_step[x - 1].column[y] = g_step[x].row[y] + plus_diagonal;
					NorE = 1;
					queue[tail] = (x - 1 + (y) * 16 + NorE * 256);
					if (tail + 1 == max) {
						tail = 0;
					} else {
						tail++;
					}
				}

			}
			if (getWallData(g_wall_info_tmp, x, y, SOUTH) == 0) {
				if (g_step[x].row[y - 1] > g_step[x].row[y] + plus_straight) {
					g_step[x].row[y - 1] = g_step[x].row[y] + plus_straight;
					NorE = 0;
					queue[tail] = (x + (y - 1) * 16 + NorE * 256);
					if (tail + 1 == max) {
						tail = 0;
					} else {
						tail++;
					}
				}
			}
			if (getWallData(g_wall_info_tmp, x, y, EAST) == 0) {
				if (g_step[x].column[y] > g_step[x].row[y] + plus_diagonal) {
					g_step[x].column[y] = g_step[x].row[y] + plus_diagonal;
					NorE = 1;
					queue[tail] = (x + (y) * 16 + NorE * 256);
					if (tail + 1 == max) {
						tail = 0;
					} else {
						tail++;
					}
				}
			}
			if (getWallData(g_wall_info_tmp, x, y + 1, WEST) == 0) {
				if (g_step[x - 1].column[y + 1]
						> g_step[x].row[y] + plus_diagonal) {
					g_step[x - 1].column[y + 1] = g_step[x].row[y]
							+ plus_diagonal;
					NorE = 1;
					queue[tail] = (x - 1 + (y + 1) * 16 + NorE * 256);
					if (tail + 1 == max) {
						tail = 0;
					} else {
						tail++;
					}
				}
			}
			if (getWallData(g_wall_info_tmp, x, y + 1, NORTH) == 0) {
				if (g_step[x].row[y + 1] > g_step[x].row[y] + plus_straight) {
					g_step[x].row[y + 1] = g_step[x].row[y] + plus_straight;
					NorE = 0;
					queue[tail] = (x + (y + 1) * 16 + NorE * 256);
					if (tail + 1 == max) {
						tail = 0;
					} else {
						tail++;
					}
				}
			}
			if (getWallData(g_wall_info_tmp, x, y + 1, EAST) == 0) {
				if (g_step[x].column[y + 1]
						> g_step[x].row[y] + plus_diagonal) {
					g_step[x].column[y + 1] = g_step[x].row[y] + plus_diagonal;
					NorE = 1;
					queue[tail] = (x + (y + 1) * 16 + NorE * 256);
					if (tail + 1 == max) {
						tail = 0;
					} else {
						tail++;
					}
				}
			}
		} else if (orient2 == 1
				&& getWallData(g_wall_info_tmp, x, y, EAST) == 0) {
			if (getWallData(g_wall_info_tmp, x, y, NORTH) == 0) {
				if (g_step[x].row[y] > g_step[x].column[y] + plus_diagonal) {
					g_step[x].row[y] = g_step[x].column[y] + plus_diagonal;
					NorE = 0;
					queue[tail] = (x + (y) * 16 + NorE * 256);
					if (tail + 1 == max) {
						tail = 0;
					} else {
						tail++;
					}
				}
			}
			if (getWallData(g_wall_info_tmp, x, y, WEST) == 0) {
				if (g_step[x - 1].column[y]
						> g_step[x].column[y] + plus_straight) {
					g_step[x - 1].column[y] = g_step[x].column[y]
							+ plus_straight;
					NorE = 1;
					queue[tail] = (x - 1 + (y) * 16 + NorE * 256);
					if (tail + 1 == max) {
						tail = 0;
					} else {
						tail++;
					}
				}
			}
			if (getWallData(g_wall_info_tmp, x, y, SOUTH) == 0) {
				if (g_step[x].row[y - 1]
						> g_step[x].column[y] + plus_diagonal) {
					g_step[x].row[y - 1] = g_step[x].column[y] + plus_diagonal;
					NorE = 0;
					queue[tail] = (x + (y - 1) * 16 + NorE * 256);
					if (tail + 1 == max) {
						tail = 0;
					} else {
						tail++;
					}
				}
			}
			if (getWallData(g_wall_info_tmp, x + 1, y, NORTH) == 0) {
				if (g_step[x + 1].row[y]
						> g_step[x].column[y] + plus_diagonal) {
					g_step[x + 1].row[y] = g_step[x].column[y] + plus_diagonal;
					NorE = 0;
					queue[tail] = (x + 1 + (y) * 16 + NorE * 256);
					if (tail + 1 == max) {
						tail = 0;
					} else {
						tail++;
					}
				}
			}
			if (getWallData(g_wall_info_tmp, x + 1, y, SOUTH) == 0) {
				if (g_step[x + 1].row[y - 1]
						> g_step[x].column[y] + plus_diagonal) {
					g_step[x + 1].row[y - 1] = g_step[x].column[y]
							+ plus_diagonal;
					NorE = 0;
					queue[tail] = (x + 1 + (y - 1) * 16 + NorE * 256);
					if (tail + 1 == max) {
						tail = 0;
					} else {
						tail++;
					}
				}
			}
			if (getWallData(g_wall_info_tmp, x + 1, y, EAST) == 0) {
				if (g_step[x + 1].column[y]
						> g_step[x].column[y] + plus_straight) {
					g_step[x + 1].column[y] = g_step[x].column[y]
							+ plus_straight;
					NorE = 1;
					queue[tail] = (x + 1 + (y) * 16 + NorE * 256);
					if (tail + 1 == max) {
						tail = 0;
					} else {
						tail++;
					}
				}
			}
		}
	}
}
/****************************************
 足立法
 ****************************************/
void searchAdachi(void) {
	float search_velo = 0.7;
	float search_velo_known = 3;
	uint8_t i, known_section_count = 0;
	int8_t x_tmp = 0, y_tmp = 0;
	g_flag_run_mode = SEARCH;
	g_log_count = 0;
	driveSuction(5, OFF);
	runStraightSearch(5, HALF_SECTION, search_velo);

	countCoord();
	checkWall();
	countStepQueue();

	while (1) {
		//////////////////////////////////////////////////////////////////////////
		g_flag_adachi_goal = 0;
		if (g_current_x == g_target_x && g_current_y == g_target_y) {
			checkWall();
			g_flag_adachi_goal = 1;
			countStepQueue();
			break;
		}
		if (g_step_map[g_current_x][g_current_y] == 255) {

			driveMotor(OFF);
			soundError();
			break;
		}
		if (g_sensor_FL + g_sensor_FR >= SEN_DEATH) {

			driveMotor(OFF);
			soundError();
			break;
		}
		if (pushButton() == 0) {

			driveMotor(OFF);
			soundError();
			break;
		}

		//////////////////////////////////////////////////////////////////////////
		checkWall();

		g_distance = 0;
		g_current_velo = search_velo;
		countStepQueue();

		//////////////////////////////////////////////////////////////////////////
		x_tmp = g_current_x;
		y_tmp = g_current_y;
		known_section_count = 0;
		while (1) {

			if (isNoWall2(g_wall_info_tmp, x_tmp, y_tmp, WALL_FRONT)
					&& isSmallerSteps2(x_tmp, y_tmp, WALL_FRONT)
					&& (isUnknownSection2(x_tmp, y_tmp) != 1)) {
				known_section_count++;

			} else {
				break;
			}
			countCoord2(&x_tmp, &y_tmp);
			if (x_tmp < 0 || y_tmp < 0) {
				break;
			}

		}
		if (known_section_count >= 3) {
			runStraight(5, SECTION * (known_section_count - 1),
					search_velo_known, search_velo);
			runStraightSearch(0, SECTION, search_velo);
			for (i = 0; i < known_section_count; i++) {
				countCoord();
			}
			g_flag_run_known_section = 1;
		}
		//////////////////////////////////////////////////////////////////////////
		if (g_flag_run_known_section != 1) {
			if (isNoWall(g_wall_info_tmp, WALL_FRONT)
					&& isSmallerSteps(WALL_FRONT)) {

				runStraightSearch(0, SECTION, search_velo);
				countCoord();

			} else if (isNoWall(g_wall_info_tmp, WALL_LEFT)
					&& isSmallerSteps( WALL_LEFT)) {

				turnSearch(&tc_90_L_07);
				checkOrient(90);
				countCoord();

			} else if (isNoWall(g_wall_info_tmp, WALL_RIGHT)
					&& isSmallerSteps( WALL_RIGHT)) {

				turnSearch(&tc_90_R_07);
				checkOrient(-90);
				countCoord();

			} else {

				runBlindAlley(search_velo);

				checkOrient(180);
				countCoord();
			}
		}
		g_flag_run_known_section = 0;
	}
	if (g_flag_adachi_goal == 1) {
		driveSuction(5, OFF);
		if (isNoWall(g_wall_info_tmp, WALL_FRONT)) {
			runStraightSearch(0, SECTION, search_velo);
			countCoord();
		}
		runStraight(5, HALF_SECTION, search_velo, 0);

		g_flag_blindalley = 1;
		waitTime(500);
		g_flag_blindalley = 0;
		switchSensorLED(OFF);
		driveMotor(OFF);
		soundGoal();
	} else {
		driveMotor(OFF);
		switchSensorLED(OFF);
	}
	g_flag_run_mode = DEFAULT;
}
/****************************************d
 古川法
 ****************************************/
void searchFurukawa(void) {
	float search_velo = 0.7;
	float search_velo_known = 3;
	uint8_t i, known_section_count = 0;
	int8_t x_tmp = 0, y_tmp = 0;
	g_flag_run_mode = SEARCH;
	g_log_count = 0;
	driveSuction(5, OFF);
	runStraight(5, HALF_SECTION, search_velo, search_velo);
	countCoord();
	checkWall();
	countStepQueue();

	while (1) {
		//////////////////////////////////////////////////////////////////////////
		g_flag_adachi_goal = 0;
		if (g_current_x == g_target_x && g_current_y == g_target_y) {
			checkWall();
			g_flag_adachi_goal = 1;
			countStepQueue();
			break;
		}
		if (g_step_map[g_current_x][g_current_y] == 255) {
//			driveRGB(RED, ON);
			g_target_velo = 0;
			waitTime(100);
			driveMotor(OFF);
			soundError();

			break;
		}
		if (g_sensor_FL + g_sensor_FR >= SEN_DEATH) {
//			driveRGB(BLUE, ON);
			g_target_velo = 0;
			waitTime(100);
			driveMotor(OFF);
			soundError();
			break;
		}
		if (pushButton() == 0) {
//			driveRGB(MAGENTA, ON);
			g_target_velo = 0;
			waitTime(100);
			driveMotor(OFF);
			soundError();
			break;
		}

		//////////////////////////////////////////////////////////////////////////
		checkWall();

		g_distance = 0;
		g_current_velo = search_velo;
		countStepQueue();

		if (isNoWall(g_wall_info_tmp, WALL_FRONT)
				&& isUnknownNextSection(WALL_FRONT)) {

			runStraightSearch(0, SECTION, search_velo);

			countCoord();

		} else if (isNoWall(g_wall_info_tmp, WALL_LEFT)
				&& isUnknownNextSection( WALL_LEFT)) {

			turnSearch(&tc_90_L_07);

			checkOrient(90);
			countCoord();

		} else if (isNoWall(g_wall_info_tmp, WALL_RIGHT)
				&& isUnknownNextSection( WALL_RIGHT)) {

			turnSearch(&tc_90_R_07);

			checkOrient(-90);
			countCoord();

		} else {
			//////////////////////////////////////////////////////////////////////////
			x_tmp = g_current_x;
			y_tmp = g_current_y;
			known_section_count = 0;
			while (1) {

				if (isNoWall2(g_wall_info_tmp, x_tmp, y_tmp, WALL_FRONT)
						&& isSmallerSteps2(x_tmp, y_tmp, WALL_FRONT)
						&& (isUnknownSection2(x_tmp, y_tmp) != 1)) {
					driveRGB(BLUE, ON);

					known_section_count++;

				} else {
					break;
				}
				countCoord2(&x_tmp, &y_tmp);
				if (x_tmp < 0 || y_tmp < 0) {
					break;
				}

			}
			if (known_section_count >= 3) {
				runStraight(5, SECTION * (known_section_count - 1),
						search_velo_known, search_velo);
				runStraightSearch(0, SECTION, search_velo);
				for (i = 0; i < known_section_count; i++) {
					countCoord();
				}
				g_flag_run_known_section = 1;
			}
			//////////////////////////////////////////////////////////////////////////
			if (g_flag_run_known_section != 1) {
				if (isNoWall(g_wall_info_tmp, WALL_FRONT)
						&& isSmallerSteps(WALL_FRONT)) {
					driveRGB(BLUE, OFF);
					runStraightSearch(0, SECTION, search_velo);

					countCoord();

				} else if (isNoWall(g_wall_info_tmp, WALL_LEFT)
						&& isSmallerSteps( WALL_LEFT)) {

					turnSearch(&tc_90_L_07);

					checkOrient(90);
					countCoord();

				} else if (isNoWall(g_wall_info_tmp, WALL_RIGHT)
						&& isSmallerSteps(WALL_RIGHT)) {

					turnSearch(&tc_90_R_07);

					checkOrient(-90);
					countCoord();

				} else {
					runBlindAlley(search_velo);

					checkOrient(180);
					countCoord();
				}
			}
			g_flag_run_known_section = 0;
		}
	}

	if (g_flag_adachi_goal == 1) {
		driveSuction(5, OFF);
		if (isNoWall(g_wall_info_tmp, WALL_FRONT)) {
			runStraightSearch(0, SECTION, search_velo);
			countCoord();
		}
		runStraight(5, HALF_SECTION, search_velo, 0);

		g_flag_blindalley = 1;
		waitTime(500);
		g_flag_blindalley = 0;
		driveMotor(OFF);
		switchSensorLED(OFF);
		soundGoal();
		matchWallGoal();
	} else {
		driveSuction(5, OFF);
		driveMotor(OFF);
		switchSensorLED(OFF);

	}
	g_flag_run_mode = DEFAULT;
}

/****************************************
 櫛潰し
 ****************************************/
void breakComb(void) {

}

/****************************************
 最短キュー
 ****************************************/
void countStepShortest(void) {
	int i, j;
	unsigned char x, y;
	short head = 0, tail = 1;
	unsigned char queue_s[257];

	g_current_x = START_X;
	g_current_y = START_Y;
	g_target_x = GOAL_X;
	g_target_y = GOAL_Y;
	g_orient = 0x01;

	for (i = 0; i < 16; i++) {
		for (j = 0; j < 16; j++) {
			g_step_map[i][j] = 255;
		}
	}

	g_step_map[g_target_x][g_target_y] = 0;

	queue_s[0] = (g_target_x + g_target_y * 16);

	while (head != tail) {
		y = queue_s[head] >> 4;
		x = queue_s[head] & 0x0f;
		head++;
		if (y < 16) {
			if (getWallData(g_wall_info, x, y, NORTH) == 0
					&& getWallDataKnown(g_wall_info, x, y, NORTH) == 1) {
				if (g_step_map[x][y + 1] == 255) {
					g_step_map[x][y + 1] = g_step_map[x][y] + 1;
					queue_s[tail] = (x + (y + 1) * 16);
					tail++;
				}
			}
		}
		if (x > 0) {
			if (getWallData(g_wall_info, x, y, WEST) == 0
					&& getWallDataKnown(g_wall_info, x, y, WEST) == 1) {
				if (g_step_map[x - 1][y] == 255) {
					g_step_map[x - 1][y] = g_step_map[x][y] + 1;
					queue_s[tail] = (x - 1 + y * 16);
					tail++;
				}
			}
		}
		if (y > 0) {
			if (getWallData(g_wall_info, x, y, SOUTH) == 0
					&& getWallDataKnown(g_wall_info, x, y, SOUTH) == 1) {
				if (g_step_map[x][y - 1] == 255) {
					g_step_map[x][y - 1] = g_step_map[x][y] + 1;
					queue_s[tail] = (x + (y - 1) * 16);
					tail++;
				}
			}
		}
		if (x < 16) {
			if (getWallData(g_wall_info, x, y, EAST) == 0
					&& getWallDataKnown(g_wall_info, x, y, EAST) == 1) {
				if (g_step_map[x + 1][y] == 255) {
					g_step_map[x + 1][y] = g_step_map[x][y] + 1;
					queue_s[tail] = (x + 1 + y * 16);
					tail++;
				}
			}
		}

	}
}

/****************************************
 path生成(小回り)
 ****************************************/
void makePath(void) {
	int p_count = 0;
	g_path[0] = STRAIGHT;
	setOrient(NORTH);
	setCurrentCoord(START_X, START_Y);
	setTargetCoord(GOAL_X, GOAL_Y);
	countCoord();
	while (1) {
		p_count++;
		if (g_current_x == g_target_x && g_current_y == g_target_y)
			break;

		if (isNoWall(g_wall_info, WALL_FRONT) && isSmallerSteps(WALL_FRONT)
				&& isUnknownWall(g_wall_info, WALL_FRONT) != 1) {

			g_path[p_count] = STRAIGHT;
			p_count++;
			g_path[p_count] = STRAIGHT;
			myprintf("1");
			countCoord();

		} else if (isNoWall(g_wall_info, WALL_LEFT) && isSmallerSteps(WALL_LEFT)
				&& isUnknownWall(g_wall_info, WALL_LEFT) != 1) {

			g_path[p_count] = L_CURVE;

			checkOrient(90);
			countCoord();
			myprintf("2");

		} else if (isNoWall(g_wall_info, WALL_RIGHT)
				&& isSmallerSteps(WALL_RIGHT)
				&& isUnknownWall(g_wall_info, WALL_RIGHT) != 1) {

			g_path[p_count] = R_CURVE;

			checkOrient(-90);
			countCoord();
			myprintf("3");

		} else {

			g_path[p_count] = ERROR;
			driveRGB(RED, ON);
			checkOrient(180);
			countCoord();
			myprintf("E");

		}

	}
	g_path[p_count] = STRAIGHT;
	g_flag_step_goal = p_count;
}
/****************************************
 path生成2(斜めなし,w90,180)
 ****************************************/
void makePath2(void) {
	int i, j = 0;
	int s_count = 0;

	for (i = 0; i <= g_flag_step_goal; i++) {
		if (g_path[i] == STRAIGHT) {
			s_count++;
		} else if (g_path[i] == L_CURVE) {
			if (i == 1) {
				g_path_2[j] = s_count;
				j++;
				g_path_2[j] = S_L_CURVE;
				s_count = 0;
			} else if (g_path[i - 1] == STRAIGHT && g_path[i + 1] == STRAIGHT) {
				if (s_count - 1 > 0) {
					g_path_2[j] = s_count - 1;
					j++;
				}
				s_count = -1;
				g_path_2[j] = S_BIG_L_CURVE;
			} else if (g_path[i - 1] == STRAIGHT && g_path[i + 1] == L_CURVE
					&& g_path[i + 2] == STRAIGHT) {
				if (s_count - 1 > 0) {
					g_path_2[j] = s_count - 1;
					j++;
				}
				s_count = -1;
				g_path_2[j] = S_U_L_CURVE;
				i++;
			} else {
				if (s_count > 0) {
					g_path_2[j] = s_count;
					j++;
				}
				s_count = 0;
				g_path_2[j] = S_L_CURVE;
			}
			j++;
		} else if (g_path[i] == R_CURVE) {
			if (i == 1) {
				g_path_2[j] = s_count;
				j++;
				g_path_2[j] = S_R_CURVE;
				s_count = 0;
			} else if (g_path[i - 1] == STRAIGHT && g_path[i + 1] == STRAIGHT) {
				if (s_count - 1 > 0) {
					g_path_2[j] = s_count - 1;
					j++;
				}
				s_count = -1;

				g_path_2[j] = S_BIG_R_CURVE;
			} else if (g_path[i - 1] == STRAIGHT && g_path[i + 1] == R_CURVE
					&& g_path[i + 2] == STRAIGHT) {
				if (s_count - 1 > 0) {
					g_path_2[j] = s_count - 1;
					j++;
				}
				s_count = -1;
				g_path_2[j] = S_U_R_CURVE;
				i++;
			} else {
				if (s_count > 0) {
					g_path_2[j] = s_count;
					j++;
				}
				s_count = 0;
				g_path_2[j] = S_R_CURVE;
			}
			j++;
		}
	}
	if (s_count > 0) {
		g_path_2[j] = s_count;
	} else {
		j--;
	}
	g_flag_step_goal_2 = j;
}
/****************************************
 path生成3(斜めあり)
 ****************************************/
void makePath3(void) {
	int i, j = 0;
	int s_count = 0;
	int diagonal_count = 0;
	char diagonal_flag = 0;

	for (i = 0; i <= g_flag_step_goal; i++) {
		if (g_path[i] == STRAIGHT) {
			s_count++;
		} else if (g_path[i] == L_CURVE) {
			/*if (i == 1) {//開幕大回りできないとき用
			 g_path_3[j] = s_count;
			 j++;
			 g_path_3[j] = S_L_CURVE;
			 s_count = 0;
			 } else */
			if (g_path[i - 1] == STRAIGHT && g_path[i + 1] == STRAIGHT) {
				//大回り
				if (s_count - 1 > 0) {
					g_path_3[j] = s_count - 1;
					j++;
					s_count = 0;
				}
				s_count = -1;
				g_path_3[j] = S_BIG_L_CURVE;
			} else if (g_path[i - 1] == STRAIGHT && g_path[i + 1] == L_CURVE
					&& g_path[i + 2] == STRAIGHT) {
				//Uターン
				if (s_count - 1 > 0) {
					g_path_3[j] = s_count - 1;
					j++;
					s_count = 0;
				}
				s_count = -1;
				g_path_3[j] = S_U_L_CURVE;
				i += 1;
			} else if (g_path[i - 1] == STRAIGHT && g_path[i + 1] == R_CURVE) {
				//入45度ターン
				if (s_count - 1 > 0) {
					g_path_3[j] = s_count - 1;
					j++;
					s_count = 0;
				}
				g_path_3[j] = L_45_I;
				diagonal_flag = 1;
			} else if (g_path[i + 1] == STRAIGHT && diagonal_flag == 1) {
				//出45度ターン
				if (diagonal_count > 0) {
					g_path_3[j] = DIAGONAL + diagonal_count;
					j++;
					diagonal_count = 0;
				}
				g_path_3[j] = L_45_O;
				s_count = -1;
				diagonal_flag = 0;
			} else if (g_path[i + 1] == L_CURVE && g_path[i + 2] == R_CURVE
					&& diagonal_flag == 1) {
				//斜め90度ターン
				if (diagonal_count > 0) {
					g_path_3[j] = DIAGONAL + diagonal_count;
					j++;
					diagonal_count = 0;
				}
				g_path_3[j] = L_V90;
				i += 1;
			} else if (g_path[i - 1] == STRAIGHT && g_path[i + 1] == L_CURVE) {
				//入135度ターン
				if (s_count - 1 > 0) {
					g_path_3[j] = s_count - 1;
					j++;
					s_count = 0;
				}
				g_path_3[j] = L_135_I;
				i += 1;
				diagonal_flag = 1;
			} else if (g_path[i + 1] == L_CURVE && g_path[i + 2] == STRAIGHT
					&& diagonal_flag == 1) {
				//出135度ターン
				if (diagonal_count > 0) {
					g_path_3[j] = DIAGONAL + diagonal_count;
					j++;
					diagonal_count = 0;
				}
				s_count = -1;
				g_path_3[j] = L_135_O;
				i += 1;
				diagonal_flag = 0;
			} else if (g_path[i - 1] == R_CURVE && g_path[i + 1] == R_CURVE
					&& diagonal_flag == 1) {
				//斜め直線
				diagonal_count += 1;
				j--;
			} else {
				if (s_count > 0) {
					g_path_3[j] = s_count;
					j++;
				}
				s_count = 0;
				g_path_3[j] = S_L_CURVE;
			}
			j++;
		} else if (g_path[i] == R_CURVE) {
			/*if (i == 1) {
			 g_path_3[j] = s_count;
			 j++;
			 g_path_3[j] = S_R_CURVE;
			 s_count = 0;
			 } else*/
			if (g_path[i - 1] == STRAIGHT && g_path[i + 1] == STRAIGHT) {
				//大回り
				if (s_count - 1 > 0) {
					g_path_3[j] = s_count - 1;
					j++;
					s_count = 0;
				}
				s_count = -1;

				g_path_3[j] = S_BIG_R_CURVE;
			} else if (g_path[i - 1] == STRAIGHT && g_path[i + 1] == R_CURVE
					&& g_path[i + 2] == STRAIGHT) {
				//Uターン
				if (s_count - 1 > 0) {
					g_path_3[j] = s_count - 1;
					j++;
					s_count = 0;
				}
				s_count = -1;
				g_path_3[j] = S_U_R_CURVE;
				i += 1;
			} else if (g_path[i - 1] == STRAIGHT && g_path[i + 1] == L_CURVE) {
				//入45度ターン
				if (s_count - 1 > 0) {
					g_path_3[j] = s_count - 1;
					j++;
					s_count = 0;
				}
				g_path_3[j] = R_45_I;
				diagonal_flag = 1;
			} else if (g_path[i + 1] == STRAIGHT && diagonal_flag == 1) {
				//出45度ターン
				if (diagonal_count > 0) {
					g_path_3[j] = DIAGONAL + diagonal_count;
					j++;
					diagonal_count = 0;
				}
				g_path_3[j] = R_45_O;
				s_count = -1;
				diagonal_flag = 0;
			} else if (g_path[i + 1] == R_CURVE && g_path[i + 2] == L_CURVE
					&& diagonal_flag == 1) {
				//斜め90度ターン
				if (diagonal_count > 0) {
					g_path_3[j] = DIAGONAL + diagonal_count;
					j++;
					diagonal_count = 0;
				}
				g_path_3[j] = R_V90;
				i += 1;
			} else if (g_path[i - 1] == STRAIGHT && g_path[i + 1] == R_CURVE) {
				//入135度ターン
				if (s_count - 1 > 0) {
					g_path_3[j] = s_count - 1;
					j++;
					s_count = 0;
				}
				g_path_3[j] = R_135_I;
				i += 1;
				diagonal_flag = 1;
			} else if (g_path[i + 1] == R_CURVE && g_path[i + 2] == STRAIGHT
					&& diagonal_flag == 1) {
				//出135度ターン
				if (diagonal_count > 0) {
					g_path_3[j] = DIAGONAL + diagonal_count;
					j++;
					diagonal_count = 0;
				}
				s_count = -1;
				g_path_3[j] = R_135_O;
				i += 1;
				diagonal_flag = 0;
			} else if (g_path[i - 1] == L_CURVE && g_path[i + 1] == L_CURVE
					&& diagonal_flag == 1) {
				//斜め直線
				diagonal_count += 1;
				j--;
			} else {
				if (s_count > 0) {
					g_path_3[j] = s_count;
					j++;
				}
				s_count = 0;
				g_path_3[j] = S_R_CURVE;
			}
			j++;
		}
	}

	if (s_count > 0) {
		g_path_3[j] = s_count;
	} else {
		j--;
	}
	g_flag_step_goal_3 = j;
}
/****************************************
 path表示
 ****************************************/
void printPath(void) {
	int i = 0;

	myprintf("PATH1\n\r");
	myprintf("/////START/////\n\r");
	while (1) {
		if (i > g_flag_step_goal)
			break;
		if (g_path[i] == 0x01) {
			myprintf("path[%d]=STRAIGHT\n\r", i);
		} else if (g_path[i] == 0x02) {
			myprintf("path[%d]=L_CURVE\n\r", i);
		} else if (g_path[i] == 0x04) {
			myprintf("path[%d]=R_CURVE\n\r", i);
		} else {
			myprintf("path[%d]=ERROR:%d\n\r", i, g_path[i]);
		}
		i++;
	}
	myprintf("/////GOAL/////\n\r");
}

/****************************************
 path表示2
 ****************************************/
void printPath2(void) {
	int i = 0;

	myprintf("PATH2\n\r");
	myprintf("/////START/////\n\r");
	while (1) {
		if (i > g_flag_step_goal_2)
			break;
		if (g_path_2[i] > 0 && g_path_2[i] <= 30) {
			myprintf("path[%d]=STRAIGHT*%d\n\r", i, g_path_2[i]);
		} else if (g_path_2[i] == S_L_CURVE) {
			myprintf("path[%d]=L_CURVE\n\r", i);
		} else if (g_path_2[i] == S_BIG_L_CURVE) {
			myprintf("path[%d]=BIG_L_CURVE\n\r", i);
		} else if (g_path_2[i] == S_U_L_CURVE) {
			myprintf("path[%d]=U_L_CURVE\n\r", i);
		} else if (g_path_2[i] == S_R_CURVE) {
			myprintf("path[%d]=R_CURVE\n\r", i);
		} else if (g_path_2[i] == S_BIG_R_CURVE) {
			myprintf("path[%d]=BIG_R_CURVE\n\r", i);
		} else if (g_path_2[i] == S_U_R_CURVE) {
			myprintf("path[%d]=U_R_CURVE\n\r", i);
		} else {
			myprintf("path[%d]=ERROR:%d\n\r", i, g_path_2[i]);
		}
		i++;
	}
	myprintf("/////GOAL/////\n\r");
}

/****************************************
 path表示3
 ****************************************/
void printPath3(void) {
	int i = 0;
	myprintf("\x1b[39m\x1b[49m\x1b[0m");
	myprintf("PATH3\n\r");
	myprintf("/////START/////\n\r");
	while (1) {
		if (i > g_flag_step_goal_3)
			break;
		if (g_path_3[i] > 0 && g_path_3[i] <= 30) {
			myprintf("path[%d]=STRAIGHT*%d\n\r", i, g_path_3[i]);
		} else if (g_path_3[i] == S_L_CURVE) {
			myprintf("path[%d]=L_CURVE\n\r", i);
		} else if (g_path_3[i] == S_BIG_L_CURVE) {
			myprintf("path[%d]=BIG_L_CURVE\n\r", i);
		} else if (g_path_3[i] == S_U_L_CURVE) {
			myprintf("path[%d]=U_L_CURVE\n\r", i);
		} else if (g_path_3[i] == S_R_CURVE) {
			myprintf("path[%d]=R_CURVE\n\r", i);
		} else if (g_path_3[i] == S_BIG_R_CURVE) {
			myprintf("path[%d]=BIG_R_CURVE\n\r", i);
		} else if (g_path_3[i] == S_U_R_CURVE) {
			myprintf("path[%d]=U_R_CURVE\n\r", i);
		} else if (g_path_3[i] == L_45_I) {
			myprintf("path[%d]=L_45_I\n\r", i);
		} else if (g_path_3[i] == L_45_O) {
			myprintf("path[%d]=L_45_O\n\r", i);
		} else if (g_path_3[i] == R_45_I) {
			myprintf("path[%d]=R_45_I\n\r", i);
		} else if (g_path_3[i] == R_45_O) {
			myprintf("path[%d]=R_45_O\n\r", i);
		} else if (g_path_3[i] == L_135_I) {
			myprintf("path[%d]=L_135_I\n\r", i);
		} else if (g_path_3[i] == L_135_O) {
			myprintf("path[%d]=L_135_O\n\r", i);
		} else if (g_path_3[i] == R_135_I) {
			myprintf("path[%d]=R_135_I\n\r", i);
		} else if (g_path_3[i] == R_135_O) {
			myprintf("path[%d]=R_135_O\n\r", i);
		} else if (g_path_3[i] == L_V90) {
			myprintf("path[%d]=L_SLA_90\n\r", i);
		} else if (g_path_3[i] == R_V90) {
			myprintf("path[%d]=R_SLA_90\n\r", i);
		} else if (g_path_3[i] >= DIAGONAL) {
			myprintf("path[%d]=SLANT*%d\n\r", i, g_path_3[i] - DIAGONAL + 1);
		} else {
			myprintf("path[%d]=ERROR:%d\n\r", i, g_path_3[i]);
		}
		i++;
	}
	myprintf("/////GOAL/////\n\r");
}
/****************************************
 path表示test
 ****************************************/
void printPathTest(void) {
	int i = 0;
	g_target_x = GOAL_X;
	g_target_y = GOAL_Y;
	countStepShortest();
	g_current_x = START_X;
	g_current_y = START_Y;
	g_orient = 0x01;
	makePath();
	makePath2();
	myprintf("PATH_TEST\n\r");
	myprintf("{");
	for (i = 0; i < g_flag_step_goal_2; i++) {
		myprintf("%d,", g_path_2[i]);
	}
	myprintf("%d};\n\r", g_path_2[g_flag_step_goal_2]);
}

/****************************************
 path表示test斜め
 ****************************************/
void printPathTestDiagonal(void) {
	int i = 0;
	g_target_x = GOAL_X;
	g_target_y = GOAL_Y;
	countStepShortest();
	g_current_x = START_X;
	g_current_y = START_Y;
	g_orient = 0x01;
	makePath();
	makePath3();
	myprintf("PATH_TEST_SLANT\n\r");
	myprintf("{");
	for (i = 0; i < g_flag_step_goal_3; i++) {
		myprintf("%d,", g_path_3[i]);
	}
	myprintf("%d};\n\r", g_path_3[g_flag_step_goal_3]);
}

/****************************************
 path走行
 ****************************************/
void runPath(void) {
	int i = 0;

	g_flag_diagonal = 0;
	g_flag_run_mode = RUN;
	while (1) {
		g_flag_path_run_goal = 0;
		if (i > g_flag_step_goal_2) {
			g_flag_path_run_goal = 1;
			break;
		}
		if ((g_sensor_FL + g_sensor_FR >= SEN_DEATH) || (g_flag_failsafe == 1))
			break;
		if (g_path_2[i] > 0 && g_path_2[i] <= 30) {
			runStraight(20, HALF_SECTION * g_path_2[i] + addInitDis(i), 4,
					connectSpeedEnd(i));
		} else if (g_path_2[i] == S_L_CURVE) {
			turnCorner(&t_90_L_05);
		} else if (g_path_2[i] == S_BIG_L_CURVE) {
			turnCorner(&t_w90_L_10);
		} else if (g_path_2[i] == S_U_L_CURVE) {
			turnCorner(&t_180_L_10);
		} else if (g_path_2[i] == S_R_CURVE) {
			turnCorner(&t_90_R_05);
		} else if (g_path_2[i] == S_BIG_R_CURVE) {
			turnCorner(&t_w90_R_10);
		} else if (g_path_2[i] == S_U_R_CURVE) {
			turnCorner(&t_180_R_10);
		} else {
			//full_color(0, 255, 0);
		}
		i++;
		g_current_x = 1;
	}
	driveSuction(70, OFF);
	driveMotor(OFF);
	switchSensorLED(OFF);
	if (g_flag_path_run_goal == 1) {
		soundGoal();
	} else {
		soundError();
	}
	g_flag_run_mode = DEFAULT;
}

/****************************************
 斜めpath走行
 ****************************************/
void runPathDiagonal(uint8_t t_velo, float velo, float acc, float d_velo,
		float d_acc) {
	int i = 0;
	float velocity;

	g_flag_failsafe = 0;
	g_flag_diagonal = 0;
	g_flag_run_mode = RUN;

	switch (t_velo) {
	case T10:
		velocity = 1.0;
		break;
	case T12:
		velocity = 1.2;
		break;
	case T14:
		velocity = 1.4;
		break;
	case T16:
		velocity = 1.6;
		break;
	case T18:
		velocity = 1.8;
		break;
	}
	if (g_path_3[0] >= 31) {
		runStraight(25, INIT_DIS, velo, velocity);
	}
	while (1) {
		g_flag_path_run_goal = 0;
		if (i == g_flag_step_goal_3) {
			g_flag_shortest_goal = 1;
		}
		if (i > g_flag_step_goal_3) {
			g_flag_path_run_goal = 1;
			break;
		}
		if ((g_sensor_FL + g_sensor_FR >= SEN_DEATH) || (g_flag_failsafe == 1))
			break;
		if (g_path_3[i] > 0 && g_path_3[i] <= 30) {
			runStraight(acc, HALF_SECTION * g_path_3[i] + addInitDis(i), velo,
					velocity);
		} else if (g_path_3[i] == S_L_CURVE) {
			turnShortest(&tc_90_L_07);
		} else if (g_path_3[i] == S_BIG_L_CURVE) {
			turnShortest(tc_para[t_velo][W90L]);
		} else if (g_path_3[i] == S_U_L_CURVE) {
			turnShortest(tc_para[t_velo][T180L]);
		} else if (g_path_3[i] == S_R_CURVE) {
			turnShortest(&tc_90_R_07);
		} else if (g_path_3[i] == S_BIG_R_CURVE) {
			turnShortest(tc_para[t_velo][W90R]);
		} else if (g_path_3[i] == S_U_R_CURVE) {
			turnShortest(tc_para[t_velo][T180R]);
		} else if (g_path_3[i] == L_45_I) {
			turnShortest(tc_para[t_velo][I45L]);
		} else if (g_path_3[i] == R_45_I) {
			turnShortest(tc_para[t_velo][I45R]);
		} else if (g_path_3[i] == L_45_O) {
			turnShortest(tc_para[t_velo][O45L]);
		} else if (g_path_3[i] == R_45_O) {
			turnShortest(tc_para[t_velo][O45R]);
		} else if (g_path_3[i] == L_135_I) {
			turnShortest(tc_para[t_velo][I135L]);
		} else if (g_path_3[i] == R_135_I) {
			turnShortest(tc_para[t_velo][I135R]);
		} else if (g_path_3[i] == L_135_O) {
			turnShortest(tc_para[t_velo][O135L]);
		} else if (g_path_3[i] == R_135_O) {
			turnShortest(tc_para[t_velo][O135R]);
		} else if (g_path_3[i] == L_V90) {
			turnShortest(tc_para[t_velo][V90L]);
		} else if (g_path_3[i] == R_V90) {
			turnShortest(tc_para[t_velo][V90R]);
		} else if (g_path_3[i] > 47 && g_path_3[i] <= 113) {
			runStraight(d_acc, sqrtf(2) * HALF_SECTION * (g_path_3[i] - 47),
					d_velo, velocity);
		} else {
		}
		i++;

		g_current_x = 1;
	}
	processShotestGoal();
	driveSuction(70, OFF);
	driveMotor(OFF);
	switchSensorLED(OFF);

	if (g_flag_path_run_goal == 1) {
		soundGoal();
	} else {
		soundError();
	}
	g_flag_run_mode = DEFAULT;
}

/****************************************
 スピードコネクト
 ****************************************/

float connectSpeedEnd(int esc) {
	if ((g_path_2[esc] & 0x80) == 0x80) {
		return 0;
	} else if (g_path_2[esc + 1] == S_L_CURVE || g_path_2[esc + 1] == S_R_CURVE) {
		return t_90_L_05.velocity;
	} else if (g_path_2[esc + 1] == S_BIG_L_CURVE
			|| g_path_2[esc + 1] == S_BIG_R_CURVE) {
		return t_w90_L_10.velocity;
	} else if (g_path_2[esc + 1] == S_U_L_CURVE
			|| g_path_2[esc + 1] == S_U_R_CURVE) {
		return t_180_L_10.velocity;
	} else {
		return 1;
	}
}

float connectSpeed1000(int esc) {
	if (esc == g_flag_step_goal_3) {
		return 0;
	} else if (g_path_3[esc + 1] == S_L_CURVE || g_path_3[esc + 1] == S_L_CURVE) {
		return t_90_L_05.velocity;
	} else if (g_path_3[esc + 1] == S_BIG_L_CURVE
			|| g_path_3[esc + 1] == S_BIG_R_CURVE) {
		return t_w90_L_10.velocity;
	} else if (g_path_3[esc + 1] == S_U_L_CURVE
			|| g_path_3[esc + 1] == S_U_R_CURVE) {
		return t_180_L_10.velocity;
	} else if (g_path_3[esc + 1] == L_45_I || g_path_3[esc + 1] == R_45_I) {
		return t_i45_L_10.velocity;
	} else if (g_path_3[esc + 1] == L_135_I || g_path_3[esc + 1] == R_135_I) {
		return t_i135_L_10.velocity;
	} else if (g_path_3[esc + 1] == L_V90 || g_path_3[esc + 1] == R_V90) {
		return t_v90_L_10.velocity;
	} else {
		return 1;
	}
}

float connectSpeed1200(int esc) {
	if (esc == g_flag_step_goal_3) {
		return 0;
	} else if (g_path_3[esc + 1] == S_L_CURVE || g_path_3[esc + 1] == S_L_CURVE) {
		return t_90_L_05.velocity;
	} else if (g_path_3[esc + 1] == S_BIG_L_CURVE
			|| g_path_3[esc + 1] == S_BIG_R_CURVE) {
		return t_w90_L_12.velocity;
	} else if (g_path_3[esc + 1] == S_U_L_CURVE
			|| g_path_3[esc + 1] == S_U_R_CURVE) {
		return t_180_L_12.velocity;
	} else if (g_path_3[esc + 1] == L_45_I || g_path_3[esc + 1] == R_45_I) {
		return t_i45_L_12.velocity;
	} else if (g_path_3[esc + 1] == L_135_I || g_path_3[esc + 1] == R_135_I) {
		return t_i135_L_12.velocity;
	} else if (g_path_3[esc + 1] == L_V90 || g_path_3[esc + 1] == R_V90) {
		return t_v90_L_12.velocity;
	} else {
		return 1;
	}
}

/****************************************
 path走行 初期距離追加
 ****************************************/
float addInitDis(uint16_t count) {
	if (count == 0) {
		return INIT_DIS;
	} else {
		return 0;
	}
}
/****************************************
 最短ゴール処理
 ****************************************/
void processShotestGoal(void) {

	switchSensorLED(OFF);
	runStraight(25, 0.01, g_current_velo, 0);
}
/****************************************
 サーキット
 ****************************************/
void selectModeCircuit(void) {
	waitTime(300);
//full_color(255, 255, 0);
	switch (selectMode(4)) {
	case 0:
		//	circuit_ctrl(1500, 2);
		break;
	case 1:
		//circuit_ctrl(1800, 2);
		break;
	case 2:
		//circuit_ctrl(2000, 2);

		break;
	case 3:
		//circuit_ctrl(2100, 2);
		break;
	case 4:
		//circuit_ctrl(2200, 2);
		break;

	default:
		break;
	}
}
