/*
 * init.cpp
 *
 *  Created on: 2016/05/24
 *      Author: 元太
 */
#include <stdint.h>
#include "iodefine.h"
#include "init.h"
#include "sensor.h"
#include "common.h"
int8_t init(void) {
	initClock();
	initIO();
	initLowPowerConsumption();
	initCMT();
	initSPI();
	initMTU();
	initTPU();
	initSCI();
	initADC();
	initMPU6000();
	return 1;
}

int8_t initIO(void) {
	PORTA.PMR.BYTE = 0x00;
	PORTE.PMR.BYTE = 0x00;
	PORT5.PMR.BYTE = 0x00;
	PORTC.PMR.BYTE = 0x00;
//モード選択LED
	PORT5.PODR.BYTE = 0x00;

	PORTA.PDR.BIT.B1 = 1;	//LED0 PORTA.PODR.BIT.B1 = 1; ON
	PORTA.PDR.BIT.B0 = 1;	//LED1
	PORTE.PDR.BIT.B4 = 1; 	//LED2
	PORTE.PDR.BIT.B5 = 1;	//LED3

	//PORTE.PDR.BIT.B0 = 1;	//spi_cs

	PORT5.PDR.BIT.B4 = 1;	//SLED FR_L 1,3
	PORT5.PDR.BIT.B5 = 1;	//SLED FL_R 0,4

	PORT3.PDR.BIT.B1 = 1;		//SW

	PORTC.PDR.BIT.B6 = 1;	//motor STBY
	PORTC.PDR.BIT.B5 = 1;	//motor M_L_IN1
	PORTC.PDR.BIT.B4 = 1;	//motor M_L_IN2
	PORTC.PDR.BIT.B3 = 1;	//motor M_R_IN1
	PORTC.PDR.BIT.B2 = 1;	//motor M_R_IN2
	return 1;
}

int8_t initClock(void) {
	unsigned short i;

	SYSTEM.PRCR.WORD = 0xA503;	//プロテクト解除

	PORT3.PDR.BIT.B6 = 0; //P36を入力に設定
	PORT3.PDR.BIT.B7 = 0; //P37を入力に設定

	SYSTEM.SOSCCR.BYTE = 0x01; //ｻﾌﾞｸﾛｯｸ発振停止
	SYSTEM.MOSCWTCR.BYTE = 0x0F; //ﾒｲﾝｸﾛｯｸ発振ｳｪｲﾄ
	SYSTEM.PLLWTCR.BYTE = 0x0F; //PLL発振ｳｪｲﾄ

	SYSTEM.PLLCR2.BIT.PLLEN = 1;	//PLL停止
	SYSTEM.PLLCR.BIT.PLIDIV = 0x00; //12.5MHzで入力
	SYSTEM.PLLCR.BIT.STC = 0x0f; //12.5MHz×16=200MHz
	SYSTEM.PLLCR2.BIT.PLLEN = 0; //PLL動作
	SYSTEM.MOSCCR.BYTE = 0x00; //ﾒｲﾝｸﾛｯｸ発振

	for (i = 0; i < 0x168; i++) {
		;
	} //発振安定待ち

	SYSTEM.SCKCR.LONG = 0x21C31211; //ICLK=100MHz,PCLK=50MHz,FCLK=50MHz
	SYSTEM.SCKCR3.BIT.CKSEL = 0x04; //PLL回路選択

	SYSTEM.PRCR.WORD = 0xA500; //プロテクト
	return 1;
}

int8_t initLowPowerConsumption(void) {

	SYSTEM.PRCR.WORD = 0xA502; //プロテクト解除

	MSTP(MTU) = 0;		// MTU:モジュールストップ状態解除
	MSTP(TPU0) = 0;		// TPUユニット0:モジュールストップ状態解除
	MSTP(CMT0) = 0;		// CMTユニット0:モジュールストップ状態解除
	MSTP(CMT1) = 0;		// CMTユニット0:モジュールストップ状態解除
	MSTP(S12AD) = 0;	// S12AD(12bitADC):モジュールストップ状態解除
	MSTP(RSPI0) = 0;	// RSPI0:モジュールストップ状態解除
	MSTP(SCI1) = 0;		// SCI1:モジュールストップ解除
	MSTP(RSPI1) = 0;	// RSPI1:モジュールストップ解除

	SYSTEM.PRCR.WORD = 0xA500;	//プロテクト
	return 1;
}

int8_t initCMT(void) {

	CMT.CMSTR0.BIT.STR0 = 0x00;	//カウントストップ
	CMT.CMSTR0.BIT.STR1 = 0x00;	//カウントストップ
	CMT0.CMCR.BIT.CMIE = 0x00;	//コンペアマッチ割り込み禁止
	CMT0.CMCR.BIT.CKS = 0x00;	// PCLK/8=50MHz/8=6.25MHz=6250000Hz
	CMT0.CMCR.BIT.CMIE = 0x01;	//コンペアマッチ割り込み許可
	CMT0.CMCOR = 6250 - 1;		//割り込み周期設定 1ms

	//IR(CMT0, CMI0)= 0x00;
	IPR( CMT0, CMI0 )= 0x0F;	//割り込み優先度設定:15
	IEN( CMT0, CMI0 )= 0x01;	//割り込み許可

	CMT1.CMCR.BIT.CMIE = 0x00;	//コンペアマッチ割り込み禁止
	CMT1.CMCR.BIT.CKS = 0x00;	// PCLK/8=50MHz/8=6.25MHz=6250000Hz
	CMT1.CMCR.BIT.CMIE = 0x01;	//コンペアマッチ割り込み許可
	CMT1.CMCOR = 6250 - 1;		//割り込み周期設定 1ms

	//IR(CMT1, CMI1)= 0x00;
	IPR( CMT1, CMI1 )= 0x0E;	//割り込み優先度設定:14
	IEN( CMT1, CMI1 )= 0x01;	//割り込み許可

	CMT.CMSTR0.BIT.STR0 = 0x01;
	CMT.CMSTR0.BIT.STR1 = 0x1;
	CMT.CMSTR1.BIT.STR2 = 0x0;
	return 1;
}

int8_t initMTU(void) {
	MPC.PWPR.BIT.B0WI = 0;
	MPC.PWPR.BIT.PFSWE = 1;		//書き込みプロテクト解除
	MPC.PB1PFS.BIT.PSEL = 0x01;	//MTIOC0C MOTOR_L
	MPC.PB3PFS.BIT.PSEL = 0x01;	//MTIOC0A MOTOR_R
	MPC.PB5PFS.BIT.PSEL = 0x01;	//MTIOC2A
	MPC.P14PFS.BIT.PSEL = 0x02;	//MTCLKA
	MPC.P15PFS.BIT.PSEL = 0x02;	//MTCLKB
	MPC.PWPR.BIT.PFSWE = 0;		//書き込みプロテクト

	PORTB.PMR.BIT.B1 = 1;		// MOTOR_L
	PORTB.PMR.BIT.B3 = 1;		// MOTOR_R
	PORTB.PMR.BIT.B5 = 0;		// SPEAKER
	PORT1.PMR.BIT.B4 = 1;		// encoder
	PORT1.PMR.BIT.B5 = 1;		// encoder

	MTU.TSTR.BYTE = 0x00;		//MTU0~5 TCNTカウントストップ

	MTU0.TCR.BIT.TPSC = 0x00;	//PCLK/16=3125000Hz
	MTU2.TCR.BIT.TPSC = 0x02;	//PCLK=50MHz

	MTU0.TCR.BIT.CCLR = 0x06;	//TGRDコンペアマッチでTCNTカウンタクリア
	MTU2.TCR.BIT.CCLR = 0x02;	//TGRBコンペアマッチでTCNTカウンタクリア

	MTU0.TIORH.BIT.IOA = 0x05;	//初期出力：H,コンペアマッチ：L
	MTU0.TIORL.BIT.IOC = 0x05;	//初期出力：H,コンペアマッチ：L
	MTU2.TIOR.BIT.IOA = 0x05;	//初期出力：H,コンペアマッチ：L

	//MTU0:MOTOR MTU2:SPEAKER
	MTU0.TGRA = (int8_t) (250 * 15 / 100);	//MOTOR_R
	MTU0.TGRC = (int8_t) (250 * 15 / 100);	//MOTOR_L
	MTU0.TGRD = 250;

	MTU2.TGRA = 5;
	MTU2.TGRB = 50;

	MTU0.TMDR.BIT.MD = 0x03;	//PWMモード2
	MTU1.TMDR.BIT.MD = 0x07;	//位相係数モード4
	MTU2.TMDR.BIT.MD = 0x03;	//PWMモード2

//	IPR( MTU0, TGIA0 )= 0x0A;	//割り込み優先度設定:10
//	IEN( MTU0, TGIA0 )= 0x01;
//
//	IPR( MTU3, TGIA3 )= 0x09;//割り込み優先度設定:9
//	IEN( MTU3, TGIA3 )= 0x01;
//
//	IPR( MTU4, TGIA4 )= 0x08;//割り込み優先度設定:8
//	IEN( MTU4, TGIA4 )= 0x01;

	MTU.TSTR.BIT.CST1 = 1;	//位相係数スタート
	return 1;
}

int8_t initTPU(void) {
	static const int16_t fled_width = 1500;
	MPC.PWPR.BIT.B0WI = 0;
	MPC.PWPR.BIT.PFSWE = 1;
	MPC.PA3PFS.BIT.PSEL = 0x03;	//TIOCD0
	MPC.PA4PFS.BIT.PSEL = 0x03;	//TIOCA1
	MPC.PA6PFS.BIT.PSEL = 0x03;	//TIOCA2
	MPC.PB6PFS.BIT.PSEL = 0x03;	//TIOCA5
	MPC.P16PFS.BIT.PSEL = 0x04;	//TCLKC
	MPC.P17PFS.BIT.PSEL = 0x04;	//TCLKD
	MPC.PWPR.BIT.PFSWE = 0;

	PORTA.PMR.BIT.B3 = 1;	//LED_BLUE
	PORTA.PMR.BIT.B4 = 1;	//LED_RED
	PORTA.PMR.BIT.B6 = 1;	//LED_GREEN
	PORTB.PMR.BIT.B6 = 1;	//suction
	PORT1.PMR.BIT.B6 = 1;	//encoder
	PORT1.PMR.BIT.B7 = 1;	//encoder

	TPUA.TSTR.BYTE = 0x00;		//TPU0~5 TCNTカウントストップ

	TPU0.TCR.BIT.TPSC = 0x00;	//PCLK=50MHz
	TPU1.TCR.BIT.TPSC = 0x00;	//PCLK=50MHz
	TPU2.TCR.BIT.TPSC = 0x00;	//PCLK=50MHz
	TPU5.TCR.BIT.TPSC = 0x00;	//PCLK=50MHz

	TPU0.TCR.BIT.CCLR = 0x05;	//TGRCコンペアマッチでTCNTカウンタクリア
	TPU1.TCR.BIT.CCLR = 0x02;	//TGRBコンペアマッチでTCNTカウンタクリア
	TPU2.TCR.BIT.CCLR = 0x02;	//TGRBコンペアマッチでTCNTカウンタクリア
	TPU5.TCR.BIT.CCLR = 0x02;	//TGRBコンペアマッチでTCNTカウンタクリア

	TPU0.TIORL.BIT.IOD = 0x02;	//初期出力：H,コンペアマッチ：L
	TPU1.TIOR.BIT.IOA = 0x02;	//初期出力：H,コンペアマッチ：L
	TPU2.TIOR.BIT.IOA = 0x02;	//初期出力：H,コンペアマッチ：L
	TPU5.TIOR.BIT.IOA = 0x02;	//初期出力：H,コンペアマッチ：L

	//TPU0:BLUE TPU1:RED TPU2:GREEN TPU5:SUCTION
	//LED_BLUE
	TPU0.TGRD = 0;
	TPU0.TGRC = fled_width;
	//LED_RED
	TPU1.TGRA = 0;
	TPU1.TGRB = fled_width;
	//GREEN_GREEN
	TPU2.TGRA = 0;
	TPU2.TGRB = fled_width;
	//SUCTION_FAN
	TPU5.TGRA = 0;
	TPU5.TGRB = 100;

	TPU0.TMDR.BIT.MD = 0x03;	//PWMモード2
	TPU1.TMDR.BIT.MD = 0x03;	//PWMモード2
	TPU2.TMDR.BIT.MD = 0x03;	//PWMモード2
	TPU4.TMDR.BIT.MD = 0x07;	//位相係数モード4
	TPU5.TMDR.BIT.MD = 0x03;	//PWMモード2

	//TPUA.TSTR.BYTE = 0x3f;	//TPU0~5 TCNTカウントスタート
	TPUA.TSTR.BIT.CST4 = 1;	//位相係数スタート
	return 1;

}

int8_t initSCI(void) {
	int16_t dmy;

	MPC.PWPR.BIT.B0WI = 0;
	MPC.PWPR.BIT.PFSWE = 1;	//書き込みプロテクト解除
	MPC.P26PFS.BIT.PSEL = 0x0A;
	MPC.P30PFS.BIT.PSEL = 0x0A;
	MPC.PWPR.BIT.PFSWE = 0;	//書き込みプロテクト

	PORT2.PMR.BIT.B6 = 1;
	PORT3.PMR.BIT.B0 = 1;
	PORT2.PDR.BIT.B6 = 1;	//TXD1
	PORT3.PDR.BIT.B0 = 0;	//RXD1

	SCI1.SCR.BIT.TE = 0;	//送信禁止
	SCI1.SCR.BIT.RE = 0;	//受信禁止
	SCI1.SCR.BIT.CKE = 0;	//内臓ボーレートジェネレータ

	SCI1.SMR.BIT.CKS = 0;	//PCLK
	SCI1.SMR.BIT.MP = 0;	//マルチプロセッサ通信機能を禁止
	SCI1.SMR.BIT.STOP = 0;	//1ストップビット
	SCI1.SMR.BIT.PE = 0;	//パリティ無し
	SCI1.SMR.BIT.CHR = 0;	//データ長8ビット
	SCI1.SMR.BIT.CM = 0;	//調歩同期式モード

	SCI1.SCMR.BYTE = 0xF2;
	SCI1.BRR = (unsigned char) (50000000 / 32 / 38400) - 1;

	for (dmy = 0; dmy < 10000; dmy++) {

	}

	SCI1.SCR.BIT.TE = 1;	//送信許可
	SCI1.SCR.BIT.RE = 1;	//受信許可

	return 1;
}

int8_t initADC(void) {
	S12AD.ADCSR.BIT.ADST = 0x00;	//AD変換ストップ
	S12AD.ADCSR.BIT.TRGE = 0x00;	//トリガによるAD変換開始禁止
	S12AD.ADCSR.BIT.CKS = 0x02; 	//PCLK/2=25MHz
	S12AD.ADCSR.BIT.ADCS = 0x00; 	//シングルスキャンモード
	//S12AD.ADANS0.WORD = 0x5E;		//0000|0000|0101|1110
	S12AD.ADSSTR01.WORD = 20; 		//サンプリング時間20ステート
	S12AD.ADCER.BIT.ADRFMT = 0;		//レジスタ右詰め
	//S12AD.ADCSR.BIT.ADST = 0x01; 	//AD変換スタート
	return 1;
}

int8_t initSPI(void) {

	MPC.PWPR.BIT.B0WI = 0;	//PFSWE書き込みプロテクト解除
	MPC.PWPR.BIT.PFSWE = 1;	//PFS書き込みプロテクト解除

	MPC.PE0PFS.BIT.PSEL = 13;
	MPC.PE1PFS.BIT.PSEL = 14;
	MPC.PE2PFS.BIT.PSEL = 14;
	MPC.PE3PFS.BIT.PSEL = 13;

	MPC.PWPR.BIT.PFSWE = 0;	//PFS書き込みプロテクト
	MPC.PWPR.BIT.B0WI = 1; 	//PFSWE書き込みプロテクト

	// ポートモードレジスタ：周辺機能設定
	PORTE.PMR.BIT.B0 = 1;
	PORTE.PMR.BIT.B1 = 1;
	PORTE.PMR.BIT.B2 = 1;
	PORTE.PMR.BIT.B3 = 1;

	RSPI1.SPCR.BIT.SPE = 0; 	//RSPI機能禁止

	RSPI1.SPDCR.BYTE = 0x00; 	//データコントロールレジスタ

	RSPI1.SPBR = 12; 			// (50*10^6)/(2*(12+1)*2^1)=961538.4615Hz

	RSPI1.SSLP.BYTE = 0x0d;

	RSPI1.SPSCR.BIT.SPSLN = 0; 	//シーケンス制御レジスタ 0→0→...

	RSPI1.SPPCR.BYTE = 0x00; 	//RSPI端子制御レジスタ

	RSPI1.SPCMD0.BIT.CPHA = 1;	//奇数エッジ:データ変化,偶数エッジ：データサンプル
	RSPI1.SPCMD0.BIT.CPOL = 1;	//アイドル時：RSPCKがHigh
	RSPI1.SPCMD0.BIT.BRDV = 1;	//ビットレート分周設定 0:分周しない 1:2分周　2:4分周
	RSPI1.SPCMD0.BIT.SSLA = 1;	//SSL信号アサート設定
	RSPI1.SPCMD0.BIT.SSLKP = 1;	//SSL信号レベル保持 1:転送終了時保持
	RSPI1.SPCMD0.BIT.SPB = 0x07;	//データ長設定ビット :8 Bit
	RSPI1.SPCMD0.BIT.LSBF = 0;	//MSBファースト
	RSPI1.SPCMD0.BIT.SPNDEN = 1;
	RSPI1.SPCMD0.BIT.SLNDEN = 1;
	RSPI1.SPCMD0.BIT.SCKDEN = 1;

	RSPI1.SPCR.BIT.SPMS = 0; 	//SPI動作
	RSPI1.SPCR.BIT.MSTR = 1; 	//RSPIマスタモード

	RSPI1.SPCR.BIT.SPE = 1; 	//RSPI機能動作

	return 1;
}

int8_t initMPU6000(void) {
	commSPI(SIGNAL_PATH_RESET, 0x07, WRITE); 	//シグナルパスリセット
	commSPI(USER_CTRL, 0x10, WRITE);			//I2C無効，SPI有効
	commSPI(PWR_MGMT_1, 0x08, WRITE);			//温度センサ無効，
	commSPI(PWR_MGMT_2, 0x0E, WRITE);
	commSPI(GYRO_CONFIG, 0x18, WRITE);
	commSPI(ACCEL_CONFIG, 0x18, WRITE);
	return 1;
}

