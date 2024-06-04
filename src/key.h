#ifndef KEY_H
#define KEY_H

#include <reg52.h>

// 定义按键引脚
sbit Key1 = P2^0; // 按键1连接的引脚
sbit Key2 = P2^1; // 按键2连接的引脚
sbit Key3 = P2^2; // 按键3连接的引脚
sbit Key4 = P2^3; // 按键4连接的引脚

// 按键检测函数，仅支持单点，不支持连点，多点。返回键值1-4
unsigned char key_scan();

#endif  