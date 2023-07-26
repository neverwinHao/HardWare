#include <reg52.h>
#include <string.h>
#include "lunarword.h"

// LCD 控制引脚
sbit RS = P2^4;    // RS 连接到 P24
sbit RW = P2^5;    // RW 连接到 P25
sbit E = P2^6;     // E 连接到 P26
sbit REST = P2^7;  // REST 连接到 P27

// LCD 数据引脚
sbit DB0 = P0^7;   // DB0 连接到 P07
sbit DB1 = P0^6;   // DB1 连接到 P06
sbit DB2 = P0^5;   // DB2 连接到 P05
sbit DB3 = P0^4;   // DB3 连接到 P04
sbit DB4 = P0^3;   // DB4 连接到 P03
sbit DB5 = P0^2;   // DB5 连接到 P02
sbit DB6 = P0^1;   // DB6 连接到 P01
sbit DB7 = P0^0;   // DB7 连接到 P00

// 函数声明
void Delay5Ms();
void Delay_ms(unsigned int milliseconds);
void Lcd_Init();
void LCD_WriteCommand(unsigned char wrcommand, unsigned char busyc);
void Wr_Data(unsigned char wrdata);
void RDbf();
void LCD_ShowString(unsigned char line, unsigned char *string);
void LCD_ShowChar(unsigned char line, unsigned char pos, unsigned char* str);
void LCD_ShowNum(unsigned char line, unsigned char x, unsigned int num, unsigned char length);
void LCD_SetCursor(unsigned char line, unsigned char pos);

// 延迟5毫秒
void Delay5Ms()
{
    unsigned char i, j;
    i = 54;
    j = 199;
    do
    {
        while (--j);
    } while (--i);
}

// 延迟指定的毫秒数
void Delay_ms(unsigned int milliseconds)
{
    unsigned int i, j;
    for (i = 0; i < milliseconds; i++)
    {
        for (j = 0; j < 12000; j++)
        {
            // 空循环以消耗时间
        }
    }
}

// LCD 初始化
void Lcd_Init(void)
{
    Delay5Ms();
    REST = 1;
    REST = 0;
    REST = 1;
    LCD_WriteCommand(0x30, 0);
    Delay5Ms();
    LCD_WriteCommand(0x30, 0);
    Delay5Ms();
    LCD_WriteCommand(0x0C, 1);
    Delay5Ms();
    LCD_WriteCommand(0x01, 1);
    Delay5Ms();
    Delay5Ms();
    LCD_WriteCommand(0x06, 1);
    Delay5Ms();
}

// 发送指令到 LCD LCD_WriteCommand
void LCD_WriteCommand(unsigned char wrcommand, unsigned char busyc)
{
    if (busyc)
        RDbf();
    RS = 0;
    RW = 0;
    E = 1;
    DB7 = wrcommand & 0x80;
    DB6 = wrcommand & 0x40;
    DB5 = wrcommand & 0x20;
    DB4 = wrcommand & 0x10;
    DB3 = wrcommand & 0x08;
    DB2 = wrcommand & 0x04;
    DB1 = wrcommand & 0x02;
    DB0 = wrcommand & 0x01;
    E = 0;
}

// 向 LCD 写入数据
void Wr_Data(unsigned char wrdata)
{
    RDbf();
    RS = 1;
    RW = 0;
    E = 1;
    DB7 = wrdata & 0x80;
    DB6 = wrdata & 0x40;
    DB5 = wrdata & 0x20;
    DB4 = wrdata & 0x10;
    DB3 = wrdata & 0x08;
    DB2 = wrdata & 0x04;
    DB1 = wrdata & 0x02;
    DB0 = wrdata & 0x01;
    E = 0;
}

// 读取忙标志位
void RDbf(void)
{
    while (1)
    {
        RS = 0;
        RW = 1;
        E = 0;
        E = 1;
        if ((P0 & 0x01) == 0)
            break;
    }
}

// 在 LCD 上显示字符串
void LCD_ShowString(unsigned char line, unsigned char *string)
{
    unsigned char addr, i;
    switch (line)
    {
        case 1:
            addr = 0x80;
            break;
        case 2:
            addr = 0x90;
            break;
        case 3:
            addr = 0x88;
            break;
        case 4:
            addr = 0x98;
            break;
    }
    LCD_WriteCommand(addr, 1);
    for (i = 0; i < 16; i++)
    {
        if (*string)
            Wr_Data(*string++);
        else
            Wr_Data(' ');
    }
}

// 在 LCD 上显示数字
void LCD_ShowNum(unsigned char line, unsigned char x, unsigned int num, unsigned char length)
{
    unsigned char str[6] = "     ";
    unsigned char i = 0;
    unsigned int temp = num;  // 保存原始数字

    // 从高位开始存储数字
    while (temp > 0)
    {
        str[length - 1 - i] = temp % 10 + '0';
        temp /= 10;
        i++;
    }

    // 在位数小于输入位数时，在数字前补零
    while (i < length)
    {
        str[length - 1 - i] = '0';
        i++;
    }

    str[length] = '\0';

    LCD_SetCursor(line, x);  // 设置光标位置

    for (i = 0; i < length; i++)
    {
        Wr_Data(str[i]);
    }
}




// LCD 设置光标位置
void LCD_SetCursor(unsigned char line, unsigned char pos)
{
    unsigned char addr;
    switch (line)
    {
        case 1:
            addr = 0x80 + pos - 1;
            break;
        case 2:
            addr = 0x90 + pos - 1;
            break;
        case 3:
            addr = 0x88 + pos - 1;
            break;
        case 4:
            addr = 0x98 + pos - 1;
            break;
        default:
            return; // 非法行数，直接返回
    }
    LCD_WriteCommand(addr, 1);
}


void LCD_ClearScreen()
{
	LCD_ShowString(1,"                 ");
	LCD_ShowString(2,"                 ");
	LCD_ShowString(3,"                 ");
	LCD_ShowString(4,"                 ");
}

// 在 LCD 上显示字符
void LCD_ShowChar(unsigned char line, unsigned char pos, unsigned char* str)
{
    unsigned char addr;
    unsigned char i = 0;
    switch (line)
    {
        case 1:
            addr = 0x80 + pos - 1;
            break;
        case 2:
            addr = 0x90 + pos - 1;
            break;
        case 3:
            addr = 0x88 + pos - 1;
            break;
        case 4:
            addr = 0x98 + pos - 1;
            break;
        default:
            return; // 非法行数，直接返回
    }
    LCD_WriteCommand(addr, 1);
    
    // 先写入指定位置的字符
    while (*str && i < 16 - pos)
    {
        Wr_Data(*str++);
        i++;
    }
	Delay_ms(2);
}


