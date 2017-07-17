/*
 * my_typedef.h
 *
 *  Created on: 2016/09/17b
 *      Author: Gen
 */

#ifndef MY_TYPEDEF_H_
#define MY_TYPEDEF_H_

#include <stdint.h>

//
typedef struct {
	float angle;
	float alpha;
	float omega;
	float velocity;
	float front;
	float rear;
	int8_t dia;
	int8_t mode;
} turn_t;

typedef struct {
	float angle;
	float omega;
	float velocity;
	float front;
	float rear;
	int8_t dia;
} turn2_t;

typedef struct {
	uint16_t row;
	uint16_t column;
	uint16_t row_known;
	uint16_t column_known;
} wall_t;

typedef struct{
	float row[15];
	float column[15];
} step_t;

#endif /* MY_TYPEDEF_H_ */
