#include "jq8900.h"

sbit sda = P1 ^ 0;

uchar key_scan();

// 延时子函数
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

// 延时子函数
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

// 延时子函数
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

// 延时子函数
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

// 以一线通信向jq8900发送指令
// 常见指令 0x11：重复播放
// 0x13：结束播放 0x0a：清除数字 0x0b：选曲确认
void SendData(uint addr) // 发 送 函 数
{
		int i = 0;
		EA = 0; //发 送 时 关 掉 中 断 ， 防 止 中 断 影 响 时 序 
		sda = 1;//开 始 拉 高
		Delay2ms();
		sda = 0; //开 始 引 导 码 
		Delay4ms(); //此 处 延 时 最 少 要 大 于 2 m s ， 此参数延 时 为 3 1 0 m s 
		for( i=0;i<8;i++) //总 共 8 位 数 据 
		{
				sda = 1;
				if(addr & 0x01) //3 : 1 表 示 数 据 位 1 , 每 个位 用 两 个 脉 冲 表 示 
				{
						Delay1500us();
						sda = 0 ;
						Delay500us();
				}
				else //1 ： 3 表 示 数 据 位 0 , 每个 位 用 两 个 脉 冲 表 示 
				{
						Delay500us();
						sda = 0;
						Delay1500us();
				}
				addr >>= 1;
		}
		sda = 1 ;
		EA = 1 ; //恢 复 中 断
}
