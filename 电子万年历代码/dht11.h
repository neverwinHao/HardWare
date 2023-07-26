#ifndef _DTH11_H_
#define _DTH11_H_

#include<reg52.h>

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif
sbit Data = P1^5;


typedef struct dht
{	uchar wendu;
	uchar shidu;
}DHT;

void TemHum(uchar *sensordata);
#endif 