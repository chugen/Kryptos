/*
 * parameter.c
 *
 *  Created on: 2016/11/22
 *      Author: Gen
 */
#include "my_typedef.h"
#include "parameter.h"

/****************************************
 ターンパラメータ
 ****************************************/
/*Others~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
turn_t pivot = 			{ 184	,6000	,500	,0		,0		,0		,0		,-2 };
turn_t pivot_90_L =		{ 90	,6000	,400	,0		,0		,0		,0		,-2 };
turn_t pivot_90_R =		{ -90	,6000	,400	,0		,0		,0		,0		,-2 };
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//スラロームパラメータ			{degree	,alpha	,omega	,velo	,front	,rear	,dia	,mode}
//turn_t t_90_L_05 = 	{ 91.6	,9000	,603	,0.5	,0.016	,0.04	,0		,-1 };
//turn_t t_90_R_05 = 	{-89.2	,9000	,603	,0.5	,0.016	,0.039	,0		,-1	};
turn_t t_90_L_05 = 		{ 90.0	,7000	,532	,0.5	,0.006	,0.028	,0		,-1 };
turn_t t_90_R_05 = 		{-90.0	,7000	,532	,0.5	,0.006	,0.028	,0		,-1	};
/*1000~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//スラロームパラメータ			{degree	,alpha	,omega	,velo	,front	,rear	,dia	,mode}
turn_t t_w90_L_10 =		{ 90	,7000	,651	,1		,0.022	,0.00	,0		,0 };
turn_t t_w90_R_10 = 	{-90	,7000	,651	,1		,0.03	,0.00	,0		,0 };

turn_t t_180_L_10 = 	{ 184	,6650	,680	,1		,0.03	,0.00	,0		,0 };
turn_t t_180_R_10 =		{-178.5	,6400	,650	,1		,0.03	,0.00	,0		,0 };

turn_t t_i45_L_10 = 	{ 45	,15500	,654	,1		,0.025	,0.00	,1		,0 };
turn_t t_i45_R_10 = 	{-45	,15500	,654	,1		,0.02	,0.00	,1		,0 };
turn_t t_o45_L_10 = 	{ 45	,15500	,634	,1		,0.065	,0.00	,0		,1 };
turn_t t_o45_R_10 =		{-45	,15500	,634	,1		,0.065	,0.00	,0		,1 };

turn_t t_i135_L_10 = 	{ 135	,10000	,1000	,1		,0.043	,0.00	,1		,0 };
turn_t t_i135_R_10 = 	{-135	,7300	,810	,1		,0.03	,0.00	,1		,0 };
turn_t t_o135_L_10 = 	{ 137.7	,10000	,1000	,1		,0.053	,0.00	,0		,1 };
turn_t t_o135_R_10 = 	{-133.8	,10000	,1000	,1		,0.057	,0.00	,0		,1 };

turn_t t_v90_L_10 = 	{ 91.5	,22000	,1056	,1		,0.045	,0.00	,1		,1 };
turn_t t_v90_R_10 =		{-89.5	,22000	,1056	,1		,0.053	,0.00	,1		,1 };
/*1200~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//スラロームパラメータ			{degree	,alpha	,omega	,velo	,front	,rear	,dia	,mode}
turn_t t_w90_L_12 =		{ 90	,8000	,696	,1.2	,0.026	,0.037	,0		,0 };
turn_t t_w90_R_12 = 	{-90	,8000	,696	,1.2	,0.026	,0.037	,0		,0 };

turn_t t_180_L_12 =		{ 178	,8000	,824	,1.2	,0.022	,0.02	,0		,0 };
turn_t t_180_R_12 =		{-178	,8000	,824	,1.2	,0.022	,0.02	,0		,0 };

turn_t t_i45_L_12 =		{ 45	,12000	,600	,1.2	,0.014	,0.030	,1		,0 };
turn_t t_i45_R_12 =		{-45	,12000	,600	,1.2	,0.014	,0.050	,1		,0 };
turn_t t_o45_L_12 =		{ 45	,12000	,600	,1.2	,0.050	,0.014	,0		,1 };
turn_t t_o45_R_12 =		{-45	,12000	,600	,1.2	,0.050	,0.014	,0		,1 };

turn_t t_i135_L_12 = 	{ 135	,15500	,1200	,1.2	,0.072	,0.062	,1		,0 };
turn_t t_i135_R_12 = 	{-135	,15500	,1200	,1.2	,0.072	,0.062	,1		,0 };
turn_t t_o135_L_12 = 	{ 135	,15500	,1200	,1.2	,0.062	,0.072	,0		,1 };
turn_t t_o135_R_12 = 	{-135	,15500	,1200	,1.2	,0.062	,0.072	,0		,1 };

turn_t t_v90_L_12 =		{ 90	,22000	,1056	,1.2	,0.052	,0.052	,1		,1 };
turn_t t_v90_R_12 =		{-90	,22000	,1056	,1.2	,0.052	,0.052	,1		,1 };
/*1400~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//スラロームパラメータ			{degree	,alpha	,omega	,velo	,front	,rear	,dia	,mode}
turn_t t_w90_L_14 =		{ 90	,12000	,852	,1.4	,0.01	,0.0	,0		,0 };
turn_t t_w90_R_14 = 	{-90	,12000	,852	,1.4	,0.01	,0.0	,0		,0 };

turn_t t_180_L_14 = 	{ 178	,11500	,954	,1.4	,0.01	,0.0	,0		,0 };
turn_t t_180_R_14 =		{-178	,11500	,954	,1.4	,0.01	,0.0	,0		,0 };

turn_t t_i45_L_14 = 	{ 45	,26000	,884	,1.4	,0.006	,0.0	,1		,0 };
turn_t t_i45_R_14 = 	{-45	,26000	,884	,1.4	,0.015	,0.0	,1		,0 };
turn_t t_o45_L_14 =		{ 45	,26000	,884	,1.4	,0.039	,0.0	,0		,1 };
turn_t t_o45_R_14 =		{-45	,26000	,884	,1.4	,0.039	,0.0	,0		,1 };

turn_t t_i135_L_14 = 	{ 135	,17000	,1241	,1.4	,0.010	,0.0	,1		,0 };
turn_t t_i135_R_14 = 	{-135	,17000	,1241	,1.4	,0.010	,0.0	,1		,0 };
turn_t t_o135_L_14 = 	{ 135	,17000	,1241	,1.4	,0.010	,0.0	,0		,1 };
turn_t t_o135_R_14 = 	{-135	,17000	,1241	,1.4	,0.010	,0.0	,0		,1 };

turn_t t_v90_L_14 = 	{ 90	,45500	,1501	,1.4	,0.030	,0.0	,1		,1 };
turn_t t_v90_R_14 =		{-90	,45500	,1501	,1.4	,0.040	,0.0	,1		,1 };
/*1600~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//スラロームパラメータ			{degree	,alpha	,omega	,velo	,front	,rear	,dia	,mode}
turn_t t_w90_L_16 =		{ 90	,12000	,852	,1.4	,0.043	,0.04	,0		,0 };
turn_t t_w90_R_16 = 	{-90	,12000	,852	,1.4	,0.043	,0.04	,0		,0 };

turn_t t_180_L_16 = 	{ 178	,11500	,954	,1.4	,0.022	,0.019	,0		,0 };
turn_t t_180_R_16 =		{-178	,11500	,954	,1.4	,0.022	,0.019	,0		,0 };

turn_t t_i45_L_16 = 	{ 45	,26000	,884	,1.4	,0.019	,0.069	,1		,0 };
turn_t t_i45_R_16 = 	{-45	,26000	,884	,1.4	,0.019	,0.069	,1		,0 };
turn_t t_o45_L_16 =		{ 45	,26000	,884	,1.4	,0.069	,0.029	,0		,1 };
turn_t t_o45_R_16 =		{-45	,26000	,884	,1.4	,0.069	,0.029	,0		,1 };

turn_t t_i135_L_16 = 	{ 135	,17000	,1241	,1.4	,0.050	,0.039	,1		,0 };
turn_t t_i135_R_16 = 	{-135	,17000	,1241	,1.4	,0.050	,0.039	,1		,0 };
turn_t t_o135_L_16 = 	{ 135	,17000	,1241	,1.4	,0.039	,0.050	,0		,1 };
turn_t t_o135_R_16 = 	{-135	,17000	,1241	,1.4	,0.039	,0.050	,0		,1 };

turn_t t_v90_L_16 = 	{ 90	,45500	,1501	,1.4	,0.020	,0.050	,1		,1 };
turn_t t_v90_R_16 =		{-90	,45500	,1501	,1.4	,0.030	,0.050	,1		,1 };
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
turn_t t_w90_R_15 = 	{-78	,18000	,1500	,1.5	,0.0	,0.18	,0		,0 };
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/****************************************
 ターン種類保存配列
 ****************************************/
 turn_t * t10[14]={&t_w90_L_10,&t_w90_R_10,&t_180_L_10,&t_180_R_10
							,&t_i45_L_10,&t_i45_R_10,&t_o45_L_10,&t_o45_R_10
							,&t_i135_L_10,&t_i135_R_10,&t_o135_L_10,&t_o135_R_10
							,&t_v90_L_10,&t_v90_R_10};
 turn_t * t12[14]={&t_w90_L_12,&t_w90_R_12,&t_180_L_12,&t_180_R_12
							,&t_i45_L_12,&t_i45_R_12,&t_o45_L_12,&t_o45_R_12
							,&t_i135_L_12,&t_i135_R_12,&t_o135_L_12,&t_o135_R_12
							,&t_v90_L_12,&t_v90_R_12};
 turn_t * t14[14]={&t_w90_L_14,&t_w90_R_14,&t_180_L_14,&t_180_R_14
							,&t_i45_L_14,&t_i45_R_14,&t_o45_L_14,&t_o45_R_14
							,&t_i135_L_14,&t_i135_R_14,&t_o135_L_14,&t_o135_R_14
							,&t_v90_L_14,&t_v90_R_14};
 turn_t * t16[14]={&t_w90_L_16,&t_w90_R_16,&t_180_L_16,&t_180_R_16
							,&t_i45_L_16,&t_i45_R_16,&t_o45_L_16,&t_o45_R_16
							,&t_i135_L_16,&t_i135_R_16,&t_o135_L_16,&t_o135_R_16
							,&t_v90_L_16,&t_v90_R_16};
/****************************************
 ターン速度保存配列
 ****************************************/
 turn_t **t_para[4]={t10,t12,t14,t16};

