#include <reg52.h>
#include "lcd.h"

sbit Key1 = P2^0; // 按键1连接的引脚
sbit Key2 = P2^1; // 按键2连接的引脚
sbit Key3 = P2^2; // 按键3连接的引脚
sbit Key4 = P2^3; // 按键4连接的引脚

void Delay5Ms();

// 按键检测，仅支持单点，不支持连点，多点。返回键值1-4
unsigned char key_scan()
{
    unsigned char keyValue = 0;
    Key1 = 1;
    Key2 = 1;
    Key3 = 1;
    Key4 = 1;
    if (Key1 == 0 || Key2 == 0 || Key3 == 0 || Key4 == 0)
    {
        Delay5Ms();
        if (Key1 == 0)
        {
            keyValue = 1;
        }
        else if (Key2 == 0)
        {
            keyValue = 2;
        }
        else if (Key3 == 0)
        {
            keyValue = 3;
        }
        else if (Key4 == 0)
        {
            keyValue = 4;
        }
        else
        {
            keyValue = 0;
        }

        if (keyValue != 0)
        {
            while (Key1 == 0 || Key2 == 0 || Key3 == 0 || Key4 == 0);
            Delay5Ms();
        }
    }
    return keyValue;
}
