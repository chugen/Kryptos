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
	uint16_t sensor_break;
	float dis_break;
	uint8_t diagonal;
} turn_t;

#endif /* MY_TYPEDEF_H_ */
