# 硬件代码

#### 介绍
电子万年历硬件代码
#### 题目要求

•基本功能

1. 当前的年、月、日、时、分、秒显示
2. 设置年、月、日、时、分、秒
3. AM、PM设置与显示
4. 农历年月日、二十四节气显示
5. 闹钟时间设置，闹钟时间到进行声光报警提示
6. 温湿度检测与显示

•高级功能

1. 闹钟音乐选择（采用TF卡或录音芯片存储音乐数据）
2. 手机通过蓝牙或WiFi网络连接该万年历，通过手机APP可以完成基本功能中的所有设置功能
3. 通过编写Android手机程序获得网上天气预报数据，并将该数据通过蓝牙或WiFi网络传递给音乐万年历，万年历可以完成天气信息显示
4. 火灾检测与报警，报警形势可以是短信。

#### 使用说明

1. 由C语言编写
1. 使用51单片机作为MCU
1. 时钟芯片DS1302
1. 温湿度传感器DHT11
1. 蓝牙模块 HC-08
1. 烟雾模块 MQ2

