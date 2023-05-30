#ifndef DHT11_H
#define DHT11_H

#include <reg52.h>
#include <intrins.h>

#define uchar unsigned char
#define uint unsigned int

extern uchar rec_dat[16];  // 声明外部静态数组

void DHT11_delay_us(uchar n);
void DHT11_delay_ms(uint z);
void Delay30us();
void DHT11_start();
uchar DHT11_rec_byte();
uchar* DHT11_receive();

#endif // DHT11_H
