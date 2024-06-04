# 硬件代码

## 介绍
电子万年历硬件代码

# 实物图：

![overview](https://github.com/neverwinHao/HardWare/blob/main/img/overview.jpg)

# 项目要求：

## 基础功能
- [x] 显示当前年、月、日、时、分、秒
- [x] 通过按钮设置年，月，日，时，分，秒
- [x] 设置和显示AM和PM
- [x] 显示中国农历年、月、日和中国二十四节气
- [x] 设置闹钟时间和闹钟音乐
- [x] 检测和显示温度和湿度

## 高级功能
- [x] 选择闹钟音乐(使用TF卡存储音乐数据)
- [x] 手机通过蓝牙连接系统，APP即可完成以上基本设置
- [x] 通过手机APP获取在线天气预报，然后在LCD上传输和显示天气
- [x] 火灾探测

## 使用说明

1. 由C语言编写
1. 使用51单片机作为MCU
1. 时钟芯片DS1302
1. 温湿度传感器DHT11
1. 蓝牙模块 HC-08
1. 烟雾模块 MQ2

## 原理图

![yuanlitu](https://github.com/neverwinHao/HardWare/blob/main/img/yuanlitu.png)

## PCB

![pcb](https://github.com/neverwinHao/HardWare/blob/main/img/pcb.jpg)

