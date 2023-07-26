#ifndef LCD_H
#define LCD_H

#include <reg52.h>
#include <string.h>

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
void LCD_ShowNum(unsigned char line, unsigned char x, unsigned int num, unsigned char length);
void LCD_SetCursor(unsigned char line, unsigned char pos);
void LCD_ClearScreen();
void LCD_ShowChar(unsigned char line, unsigned char pos, unsigned char* str);
#endif  // LCD_H
