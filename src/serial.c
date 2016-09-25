/*
 * serial.cpp
 *
 *  Created on: 2016/06/10
 *      Author: 元太
 */
#include "iodefine.h"
#include <stdio.h>
#include <stdarg.h>



void put1byte(char c){
	while ( SCI1.SSR.BIT.TDRE == 0 ) ;
	//SCI1.SSR.BIT.TDRE = 0;
	SCI1.TDR = c;
}

void putnbyte(char *buf,int len){
	int c;
    for(c = 0; c < len; c++){
		put1byte(buf[c]);
	}
}

int myprintf(const char *fmt, ...){
	static char buffer[100];
	int len;

	va_list ap;
	va_start(ap, fmt);

	len = vsprintf(buffer, fmt, ap);
	putnbyte(buffer, len);
	va_end(ap);
	return len;
}




