/*
 * map.h
 *
 *  Created on: 2016/10/06
 *      Author: Gen
 */

#ifndef MAP_H_
#define MAP_H_

/****************************************
 方位管理
 ****************************************/
void checkOrient(int ori_deg);
/****************************************
 方位セット
 ****************************************/
void setOrient(uint8_t orient);
/****************************************
 座標管理
 ****************************************/
void countCoord(void);
/****************************************
現在座標セット
 ****************************************/
void setCurrentCoord(uint16_t x,uint16_t y);
/****************************************
ゴール座標セット
 ****************************************/
void setGoalCoord(uint16_t x,uint16_t y);
/****************************************
 map表示
 ****************************************/
void printMap(void);
/****************************************
 初期壁セット
 ****************************************/
void setInitWall(void);
/****************************************
 壁情報一致
 ****************************************/
void matchWall(void);
/****************************************
 壁情報決定版
 ****************************************/
void matchWallGoal(void) ;

/****************************************
 壁情報読み込み
 ****************************************/
void checkWall(void);

/****************************************
 queuemap
 ****************************************/
void countStepQueue(void);
/****************************************
 足立法
 ****************************************/
void searchAdachi(void);
/****************************************
 古川法
 ****************************************/
void searchFurukawa(void);
/****************************************
 櫛潰し
 ****************************************/
void breakComb(void);
/****************************************
 最短
 ****************************************/
void countStepShortest(void);
/****************************************
 探索表示
 ****************************************/
void printSearch(void);
/****************************************
 path生成(小回り)
 ****************************************/
void makePath(void);
/****************************************
 path生成2
 ****************************************/
void makePath2(void);
/****************************************
 path生成3
 ****************************************/
void makePath3(void);
/****************************************
 path表示
 ****************************************/
void printPath(void);
/****************************************
 path表示2
 ****************************************/
void printPath2(void);
/****************************************
 path表示3
 ****************************************/
void printPath3(void);
/****************************************
 path表示test
 ****************************************/
void printPathTest(void);
/****************************************
 path表示test斜め
 ****************************************/
void printPathTestDiagonal(void);
/****************************************
 path走行
 ****************************************/
void runPath(void) ;
/****************************************
 斜めpath走行1
 ****************************************/
void runPathDiagonal(void);
/****************************************
 path走行test
 ****************************************/
void runPathTest(void);
/****************************************
 path走行test斜め
 ****************************************/
void runPathTestDiagonal(void) ;
/****************************************
 スピードコネクト
 ****************************************/
float connectSpeedEnd(int esc);
float connectSpeed1000(int esc);
float connectSpeedEndTest(int esc);
float connectSpeedEndTestDiagonal(int esc);
/****************************************
 path走行　初期距離追加
 ****************************************/
float addInitDis(uint16_t count);
/****************************************
 サーキット
 ****************************************/
void selectModeCircuit(void);


#endif /* MAP_H_ */
