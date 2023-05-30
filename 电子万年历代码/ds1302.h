#ifndef __DS1302_H_
#define __DS1302_H_

#include <reg52.h>
#include <intrins.h>
#include "lcd.h"

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif

sbit SCLK = P1^2;
sbit DSIO = P1^3;
sbit RST = P1^4;


typedef struct time
{
    char sec;
    char min;
    char hour;
    char day;
    char mon;
    char week;
    char year;
    uchar date[11];
    uchar times[9];
} TIME;

typedef struct alarm
{
    char min;
    char hour;
} ALARM;

void Ds1302Write(uchar addr, uchar dat);
uchar Ds1302Read(uchar addr);
void Ds1302Init();
void read_time(uchar *timedata);
void turninto(TIME *timedata);
void set_time(uchar *timedata);

#endif