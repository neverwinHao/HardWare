#ifndef KEY_H
#define KEY_H

#include <reg52.h>

// ���尴������
sbit Key1 = P2^0; // ����1���ӵ�����
sbit Key2 = P2^1; // ����2���ӵ�����
sbit Key3 = P2^2; // ����3���ӵ�����
sbit Key4 = P2^3; // ����4���ӵ�����

// ������⺯������֧�ֵ��㣬��֧�����㣬��㡣���ؼ�ֵ1-4
unsigned char key_scan();

#endif  