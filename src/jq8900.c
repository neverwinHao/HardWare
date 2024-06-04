#include "jq8900.h"

sbit sda = P1 ^ 0;

uchar key_scan();

// ��ʱ�Ӻ���
void Delay1500us()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	i = 17;
	j = 31;
	do
	{
		while (--j);
	} while (--i);
}

// ��ʱ�Ӻ���
void Delay500us()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 6;
	j = 93;
	do
	{
		while (--j);
	} while (--i);
}

// ��ʱ�Ӻ���
void Delay2ms()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 22;
	j = 128;
	do
	{
		while (--j);
	} while (--i);
}

// ��ʱ�Ӻ���
void Delay4ms()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	i = 44;
	j = 4;
	do
	{
		while (--j);
	} while (--i);
}

// ��һ��ͨ����jq8900����ָ��
// ����ָ�� 0x11���ظ�����
// 0x13���������� 0x0a��������� 0x0b��ѡ��ȷ��
void SendData(uint addr) // �� �� �� ��
{
		int i = 0;
		EA = 0; //�� �� ʱ �� �� �� �� �� �� ֹ �� �� Ӱ �� ʱ �� 
		sda = 1;//�� ʼ �� ��
		Delay2ms();
		sda = 0; //�� ʼ �� �� �� 
		Delay4ms(); //�� �� �� ʱ �� �� Ҫ �� �� 2 m s �� �˲����� ʱ Ϊ 3 1 0 m s 
		for( i=0;i<8;i++) //�� �� 8 λ �� �� 
		{
				sda = 1;
				if(addr & 0x01) //3 : 1 �� ʾ �� �� λ 1 , ÿ ��λ �� �� �� �� �� �� ʾ 
				{
						Delay1500us();
						sda = 0 ;
						Delay500us();
				}
				else //1 �� 3 �� ʾ �� �� λ 0 , ÿ�� λ �� �� �� �� �� �� ʾ 
				{
						Delay500us();
						sda = 0;
						Delay1500us();
				}
				addr >>= 1;
		}
		sda = 1 ;
		EA = 1 ; //�� �� �� ��
}
