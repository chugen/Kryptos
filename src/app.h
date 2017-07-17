/*
 * app.hpp
 *
 *  Created on: 2016/06/28
 *      Author: 元太
 */

#ifndef APP_HPP_
#define APP_HPP_
/****************************************
 ビットシフト
 ****************************************/
void shiftBit(uint8_t *value, uint8_t shift, uint8_t shift_dir);
uint8_t getBitShiftValue4bit(uint8_t *value, uint8_t shift, uint8_t shift_dir);
uint8_t getBitShiftValue8bit(uint8_t *value, uint8_t shift, uint8_t shift_dir);
/****************************************
 Wait関数
 ****************************************/
void waitTime(int16_t wait_ms);
void waitTimeMicro(uint16_t wait_us);
/****************************************
 バッテリーチェック
 ****************************************/
float checkLowVoltage(void);

/****************************************
センサー待ち
 ****************************************/
void waitSensor(void);
/****************************************
 スイッチ
 ****************************************/
int16_t pushButton(void);
int16_t waitButton(void);

/****************************************
 モード選択LED
 ****************************************/
int16_t driveLED(int16_t mode);
/****************************************
 フルカラーLED
 ****************************************/
int16_t driveRGB(int16_t red, int16_t green, int16_t blue, int8_t on_off);
/****************************************
 ブザー
 ****************************************/
void driveBuzzer(float freq, float wait_ms);
void driveBuzzerIntrpt(uint8_t left_right,uint8_t on_off);
/****************************************
 モード選択
 ****************************************/
int16_t selectMode(int16_t max_mode);
/****************************************
 deg-rad変換
 ****************************************/
float convDegreeToRadian(float degree);
/****************************************
 ログ書き出し関数
 ****************************************/
void printLog(void);
void printLog4(void);
void printLogInt(void);

/****************************************
 ゴール音
 ****************************************/
void soundGoal(void);
/****************************************
 エラー音
 ****************************************/
void soundError(void);
/****************************************
 スタート音
 ****************************************/
void soundStartSearch(void);
void soundStartRun(void) ;

/****************************************
 通知音
 ****************************************/
void soundSensor(void);
void soundButton(void);
void soundPrint(void);
/****************************************
 カウント音
 ****************************************/
void soundCount(int16_t mode);
/****************************************
 起動通知LED
 ****************************************/
void notificateStartUp(void);
#endif /* APP_HPP_ */
