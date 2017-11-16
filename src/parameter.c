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
turn2_t tc_pivot = 		{ 180	,700	,0		,0		,0		,0 };
turn2_t tc_pivot_90_L =	{ 90	,700	,0		,0		,0		,0 };
turn2_t tc_pivot_90_R =	{ -90	,700	,0		,0		,0		,0 };

turn2_t tc_test = 		{ 	0	,1300	,0.9	,0  	,0  	,0 };
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//スラロームパラメータ			{degree	,omega	,velo	,front	,rear	,dia}
//turn2_t tc_90_L_07 = 	{ 90.0	,795	,0.7	,0.002	,0.012	,0};
//turn2_t tc_90_R_07 = 	{-90.0	,795	,0.7	,0.002	,0.012	,0};
turn2_t tc_90_L_07 = 	{ 90.0	,1000	,0.7	,0.0165	,0.0360	,0};
turn2_t tc_90_R_07 = 	{-90.0	,1000	,0.7	,0.0145	,0.0370	,0};
/*1000~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//スラロームパラメータ			{degree	,omega	,velo	,front	,rear	,dia}
turn2_t tc_w90_L_10 =	{ 90	,651	,1		,0.022	,0.00	,0 };
turn2_t tc_w90_R_10 = 	{-90	,651	,1		,0.03	,0.00	,0 };

turn2_t tc_180_L_10 = 	{ 180	,680	,1		,0.03	,0.00	,0 };
turn2_t tc_180_R_10 =	{-180	,650	,1		,0.03	,0.00	,0 };

turn2_t tc_i45_L_10 = 	{ 45	,654	,1		,0.025	,0.00	,1 };
turn2_t tc_i45_R_10 = 	{-45	,654	,1		,0.02	,0.00	,1 };
turn2_t tc_o45_L_10 = 	{ 45	,634	,1		,0.065	,0.00	,0 };
turn2_t tc_o45_R_10 =	{-45	,634	,1		,0.065	,0.00	,0 };

turn2_t tc_i135_L_10 = 	{ 135	,1000	,1		,0.043	,0.00	,1 };
turn2_t tc_i135_R_10 = 	{-135	,810	,1		,0.03	,0.00	,1 };
turn2_t tc_o135_L_10 = 	{ 135	,1000	,1		,0.053	,0.00	,0 };
turn2_t tc_o135_R_10 = 	{-135	,1000	,1		,0.057	,0.00	,0 };

turn2_t tc_v90_L_10 = 	{ 90	,1056	,1		,0.045	,0.00	,1 };
turn2_t tc_v90_R_10 =	{-90	,1056	,1		,0.053	,0.00	,1 };
/*1200~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//スラロームパラメータ			{degree	,omega	,velo	,front	,rear	,dia}
turn2_t tc_w90_L_12 =	{ 90	,696	,1.2	,0.026	,0.037	,0};
turn2_t tc_w90_R_12 = 	{-90	,696	,1.2	,0.026	,0.037	,0};

turn2_t tc_180_L_12 =	{ 180	,824	,1.2	,0.022	,0.02	,0};
turn2_t tc_180_R_12 =	{-180	,824	,1.2	,0.022	,0.02	,0};

turn2_t tc_i45_L_12 =	{ 45	,600	,1.2	,0.014	,0.030	,1};
turn2_t tc_i45_R_12 =	{-45	,600	,1.2	,0.014	,0.050	,1};
turn2_t tc_o45_L_12 =	{ 45	,600	,1.2	,0.050	,0.014	,0};
turn2_t tc_o45_R_12 =	{-45	,600	,1.2	,0.050	,0.014	,0};

turn2_t tc_i135_L_12 = 	{ 135	,1200	,1.2	,0.072	,0.062	,1};
turn2_t tc_i135_R_12 = 	{-135	,1200	,1.2	,0.072	,0.062	,1};
turn2_t tc_o135_L_12 = 	{ 135	,1200	,1.2	,0.062	,0.072	,0};
turn2_t tc_o135_R_12 = 	{-135	,1200	,1.2	,0.062	,0.072	,0};

turn2_t tc_v90_L_12 =	{ 90	,1056	,1.2	,0.052	,0.052	,1};
turn2_t tc_v90_R_12 =	{-90	,1056	,1.2	,0.052	,0.052	,1};
/*1400~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//スラロームパラメータ			{degree	,omega	,velo	,front	,rear	,dia}
turn2_t tc_w90_L_14 =	{ 90	,852	,1.4	,0.0165	,0.050	,0};
turn2_t tc_w90_R_14 = 	{-90	,852	,1.4	,0.014	,0.0495	,0};

turn2_t tc_180_L_14 = 	{ 180	,1050	,1.4	,0.01	,0.045	,0};
turn2_t tc_180_R_14 =	{-180	,1055	,1.4	,0.01	,0.050	,0};

turn2_t tc_i45_L_14 = 	{ 45	,884	,1.4	,0.0073	,0.0835	,1};
turn2_t tc_i45_R_14 = 	{-45	,884	,1.4	,0.0122	,0.0755	,1};
turn2_t tc_o45_L_14 =	{ 45	,800	,1.4	,0.0568	,0.034	,0};
turn2_t tc_o45_R_14 =	{-45	,800	,1.4	,0.0550	,0.0325	,0};

turn2_t tc_i135_L_14 = 	{ 135	,1280	,1.4	,0.0339	,0.061	,1};
turn2_t tc_i135_R_14 = 	{-135	,1280	,1.4	,0.0336	,0.061	,1};
turn2_t tc_o135_L_14 = 	{ 135	,1220	,1.4	,0.0244	,0.069	,0};
turn2_t tc_o135_R_14 = 	{-135	,1300	,1.4	,0.0299	,0.079	,0};

turn2_t tc_v90_L_14 = 	{ 90	,1500	,1.4	,0.0311	,0.07	,1};
turn2_t tc_v90_R_14 =	{-90	,1500	,1.4	,0.0306	,0.07	,1};
/*1600~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//スラロームパラメータ			{degree	,omega	,velo	,front	,rear	,dia}
turn2_t tc_w90_L_16 =	{ 90	,1064	,1.6	,0.01	,0.028	,0};
turn2_t tc_w90_R_16 = 	{-90	,1064	,1.6	,0.01	,0.028	,0};

turn2_t tc_180_L_16 = 	{ 180	,1200	,1.6	,0.027	,0.028	,0};
turn2_t tc_180_R_16 =	{-180	,1200	,1.6	,0.027	,0.028	,0};

turn2_t tc_i45_L_16 = 	{ 45	,884	,1.6	,0.019	,0.069	,1};
turn2_t tc_i45_R_16 = 	{-45	,884	,1.6	,0.019	,0.069	,1};
turn2_t tc_o45_L_16 =	{ 45	,884	,1.6	,0.069	,0.029	,0};
turn2_t tc_o45_R_16 =	{-45	,884	,1.6	,0.069	,0.029	,0};

turn2_t tc_i135_L_16 = 	{ 135	,1241	,1.6	,0.050	,0.039	,1};
turn2_t tc_i135_R_16 = 	{-135	,1241	,1.6	,0.050	,0.039	,1};
turn2_t tc_o135_L_16 = 	{ 135	,1241	,1.6	,0.039	,0.050	,0};
turn2_t tc_o135_R_16 = 	{-135	,1241	,1.6	,0.039	,0.050	,0};

turn2_t tc_v90_L_16 = 	{ 90	,1501	,1.6	,0.010	,0.050	,1};
turn2_t tc_v90_R_16 =	{-90	,1501	,1.6	,0.015	,0.050	,1};
/*1800~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//スラロームパラメータ			{degree	,omega	,velo	,front	,rear	,dia}
turn2_t tc_w90_L_18 =	{ 90	,852	,1.8	,0.043	,0.04	,0 };
turn2_t tc_w90_R_18 = 	{-90	,852	,1.8	,0.043	,0.04	,0 };

turn2_t tc_180_L_18 = 	{ 180	,954	,1.8	,0.022	,0.019	,0 };
turn2_t tc_180_R_18 =	{-180	,954	,1.8	,0.022	,0.019	,0 };

turn2_t tc_i45_L_18 = 	{ 45	,884	,1.8	,0.019	,0.069	,1 };
turn2_t tc_i45_R_18 = 	{-45	,884	,1.8	,0.019	,0.069	,1 };
turn2_t tc_o45_L_18 =	{ 45	,884	,1.8	,0.069	,0.029	,0 };
turn2_t tc_o45_R_18 =	{-45	,884	,1.8	,0.069	,0.029	,0 };

turn2_t tc_i135_L_18 = 	{ 135	,1241	,1.8	,0.050	,0.039	,1 };
turn2_t tc_i135_R_18 = 	{-135	,1241	,1.8	,0.050	,0.039	,1 };
turn2_t tc_o135_L_18 = 	{ 135	,1241	,1.8	,0.039	,0.050	,0 };
turn2_t tc_o135_R_18 = 	{-135	,1241	,1.8	,0.039	,0.050	,0 };

turn2_t tc_v90_L_18 = 	{ 90	,1501	,1.8	,0.020	,0.050	,1 };
turn2_t tc_v90_R_18 =	{-90	,1501	,1.8	,0.030	,0.050	,1 };
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/****************************************
 ターンパラメータ
 ****************************************/
/*Others~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
turn_t pivot = 			{ 180	,6000	,500	,0		,0		,0		,0		,-2 };
turn_t pivot_90_L =		{ 90	,6000	,400	,0		,0		,0		,0		,-2 };
turn_t pivot_90_R =		{ -90	,6000	,400	,0		,0		,0		,0		,-2 };

turn_t t_test = 		{ 720.0	,7000	,1300	,0.9	,0  	,0  	,0		,-1 };
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
turn_t t_o45_R_14 =		{-45	,26000	,884	,1.4	,0.059	,0.0	,0		,1 };

turn_t t_i135_L_14 = 	{ 135	,17000	,1241	,1.4	,0.010	,0.0	,1		,0 };
turn_t t_i135_R_14 =	{-135	,17000	,1241	,1.4	,0.010	,0.0	,1		,0 };
turn_t t_o135_L_14 = 	{ 135	,17000	,1241	,1.4	,0.010	,0.0	,0		,1 };
turn_t t_o135_R_14 = 	{-135	,17000	,1241	,1.4	,0.010	,0.0	,0		,1 };

turn_t t_v90_L_14 = 	{ 90	,45500	,1501	,1.4	,0.040	,0.0	,1		,1 };
turn_t t_v90_R_14 =		{-90	,45500	,1501	,1.4	,0.030	,0.0	,1		,1 };
/*1600~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//スラロームパラメータ			{degree	,alpha	,omega	,velo	,front	,rear	,dia	,mode}
turn_t t_w90_L_16 =		{ 90	,19000	,1064	,1.6	,0.01	,0.028	,0		,0 };
turn_t t_w90_R_16 = 	{-90	,19000	,1064	,1.6	,0.01	,0.028	,0		,0 };

turn_t t_180_L_16 = 	{ 180	,18000	,928	,1.6	,0.027	,0.028	,0		,0 };
turn_t t_180_R_16 =		{-180	,18000	,928	,1.6	,0.027	,0.028	,0		,0 };

turn_t t_i45_L_16 = 	{ 45	,26000	,884	,1.6	,0.019	,0.069	,1		,0 };
turn_t t_i45_R_16 = 	{-45	,26000	,884	,1.6	,0.019	,0.069	,1		,0 };
turn_t t_o45_L_16 =		{ 45	,26000	,884	,1.6	,0.069	,0.029	,0		,1 };
turn_t t_o45_R_16 =		{-45	,26000	,884	,1.6	,0.069	,0.029	,0		,1 };

turn_t t_i135_L_16 = 	{ 135	,17000	,1241	,1.6	,0.050	,0.039	,1		,0 };
turn_t t_i135_R_16 = 	{-135	,17000	,1241	,1.6	,0.050	,0.039	,1		,0 };
turn_t t_o135_L_16 = 	{ 135	,17000	,1241	,1.6	,0.039	,0.050	,0		,1 };
turn_t t_o135_R_16 = 	{-135	,17000	,1241	,1.6	,0.039	,0.050	,0		,1 };

turn_t t_v90_L_16 = 	{ 90	,45500	,1501	,1.6	,0.010	,0.050	,1		,1 };
turn_t t_v90_R_16 =		{-90	,45500	,1501	,1.6	,0.015	,0.050	,1		,1 };
/*1800~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//スラロームパラメータ			{degree	,alpha	,omega	,velo	,front	,rear	,dia	,mode}
turn_t t_w90_L_18 =		{ 90	,12000	,852	,1.8	,0.043	,0.04	,0		,0 };
turn_t t_w90_R_18 = 	{-90	,12000	,852	,1.8	,0.043	,0.04	,0		,0 };

turn_t t_180_L_18 = 	{ 178	,11500	,954	,1.8	,0.022	,0.019	,0		,0 };
turn_t t_180_R_18 =		{-178	,11500	,954	,1.8	,0.022	,0.019	,0		,0 };

turn_t t_i45_L_18 = 	{ 45	,26000	,884	,1.8	,0.019	,0.069	,1		,0 };
turn_t t_i45_R_18 = 	{-45	,26000	,884	,1.8	,0.019	,0.069	,1		,0 };
turn_t t_o45_L_18 =		{ 45	,26000	,884	,1.8	,0.069	,0.029	,0		,1 };
turn_t t_o45_R_18 =		{-45	,26000	,884	,1.8	,0.069	,0.029	,0		,1 };

turn_t t_i135_L_18 = 	{ 135	,17000	,1241	,1.8	,0.050	,0.039	,1		,0 };
turn_t t_i135_R_18 = 	{-135	,17000	,1241	,1.8	,0.050	,0.039	,1		,0 };
turn_t t_o135_L_18 = 	{ 135	,17000	,1241	,1.8	,0.039	,0.050	,0		,1 };
turn_t t_o135_R_18 = 	{-135	,17000	,1241	,1.8	,0.039	,0.050	,0		,1 };

turn_t t_v90_L_18 = 	{ 90	,45500	,1501	,1.8	,0.020	,0.050	,1		,1 };
turn_t t_v90_R_18 =		{-90	,45500	,1501	,1.8	,0.030	,0.050	,1		,1 };
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
 turn_t * t18[14]={&t_w90_L_18,&t_w90_R_18,&t_180_L_18,&t_180_R_18
							,&t_i45_L_18,&t_i45_R_18,&t_o45_L_18,&t_o45_R_18
							,&t_i135_L_18,&t_i135_R_18,&t_o135_L_18,&t_o135_R_18
							,&t_v90_L_18,&t_v90_R_18};
 /****************************************
  ターン種類保存配列
  ****************************************/
  turn2_t * tc10[14]={&tc_w90_L_10,&tc_w90_R_10,&tc_180_L_10,&tc_180_R_10
 							,&tc_i45_L_10,&tc_i45_R_10,&tc_o45_L_10,&tc_o45_R_10
 							,&tc_i135_L_10,&tc_i135_R_10,&tc_o135_L_10,&tc_o135_R_10
 							,&tc_v90_L_10,&tc_v90_R_10};
  turn2_t * tc12[14]={&tc_w90_L_12,&tc_w90_R_12,&tc_180_L_12,&tc_180_R_12
 							,&tc_i45_L_12,&tc_i45_R_12,&tc_o45_L_12,&tc_o45_R_12
 							,&tc_i135_L_12,&tc_i135_R_12,&tc_o135_L_12,&tc_o135_R_12
 							,&tc_v90_L_12,&tc_v90_R_12};
  turn2_t * tc14[14]={&tc_w90_L_14,&tc_w90_R_14,&tc_180_L_14,&tc_180_R_14
 							,&tc_i45_L_14,&tc_i45_R_14,&tc_o45_L_14,&tc_o45_R_14
 							,&tc_i135_L_14,&tc_i135_R_14,&tc_o135_L_14,&tc_o135_R_14
 							,&tc_v90_L_14,&tc_v90_R_14};
  turn2_t * tc16[14]={&tc_w90_L_16,&tc_w90_R_16,&tc_180_L_16,&tc_180_R_16
 							,&tc_i45_L_16,&tc_i45_R_16,&tc_o45_L_16,&tc_o45_R_16
 							,&tc_i135_L_16,&tc_i135_R_16,&tc_o135_L_16,&tc_o135_R_16
 							,&tc_v90_L_16,&tc_v90_R_16};
  turn2_t * tc18[14]={&tc_w90_L_18,&tc_w90_R_18,&tc_180_L_18,&tc_180_R_18
 							,&tc_i45_L_18,&tc_i45_R_18,&tc_o45_L_18,&tc_o45_R_18
 							,&tc_i135_L_18,&tc_i135_R_18,&tc_o135_L_18,&tc_o135_R_18
 							,&tc_v90_L_18,&tc_v90_R_18};
/****************************************
 ターン速度保存配列
 ****************************************/
 turn_t **t_para[5]={t10,t12,t14,t16,t18};
 turn2_t **tc_para[5]={tc10,tc12,tc14,tc16,tc18};
 /****************************************
距離toセンサー値 パラメータ
  ****************************************/
const sensor_t SENSOR_PARAMS[4]={{1.57046134,0.23008809,0},{51022,-17142,1583.6},{35077,-12813,1309.5},{1.71559912,0.25294874,0}};
