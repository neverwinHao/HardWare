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
void Wr_Command(unsigned char wrcommand, unsigned char busyc);
void Wr_Data(unsigned char wrdata);
void RDbf();
void Display_String(unsigned char line, unsigned char *string);

void main()
{
    Lcd_Init();
    while (1)
    {
        Display_String(1, "���Ʋ���LCD");
        Display_String(3, "����ʮ����");
        Display_String(4, "���߲���С");
        Delay_ms(1000); // �����ӳ�ʱ�䣬����1��
    }
}

// �ӳ�5����
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

// �ӳ�ָ���ĺ�����
void Delay_ms(unsigned int milliseconds)
{
    unsigned int i, j;
    for (i = 0; i < milliseconds; i++)
    {
        for (j = 0; j < 12000; j++)
        {
            // ��ѭ��������ʱ��
        }
    }
}

// LCD ��ʼ��
void Lcd_Init(void)
{
    Delay5Ms();
    REST = 1;
    REST = 0;
    REST = 1;
    Wr_Command(0x30, 0);
    Delay5Ms();
    Wr_Command(0x30, 0);
    Delay5Ms();
    Wr_Command(0x0C, 1);
    Delay5Ms();
    Wr_Command(0x01, 1);
    Delay5Ms();
    Delay5Ms();
    Wr_Command(0x06, 1);
    Delay5Ms();
}

// ����ָ� LCD
void Wr_Command(unsigned char wrcommand, unsigned char busyc)
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

// �� LCD д������
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

// ��ȡæ��־λ
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

// �� LCD ����ʾ�ַ���
void Display_String(unsigned char line, unsigned char *string)
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
    Wr_Command(addr, 1);
    for (i = 0; i < 16; i++)
    {
        if (*string)
            Wr_Data(*string++);
        else
            Wr_Data(' ');
    }
}
