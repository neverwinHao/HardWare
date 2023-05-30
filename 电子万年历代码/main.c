#include <REG52.H>
#include "lcd.h"
#include "key.h"


void main()
{
    unsigned char keyNum;
    Lcd_Init();

    while (1)
    {
        keyNum = key_scan();

        if (keyNum != 0)
        {
            char keyChar = '0' + keyNum;  // 将键值转换为字符

            // 在LCD上显示按键数字
            LCD_ShowString(1, &keyChar);
        }
    }
}