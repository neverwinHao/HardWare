#include "ds1302.h"

uchar code READ_RTC_ADDR[7] = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8b, 0x8d};
uchar code WRITE_RTC_ADDR[7] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c};

uchar initial_time[7] = {0x00, 0x09, 0x10, 0x20, 0x05, 0x04, 0x22};

void Ds1302Write(uchar addr, uchar dat)
{
    uchar n;
    RST = 0;
    _nop_();
    SCLK = 0;
    _nop_();
    RST = 1;
    _nop_();

    for (n = 0; n < 8; n++)
    {
        DSIO = addr & 0x01;
        addr >>= 1;
        SCLK = 1;
        _nop_();
        SCLK = 0;
        _nop_();
    }

    for (n = 0; n < 8; n++)
    {
        DSIO = dat & 0x01;
        dat >>= 1;
        SCLK = 1;
        _nop_();
        SCLK = 0;
        _nop_();
    }

    RST = 0;
    _nop_();
}

uchar Ds1302Read(uchar addr)
{
    uchar n, dat, dat1;
    RST = 0;
    _nop_();
    SCLK = 0;
    _nop_();
    RST = 1;
    _nop_();

    for (n = 0; n < 8; n++)
    {
        DSIO = addr & 0x01;
        addr >>= 1;
        SCLK = 1;
        _nop_();
        SCLK = 0;
        _nop_();
    }

    _nop_();

    for (n = 0; n < 8; n++)
    {
        dat1 = DSIO;
        dat = (dat >> 1) | (dat1 << 7);
        SCLK = 1;
        _nop_();
        SCLK = 0;
        _nop_();
    }

    RST = 0;
    _nop_();
    SCLK = 1;
    _nop_();
    DSIO = 0;
    _nop_();
    DSIO = 1;
    _nop_();

    return dat;
}

void Ds1302Init()
{
    uchar n;
    Ds1302Write(0x8E, 0x00);

    for (n = 0; n < 7; n++)
    {
        Ds1302Write(WRITE_RTC_ADDR[n], initial_time[n]);
    }

    Ds1302Write(0x8E, 0x80);
}

void read_time(uchar *timedata)
{
    uchar i, tmp;

    for (i = 0; i < 7; i++)
    {
        timedata[i] = Ds1302Read(READ_RTC_ADDR[i]);
    }

    for (i = 0; i < 7; i++)
    {
        tmp = timedata[i];
        timedata[i] = (tmp / 16 % 10) * 10;
        timedata[i] += (tmp % 16);
    }
}

void turninto(TIME *timedata)
{
    timedata->date[0] = '2';
    timedata->date[1] = '0';
    timedata->date[2] = timedata->year / 10 + '0';
    timedata->date[3] = timedata->year % 10 + '0';
    timedata->date[4] = '-';
    timedata->date[5] = timedata->mon / 10 + '0';
    timedata->date[6] = timedata->mon % 10 + '0';
    timedata->date[7] = '-';
    timedata->date[8] = timedata->day / 10 + '0';
    timedata->date[9] = timedata->day % 10 + '0';
    timedata->date[10] = '\0';

    timedata->times[0] = timedata->hour / 10 + '0';
    timedata->times[1] = timedata->hour % 10 + '0';
    timedata->times[2] = ':';
    timedata->times[3] = timedata->min / 10 + '0';
    timedata->times[4] = timedata->min % 10 + '0';
    timedata->times[5] = ':';
    timedata->times[6] = timedata->sec / 10 + '0';
    timedata->times[7] = timedata->sec % 10 + '0';
    timedata->times[8] = '\0';
}

void set_time(uchar *timedata)
{
    uchar i, tmp, tmps[7];

    for (i = 0; i < 7; i++)
    {
        tmp = timedata[i];
        tmps[i] = (tmp / 10 << 4) + (tmp % 10);
    }

    Ds1302Write(0x8E, 0x00);

    for (i = 0; i < 7; i++)
    {
        Ds1302Write(WRITE_RTC_ADDR[i], tmps[i]);
    }

    Ds1302Write(0x8E, 0x80);
}