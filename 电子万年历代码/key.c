#include <reg52.h>
#include "lcd.h"

sbit Key1 = P2^0; // ����1���ӵ�����
sbit Key2 = P2^1; // ����2���ӵ�����
sbit Key3 = P2^2; // ����3���ӵ�����
sbit Key4 = P2^3; // ����4���ӵ�����

void Delay5Ms();

// ������⣬��֧�ֵ��㣬��֧�����㣬��㡣���ؼ�ֵ1-4
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
