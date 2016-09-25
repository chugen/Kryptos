/*
 * my_typedef.h
 *
 *  Created on: 2016/09/17
 *      Author: Gen
 */

#ifndef MY_TYPEDEF_H_
#define MY_TYPEDEF_H_

//左右区別する　float型のパラメータ
typedef struct float_LR{
	float L;
	float R;
} floatLR_t;

//左右区別する　int型のパラメータ
typedef struct  {
	int L;
	int R;
} int_LR_t;

#endif /* MY_TYPEDEF_H_ */
