/*
 * my_typedef.h
 *
 *  Created on: 2016/09/17
 *      Author: Gen
 */

#ifndef MY_TYPEDEF_H_
#define MY_TYPEDEF_H_

#include <stdint.h>

//
typedef struct{
	float angle;
	float angular_accele;
	float max_angular_velo;
	float velocity;
	float front;
	float rear;
	int8_t dia;
	int8_t mode;
} turn_t;

#endif /* MY_TYPEDEF_H_ */
