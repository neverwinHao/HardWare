#ifndef LCD_H
#define LCD_H

#include <reg52.h>
#include <string.h>

// LCD ��������
sbit RS = P2^4;    // RS ���ӵ� P24
sbit RW = P2^5;    // RW ���ӵ� P25
sbit E = P2^6;     // E ���ӵ� P26
sbit REST = P2^7;  // REST ���ӵ� P27

// LCD ��������
sbit DB0 = P0^7;   // DB0 ���ӵ� P07
sbit DB1 = P0^6;   // DB1 ���ӵ� P06
sbit DB2 = P0^5;   // DB2 ���ӵ� P05
sbit DB3 = P0^4;   // DB3 ���ӵ� P04
sbit DB4 = P0^3;   // DB4 ���ӵ� P03
sbit DB5 = P0^2;   // DB5 ���ӵ� P02
sbit DB6 = P0^1;   // DB6 ���ӵ� P01
sbit DB7 = P0^0;   // DB7 ���ӵ� P00


// ��������
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
