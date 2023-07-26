#ifndef _T_H_
#define _T_H_

#include "DS1302.h"
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif

void turnToLunar(TIME *t, uchar *lunar);
uchar getSolarIndex(TIME *t);

#endif

